<?php 
    require_once('../../private/initialize.php');
    $page_title = 'Staff Login'; 
    include(SHARED_PATH . '/staff_header.php');

    $errors = [];
    $staffID = '';
    $password = '';

    if(is_post_request()){

        $staffID = $_POST['staffID'];
        $password = $_POST['password'];

        // Validations
        if(is_blank($staffID)){
            $errors[] = "Staff ID cannot be blank.";
        }
        if(is_blank($password)){
            $errors[] = "Password cannot be blank.";
        }

        // No validation errors - continue login attempt
        if(!is_blank($password) && !is_blank($staffID) && empty($errors)){
            $staff = find_staff_by_staffID($staffID);
            $failure = "Login unsuccessful.";

            // Check staffID
            if($staff){
                // Check active status
                if($staff['active'] == 0){
                    $errors[] = "Staff member inactive. If this is a mistake, please contact IT.";
                }
                // Check password
                else if(password_verify($password, $staff['password'])){
                    log_in_admin($staff);
                    $_SESSION['status'] = "Welcome back, " . h($staffID) . "!";
                    redirect_to(url_for('/staff/index.php'));
                }
                else{
                    $errors[] = $failure;
                }
            }
            else{
                $errors[] = $failure;
            }
        }
    }
?>
        <!-- Page contents -->
        <div id="content">
            <h1>Staff Login</h1>

            <?php echo display_errors($errors); ?>

            <p>Staff, if you have forgotten your password, please contact IT.</p>
            <!-- Get userID and password to login as staff -->
            <form action="staff_login.php" method="post">
                UserID:<br />
                <input type="text" name="staffID" value="<?php echo h($staffID); ?>" /><br /><br />
                Password:<br />
                <input type="password" name="password" value="" /><br /><br />
                <input type="submit" name="submit" value="Login" />
            </form>

            <br /><a href="<?php echo url_for('/login_general.php'); ?>">Return to Store</a>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>