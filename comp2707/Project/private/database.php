<?php
    /*
    * Developer: Dennis Dao
    * July 18, 2022
    *  v1.0
    * /

    // Various database functions

    /* Referenced from Kevin Skoglund's PHP with MySQL Essential Training 2 - Build a CMS Course*/
    /* The course was a continuation of A3's course - that was Part 1.
    /* https://www.linkedin.com/learning/php-with-mysql-essential-training-2-build-a-cms*/

    require_once('db_credentials.php');

    // Connect to the database
    function db_connect(){
        $connection = mysqli_connect(DB_SERVER, DB_USER, DB_PASS, DB_NAME);
        confirm_db_connect();
        return $connection;
    }

    // Disconnect from the database
    function db_disconnect($connection){
        if(isset($connection)){
            mysqli_close($connection);
        }
    }

    // Escape characters in queries to prevent a SQL injection
    function db_escape($connection, $string){
        if(isset($connection)){
            return mysqli_real_escape_string($connection, $string);
        }
    }

    // Confirm connection was successful
    function confirm_db_connect(){
        if(mysqli_connect_errno()){
            $msg = "Database connection failed: ";
            $msg .= mysqli_connect_error();
            $msg .= " (" . mysqli_connect_errno() . ")";
            exit($msg);
        }
    }

    // Confirm query was successful
    function confirm_result_set($result_set){
        if(!$result_set){
            exit("Database query failed.");
        }
    }
?>