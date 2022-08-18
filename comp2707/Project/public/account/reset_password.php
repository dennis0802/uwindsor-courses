<?php 
    require_once('../../private/initialize.php');
    
    if(!isset($_GET['id'])){
        redirect_to(url_for("/index.php"));
    }
    $id = $_GET['id'];
    $cur_user = find_user_by_id($id);

    if(is_post_request()){
        $user = [];
        $user['id'] = $id;
        $user['userID'] = $cur_user['userID'] ?? '';
        $user['email'] = $cur_user['email'] ?? '';
        $user['fname'] = $cur_user['fname'] ?? '';
        $user['lname'] = $cur_user['lname'] ?? '';
        $user['birthday'] = $cur_user['birthday'] ?? '';
        $user['address'] = $cur_user['address'] ?? '';
        $user['postCode'] = $cur_user['postCode'] ?? '';
        $user['city'] = $cur_user['city'] ?? '';
        $user['country'] = $cur_user['country'] ?? '';
        $user['password'] = $_POST['password'] ?? '';
        $user['confirmPass'] = $_POST['confirmPass'] ?? '';
        $user['securityQuestion'] = $cur_user['securityQuestion'] ?? '';
        $user['answer'] = $cur_user['answer'] ?? '';

        $result=reset_password($user);

        // If account is succesfully created, also log the user in
        if($result === true){
            $_SESSION['status'] = "Password successfully reset. Welcome back, " . h($user['userID']) . "!";
            log_in_user($user);
            redirect_to(url_for('/account/index.php'));
        }
        else{
            $errors = $result;
        }
    }

    if(!isset($_SESSION['found'])){
        redirect_to(url_for("/index.php"));
    }
    // Unset immediately after setting in the previous post request to prevent users from coming here with changing the url.
    unset($_SESSION['found']);

    $page_title = 'Reset Password';
?>

<?php include(SHARED_PATH . '/public_header.php'); ?>
        <div id="page">
            <h1>Reset Password</h1>
            <?php echo display_errors($errors); ?>
            
            <p>Please enter your new password.</p>

            <form action=<?php echo url_for("/account/reset_password.php?id=" . h(u($id)));?> method="post">
                <dl>
                    <dt>Password</dt>
                    <dd><input type="password" name="password" value=""/></dd>
                </dl>
                <dl>
                    <dt>Confirm Password</dt>
                    <dd><input type="password" name="confirmPass" value=""/></dd>
                </dl>
                <input type="submit" name="submit" value="Reset Password" />
            </form>
            <br />
        </div>

<?php include(SHARED_PATH . '/public_footer.php'); ?>