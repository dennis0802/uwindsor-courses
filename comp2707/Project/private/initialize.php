<?php
    /*
    * Developer: Dennis Dao
    * July 18, 2022
    *  v1.0
    * /

    // Start-up for every page

    /* Referenced from Kevin Skoglund's PHP with MySQL Essential Training 2 - Build a CMS Course*/
    /* The course was a continuation of A3's course - that was Part 1.
    /* https://www.linkedin.com/learning/php-with-mysql-essential-training-2-build-a-cms*/

    ob_start(); //output buffering
    session_start(); // turn on sessions

    // Assign file paths to PHP constants
    // __FILE__ returns the current path to this file
    // dirname() returns the path to the parent directory
    define("PRIVATE_PATH", dirname(__FILE__));
    define("PROJECT_PATH", dirname(PRIVATE_PATH));
    define("PUBLIC_PATH", PROJECT_PATH . '/public');
    define("SHARED_PATH", PRIVATE_PATH . '/shared');

    // Assign the root URL to a PHP constant
    // * Do not need to include the domain
    // * Use same document root as webserver
    // * Can set a hardcoded value:
    // define("WWW_ROOT", '/~kevinskoglund/globe_bank/public');
    // define("WWW_ROOT", '');
    // * Can dynamically find everything in URL up to "/public"
    $public_end = strpos($_SERVER['SCRIPT_NAME'], '/public') + 7;
    $doc_root = substr($_SERVER['SCRIPT_NAME'], 0, $public_end);
    define("WWW_ROOT", $doc_root);

    require_once('functions.php');
    require_once('auth_functions.php');
    require_once('database.php');
    require_once('query_functions.php');
    require_once('validation_functions.php');

    // Set timezone for all date related functions - omitting this makes times in UTC
    date_default_timezone_set('America/Toronto');

    $db = db_connect();
    $errors = [];
?>