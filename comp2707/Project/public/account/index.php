<?php require_once('../../private/initialize.php') ?>
<?php include(SHARED_PATH . '/public_header.php') ?>
<?php 
    // Staff have their own account management, redirect to their management area
    if(is_admin_logged_in()){
        redirect_to(url_for('/staff/index.php'));
    }

    require_user_login();
    $userInfo = find_user_by_id($_SESSION['user_id']);
    $service_set = find_service_by_user_id($_SESSION['user_id']);
    $order_set = find_order_by_user_id($_SESSION['user_id']);
?>

        <!-- Page contents -->
        <div id="page">
            <h1>Account Management for: <?php echo $_SESSION['usernameU']?></h1>
            <?php echo display_session_message(); ?>

            <hr />

            <!-- Display user information -->
            <h2>Basic Information</h2>

            <p><b>Name</b>: <?php echo $userInfo['fname'] . ' ' . $userInfo['lname'];?></p>
            <p><b>Email</b>: <?php echo $userInfo['email'];?></p>
            <p><b>Birthday</b>: <?php echo $userInfo['birthday'];?> </p>
            <p><b>Address</b>: <?php echo $userInfo['address'];?></p>
            <p><b>City</b>: <?php echo $userInfo['city'];?></p>
            <p><b>Country</b>: <?php echo $userInfo['country'];?></p>
            <p><b>Postal Code</b>: <?php echo $userInfo['postCode'];?></p>

            <hr />

            <!-- Display user's requests -->
            <h2>Service Requests</h2>

            <table class="list">
                <tr>
                    <th>ID</th>
                    <th>Request Subject</th>
                    <th>Request Made</th>
                    <th>Request Last Action</th>
                    <th>Marked As</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                </tr>

                <?php 
                    while($service = mysqli_fetch_assoc($service_set)){ 
                ?>

                <tr>
                    <td><?php echo h($service['id']); ?></td>
                    <td><?php echo h($service['requestSubject']); ?></td>
                    <td><?php echo h($service['requestMade']); ?></td>
                    <td><?php echo h($service['requestLastAction']); ?></td>
                    <td><?php echo h($service['resolved'] == 1 ? 'resolved' : 'unresolved'); ?></td>
                    <td><a class="action" href="<?php echo  url_for('account/showRequest.php?id=' . h(u($service['id'])))?>">View</a>
                    <?php 
                        if (h($service['resolved']) == 0){ 
                    ?>

                    <td><a class="action" href="<?php echo  url_for('account/editRequest.php?id=' . h(u($service['id'])))?>">Edit</a>
                    <?php 
                        } 
                        else{ 
                            echo "<td>&nbsp;</td>"; 
                        }
                    ?>

                </tr>
                <?php 
                } 
                ?>

            </table>
            <hr />

            <!-- Display user's orders -->
            <h2>Orders</h2>
            <table class="list">
                <tr>
                    <th>ID</th>
                    <th>Products</th>
                    <th>Amount</th>
                    <th>Order Made</th>
                    <th>Total Paid</th>
                    <th>Fulfilled</th>
                </tr>

                <?php 
                    while($order = mysqli_fetch_assoc($order_set)){ 
                ?>

                <tr>
                    <td><?php echo h($order['id']); ?></td>
                    <td><?php                        
                            $ids = explode(",", h ($order['productIDs']));
                            foreach($ids as $productID){
                                $product = find_product_by_id($productID);
                                if($product === null){
                                    break;
                                }
                                echo $product['name'] . "<br />";
                            }
                            echo "</td>";
                        ?>

                    <td><?php echo h($order['amts']); ?></td>
                    <td><?php echo h($order['orderMade']); ?></td>
                    <td><?php echo "$" . h($order['paid']); ?></td>
                    <td><?php echo h($order['fulfilled'] == 1 ? 'fulfilled' : 'pending'); ?></td>
                </tr>
                <?php 
                    } 
                ?>

            </table>
            <hr />
            
            <!-- Let user delete, edit, or log out of account -->
            <h2>Account Actions</h2>
            <a href="<?php echo url_for('account/editAccount.php?id=' . h(u($userInfo['id'])))?>"><b>Edit Account</b></a><br /><br />
            <a id="delete" href="<?php echo url_for('account/deleteAccount.php?id=' . h(u($userInfo['id'])))?>"><b>Delete Account</b></a><br /><br />
            <a href="<?php echo url_for('/store_logout.php')?>"><b>Log Out</b></a><br /><br />
        </div>

<?php include(SHARED_PATH . '/public_footer.php') ?>