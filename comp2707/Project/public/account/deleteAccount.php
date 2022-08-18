<?php require_once('../../private/initialize.php') ?>

<?php
    require_user_login();

    $page_title = 'Delete User'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/account/index.php'));
    }
    $id = $_GET['id'];
    $user = find_user_by_id($id);
    
    if(is_post_request()){
        $result=delete_user($id);

        if($result === true){
            log_out_user();
            $_SESSION['status'] = "Account deleted.";
            redirect_to(url_for('/index.php'));
        }
        else{
            $errors = $result;
        }
    }
?>

<?php include(SHARED_PATH . '/public_header.php'); ?>
        <!-- Page contents -->
        <div id="page">
            <hr />
            <a href="<?php echo url_for('/account/index.php'); ?>">&laquo; Back to Account</a>

            <hr />
            <div>
            <h1>Delete Account</h1>
            <?php echo display_errors($errors); ?>
            <p>Are you sure you want to delete your account?</p>
            <p><?php echo "User ID: " . h($user['userID']); ?></p>
            <p><?php echo "Name: " . h($user['fname'] . ' ' . $user['lname']); ?></p>
            <p>
                <b><i>*Please note that if you have orders and service requests active on file, 
                you will be unable to delete your account until the orders and requests are cleared.
                </i></b>
            </p>

            <form action="<?php echo url_for('/account/deleteAccount.php?id=' . h(u($user['id']))); ?>" method="post">
                <div id="operations">
                <input type="submit" name="commit" value="Delete Account" />
                </div>
            </form>
            </div>
        </div>
        
<?php include(SHARED_PATH . '/public_footer.php'); ?>

