<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $id = $_GET['id'] ?? '1';
    $staff = find_staff_by_id($id);
    $page_title = 'Show Staff'; 
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <!-- Show staff contents -->
        <div id="content">
            <a href="<?php echo url_for('staff/admins/index.php');?>">&laquo; Back to Staff Page</a>
            <div>
            <h1>Staff: <?php echo h($staff['fname']) . ' ' . h($staff['lname']) ?></h1>
            </div>

            <div>
                <dl>
                    <dt>ID</dt>
                    <dd><?php echo h($staff['id']); ?></dd>

                </dl>
                <dl>
                    <dt>UserID</dt>
                    <dd><?php echo h($staff['staffID']); ?></dd>

                </dl>
                <dl>
                    <dt>Email</dt>
                    <dd><?php echo h($staff['email']); ?></dd>

                </dl>
                <dl>
                    <dt>First Name</dt>
                    <dd><?php echo h($staff['fname']); ?></dd>

                </dl>
                <dl>
                    <dt>Last Name</dt>
                    <dd><?php echo h($staff['lname']); ?></dd>

                </dl>
                <dl>
                    <dt>Active?</dt>
                    <dd><?php echo h($staff['active'] == '1' ? 'true' : 'false'); ?></dd>
                    
                </dl>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>