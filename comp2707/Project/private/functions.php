<?php 
    /*
    * Developer: Dennis Dao
    * July 18, 2022
    *  v1.0
    * /

    // Various functions for the website

    /* Referenced from Kevin Skoglund's PHP with MySQL Essential Training 2 - Build a CMS Course*/
    /* The course was a continuation of A3's course - that was Part 1.
    /* https://www.linkedin.com/learning/php-with-mysql-essential-training-2-build-a-cms*/

    // Shortcut for urls, up to the public folder
    function url_for($script_path){
        // Add leading '/' if absent
        if($script_path[0] != '/'){
            $script_path = "/" . $script_path;
        }
        return WWW_ROOT . $script_path;
    }

    // Shortcut for safely using html in a static context
    function h($string=""){
        return htmlspecialchars($string);
    }

    // Shortcut for safely using strings in the url
    function u($string=""){
        return urlencode($string);
    }

    // Redirect to another link
    function redirect_to($location){
        header("Location: " . $location);
        exit;
    }

    // Check if the server has done a POST request
    function is_post_request(){
        return $_SERVER['REQUEST_METHOD'] == 'POST';
    }

    // Check if the server has done a GET request
    function is_get_request(){
        return $_SERVER['REQUEST_METHOD'] == 'GET';
    }

    // Get and clear current status message
    function get_and_clear_session_message(){
        if(isset($_SESSION['status']) && $_SESSION['status'] != ''){
            $msg = $_SESSION['status'];
            unset($_SESSION['status']);
            return $msg;
        }
    }

    // Display the retrieved session message
    function display_session_message(){
        $msg = get_and_clear_session_message();
        if(!is_blank($msg)){
            return '<div id="message">' . h($msg) . '</div>';
        }
    }

    // Display errors (if any)
    function display_errors($errors=array()){
        $output = '';
        if(!empty($errors)){
            $output .= "<div class=\"errors\">";
            $output .= "Please fix the following errors:";
            $output .= "<ul>";
            foreach($errors as $error){
                $output .= "<li>" . h($error) . "</li>";
            }
            
            $output .= "</ul>";
            $output .= "</div>";
        }
        return $output;
    }
?>