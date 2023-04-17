<?php


require_once "db.php";
require_once "constants.php";
require_once "utils.php";

function handleRegister(): void {
    $db = connectToDB();

    if ($db == null) {
        setcookie(LOGIN_STATUS, "internal_error");
        redirect("/");
    }

    if (!isset($_POST["name"]) || !isset($_POST["password"])) {
        setcookie(LOGIN_STATUS, "invalid");
        redirect("/");
    }

    $name = $_POST["name"];

    // validating user input
    //   -> prevents SQL Injection
    //   -> AND injection of JavaScript (XSS)
    // if (!preg_match(USER_NAME_REGEX, $name)) {
    //     setcookie(LOGIN_STATUS, "invalid_username");
    //     redirect("/");
    // }

    $query = "SELECT count(name) as count FROM user WHERE name=:name";

    // prepared statement to prevent SQL Injection
    $statement = $db->prepare($query, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
    $statement->execute(array("name" => $name));

    $result = $statement->fetch();

    if ($result["count"] != 0) {
        setcookie(LOGIN_STATUS, "exists");
        redirect("/");
    }

    $password = $_POST["password"];
    $pw_hash = hash(PW_HASH_ALGORITHM, $password);

    $query = "INSERT INTO user (name, pw_hash) VALUES (:name, :pw_hash);";

    // prepared statement to prevent SQL Injection
    $statement = $db->prepare($query, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
    $statement->execute(array("name" => $name, "pw_hash" => $pw_hash));

    session_start();
    $_SESSION[USER_ID] = $db->lastInsertId();
    redirect("/tools.php");
}
