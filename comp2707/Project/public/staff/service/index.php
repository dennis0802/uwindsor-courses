<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Service Management';
    $service_set = find_all_service();
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <!-- Options for staff to use -->
        <div id="content">
            <h1>Customer Service</h1>

            <p>Please create requests ONLY if the user is unable to.</p>
            <div class="actions">
                <a href="<?php echo url_for('/staff/service/new.php'); ?>">Create New Customer Service Request</a>
            </div>

            <table class="list">
                <tr>    
                    <th>ID</th>
                    <th>User's Name</th>
                    <th>User's ID</th>
                    <th>Request Subject</th>
                    <th>Request Made</th>
                    <th>Last Request Action</th>
                    <th>Resolved?</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                </tr>

            <?php while($service = mysqli_fetch_assoc($service_set)) { ?>
                <?php $user = find_user_by_id(h($service['userID'])); ?>

                <tr>
                    <td><?php echo h($service['id']); ?></td>
                    <td><?php echo h($user['fname']) . ' ' . h($user['lname']); ?></td>
                    <td><?php echo h($user['userID']); ?></td>
                    <td><?php echo h($service['requestSubject']); ?></td>
                    <td><?php echo h($service['requestMade']); ?></td>
                    <td><?php echo h($service['requestLastAction']); ?></td>
                    <td><?php echo h($service['resolved'] == 1 ? 'resolved' : 'unresolved'); ?></td>
                    <td><a class="action" href="<?php echo url_for('/staff/service/show.php?id=' . h(u($service['id']))) ?>">View</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/service/edit.php?id=' . h(u($service['id']))) ?>">Edit</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/service/delete.php?id=' . h(u($service['id']))) ?>">Delete</a></td>
                </tr>
                <?php } ?>

            </table>

            <?php
                mysqli_free_result($service_set);
            ?>
            
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>