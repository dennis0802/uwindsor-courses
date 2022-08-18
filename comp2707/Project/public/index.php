<!-- All images will be fixed later and referenced properly-->
<?php require_once('../private/initialize.php') ?>
<?php include(SHARED_PATH . '/public_header.php') ?>
        <div id="page">
            <?php echo display_session_message(); ?>
            <!-- Photo by <a href="https://unsplash.com/@karthikb351?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">
                Karthik Balakrishnan</a> on 
                <a href="https://unsplash.com/s/photos/board-games?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">
            Unsplash</a>-->
            <img  class="homepage" src="<?php echo url_for("images/boardGame.jpg");?>" alt="Board game on table" />
            <p class="homepage">
                At Tabletop Games, we provide products to help support your tabletop gaming hobbies. Give us a chance,
                and we'll show that our deck of games has what you're looking for!
            </p>

            <div class="display-blocks">
                <div class="display">
                    <img src="<?php echo url_for("images/monopoly.jpg");?>" alt="Monopoly" />
                    <h1>First Visit?</h1>
                    <!-- Photo by <a href="https://unsplash.com/es/@travelkat74?utm_source=unsplash&utm_medium=referral&utm_
                        content=creditCopyText">Kathy Marsh</a> on 
                        <a href="https://unsplash.com/s/photos/board-games?utm_source=unsplash&utm_medium=referral&utm_
                        content=creditCopyText">Unsplash</a>-->
                    <p>
                        First time visiting this site? Welcome! Before you can start adding products to purchase, 
                        you will need an account with us to access a shopping cart.
                    </p>
                    <p><a href="<?php echo url_for("account/register.php");?>">Register for an account...</a> </p>
                </div>

                <div class="display">
                    <!--Photo by <a href="https://unsplash.com/@motivesandplaces?utm_source=unsplash&utm_medium=referral&utm_content=
                                creditCopyText">Aksel Fristrup</a> on <a href="https://unsplash.com/s/photos/board-games?utm_source=
                                unsplash&utm_medium=referral&utm_content=creditCopyText">Unsplash</a>-->
                    <img src="<?php echo url_for("images/catan.jpg");?>" width="300px" height ="250px" alt="Catan" />
                    <h1>Categories</h1>
                    <p>Begin exploring our categories to find an assortment of products you may enjoy. </p>
                    <?php 
                        $category_set = find_all_categories(['visible' => true]); 
                        $firstID = mysqli_fetch_assoc($category_set)['id'];
                        mysqli_free_result($category_set);
                    ?>
                    <p><a href="<?php echo url_for("category.php?id=" . h(u($firstID))); ?>">Start browsing...</a></p>
                </div>

                <div class="display">
                    <!--Photo by <a href="https://unsplash.com/@nci?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">
                        National Cancer Institute</a> on <a href="https://unsplash.com/s/photos/board-games?utm_source=unsplash&utm_
                        medium=referral&utm_content=creditCopyText">Unsplash</a>-->
                    <img src="<?php echo url_for("images/family.jpg");?>" alt="Family" />
                    <h1>Need Help?</h1>
                    <p>
                        Need some help? Head over to our customer service request page and we'll see what we can do for you!
                        Requests will be responded as soon as possible during business days.
                    </p>
                    <p><a href="<?php echo url_for('/service.php');?>">Get help...</a> </p>
                </div>
            </div>

            <br />

            <div class="display-blocks">
                <!-- The 3 recently added products if they exist -->
                <h1 class="homepage">Recently Added</h1>
                <?php 
                    $product_set = find_recent_three_products(['visible' => true]);
                    for($i = 0; $i < 3; $i++){
                        $product = mysqli_fetch_assoc($product_set);
                        if($product === null){
                            echo "Coming soon!";
                            break;
                        }
                ?>

                    <div class="display">
                        <a href="<?php echo url_for('/product.php?prod_id=' . $product['id']);?>">
                            <img src="<?php echo url_for("images/" . $product['imageRef']);?>" alt="<?php echo $product['name'];?>" />
                        </a>
                        <h4><?php echo $product['name'];?></h4>
                        <p><b><?php echo "$" . $product['price'];?></b></p>
                    </div>
                <?php
                    }
                ?>

            </div>
        </div>

<?php include(SHARED_PATH . '/public_footer.php') ?>