<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Edit Order'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/users/index.php'));
    }
    $id = $_GET['id'];

    if(is_post_request()){
        $order = [];
        $order['id'] = $id;
        $order['userID'] = $_POST['userID'] ?? '';
        $order['productIDs'] = $_POST['prodIDs'] ?? '';
        $order['amts'] = $_POST['amts'] ?? '';
        $order['fulfilled'] = $_POST['fulfilled'] ?? '';
        $order['paid'] = $_POST['paid'] ?? '';
        $result=update_order($order);

        if($result === true){
            $_SESSION['status'] = "The order was edited successfully.";
            redirect_to(url_for('/staff/orders/show.php?id=' . $id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $order = find_order_by_id($id);
        $productIDs = explode(',', $order['productIDs']);
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/users/show.php?id=' . h(u($order['userID']))); ?>">&laquo; Back to Orders</a>

            <div>
                <h1>Edit Order</h1>

                <?php echo display_errors($errors); ?>
                
                <form action="<?php echo url_for('staff/orders/edit.php?id=' . h(u($id))); ?>" method="post">
                    <dl>
                        <dt>User ID</dt>
                        <dd>
                            <select name="userID">
                                <?php
                                    $user_set = find_all_users();
                                    while($user = mysqli_fetch_assoc($user_set)){
                                        echo "<option value=\"" . h($user['id']) . "\"";
                                        if($order["userID"] == $user['id']){
                                            echo " selected";
                                        }
                                        echo ">" . h($user['userID']) . "</option>\n\t\t\t\t\t\t\t\t";
                                    }
                                ?>

                            </select>
                        </dd>
                    </dl>
                    <dl>
                    <dl>
                        <dt>Products</dt>
                        <dd>
                            The selected items will appear in the same order as this list<br/>
                            <select name="prodIDs[]" multiple="multiple">
                                <?php
                                    $product_set = find_all_products();
                                    while($product = mysqli_fetch_assoc($product_set)){
                                        echo "<option value=\"" . h($product['id']) . "\"";
                                        if(in_array($product["id"], $productIDs)){
                                            echo " selected";
                                        }
                                        echo ">" . h($product['name']) . "</option>\n\t\t\t\t\t\t\t\t";
                                    }
                                ?>

                            </select>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Amount Ordered</dt>
                        <dd>Please enter in the form: (#,#,#) where '#' is each product's amount
                        <dd><input type="text" name="amts" value="<?php echo h($order['amts']); ?>"/></dd>
                    </dl>

                    <dl>
                        <dt>Amount Paid</dt>
                        <dd><input type="number" name="paid" value="<?php echo h($order['paid'])?>" min="0.01" max="999999.99" step="0.01"/></dd>
                    </dl>

                    <dl>
                        <dt>Fulfilled</dt>
                        <dd>
                        <input type="hidden" name="fulfilled" value="0" />
                        <input type="checkbox" name="fulfilled" value="1" <?php if($order['fulfilled'] == "1"){echo " checked";}?>/>
                        </dd>
                    </dl>

                    <div id="operations">
                        <input type="submit" value="Edit Order" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>