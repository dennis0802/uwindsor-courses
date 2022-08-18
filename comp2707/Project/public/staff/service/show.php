<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $id = $_GET['id'] ?? '1';
    $service = find_service_by_id($id);
    $page_title = 'Show Customer Service';
    $user = find_user_by_id($service['userID']); 
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('staff/service/index.php');?>">&laquo; Back to Customer Service Page</a>
            <div>
            <h1>Service for: <?php echo h($user['fname']) . ' ' . h($user['lname']) ?></h1>
            </div>

            <div>
                <dl>
                    <dt>ID</dt>
                    <dd><?php echo h($service['id']); ?></dd>
                </dl>
                <dl>
                    <dt>User ID</dt>
                    <dd><?php echo h($user['userID']); ?></dd>
                </dl>
                <dl>
                    <dt>Request Made</dt>
                    <dd><?php echo h($service['requestMade']); ?></dd>
                </dl>
                <dl>
                    <dt>Request Details</dt>
                    <dd>
                        <textarea name="requestDetails" cols="60" rows="10" readonly>
                            <?php echo h($service['requestDetails']); ?>

                        </textarea>
                    </dd>
                </dl>
                <dl>
                    <dt>Request Response</dt>
                    <dd>
                        <textarea name="requestResponse" cols="60" rows="10" readonly>
                            <?php echo h($service['requestResponse']); ?>
                            
                        </textarea>
                    </dd>
                </dl>
                <dl>
                    <dt>Resolved?</dt>
                    <dd><?php echo h($service['resolved'] == 1 ? 'resolved' : 'unresolved'); ?></dd>
                </dl>


            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>