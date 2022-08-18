<?php require_once('../private/initialize.php') ?>
<?php
    $page_title = 'Customer Service';

    if(is_post_request()){
        $service = [];
        $service['userID'] = $_SESSION['user_id'] ?? '';
        $service['requestMade'] = date("Y-m-d");
        $service['requestLastAction'] = date("Y-m-d");
        $service['requestSubject'] = $_POST['requestSubject'] ?? '';
        $service['requestDetails'] = $_POST['requestDetails'] ?? '';
        $service['requestResponse'] = '';
        $service['resolved'] = 0;

        $result=insert_service($service);

        if($result === true){
            $new_id = mysqli_insert_id($db);
            $_SESSION['status'] = "The service request was added successfully. Your request has ID#" . $new_id . '.';
            redirect_to(url_for('account/index.php'));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $service = [];
        $service['userID'] = $_SESSION['user_id'] ?? '';
        $service['requestSubject'] = '';
        $service['requestDetails'] = '';
    }
?>

<?php include(SHARED_PATH . '/public_header.php') ?>
        <!-- Page contents -->
        <div id="page">
            <h1>Customer Service</h1>
            <?php echo display_errors($errors); ?><br />
            <!-- Photo by <a href="https://unsplash.com/@bigpotatogames?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">
                Big Potato</a> on <a href="https://unsplash.com/s/photos/board-games?utm_source=unsplash&utm_medium=referral&utm_content=credit
                CopyText">Unsplash</a>-->
        
            <img src="<?php echo url_for("/images/colorbrain.jpg");?>" alt="colorbrain" />
            
            <p>
                Need help with purchasing products or store navigation? Let us know by filling in a request and we'll help
                to the best of our ability!
            </p>

            <?php 
                if(is_user_logged_in()){
            ?>

            <!-- Get userID and password to login as user -->
            <form action="service.php" method="post">
                Request Subject:<br />
                <input type="text" name="requestSubject" value="<?php echo h($service['requestSubject']); ?>"/><br /><br />
                Request Details:<br />
                <textarea name="requestDetails" cols="60" rows="20"><?php echo h($service['requestDetails']); ?></textarea><br /><br />
                <input type="submit" name="submit" value="Submit Request" />
            </form>
        
            <br />

            <?php 
                }
                else{
                    echo "<p>You must be logged in as a store user to fill in a customer service request.</p>";
                } 
            ?>
            
        </div>

<?php include(SHARED_PATH . '/public_footer.php') ?>