<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Staff Management'; 
    $staff_set = find_all_staff();
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <!-- Options for staff to use -->
        <div id="content">
            <h1>Staff</h1>

            <p>The staff member with ID#1 is the root user for the site.
            <div class="actions">
                <a href="<?php echo url_for('/staff/admins/new.php'); ?>">Create New Staff Member</a>
            </div>

            <table class="list">
                <tr>    
                    <th>ID</th>
                    <th>Staff ID</th>
                    <th>Email</th>
                    <th>First Name</th>
                    <th>Last Name</th>
                    <th>User Active?</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                </tr>

            <?php while($staff = mysqli_fetch_assoc($staff_set)) { ?>

                <tr>
                    <td><?php echo h($staff['id']); ?></td>
                    <td><?php echo h($staff['staffID']); ?></td>
                    <td><?php echo h($staff['email']); ?></td>
                    <td><?php echo h($staff['fname']); ?></td>
                    <td><?php echo h($staff['lname']); ?></td>
                    <td><?php echo h($staff['active'] == 1 ? "Active" : "Inactive"); ?></td>
                    <td><a class="action" href="<?php echo url_for('/staff/admins/show.php?id=' . h(u($staff['id']))) ?>">View</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/admins/edit.php?id=' . h(u($staff['id']))) ?>">Edit</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/admins/delete.php?id=' . h(u($staff['id']))) ?>">Delete</a></td>
                </tr>
                <?php } ?>

            </table>

            <?php
                mysqli_free_result($staff_set);
            ?>
            
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>