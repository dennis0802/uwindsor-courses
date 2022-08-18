<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $id = $_GET['id'] ?? '1';
    $product= find_product_by_id($id);
    $category = find_category_by_id($product['categoryID']);
?>

<?php $page_title = 'Show Product'; ?>
<?php include(SHARED_PATH . '/staff_header.php'); ?>

        <div id="content">
            <a href="<?php echo url_for('staff/categories/show.php?id=' . h(u($category['id'])));?>">&laquo; Back to Category Page</a>

            <div>
                <h1>Product: <?php echo h($product['name']); ?></h1>
                <img src="<?php echo url_for('/images/' . h(u($product['imageRef'])));?>" alt= "Image not found" />
                <div>
                    <dl>
                        <dt>Category</dt>
                        <dd><?php echo h($category['catName']); ?></dd>
                    </dl>
                    <dl>
                        <dt>Product Name</dt>
                        <dd><?php echo h($product['name']); ?></dd>
                    </dl>
                    <dl>
                        <dt>Price</dt>
                        <dd><?php echo '$' . h($product['price']); ?></dd>
                    </dl>
                    <dl>
                        <dt>Stock</dt>
                        <dd><?php echo h($product['stock']); ?></dd>
                    </dl>
                    <dl>
                        <dt>Purchased</dt>
                        <dd><?php echo h($product['purchased']); ?></dd>
                    </dl>
                    <dl>
                        <dt>Position</dt>
                        <dd><?php echo h($product['position']); ?></dd>
                    </dl>
                    <dl>
                        <dt>Description</dt>
                        <dd>
                            <textarea name="description" cols="60" rows="10" readonly>
                                <?php echo h($product['description']); ?>
                                
                            </textarea>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Image Reference</dt>
                        <dd>Name: <?php echo h($product['imageRef']); ?></dd>
                    </dl>
                    <dl>
                        <dt>Visibility</dt>
                        <dd><?php echo h($product['visible'] == '1' ? 'true' : 'false'); ?></dd>
                    </dl>
                </div>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php'); ?>