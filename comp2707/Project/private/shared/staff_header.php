<!--
    Staff Side
    Developer: Dennis Dao
    Date: July 18, 2022
    v1.0
    Note: early start to experiment with page aesthetics and structure before building
-->

<!DOCTYPE html>
<html lang="en">
    <head>
        <title>Tabletop Games - <?php echo h($page_title); ?></title>
        <meta charset="utf-8">
        <link rel="stylesheet" media="all" href="<?php echo url_for('/stylesheets/staff.css'); ?>"/>
        <link rel="icon" type="image/x-icon" href="<?php echo url_for('/images/favicon.ico');?>">
    </head>

    <body>
        <header>
            <h1>Tabletop Games Staff Area</h1>
        </header>

        <!-- Header menu of staff options -->
        <nav>
            <?php if(isset($_SESSION['admin_id'])){echo "Hello, " . $_SESSION['usernameA'] . "!";}else{echo '';}?><br />
            <?php if(isset($_SESSION['admin_id'])){?>

            <ul>
                <li><a href="<?php echo url_for('/staff/index.php'); ?>">Menu</a></li>
                <li><a href="<?php echo url_for('/staff/staff_logout.php'); ?>">Logout</a></li>
            </ul>
            <?php } ?>
            
        </nav>

        <?php echo display_session_message(); ?>

