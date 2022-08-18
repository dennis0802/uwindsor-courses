<?php require_once('../private/initialize.php') ?>

<?php
    // Is in public header but page requires it earlier due to redirecting if the id doesn't exist and
    // the page's title is reliant on the id
    if(isset($_GET['searchquery'])){
        $search = $_GET['searchquery'];
        redirect_to(url_for('/search.php?search=' . h(u($search))));
    }

    if(!isset($_GET['id'])){
        redirect_to(url_for('index.php'));
    }
    $id = $_GET['id'];

    $category = find_category_by_id($id);
    if($category['visible'] === false || !$category){
        redirect_to(url_for('/index.php'));
    }

    $product_set = find_products_by_category_id($category['id']);
    $page_title = h($category['catName']);
?>

<?php include(SHARED_PATH . '/public_header.php') ?>
        <!-- Page content -->
        <div id="page">
            <?php 
                $category = find_category_by_id($id);
                echo "<h1>" . $category['catName'] . "</h1>\n\t\t\t";
                echo "<p>" . $category['description'] . "</p>";
            ?> 

            <!-- List out products from the category -->
            <table class="list">
                <tr>
                    <th colspan="3">Products</th>
                </tr>
            <?php 
                while($product = mysqli_fetch_assoc($product_set)){
            ?>

                <!-- If product is visible - display it. Otherwise, print an empty space (&nbsp) -->
                <tr>
            <?php 
                if($product['visible']){ ?>

                    <td class='productDisplay'><a href="<?php echo url_for('/product.php?prod_id=' . h(u($product['id'])));?>">
                    <img src="<?php echo url_for('/images/' . h(u($product['imageRef'])));?>" alt="<?php echo $product['name']?>"/><br /><br /></a>
                    <?php echo $product['name'] . "<br /><b>$" . $product['price'] . "</b>"; } else{}?></td>
            <?php 
                        $product = mysqli_fetch_assoc($product_set); 
                        if($product === null){
                            echo "\t\t<td class='productDisplay'>&nbsp;</td>";
                            echo "\n\t\t\t\t\t<td class='productDisplay'>&nbsp;</td>";
                            break;
                        }
                        if($product['visible']){
            ?>

                    <td class='productDisplay'><a href="<?php echo url_for('/product.php?prod_id=' . h(u($product['id'])));?>">
                    <img src="<?php echo url_for('/images/' . h(u($product['imageRef'])));?>" alt="<?php echo $product['name']?>"/><br /><br /></a>
                    <?php echo $product['name'] . "<br /><b>$" . $product['price'] . "</b>"; }?></td>
            <?php 
                        $product = mysqli_fetch_assoc($product_set); 
                        if($product === null){
                            echo "\t\t<td class='productDisplay'>&nbsp;</td>";
                            break;
                        }
                        if($product['visible']){
            ?>
            
                    <td class='productDisplay'><a href="<?php echo url_for('/product.php?prod_id=' . h(u($product['id'])));?>">
                    <img src="<?php echo url_for('/images/' . h(u($product['imageRef'])));?>" alt="<?php echo $product['name']?>"/><br /><br /></a>
                    <?php echo $product['name'] . "<br /><b>$" . $product['price'] . "</b>"; }?></td>
                </tr>
            <?php 
                } 
            ?>

            </table>
            <br />
        </div>

<?php include(SHARED_PATH . '/public_footer.php') ?>