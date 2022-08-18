<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Delete Product'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/index.php'));
    }
    $id = $_GET['id'];
    $product = find_product_by_id($id);
    
    if(is_post_request()){
        $result=delete_product($id);

        if($result === true){
            $_SESSION['status'] = "The product was deleted successfully.";
            redirect_to(url_for('/staff/categories/show.php?id=' . h(u($product['categoryID']))));
        }
        else{
            $errors = $result;
        }
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('/staff/categories/show.php?id=' . h(u($product['categoryID']))); ?>">&laquo; Back to Products</a>

            <div>
            <h1>Delete Product</h1>
            <?php echo display_errors($errors); ?>
            
            <p>Are you sure you want to delete this product?</p>
            <p><?php echo "Product: " . h($product['name']); ?></p>

            <form action="<?php echo url_for('/staff/products/delete.php?id=' . h(u($product['id']))); ?>" method="post">
                <div id="operations">
                <input type="submit" name="commit" value="Delete Product" />
                </div>
            </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>