<!--
    Public Side
    Developer: Dennis Dao
    Date: July 18, 2022
    v1.0
    Note: early start to experiment with page aesthetics and structure before building
-->

<?php
    $current_id = '';
    $search = '';
    
    if(isset($_GET['searchquery'])){
        $search = $_GET['searchquery'];
        redirect_to(url_for('/search.php?search=' . h(u($search))));
    }
    else if(isset($_GET['id'])){
        $current_id = $_GET['id']  ?? '';
    }
    else if(isset($_GET['prod_id'])){
        $product = find_product_by_id($_GET['prod_id']);
        $category = find_category_by_id($product['categoryID']);
        $current_id = $category['id'];
    }
    else 

?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <!-- set title to ... - page_title if avaialble -->
        <title>Tabletop Games <?php if(isset($page_title)){ echo '- ' . h($page_title); } ?></title>
        <link rel="stylesheet" media="all" href="<?php echo url_for('/stylesheets/public.css'); ?>" />
        <link rel="icon" type="image/x-icon" href="<?php echo url_for('/images/favicon.ico');?>">

    </head>

    <body>
        <!-- Public header -->
        <header>
            <!-- Header image to homepage -->
            <a href="<?php echo url_for('/index.php')?>">
                <img src="<?php echo url_for('/images/logo.png'); ?>" alt="temp" />
            </a>

            <!-- Login message -->
            <table id="header-fields">
                <tr>
                    <td>
                        <form>
                            <input type="text" name="searchquery" id="search" placeholder="Search..."/>
                            <input type="image" src="<?php echo url_for('\images\search.png')?>" alt="Search"/>
                        </form>
                    </td>
                </tr>
                <tr>
                    <td>
                    <?php 
                        // User is logged in
                        if(is_user_logged_in()){ 
                            echo "\tHello, "?><a href="<?php echo url_for("/account/index.php");?>"><b><?php echo $_SESSION['usernameU'] . "!";?></b></a>
                    <?php 
                        }
                        // Staff logged in
                        elseif(is_admin_logged_in()){ 
                            echo "\tHello, ";?><a href="<?php echo url_for("/staff/index.php");?>"><b><?php echo $_SESSION['usernameA'] . '!';?></b></a>
                    <?php }
                        // No one is logged in 
                        else{ 
                            echo "\tYou are not logged in:";?><a id="login" href="<?php echo url_for("/login_general.php");?>"><b>Login</b></a>        
                    <?php 
                        }
                    ?>

                    </td>
                </tr>
            </table>

            <!-- Horizontal navigation -->
            <div class="scrollmenu">
            <?php 
                $category_set = find_all_categories(['visible' => true]);
                while($category = mysqli_fetch_assoc($category_set)){
                    if($current_id === $category['id']){
                        echo "\n"
            ?>
                <a class="selected" href="<?php echo url_for('/category.php?id=' . $category['id']);?>">
                    <b><?php echo $category['catName'];?></b>
                </a>
            <?php   
                    }
            
                    else{
                        echo "\n"
            ?>
                <a href="<?php echo url_for('/category.php?id=' . $category['id']);?>">
                    <b><?php echo $category['catName'];?></b>
                </a>                           
            <?php   
                    }
                }
            ?>

                <!-- Remaining sections -->
                <a href="<?php echo url_for('/service.php'); ?>"><b>Customer Service</b></a>
                <a href="<?php echo url_for('/account/cart.php'); ?>"><b>Cart</b></a>
            </div>
        </header>

