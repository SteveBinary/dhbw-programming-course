<?php

require_once "login.php";
require_once "register.php";

if (isset($_REQUEST["action"]) && $_REQUEST["action"] == "Register") {
    handleRegister();
} elseif (isset($_REQUEST["action"]) && $_REQUEST["action"] == "Login") {
    handleLogin();
}

?>

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

<h2>Login</h2>

<style>
    table, tr, td {
        border: none;
        background-color: var(--bg);
    }
</style>

<form action="" method="post">
    <table>
        <tr>
            <td><label for="name">username:</label></td>
            <td><input type="text" id="name" name="name" required></td>
        </tr>

        <tr>
            <td><label for="password">password:</label>
            <td><input type="password" id="password" name="password" required>
        </tr>

        <tr>
            <td><input type="submit" name="action" value="Login"></td>
            <td><input type="submit" name="action" value="Register"></td>
        </tr>
    </table>
</form>

<?php

require_once "constants.php";

if (!isset($_COOKIE[LOGIN_STATUS])) return;

if ($_COOKIE[LOGIN_STATUS] == "invalid") {
    echo "<div>Invalid username or password!</div>";
    setcookie(LOGIN_STATUS, "", time() - 3600);
} elseif ($_COOKIE[LOGIN_STATUS] == "exists") {
    echo "<div>Username already taken!</div>";
    setcookie(LOGIN_STATUS, "", time() - 3600);
} elseif ($_COOKIE[LOGIN_STATUS] == "internal_error") {
    echo "<div>We encountered an internal error. Please try again!</div>";
    setcookie(LOGIN_STATUS, "", time() - 3600);
} elseif ($_COOKIE[LOGIN_STATUS] == "invalid_username") {
    echo "<div>The username must have 1 to 20 characters.</div><div>It must only contain lower and upper case letters, numbers and an underscore!</div>";
    setcookie(LOGIN_STATUS, "", time() - 3600);
}

?>

</body>
</html>
