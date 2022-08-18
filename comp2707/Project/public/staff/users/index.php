<?php 
    require_once('../../../private/initialize.php');
    $page_title = 'User Management'; 
    require_admin_login();
    $user_set = find_all_users();
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <!-- Options for staff to use -->
        <div id="content">
            <h1>Users and Orders</h1>

            <p>Orders can be managed by viewing a user.</p>
            <div class="actions">
                <a href="<?php echo url_for('/staff/users/new.php'); ?>">Create New User</a>
            </div>

            <table class="list">
                <tr>    
                    <th>ID</th>
                    <th>User ID</th>
                    <th>Email</th>
                    <th>First Name</th>
                    <th>Last Name</th>
                    <th>Birthday</th>
                    <th>Country</th>
                    <th>Orders Made</th>
                    <th>Recent Order</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                </tr>

            <?php while($user = mysqli_fetch_assoc($user_set)) { ?>
                <tr>
                    <?php $order_count = count_orders_by_user_id($user['id']); ?>
                    <?php $recentDate = find_recent_date_by_user_id($user['id']); ?>
                    <td><?php echo h($user['id']); ?></td>
                    <td><?php echo h($user['userID']); ?></td>
                    <td><?php echo h($user['email']); ?></td>
                    <td><?php echo h($user['fname']); ?></td>
                    <td><?php echo h($user['lname']); ?></td>
                    <td><?php echo h($user['birthday']); ?></td>
                    <td><?php echo h($user['country']); ?></td>
                    <td><?php echo h($order_count);?> </td>
                    <td><?php echo h($recentDate);?> </td>
                    <td><a class="action" href="<?php echo url_for('/staff/users/show.php?id=' . h(u($user['id']))) ?>">View</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/users/edit.php?id=' . h(u($user['id']))) ?>">Edit</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/users/delete.php?id=' . h(u($user['id']))) ?>">Delete</a></td>
                </tr>
                <?php } ?>
            </table>

            <?php
                mysqli_free_result($user_set);
            ?>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>