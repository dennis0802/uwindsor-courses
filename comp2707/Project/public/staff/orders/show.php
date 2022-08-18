<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $id = $_GET['id'] ?? '1';
    $order = find_order_by_id($id);
    $user = find_user_by_id($order['userID']);;
?>

<?php $page_title = 'Show Order'; ?>
<?php include(SHARED_PATH . '/staff_header.php'); ?>

<div id="content">
    <a href="<?php echo url_for('staff/users/show.php?id=' . h(u($user['id'])));?>">&laquo; Back to User Page</a>

    <div>
        <h1>Order by: <?php echo h($user['fname']) . ' ' . h($user['lname']); ?></h1>

        <div>
            <dl>
                <dt>User ID</dt>
                <dd><?php echo h($order['userID']); ?></dd>
            </dl>
            <dl>
                <dt>Products</dt>
                <dd>
                    <?php 
                        $ids = explode(",", h ($order['productIDs']));
                        foreach($ids as $productID){
                            $product = find_product_by_id($productID);
                            if($product === null){
                                break;
                            }
                            echo $product['name'] . "<br />";
                        }
                    ?>
                </dd>
            </dl>
            <dl>
                <dt>Amount Ordered</dt>
                <dd><?php echo h($order['amts']); ?></dd>
            </dl>
            <dl>
                <dt>Order Made</dt>
                <dd><?php echo h($order['orderMade']); ?></dd>
            </dl>
            <dl>
                <dt>Amount Paid</dt>
                <dd><?php echo "$" . h($order['paid']); ?></dd>
            </dl>
            <dl>
                <dt>Fulfilled?</dt>
                <dd><?php echo h($order['fulfilled'] == 1 ? "fulfilled" : "pending"); ?>
            </dl>
        </div>
    </div>
</div>

<?php include(SHARED_PATH . '/staff_footer.php'); ?>