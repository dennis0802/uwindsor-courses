<?php 

// Performs all actions necessary to log in an admin
function log_in_admin($admin) {
// Renerating the ID protects the admin from session fixation.
    session_regenerate_id();
    $_SESSION['admin_id'] = $admin['id'];
    $_SESSION['last_login'] = time();
    $_SESSION['usernameA'] = $admin['staffID'];
    return true;
}

// Performs all actions necessary to log in a user
function log_in_user($user){
    session_regenerate_id();
    $_SESSION['user_id'] = $user['id'];
    $_SESSION['last_login'] = time();
    $_SESSION['usernameU'] = $user['userID'];
    $_SESSION['cart'] = [];
    return true;
}

// is_logged_in() contains all the logic for determining if a
// request should be considered a "logged in" request or not.
// It is the core of require_login() but it can also be called
// on its own in other contexts (e.g. display one link if an admin
// is logged in and display another link if they are not)
function is_admin_logged_in() {
// Having a admin_id in the session serves a dual-purpose:
// - Its presence indicates the admin is logged in.
// - Its value tells which admin for looking up their record.
return isset($_SESSION['admin_id']);
}

// is_logged_in() contains all the logic for determining if a
// request should be considered a "logged in" request or not.
// It is the core of require_login() but it can also be called
// on its own in other contexts (e.g. display one link if an admin
// is logged in and display another link if they are not)
function is_user_logged_in() {
// Having a admin_id in the session serves a dual-purpose:
// - Its presence indicates the admin is logged in.
// - Its value tells which admin for looking up their record.
return isset($_SESSION['user_id']);
}

// Call require_login() at the top of any page which needs to
// require a valid login before granting acccess to the page.
function require_admin_login() {
    if(!is_admin_logged_in()) {
        redirect_to(url_for('/staff/staff_login.php'));
    } else {
        // Do nothing, let the rest of the page proceed
    }
}

// Call require_login() at the top of any page which needs to
// require a valid login before granting acccess to the page.
function require_user_login() {
    if(!is_user_logged_in()) {
        redirect_to(url_for('/index.php'));
    } else {
        // Do nothing, let the rest of the page proceed
    }
}

// Performs all actions necessary to log out an admin
function log_out_admin(){
    unset($_SESSION['admin_id']);
    unset($_SESSION['last_login']);
    unset($_SESSION['usernameA']);
    return true;
}

// Performs all actions necessary to log out a user
function log_out_user(){
    unset($_SESSION['user_id']);
    unset($_SESSION['last_login']);
    unset($_SESSION['usernameU']);
    unset($_SESSION['cart']);
    return true;    
}

?>