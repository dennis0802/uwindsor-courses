<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $id = $_GET['id'] ?? '1';
    $category = find_category_by_id($id);
    $product_set = find_products_by_category_id($id);
    $page_title = 'Show Category';
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <a href="<?php echo url_for('staff/categories/index.php');?>">&laquo; Back to Categories</a>
            <div>
            <h1>Category Name: <?php echo h($category['catName']); ?></h1>
            </div>

            <div>
                <dl>
                    <dt>Category ID</dt>
                    <dd><?php echo h($category['id']); ?></dd>
                </dl>
                <dl>
                    <dt>Position</dt>
                    <dd><?php echo h($category['position']); ?></dd>
                </dl>
                <dl>
                    <dt>Total Purchases</dt>
                    <dd><?php echo h($category['totalPurchases']); ?></dd>
                </dl>

                <dl>
                    <dt>Description</dt>
                    <dd>
                        <textarea name="description" cols="60" rows="10" readonly>
                            <?php echo h($category['description']); ?>

                        </textarea>
                    </dd>
                </dl>

                <dl>
                    <dt>Visible?</dt>
                    <dd><?php echo h($category['visible'] == 1 ? 'true' : 'false'); ?></dd>
                </dl>
            </div>

            <hr />
            
            <!-- Products in this category -->
            <div>
                <h2>Products</h2>
                
                <div class="actions">
                    <a href="<?php echo url_for('/staff/products/new.php?catID=' . h(u($category['id'])))?>">Create New Product</a>
                </div>

                <table class="list">
                    <tr>
                        <th>ID</th>
                        <th>Product Name</th>
                        <th>Price</th>
                        <th>Stock</th>
                        <th>Purchased</th>
                        <th>Position</th>
                        <th>Visible</th>
                        <th>&nbsp;</th>
                        <th>&nbsp;</th>
                        <th>&nbsp;</th>
                    </tr>

                    <?php while($product = mysqli_fetch_assoc($product_set)){ ?>
                    <?php $category = find_category_by_id($product['categoryID']); ?>

                    <tr>
                        <td><?php echo $product['id']; ?></td>
                        <td><?php echo $product['name']; ?></td>
                        <td><?php echo '$' . $product['price']; ?></td>
                        <td><?php echo $product['stock']; ?></td>
                        <td><?php echo $product['purchased']; ?></td>
                        <td><?php echo $product['position']; ?></td>
                        <td><?php echo $product['visible'] == 1 ? 'true' : 'false'; ?></td>
                        <td><a class="action" href="<?php echo url_for('/staff/products/show.php?id=' . h(u($product['id']))) ?>">View</a></td>
                        <td><a class="action" href="<?php echo url_for('/staff/products/edit.php?id=' . h(u($product['id']))) ?>">Edit</a></td>
                        <td><a class="action" href="<?php echo url_for('/staff/products/delete.php?id=' . h(u($product['id']))) ?>">Delete</a></td>
                    </tr>
                    <?php } ?>
                    
                </table>
                <br />
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>