<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Delete Order'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/index.php'));
    }
    $id = $_GET['id'];
    $order = find_order_by_id($id);
    $user = find_user_by_id($order['userID']);
    
    if(is_post_request()){
        $result=delete_order($id);

        if($result === true){
            $_SESSION['status'] = "The order was deleted successfully.";
            redirect_to(url_for('/staff/users/show.php?id=' . h(u($order['userID']))));
        }
        else{
            $errors = $result;
        }
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('/staff/users/show.php?id=' . h(u($order['userID']))); ?>">&laquo; Back to Staff Page</a>

            <div>
            <h1>Delete Order</h1>
            <?php echo display_errors($errors); ?>
            <p>Are you sure you want to delete this order?</p>
            <p><?php echo "Order ID: " . h($order['id']); ?></p>
            <p><?php echo "Order for: " . h($user['fname']) . ' ' . h($user['lname']); ?></p>
            <p><?php echo "Order Made: " . h($order['orderMade']); ?></p>
            <p><?php echo "Products:<br />"?>
            <?php 
            $ids = explode(",", h ($order['productIDs']));
                foreach($ids as $productID){
                    $product = find_product_by_id($productID);
                    if($product === null){
                        break;
                    }
                    echo $product['name'] . "<br />";
                }
            ?></p>
            <form action="<?php echo url_for('/staff/orders/delete.php?id=' . h(u($order['id']))); ?>" method="post">
                <div id="operations">
                <input type="submit" name="commit" value="Delete Order" />
                </div>
            </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>