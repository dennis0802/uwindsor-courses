<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Order Management'; 
    redirect_to('/staff/index.php');
    //$order_set = find_all_orders();
?>


<?php /*include(SHARED_PATH . '/staff_header.php'); ?>
        <!-- Options for staff to use -->
        <div id="content">
            <h1>Orders</h1>

            <div class="actions">
                <a href="<?php echo url_for('/staff/orders/new.php'); ?>">Create New Order</a>
            </div>

            <table class="list">
                <tr>    
                    <th>ID</th>
                    <th>User ID</th>
                    <th>Product ID</th>
                    <th>Amount Purchased</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                </tr>

            <?php while($order = mysqli_fetch_assoc($order_set)) { ?>
                <tr>
                    <td><?php echo h($order['id']); ?></td>
                    <td><?php echo h($order['userID']); ?></td>
                    <td><?php echo h($order['prodID']); ?></td>
                    <td><?php echo h($order['amt']); ?></td>
                    <td><a class="action" href="<?php echo url_for('/staff/orders/show.php?id=' . h(u($order['id']))) ?>">View</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/orders/edit.php?id=' . h(u($order['id']))) ?>">Edit</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/orders/delete.php?id=' . h(u($order['id']))) ?>">Delete</a></td>
                </tr>
                <?php } ?>
            </table>

            <?php
                mysqli_free_result($order_set);
            ?>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');*/?>