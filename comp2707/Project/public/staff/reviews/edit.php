<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Create Review'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/service/index.php'));
    }
    $id = $_GET['id'];

    if(is_post_request()){
        $review = [];
        $review['id'] = $id;
        $review['userID'] = $_POST['userID'] ?? '';
        $review['productID'] = $_POST['productID'] ?? '';
        $review['title'] = $_POST['title'] ?? '';
        $review['rating'] = $_POST['rating'] ?? '';
        $review['contents'] = $_POST['contents'] ?? '';
        $review['reviewMade'] = date("Y-m-d");
        $review['flagged'] = $_POST['flagged'] ?? '';
        $review['reviewed'] = $_POST['reviewed'] ?? '';

        $result=update_review($review);

        if($result === true){
            $_SESSION['status'] = "The review was updated successfully.";
            redirect_to(url_for('/staff/reviews/show.php?id=' . $id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $review = find_review_by_id($id);
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/reviews/index.php'); ?>">&laquo; Back to Reviews</a>

            <div>
                <h1>Create Review</h1>

                <?php echo display_errors($errors); ?>
                
                <form action="<?php echo url_for('staff/reviews/edit.php?id=' . h(u($id))); ?>" method="post">
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
                    <dl>
                        <dt>Flagged?</dt>
                        <input type="hidden" name="flagged" value="0" />
                        <input type="checkbox" name="flagged" value="1" <?php if($review['flagged'] == "1"){echo " checked";}?>/>
                    </dl>
                    <dl>
                        <dt>Reviewed?</dt>
                        <input type="hidden" name="reviewed" value="0" />
                        <input type="checkbox" name="reviewed" value="1" <?php if($review['reviewed'] == "1"){echo " checked";}?>/>
                    </dl>

                    <div id="operations">
                        <input type="submit" value="Edit Review" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>