<?php
    require_once('../../private/initialize.php');

    // Status message
    $_SESSION['status'] = "You have logged out.";

    log_out_admin();
    redirect_to(url_for('/staff/staff_login.php'));
?>