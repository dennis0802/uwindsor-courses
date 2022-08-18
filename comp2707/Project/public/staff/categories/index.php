<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Category Management'; 
    $category_set = find_all_categories();
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <!-- Options for staff to use -->
        <div id="content">
            <h1>Categories</h1>

            <p>Products can be managed by viewing a category.</p>
            <div class="actions">
                <a href="<?php echo url_for('/staff/categories/new.php'); ?>">Create New Category</a>
            </div>

            <table class="list">
                <tr>    
                    <th>ID</th>
                    <th>Category Name</th>
                    <th>Position</th>
                    <th>Total Products</th>
                    <th>Total Purchases</th>
                    <th>Visible</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                    <th>&nbsp;</th>
                </tr>

            <?php while($category = mysqli_fetch_assoc($category_set)) { ?>
                <?php $count = count_products_by_category_id($category['id']); ?>

                <tr>
                    <td><?php echo h($category['id']); ?></td>
                    <td><?php echo h($category['catName']); ?></td>
                    <td><?php echo h($category['position']); ?></td>
                    <td><?php echo h($count); ?></td>
                    <td><?php echo h($category['totalPurchases']); ?></td>
                    <td><?php echo h($category['visible'] == 1 ? 'true' : 'false'); ?></td>
                    <td><a class="action" href="<?php echo url_for('/staff/categories/show.php?id=' . h(u($category['id']))) ?>">View</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/categories/edit.php?id=' . h(u($category['id']))) ?>">Edit</a></td>
                    <td><a class="action" href="<?php echo url_for('/staff/categories/delete.php?id=' . h(u($category['id']))) ?>">Delete</a></td>
                </tr>
                <?php } ?>

            </table>

            <?php
                mysqli_free_result($category_set);
            ?>
            
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>