<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Delete User'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/users/index.php'));
    }
    $id = $_GET['id'];
    $user = find_user_by_id($id);
    
    if(is_post_request()){
        $result=delete_user($id);

        if($result === true){
            $_SESSION['status'] = "The user was deleted successfully.";
            redirect_to(url_for('/staff/users/index.php'));
        }
        else{
            $errors = $result;
        }
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('/staff/users/index.php'); ?>">&laquo; Back to User Page</a>

            <div>
                <h1>Delete User</h1>
                <?php echo display_errors($errors); ?>

                <p>Are you sure you want to delete this user member?</p>
                <p><?php echo "User ID: " . h($user['userID']); ?></p>
                <p><?php echo "Name: " . h($user['fname'] . ' ' . $user['lname']); ?></p>

                <form action="<?php echo url_for('/staff/users/delete.php?id=' . h(u($user['id']))); ?>" method="post">
                    <div id="operations">
                        <input type="submit" name="commit" value="Delete User" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>
