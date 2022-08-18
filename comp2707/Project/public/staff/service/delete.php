<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Delete Service Request'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/service/index.php'));
    }
    $id = $_GET['id'];
    $service = find_service_by_id($id);
    $user = find_user_by_id($service['userID']);
    
    if(is_post_request()){
        $result=delete_service($id);
        
        if($result === true){
            $_SESSION['status'] = "The service request was deleted successfully.";
            redirect_to(url_for('/staff/service/index.php'));
        }
        else{
            $errors = $result;
        }
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('/staff/service/index.php'); ?>">&laquo; Back to Staff Page</a>

            <div>
            <h1>Delete Service</h1>
            <?php echo display_errors($errors); ?>

            <p>Are you sure you want to delete this service request?</p>
            <p><?php echo "From: " . h($user['fname'] . ' ' . $user['lname']); ?></p>
            <p><?php echo "Request Subject: " . h($service['requestSubject']); ?></p>
            <p>Request Details:</p>
            <textarea name="requestDetails" cols="60" rows="10" readonly>
                <?php echo h($service['requestDetails']); ?>
            
            </textarea>
            <p><?php echo "Resolved? : " . h($service['resolved'] == 1 ? 'resolved' : 'unresolved'); ?></p>
            <form action="<?php echo url_for('/staff/service/delete.php?id=' . h(u($service['id']))); ?>" method="post">
                <div id="operations">
                <input type="submit" name="commit" value="Delete Service Request" />
                </div>
            </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>