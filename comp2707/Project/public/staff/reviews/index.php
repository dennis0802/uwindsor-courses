<?php 
    require_once('../../../private/initialize.php');
    $page_title = 'Review Management'; 
    require_admin_login();
    $review_set = find_all_reviews();
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <!-- Options for staff to use -->
        <div id="content">
            <h1>Reviews</h1>

            <p>Please use this only if users are unable to make a review on their own.</p>
            <div class="actions">
                <a href="<?php echo url_for('/staff/reviews/new.php'); ?>">Create New Review</a>
            </div>

            <table class="list">
                <tr>    
                    <th>ID</th>
                    <th>User ID</th>
                    <th>Product Name</th>
                    <th>Review Title</th>
                    <th>Rating (#/5)</th>
                    <th>Review Made</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                </tr>

            <?php while($review = mysqli_fetch_assoc($review_set)) { ?>
                
                <tr>
                    <?php 
                        $user = find_user_by_id($review['userID']);
                        $product = find_product_by_id($review['productID']);
                    ?>

                    <td><?php echo h($review['id']); ?></td>
                    <td><?php echo h($user['userID']); ?></td>
                    <td><?php echo h($product['name']); ?></td>
                    <td><?php echo h($review['title']); ?></td>
                    <td><?php echo h($review['rating']); ?></td>
                    <td><?php echo h($review['reviewMade']); ?></td>
                    <td><a class="action" href="<?php echo url_for('/staff/reviews/show.php?id=' . h(u($review['id']))) ?>">View</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/reviews/edit.php?id=' . h(u($review['id']))) ?>">Edit</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/reviews/delete.php?id=' . h(u($review['id']))) ?>">Delete</a></td>
                </tr>
                <?php } ?>

            </table>

            <?php
                mysqli_free_result($review_set);
            ?>
            
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>