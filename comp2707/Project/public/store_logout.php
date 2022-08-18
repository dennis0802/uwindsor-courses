<?php
    // Handles log outs from the store page
    require_once('../private/initialize.php');

    // Status message
    $_SESSION['status'] = "You have logged out.";

    // Depending on who's logged in, log them out and send them to the homepage
    if(is_admin_logged_in()){
        log_out_admin();
        redirect_to(url_for('/index.php'));
    }
    else{
        log_out_user();
        redirect_to(url_for('/index.php'));        
    }
?>