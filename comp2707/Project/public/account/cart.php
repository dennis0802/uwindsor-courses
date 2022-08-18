<?php require_once('../../private/initialize.php') ?>
<?php 
    // If removing was requested, unset from the associative array cart
    if(isset($_GET['remove_prodID'])){
        $id = $_GET['remove_prodID'];
        if(!(isset($_SESSION['cart'][$id]))){
            redirect_to(url_for('/account/cart.php'));
        }

        unset($_SESSION['cart'][$id]);
        $_SESSION['status'] = "Product was successfully removed.";
    }
    if(is_post_request()){
        redirect_to(url_for('/account/payment.php'));
    }

    if(isset($_SESSION['cart'])){
        $amts = array_values($_SESSION['cart']);
        $cartCount = 0;
        foreach($amts as $amt){
            $cartCount += $amt;
        }
        $productIDs = array_keys($_SESSION['cart']);
    }
    else{
        $cartCount = '';
    }

    $page_title = "View Cart";
    $total = 0.00;
?>

<?php include(SHARED_PATH . '/public_header.php') ?>
        <!-- Page content -->
        <div id="page">
            <h1>Shopping Cart</h1>
            <?php echo display_session_message(); ?>

            <p>Manage what's in your shopping cart and checkout.</p>
            <?php 
                if(is_user_logged_in()){
            ?>

            <p><?php echo "Your shopping cart has " . $cartCount. ' item(s).'; ?></p>
            <table class="list">
                <tr>
                    <th>Product Name</th>
                    <th>Amount Purchased</th>
                    <th>Cost</th>
                    <th>Subtotal</th>
                    <th>&nbsp;</th>
                </tr>

                <?php 
                    foreach($productIDs as $productID){ 
                    $cartProduct = find_product_by_id($productID);
                ?>

                <tr>
                    <td>
                        <!-- Half the size of the image for a cart image version -->
                        <img src="<?php echo url_for('/images/' . h(u($cartProduct['imageRef'])));?>" alt="<?php echo $cartProduct['name'];?>" width="150" height="133" /><br />
                        <?php echo h($cartProduct['name']);?>
                        
                    </td>
                    <td><?php echo h($_SESSION['cart'][$productID]);?></td>
                    <td><?php echo h('$' . $cartProduct['price']);?></td>
                    <td><?php echo '$' . h($cartProduct['price'] * $_SESSION['cart'][$productID]);?></td>
                    <td><a href="<?php echo url_for('/account/cart.php?remove_prodID=' . $cartProduct['id']); ?>">Remove</a></td>
                </tr>
                <?php $total += $cartProduct['price'] * $_SESSION['cart'][$productID];} ?>

                <tr>
                    <td colspan="3" id="total"><b>Total:</b></td>
                    <td><?php echo '$' . $total?></td>
                </tr>
            </table>

            <form action="<?php echo url_for('/account/cart.php'); ?>" method="post">
                <div id="total">
                    <?php if($cartCount > 0){ ?>
                        
                    <input type="submit" name="checkout" value="Checkout" />
                    <?php }
                    else{
                        echo "Please add products to your cart before checking out.";
                    } ?>
                    
                </div>
            </form>
            <?php 
                }
                else{
                    echo "<p>You must be logged in as a store user to access a shopping cart.</p>";
                }
            ?>
            
        </div>

<?php include(SHARED_PATH . '/public_footer.php') ?>