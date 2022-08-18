<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Delete Staff'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/admins/index.php'));
    }
    $id = $_GET['id'];
    $staff = find_staff_by_id($id);

    if(is_post_request()){
        // Root user will have ID 1 and cannot be deleted
        if($id == 1){
            $errors[] = "Root user cannot be deleted.";
        }
        else if($_SESSION['admin_id'] == $id){
            $errors[] = "You cannot delete your own account while logged in.";
        }
        else{
            $result=delete_staff($id);

            if($result === true){
                $_SESSION['status'] = "The staff was deleted successfully.";
                redirect_to(url_for('/staff/admins/index.php'));
            }
            else{
                $errors = $result;
            }
        }
    }

?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('/staff/admins/index.php'); ?>">&laquo; Back to Staff Page</a>

            <div>
                <h1>Delete Staff</h1>
                <?php echo display_errors($errors); ?>
                <p>Are you sure you want to delete this staff member?</p>
                <p><?php echo "Staff ID: " . h($staff['staffID']); ?></p>
                <p><?php echo "Name: " . h($staff['fname'] . ' ' . $staff['lname']); ?></p>

                <form action="<?php echo url_for('/staff/admins/delete.php?id=' . h(u($staff['id']))); ?>" method="post">
                    <div id="operations">
                        <input type="submit" name="commit" value="Delete Admin" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>