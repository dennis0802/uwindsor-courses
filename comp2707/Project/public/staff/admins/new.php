<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Create User'; 

    if(is_post_request()){
        $staff = [];
        $staff['staffID'] = $_POST['staffID'] ?? '';
        $staff['email'] = $_POST['email'] ?? '';
        $staff['password'] = $_POST['password'] ?? '';
        $staff['fname'] = $_POST['fname'] ?? '';
        $staff['lname'] = $_POST['lname'] ?? '';
        $staff['active'] = $_POST['active'] ?? '';
        $staff['password'] = $_POST['password'] ?? '';
        $staff['confirmPass'] = $_POST['confirmPass'] ?? '';

        $result=insert_staff($staff);

        if($result === true){
            $new_id = mysqli_insert_id($db);
            $_SESSION['status'] = "The staff was added successfully.";
            redirect_to(url_for('/staff/admins/show.php?id=' . $new_id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $staff = [];
        $staff['staffID'] = '';
        $staff['email'] = '';
        $staff['password'] = '';
        $staff['fname'] = '';
        $staff['lname'] = '';
        $staff['active'] = '';
        $staff['password'] = '';
        $staff['confirmPass'] = '';
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/admins/index.php'); ?>">&laquo; Back to List</a>

            <div>
                <h1>Create Staff</h1>

                <?php echo display_errors($errors); ?>
                
                <form action="<?php echo url_for('staff/admins/new.php'); ?>" method="post">
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
                        Staff IDs should be between 4-25 characters long and incude at least one number.
                        No special characters allowed.
                    </p>
                    <p>
                        Passwords should be at least 12 characters and include at least one uppercase
                        letter, lowercase letter, number, and symbol.
                    </p>

                    <div id="operations">
                        <input type="submit" value="Create Staff" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>