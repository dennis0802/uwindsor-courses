<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $id = $_GET['id'] ?? '1';
    $user = find_user_by_id($id);
    $order_set = find_order_by_user_id($user['id']);
    $page_title = 'Show User'; 
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('staff/users/index.php');?>">&laquo; Back to User Page</a>
            <div>
            <h1>User: <?php echo h($user['fname']) . ' ' . h($user['lname']) ?></h1>
            </div>

            <div>
                <dl>
                    <dt>ID</dt>
                    <dd><?php echo h($user['id']); ?></dd>

                </dl>
                <dl>
                    <dt>UserID</dt>
                    <dd><?php echo h($user['userID']); ?></dd>

                </dl>
                <dl>
                    <dt>Email</dt>
                    <dd><?php echo h($user['email']); ?></dd>

                </dl>
                <dl>
                    <dt>First Name</dt>
                    <dd><?php echo h($user['fname']); ?></dd>

                </dl>
                <dl>
                    <dt>Last Name</dt>
                    <dd><?php echo h($user['lname']); ?></dd>

                </dl>
                <dl>
                    <dt>Birthday</dt>
                    <dd><?php echo h($user['birthday']); ?></dd>

                </dl>
                <dl>
                    <dt>Address</dt>
                    <dd><?php echo h($user['address']); ?></dd>

                </dl>
                <dl>
                    <dt>Postal Code</dt>
                    <dd><?php echo h($user['postCode']); ?></dd>

                </dl>
                <dl>
                    <dt>City</dt>
                    <dd><?php echo h($user['city']); ?></dd>

                </dl>
                <dl>
                    <dt>Country</dt>
                    <dd><?php echo h($user['country']); ?></dd>

                </dl>
                <dl>
                    <dt>Current Security Question</dt>
                    <dd><?php echo h($user['securityQuestion']); ?></dd>
                </dl>
            </div>

            <hr />

            <div>
                <h2>Orders</h2>
                                
                <div class="actions">
                    <a href="<?php echo url_for('/staff/orders/new.php?userID=' . h(u($user['id'])))?>">Create New Order</a>
                </div>

                <table class="list">
                    <tr>    
                        <th>ID</th>
                        <th>Products</th>
                        <th>Amount Purchased</th>
                        <th>Order Made</th>
                        <th>Order Status</th>
                        <th>Paid</th>
                        <th>&nbsp;</th>
                        <th>&nbsp;</th>
                        <th>&nbsp;</th>
                    </tr>

                <?php while($order = mysqli_fetch_assoc($order_set)) { ?>

                    <tr>
                        <td><?php echo h($order['id']); ?></td>
                        <td>
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

                        </td>
                        <td><?php echo h($order['amts']); ?></td>
                        <td><?php echo h($order['orderMade']); ?></td>
                        <td><?php echo h($order['fulfilled'] == 1 ? 'fulfilled' : 'pending'); ?></td>
                        <td><?php echo "$" . h($order['paid']); ?></td>
                        <td><a class="action" href="<?php echo url_for('/staff/orders/show.php?id=' . h(u($order['id']))) ?>">View</a></td>
                        <td><a class="action" href="<?php echo url_for('/staff/orders/edit.php?id=' . h(u($order['id']))) ?>">Edit</a></td>
                        <td><a class="action" href="<?php echo url_for('/staff/orders/delete.php?id=' . h(u($order['id']))) ?>">Delete</a></td>
                    </tr>
                <?php } ?>
                
                </table>
                <br />
            </div>

        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>