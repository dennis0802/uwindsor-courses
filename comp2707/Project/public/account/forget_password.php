<?php 
    require_once('../../private/initialize.php');

    $page_title = 'Forget Password';
    $email = '';
    $errors = [];

    if(is_post_request()){
        $email = $_POST['email'];
        $user = find_user_by_email($email);
        if($user === null){
            $errors[] = "User with that email cannot be found.";
        }
        else{
            redirect_to(url_for("/account/found.php?id=" . h(u($user['id']))));
        }
    }
?>

<?php include(SHARED_PATH . '/public_header.php'); ?>
        <div id="page">
            <h1>Forget Password</h1>
            <?php echo display_errors($errors); ?>
            
            <p>Please enter your email that you registered your account with to retrieve the security question.</p>
            <form action="forget_password.php" method="post">
                Email:<br />
                <input type="text" name="email" value="<?php echo h($email); ?>" /><br /><br />
                <input type="submit" name="submit" value="Enter Email" />
            </form>
            <br />
        </div>

<?php include(SHARED_PATH . '/public_footer.php'); ?>