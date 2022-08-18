<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Delete Category'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/categories/index.php'));
    }
    $id = $_GET['id'];
    $category = find_category_by_id($id);
    
    if(is_post_request()){
        $result=delete_category($id);

        if($result === true){
            $_SESSION['status'] = "The category was deleted successfully.";
            redirect_to(url_for('/staff/categories/index.php'));
        }
        else{
            $errors = $result;
        }
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('/staff/categories/index.php'); ?>">&laquo; Back to Staff Page</a>

            <div>
            <h1>Delete Category</h1>
            <?php echo display_errors($errors); ?>
            
            <p>Are you sure you want to delete this category?</p>
            <p><?php echo "Category: " . h($category['catName']); ?></p>

            <form action="<?php echo url_for('/staff/categories/delete.php?id=' . h(u($category['id']))); ?>" method="post">
                <div id="operations">
                <input type="submit" name="commit" value="Delete Category" />
                </div>
            </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>