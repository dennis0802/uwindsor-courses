<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $id = $_GET['id'] ?? '1';
    $review = find_review_by_id($id);
    $page_title = 'Show Review';
    $user = find_user_by_id($review['userID']); 
    $product = find_product_by_id($review['productID']);
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('staff/reviews/index.php');?>">&laquo; Back to Reviews Page</a>
            <div>
                <h1>Review for: <?php echo h($product['name'])?></h1>
            </div>

            <div>
                <dl>
                    <dt>ID</dt>
                    <dd><?php echo h($review['id']); ?></dd>
                </dl>
                <dl>
                    <dt>User ID</dt>
                    <dd><?php echo h($user['userID']); ?></dd>
                </dl>
                <dl>
                    <dt>Review Made</dt>
                    <dd><?php echo h($review['reviewMade']); ?></dd>
                </dl>
                <dl>
                    <dt>Review Title</dt>
                    <dd><?php echo h($review['title']); ?></dd>
                </dl>
                <dl>
                    <dt>Rating</dt>
                    <dd><?php echo h($review['rating']) . "/5.0"; ?></dd>
                </dl>
                <dl>
                    <dt>Review Contents</dt>
                    <dd>
                        <textarea name="contents" cols="60" rows="10" readonly>
                            <?php echo h($review['contents']); ?>

                        </textarea>
                    </dd>
                </dl>
                <dl>
                    <dt>Flagged?</dt>
                    <dd><?php echo h($review['flagged'] == 1 ? 'flagged' : 'unflagged'); ?></dd>
                </dl>
                <dl>
                    <dt>Reviewed?</dt>
                    <dd><?php echo h($review['reviewed'] == 1 ? 'reviewed' : 'unreviewed'); ?></dd>
                </dl>

            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>