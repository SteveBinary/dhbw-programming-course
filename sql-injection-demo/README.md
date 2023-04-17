# sqli-demo

<!-- TOC -->

- [Prerequisites](#prerequisites)
- [Getting started](#getting-started)
- [Doing some actual SQL Injection](#doing-some-actual-sql-injection)
    - [1. Login without credentials](#1-login-without-credentials)
    - [2. Explore the database](#2-explore-the-database)
    - [3. Causing substantial damage](#3-causing-substantial-damage)
- [Preventing SQL Injection](#preventing-sql-injection)
- [Bonus: Exploit another vulnerability](#bonus-exploit-another-vulnerability)

<!-- TOC -->

## Prerequisites

- PHP 8.1
- MySQL 8.0
- Docker is recommended for setting up the database

## Getting started

1. Set up an MySQL instance, e.g. using Docker:
   ```shell
     docker run --name MySQL-SQLI -p 3306:3306 -e MYSQL_ROOT_PASSWORD=super-secret-password -v mysql_sqli:/var/lib/mysql -d mysql:8.0
   ```
2. Initialize the database:
    - Import/Restore from the self-contained database dump file [db_dump.sql](db_dump.sql).
    - Note: a database called `sqli_demo_app` is created
      which contains multiple tables already filled with initial data.
3. Configure the application to use the just created database. \
   Set those environment variables (you might want to change your password):
    - DB_URL=mysql:host=localhost:3306;dbname=sqli_demo_app
    - DB_USER=root
    - DB_PASSWORD=super-secret-password
4. Run the PHP application with a server of your choice.
5. The demo should be available at [http://localhost](http://localhost)
6. A user `admin` with password `admin` already exists. Use this for testing your setup.

## Doing some actual SQL Injection

### 1. Login without credentials

If you take a closer look in [login.php](login.php) on line 38-40, you can see that the raw user input is used in the SQL query.
That's the SQL Injection vulnerability.
Now anyone can inject arbitrary SQL syntax into the query which gets executed.

On many systems the admin is the first one to create an account and thus has the first user id.
You can exploit the vulnerability to login as the admin by using a Boolean-based attack.
That is essentially using an always-true statement.

With the query from the code ([login.php](login.php) line 38) (or by guessing)

```sql
SELECT id FROM user WHERE name = '$name' AND pw_hash = '$pw_hash';
```

we can find a value for `$name` to construct an always-true statement:

```text
' OR 1=1; --
```

Input this for the username and the password doesn't matter anymore.
You will be logged in as the admin because it is the first account.

The `'` closes the name string after which we use the always-true statement `OR 1=1`.
The `--` are just SQL comments to end the query in case there is something after that.
Here is the resulting query that is executed:

```sql
SELECT id FROM user WHERE name = '' OR 1 = 1; --' AND pw_hash='$pw_hash';
```

As you can see, the name will never be `''` but the `OR 1=1` makes the predicate true nonetheless, thus you will be logged in.

### 2. Explore the database

Now we are logged in and know a technique to abuse the SQL queries.
After login you are presented with a greeting and a text field to search for some hacking tools.

Now, we sneak a UNION statement into the search query (Union-based attack).
We can abuse the fact, that MySQL uses a pseudo database called `INFORMATION_SCHEMA`, to retrieve valuable information about the system.
This database stores information like names of all databases, tables per database and columns per table.

With the original query ([tool.php](tools.php) line 72) (or by guessing)

```sql
SELECT name FROM tool WHERE name LIKE '%$search_term%' ORDER BY name;
```

we can construct a search term for executing a Union statement to:

- get the names of all databases:
  ```text
  0x41414141' UNION SELECT TABLE_SCHEMA FROM INFORMATION_SCHEMA.TABLES GROUP BY TABLE_SCHEMA; --
  ```
- then get the tables of specific db:
  ```text
  0x41414141' UNION SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE='BASE TABLE' AND INFORMATION_SCHEMA.TABLES.TABLE_SCHEMA='sqli_demo_app'; --
  ```
- then get the column names of a table:
  ```text
  0x41414141' UNION SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE `TABLE_SCHEMA`='sqli_demo_app' AND `TABLE_NAME`='secret'; --
  ```
- and finally get the contents of specific column → The flag to find:
  ```text
  0x41414141' UNION SELECT message FROM secret; --
  ```

The `0x41414141` in front is just to don't get the hacking tools, but only the information about the system we want to extract.

### 3. Causing substantial damage

So we explored the database and stole all the data we could find, but how can we teach the victim a lesson it won't forget?

**Deleting the production database!**

By exploiting the ability of MySQL to execute batched statements (basically multiple separate statements in a single query),
we can cause substantial damage, like deleting the whole database.

The search query just has to be ended and an additional statement can be injected, e.g. dropping a database.
The following input for the search term will archive this:

```text
'; DROP DATABASE sqli_demo_app; --
``` 

## Preventing SQL Injection

| Method                                 | Comment                                                                                                  |
|----------------------------------------|----------------------------------------------------------------------------------------------------------|
| input validation / sanitization        | Certain special characters don't get interpreted as part of the query (e.g. `'` or `=`)                  |
| least privileges                       | The hacker can only do as much as the DB user can do. Especially don't use the root user!                |
| disable batched statements in the DBMS | Prevents e.g. the `DROP DATABASE` statement to be executed after injection.                              |
| prepared statements                    | Always recommended when working with user input → basically as powerful as the 3 methods above combined! |

## Bonus: Exploit another vulnerability

Did you notice that the username is displayed after logging in?
That is a hint to another kind of vulnerability: Cross-Site Scripting (XSS).

There are two XSS variants combined in this case:

- Reflected XSS: \
  The user input is reflected back into the application.
  In this case the username is immediately displayed after logging in.
- Stored XSS: \
  The user input is not only reflected back, but also stored somewhere.
  In this case the username is stored in a database.

The username is directly inserted into the DOM as is and no one validates it in some sense.
So, if it is inserted into the DOM, you might be tempted to write some JavaScript.
In the login form write this script-tag as the username and choose a password:

```html
<script> alert("hello XSS"); </script>
```

Now, register this new user...
And it works!!!
As you can see an alert popup occurred, which means that the JavaScript in the script-tag was actually executed.
And because you registered the user, the malicious string is also stored in the database.

You injected JavaScript into the website and made it persistent, thus you exploited the XSS vulnerability.

If you take a look in [register.php](register.php) (line 35), you can see the prepared statement for executing SQL queries.
So, SQL Injection is prevented... but the XSS vulnerability still exists!
**That's an important lesson to learn!**

**How can you prevent this kind of JavaScript Injection?**

The easiest way is to validate / sanitize the user input.
(See [login.php](login.php) and [register.php](register.php) on line 24-30)
