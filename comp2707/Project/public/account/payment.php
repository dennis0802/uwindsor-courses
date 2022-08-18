<?php require_once('../../private/initialize.php'); ?>
<?php 
    require_user_login();
    
    $page_title = 'Payment'; 
    $provider = 'default';
    $credit = '';
    $expiry = '';

    if(empty($_SESSION['cart'])){
        redirect_to(url_for('/account/cart.php'));
    }

    $productIDs = array_keys($_SESSION['cart']);
    $productAmts = array_values($_SESSION['cart']);
    $totalPayment = 0;

    foreach($productIDs as $productID){
        $cartProduct = find_product_by_id($productID);
        $totalPayment += $cartProduct['price'] * $_SESSION['cart'][$productID];
    }

    if(is_post_request()){
        $errors = [];

        // Validate form data
        $provider = $_POST['provider'] ?? '';
        $credit = $_POST['credit'] ?? '';
        $expiry = $_POST['expiry'];

        if(is_blank($provider)){
            $errors[] = "Provider cannot be empty";
        }
        else if($provider === "default"){
            $errors[] = "Provider was not selected.";
        }

        if(is_blank($credit)){
            $errors[] = "Credit card number cannot be empty.";
        }
        // Credit card number must be only digits
        else if(!has_valid_credit($credit)){
            $errors[] = "Credit card number is not valid. Credit card number should have 15-16 digits.";
        }

        // Expiry date
        if(is_blank($expiry)){
            $errors[] = "Expiry date cannot be empty.";
        }

        if(!empty($errors)){
            // Proceed to display errors
        }
        // Proceed with payment if no errors
        else{
            // Instead, decrement stock and increase amount for each product purchased in the database
            foreach($productIDs as $productID){
                $product = find_product_by_id($productID);
                $category = find_category_by_id($product['categoryID']);
                $amtPurchased = $_SESSION['cart'][$productID];
                $result1 = update_product_stock($product, $amtPurchased);
                $result2 = update_product_purchase($product, $amtPurchased);
                $result3 = update_total_purchases($category, $amtPurchased);

                if($result1 === false || $result2 === false || $result3 === false){
                    $errors[] = "Order could not be processed. Please contact customer service.";
                    break;
                }
            }

            // Set up the ordered products string for the database.
            $purchasedAmts = '';
            for($i = 0; $i < count($productIDs) ; $i++){
                if($i == count($productIDs) - 1){
                    $purchasedAmts .= $productAmts[$i];
                }
                else{
                    $purchasedAmts .= $productAmts[$i] . ',';
                }
            }

            $order = [];
            $order['userID'] = $_SESSION['user_id'];
            $order['productIDs'] = $productIDs;
            $order['amts'] = $purchasedAmts;
            $order['paid'] = $totalPayment;
            $order['fulfilled'] = 0;

            $result = insert_order($order);

            if($result === true){
                // Save order to database and redirect to landing page
                // If this were a full ecommerce site, the forwarding would happen here
                // Empty cart and reinitialize cart
                $new_id = mysqli_insert_id($db);
                unset($_SESSION['cart']);
                $_SESSION['cart'] = [];
                $_SESSION['status'] = "Order successfully processed! Thanks for shopping with us, your order has been saved with ID#" . $new_id;
                redirect_to(url_for('/index.php'));
            }
            else{
                $errors[] = "Order could not be processed. Please contact customer service.";
            }


        }
    }
?>
<?php include(SHARED_PATH . '/public_header.php');?>

        <!-- Page contents -->
        <div id="page">
            <a href="<?php echo url_for('/account/cart.php'); ?>">&laquo; Back to Cart</a>
            <h1>Payment</h1>
            <?php echo display_errors($errors); ?>
            <p>
                Before we can fully process your order, please enter your selected credit card information. Be assured that we don't
                store your credit information on our databases, we will forward to a third-party credit processor.
            </p>

            <?php echo "<h2>Total payable: $" . $totalPayment . "</h2>"; ?>

            <form action="<?php echo url_for('account/payment.php'); ?>" method="post">
                <dl>
                    <dt>Credit Card Provider</dt>
                    <select name="provider">
                        <option value="default" hidden selected>Select a provider...</option>
                        <option value="American Express">American Express</option>
                        <option value="Mastercard">Mastercard</option>
                        <option value="Visa">Visa</option>
                        <option value="Diner's Club">Diner's Club</option>
                    </select>
                </dl>
                <dl>
                    <dt>Credit Card Number</dt>
                    <dd><input type="text" name="credit" value="<?php echo h($credit); ?>"/></dd>
                </dl>
                <dl>
                    <dt>Expiry Date</dt>
                    <dd><input type="month" name="expiry" value="<?php echo h($expiry); ?>"/></dd>
                </dl>
                <input type="submit" name="submit" value="Confirm Order" /><br /><br />
            </form>
        </div>

<?php include(SHARED_PATH . '/public_footer.php');?>