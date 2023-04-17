<?php


function connectToDB(): PDO|null {
    // Make sure that those environment variables are set!
    $dbURL = getenv("DB_URL", true);
    $dbUser = getenv("DB_USER", true);
    $dbPassword = getenv("DB_PASSWORD", true);

    try {
        return new PDO($dbURL, $dbUser, $dbPassword);
    } catch (PDOException) {
        return null;
    }
}
