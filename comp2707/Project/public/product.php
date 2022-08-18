<?php require_once('../private/initialize.php') ?>

<?php
    // Is in public header but page requires it earlier due to redirecting if the id doesn't exist and
    // the page's title is reliant on the id
    if(isset($_GET['searchquery'])){
        $search = $_GET['searchquery'];
        redirect_to(url_for('/search.php?search=' . h(u($search))));
    }

    if(!isset($_GET['prod_id'])){
        redirect_to(url_for('index.php'));
    }
    $id = $_GET['prod_id'];

    $product = find_product_by_id($id);
    $category = find_category_by_id($product['categoryID']);
    $review_set = find_reviews_by_product_id($product['id']);
    if($product['visible'] === false || $category['visible'] == false || !$product){
        redirect_to(url_for('/index.php'));
    }

    // If add to cart was pressed, add to the session array
    if(is_post_request()){
        $amount = $_POST['amount'];

        // Item is already in cart - add the amount with existing
        if(array_key_exists($id, $_SESSION['cart'])){
            $_SESSION['cart'][$id] += $amount;
        }
        // New item
        else{
            $_SESSION['cart'] += array($id => $amount);
        }

        $_SESSION['status'] = "Product was successfully added to your cart.";
        redirect_to(url_for('/product.php?prod_id=' . h(u($id))));
    }

    $flag = 0; // Flag variable to flag if reviews were found
    $page_title = $product['name'];
    $amount = 1;

    // Errors from manage_review.php
    if(isset($_SESSION['errors'])){
        $errors = $_SESSION['errors'];
        unset($_SESSION['errors']);
    }
?>

<?php include(SHARED_PATH . '/public_header.php') ?>
        <div id="page">
            <?php echo display_session_message(); ?>

            <!-- Dynamic product info -->
            <?php 
                $product = find_product_by_id($id);
                echo "<h1>" . $product['name'] . "</h1>";
            ?> 
            <img src="<?php echo url_for('/images/' . h(u($product['imageRef'])));?>" alt="<?php echo $product['name']?>" /><br /><br />
            <?php echo display_errors($errors); ?>

            <p><b>$<?php echo $product['price'];?></b></p>
            <p>
                <?php $allowed_tags = '<div><img><h1><h2><p><br><ul><li>'; ?>
                <?php echo strip_tags($product['description'], $allowed_tags); ?>
            </p>
            
            <form action="<?php echo url_for('/product.php?prod_id=' . h(u($id))); ?>" method="post">
                <div id="total">
                    <p>In Stock: <?php echo $product['stock']; ?></p>
                    <label for="amount">Amount</label>
                    <input type="number" name="amount" value="<?php echo h($amount)?>" min="1" max="<?php echo h($product['stock']);?>" /><br /><br />
                <?php 
                    if(!isset($_SESSION['user_id'])){
                        echo "\tYou must be logged in as a store user to add products to your cart!";
                    } 
                    else if($product['stock'] > 0){ 
                ?>

                    <input type="submit" name="addToCart" value="Add to Cart" />
                <?php 
                    } 
                    else {
                        echo "\tOut of Stock! Check back soon.";
                    } 
                ?>

                </div>
            </form>

            <!-- Review content -->
            <h2>Reviews</h2>
            <p>Sorted by most recent. If you feel a review is irrelevant to the product, please flag it and we'll take a look at it.</p>

            <dl>
            <?php while($review = mysqli_fetch_assoc($review_set)) { 
                $user = find_user_by_id($review['userID']);
                $flag = 1;
            ?>

                <!-- Review per user -->
                <dt class="review"><?php echo $review['title'];?></dt>
                <dd class="rating"><?php echo $review['rating'] . "/5.0"; ?></dd>
                <dd><?php echo $review['reviewMade']; ?> </dd>
                <dd><?php echo $user['userID']?></dd>
                <br />
                <dd><?php echo $review['contents'];?></dd>

                <dd>
                <?php if($review['flagged'] == 0 && $user['id'] != $_SESSION['user_id']){?>
                    
                    <!-- Flag review if irrelevant -->
                    <form action=<?php echo url_for("/manage_review.php?prod_id=" . h(u($id)) . "&review_id=" . h(u($review['id']))); ?> method="post">
                        <input type="submit" name="submit" value="Flag Review" />
                    </form>
                <?php }
                else if($review['flagged'] == 1 && $review['reviewed'] == 0){
                    echo "<b>Flagged for review</b>";
                };
                ?>

                </dd>

                <?php if($review['reviewed'] == 1 && $review['flagged'] == 1){
                    echo "<dd><b>Reviewed and acceptable</b></dd>";
                };
                ?>

                <br />
            <?php } ?>

            <?php 
                if($flag === 0){
                echo "\t<dd>No reviews available. Check back soon!<dd>";
            }
            ?>

            </dl>

            <!-- Leaving reviews - will be sent to a separate php page due to this one already used to add to cart -->
            <h2>Want to leave a review?</h2>
            <?php 
                if(is_user_logged_in()){
                    $review = [];
                    $review['userID'] = $_SESSION['user_id'];
                    $review['productID'] = $id;
                    $review['title'] = '';
                    $review['contents'] = '';
                    $review['rating'] = 0.0;
            ?>

            <!-- Submitting review -->
            <form action=<?php echo url_for("/manage_review.php?prod_id=" . h(u($id))); ?> method="post">
                Rating: <br />
                <input type="number" name="rating" min="0" max="5" step="0.5" value="<?php echo h($review['rating']); ?>"/></dd><br /><br />
                Review Title:<br />
                <input type="text" name="title" value="<?php echo h($review['title']); ?>"/><br /><br />
                Review Contents:<br />
                <textarea name="contents" cols="60" rows="20"><?php echo h($review['contents']); ?></textarea><br /><br />
                <input type="submit" name="submit" value="Submit Review" />
            </form>
        
            <br />

            <?php 
                }
                else{
                    echo "<p>You must be logged in as a store user to leave a review.</p>";
                } 
            ?>

        </div>

<?php include(SHARED_PATH . '/public_footer.php') ?>