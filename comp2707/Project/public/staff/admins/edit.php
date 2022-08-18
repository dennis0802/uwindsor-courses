<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Edit Staff'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/admins/index.php'));
    }
    $id = $_GET['id'];
    
    if(is_post_request()){
        $staff = [];
        $staff['id'] = $id;
        $staff['staffID'] = $_POST['staffID'] ?? '';
        $staff['email'] = $_POST['email'] ?? '';
        $staff['password'] = $_POST['password'] ?? '';
        $staff['fname'] = $_POST['fname'] ?? '';
        $staff['lname'] = $_POST['lname'] ?? '';
        $staff['active'] = $_POST['active'] ?? '';
        $staff['password'] = $_POST['password'] ?? '';
        $staff['confirmPass'] = $_POST['confirmPass'] ?? '';

        $result=update_staff($staff);

        if($result === true){
            $_SESSION['status'] = "The staff was edited successfully.";
            redirect_to(url_for('/staff/admins/show.php?id=' . $id));
        }
        else{
            $errors = $result;
        }
    }
    
    else{
        $staff = find_staff_by_id($id);
    }
    include(SHARED_PATH . '/staff_header.php');
?>
        <!-- Page contents -->
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/admins/index.php'); ?>">&laquo; Back to Staff Page</a>

            <div>
                <h1>Edit Staff</h1>

                <?php echo display_errors($errors); ?>

                <form action="<?php echo url_for("staff/admins/edit.php?id=" . h(u($id))); ?>" method="post">
                    <dl>
                        <dt>Staff ID</dt>
                        <dd><input type="text" name="staffID" value="<?php echo h(u($staff['staffID'])); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Email</dt>
                        <dd><input type="text" name="email" value="<?php echo h(($staff['email'])); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>First Name</dt>
                        <dd><input type="text" name="fname" value="<?php echo h(u($staff['fname'])); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Last Name</dt>
                        <dd><input type="text" name="lname" value="<?php echo h($staff['lname']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Password</dt>
                        <dd><input type="password" name="password" value=""/></dd>
                    </dl>
                    <dl>
                        <dt>Confirm Password</dt>
                        <dd><input type="password" name="confirmPass" value=""/></dd>
                    </dl>
                    <dl>
                        <dt>Active?</dt>
                        <input type="hidden" name="active" value="0" />
                        <input type="checkbox" name="active" value="1" <?php if($staff['active'] == "1"){echo " checked";}?>/>
                    </dl>

                    <p>
                        UserIDs should be between 4-25 characters long and include at least one number.
                        No special characters allowed.
                    </p>
                    <p>
                        Passwords should be at least 12 characters and include at least one uppercase
                        letter, lowercase letter, number, and symbol.
                    </p>

                    <div id="operations">
                        <input type="submit" value="Edit Admin" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>