<?php require_once('../private/initialize.php') ?>
<?php
    $search_term = $_GET['search'] ?? 'blank';
    if($search_term == ''){
        $search_term = '\'\'';
    }

    $page_title = "Search";
    $product_set = find_products_by_search($search_term, ['visible' => true]);
    $count = mysqli_num_rows($product_set);
?>

<?php include(SHARED_PATH . '/public_header.php') ?>
        <!-- Page contents -->
        <div id="page">
            <h1>Search Results for: <?php echo h($search_term) ?></h1>
            <p><?php echo h($count) ?> results found.</p>
            <table>
                <?php
                    while($product = mysqli_fetch_assoc($product_set)){
                ?>
                
                    <tr>
                        <td>
                            <a href="<?php echo url_for('/product.php?prod_id=' . h(u($product['id'])));?>">
                                <img src="<?php echo url_for('/images/' . h(u($product['imageRef'])));?>" alt="<?php echo $product['name']?>"/>
                            </a>
                            <br />
                            <p><b><?php echo h($product['name']); ?></b></p>
                            <p><?php echo "$" . h($product['price']); ?></p>
                        </td>
                    </tr>
                <?php
                    }
                ?>

            </table>
            <br /><br />
        </div>

<?php include(SHARED_PATH . '/public_footer.php') ?>
