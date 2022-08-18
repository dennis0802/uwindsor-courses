<?php require_once('../private/initialize.php') ?>
<?php include(SHARED_PATH . '/public_header.php') ?>

<?php
    $errors = [];
    $userID = '';
    $password = '';

    if(is_admin_logged_in()){
        redirect_to(url_for('/staff/index.php'));
    }
    else if(is_user_logged_in()){
        redirect_to(url_for('/account.php'));
    }

    if(is_post_request()){

        $userID = $_POST['userID'];
        $password = $_POST['password'];

        // Validations
        if(is_blank($userID)){
            $errors[] = "User ID cannot be blank.";
        }
        if(is_blank($password)){
            $errors[] = "Password cannot be blank.";
        }

        // No validation errors - continue login attempt
        if(!is_blank($password) && !is_blank($userID) && empty($errors)){
            $user = find_user_by_userID($userID);
            $failure = "Login unsuccessful.";

            // Check userID
            if($user){
                // Check password
                if(password_verify($password, $user['password'])){
                    log_in_user($user);
                    $_SESSION['status'] = "Welcome back, " . h($userID) . "!";
                    redirect_to(url_for('/index.php'));
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
        <div id="page">
            <h1>User Login</h1>
            <?php echo display_errors($errors); ?>

            <!-- Get userID and password to login as user -->
            <form action="login_user.php" method="post">
                UserID:<br />
                <input type="text" name="userID" value="<?php echo h($userID); ?>" /><br /><br />
                Password:<br />
                <input type="password" name="password" value="" /><br /><br />
                <input type="submit" name="submit" value="Login" />
            </form>

            <br />

            <a href="<?php echo url_for('/account/forget_password.php'); ?>">Forgot your password?</a><br /><br />
            <a href="<?php echo url_for('/index.php'); ?>">Return to Store</a><br /><br />
        </div>

<?php include(SHARED_PATH . '/public_footer.php') ?>