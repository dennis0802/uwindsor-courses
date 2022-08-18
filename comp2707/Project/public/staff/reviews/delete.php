<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Delete Review'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/reviews/index.php'));
    }
    $id = $_GET['id'];
    $review = find_review_by_id($id);
    $user = find_user_by_id($review['userID']);
    $product = find_product_by_id($review['productID']);
    
    if(is_post_request()){
        $result=delete_review($id);
        
        if($result === true){
            $_SESSION['status'] = "The review was deleted successfully.";
            redirect_to(url_for('/staff/reviews/index.php'));
        }
        else{
            $errors = $result;
        }
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('/staff/reviews/index.php'); ?>">&laquo; Back to Staff Page</a>

            <div>
            <h1>Delete Review</h1>
            <?php echo display_errors($errors); ?>

            <p>Are you sure you want to delete this review?</p>
            <p><?php echo "From: " . h($user['userID']); ?></p>
            <p><?php echo "Product: " . h($product['name']); ?></p>
            <p><?php echo "Rating: " . h($review['rating']);?></p>
            <p>Review Contents:</p>
            <textarea name="contents" cols="60" rows="10" readonly>
                <?php echo h($review['contents']); ?>
            
            </textarea>
            <form action="<?php echo url_for('/staff/reviews/delete.php?id=' . h(u($review['id']))); ?>" method="post">
                <div id="operations">
                <input type="submit" name="commit" value="Delete Review" />
                </div>
            </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>