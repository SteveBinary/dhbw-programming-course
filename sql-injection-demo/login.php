<?php

require_once "db.php";
require_once "constants.php";
require_once "utils.php";

function handleLogin(): void {
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

    $password = $_POST["password"];

    $pw_hash = hash(PW_HASH_ALGORITHM, $password);

    // DANGER!!!
    // attack:   ' OR 1=1; --
    $query = "SELECT id FROM user WHERE name='$name' AND pw_hash='$pw_hash';";

    $user = $db->query($query)->fetch();


    // // prepared statement to prevent SQL Injection
    // $query = "SELECT id FROM user WHERE name=:name AND pw_hash=:pw_hash;";
    // $statement = $db->prepare($query, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
    // $statement->execute(array("name" => $name, "pw_hash" => $pw_hash));


    if ($user === false) {
        setcookie(LOGIN_STATUS, "invalid");
        redirect("/");
    }

    session_start();
    $_SESSION[USER_ID] = $user["id"];
    redirect("/tools.php");
}
