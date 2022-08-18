<?php
    require_once('../../../private/initialize.php');
    require_admin_login();

    if(is_post_request()){
        $product = [];
        $product['catID'] = $_POST['catID'] ?? '';
        $product['prodName'] = $_POST['prodName'] ?? '';
        $product['price'] = $_POST['price'] ?? '';
        $product['stock'] = $_POST['stock'] ?? '';
        $product['purchased'] = 0;
        $product['position'] = $_POST['position'] ?? '';
        $product['visible'] = $_POST['visible'] ?? '';
        $product['description'] = $_POST['description'] ?? '';
        $product['imageRef'] = $_POST['imageRef'] ?? '';

        $result = insert_product($product);
        if($result === true){
            $new_id = mysqli_insert_id($db);
            $_SESSION['status'] = "The product was created successfully.";
            redirect_to(url_for('/staff/products/show.php?id=' . $new_id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $product = [];
        $product['catID'] = $_GET['catID'] ?? '1';
        $product['prodName'] = '';
        $product['price'] = '0.00';
        $product['stock'] = '0';
        $product['purchased'] = '';
        $product['position'] = '';
        $product['description'] = '';
        $product['imageRef'] = '';
        $product['visible'] = '';
    }
    $product_count = count_products_by_category_id($product['catID']) + 1;
    $product["position"] = $product_count;
?>

<?php $page_title = 'Create Product'?>
<?php include(SHARED_PATH . '/staff_header.php');?>

        <div id="content">
            <a href="<?php echo url_for('staff/categories/show.php?id=' . h(u($product['catID'])));?>">&laquo; Back to Category Page</a>

            <div>
                <h1>Create Product</h1>

                <?php echo display_errors($errors); ?>
                <form action="<?php echo url_for('/staff/products/new.php'); ?>" method="post">
                    <dl>
                        <dt>Category</dt>
                        <dd>
                            <select name="catID">
                                <?php
                                    $category_set = find_all_categories();
                                    while($category = mysqli_fetch_assoc($category_set)){
                                        echo "<option value=\"" . h($category['id']) . "\"";
                                        if($product["catID"] == $category['id']){
                                            echo " selected";
                                        }
                                        echo ">" . h($category['catName']) . "</option>";
                                    }
                                ?>
                            </select>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Product Name</dt>
                        <dd><input type="text" name="prodName" value="<?php echo h($product['prodName']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Price ($)</dt>
                        <dd><input type="number" min="0.00" step="0.01" name="price" value="<?php echo h($product['price']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Stock</dt>
                        <dd><input type="number" min="0" name="stock" value="<?php echo h($product['stock']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Position</dt>
                        <dd>
                            <select name="position">
                                <?php
                                    for($i = 1; $i <= $product_count; $i++){
                                        echo "<option value=\"{$i}\"";
                                        if($product["position"] == $i){
                                            echo " selected";
                                        }
                                        echo ">{$i}</option>\n\t\t\t\t\t\t\t\t";
                                    }
                                ?>
                            </select>
                        </dd>
                    </dl>

                    <dl>
                        <dt>Description</dt>
                        <dd>                    
                            <textarea name="description" cols="60" rows="20"><?php echo h($product['description']); ?></textarea>
                        </dd>
                    </dl>

                    <dl>
                        <dt>Image Reference</dt>
                        <dd>Please ensure the file exists in the web server and has the appropriate extension</dd>
                        <dd><input type="text" name="imageRef" value="<?php echo h($product['imageRef']); ?>"/></dd>
                    </dl>

                    <dl>
                        <dt>Visible</dt>
                        <dd>
                            <input type="hidden" name="visible" value="0" />
                            <input type="checkbox" name="visible" value="1" <?php if($product['visible'] == "1"){echo " checked";}?>/>
                        </dd>
                    </dl>
                    <div id="operations">
                        <input type="submit" value="Create Product" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php'); ?>