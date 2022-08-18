<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Create Review'; 

    if(is_post_request()){
        $review = [];
        $review['userID'] = $_POST['userID'] ?? '';
        $review['productID'] = $_POST['productID'] ?? '';
        $review['rating'] = $_POST['rating'] ?? '';
        $review['title'] = $_POST['title'] ?? '';
        $review['contents'] = $_POST['contents'] ?? '';
        $review['reviewMade'] = date("Y-m-d");
        $review['flagged'] = 0;
        $review['reviewed'] = 0;

        $result=insert_review($review);

        if($result === true){
            $new_id = mysqli_insert_id($db);
            $_SESSION['status'] = "The review was added successfully.";
            redirect_to(url_for('/staff/reviews/show.php?id=' . $new_id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $review = [];
        $review['userID'] = '';
        $review['productID'] = '';
        $review['rating'] = 0.0;
        $review['title'] = '';
        $review['contents'] = '';
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/reviews/index.php'); ?>">&laquo; Back to Reviews</a>

            <div>
                <h1>Create Review</h1>

                <?php echo display_errors($errors); ?>
                
                <form action="<?php echo url_for('staff/reviews/new.php'); ?>" method="post">
                    <dl>
                        <dt>Review from User ID</dt>
                        <dd>
                            <select name="userID">
                                <?php
                                    $user_set = find_all_users();
                                    while($user = mysqli_fetch_assoc($user_set)){
                                        echo "<option value=\"" . h($user['id']) . "\"";
                                        if($review["userID"] == $user['id']){
                                            echo " selected";
                                        }
                                        echo ">" . h($user['userID']) . "</option>\n\t\t\t\t\t\t\t\t";
                                    }
                                ?>

                            </select>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Review for Product</dt>
                        <dd>
                            <select name="productID">
                                <?php
                                    $product_set = find_all_products();
                                    while($product = mysqli_fetch_assoc($product_set)){
                                        echo "<option value=\"" . h($product['id']) . "\"";
                                        if($review["productID"] == $product['id']){
                                            echo " selected";
                                        }
                                        echo ">" . h($product['name']) . "</option>\n\t\t\t\t\t\t\t\t";
                                    }
                                ?>

                            </select>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Review Title</dt>
                        <dd><input type="text" name="title" value="<?php echo h($review['title']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Rating</dt>
                        <dd><input type="number" name="rating" min="0" max="5" step="0.5" value="<?php echo h($review['rating']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Review Contents</dt>
                        <dd>                    
                            <textarea name="contents" cols="60" rows="20"><?php echo h($review['contents']); ?></textarea>
                        </dd>
                    </dl>

                    <div id="operations">
                        <input type="submit" value="Create Review" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>