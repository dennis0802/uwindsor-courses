<?php 
    require_once('../../private/initialize.php');
    require_admin_login();
    $page_title = 'Staff Home'; 
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <!-- Options for staff to use -->
        <div id="content">
            <div id="main-menu">
                <h2>Main Menu</h2>
                <ul>
                    <li><a href="<?php echo url_for('staff/admins/index.php');?>">Staff</a></li>
                    <li><a href="<?php echo url_for('staff/reviews/index.php');?>">Reviews</a></li>
                    <li><a href="<?php echo url_for('staff/service/index.php');?>">Customer Service</a></li>
                    <li><a href="<?php echo url_for('staff/users/index.php');?>">Users and Orders</a></li>
                    <li><a href="<?php echo url_for('staff/categories/index.php');?>">Categories and Products</a></li>
                    <br />
                    <li><a href="<?php echo url_for('index.php'); ?>">Return to Store</a></li>
                </ul>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>