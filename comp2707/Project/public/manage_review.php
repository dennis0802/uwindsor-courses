<?php
    // This will only be used to process the review submission
    require_once('../private/initialize.php');
    require_user_login();

    if(is_post_request()){
        // Review added
        if(isset($_GET['prod_id']) && !isset($_GET['review_id'])){
            $prod_id = $_GET['prod_id'];
            
            $review = [];
            $review['userID'] = $_SESSION['user_id'] ?? '';
            $review['productID'] = $prod_id ?? '';
            $review['rating'] = $_POST['rating'] ?? '';
            $review['title'] = $_POST['title'] ?? '';
            $review['contents'] = $_POST['contents'] ?? '';
            $review['reviewMade'] = date("Y-m-d");
            $review['flagged'] = 0;
            $review['reviewed'] = 0;

            $result=insert_review($review);

            if($result === true){
                $_SESSION['status'] = "The review was added successfully.";
                redirect_to(url_for('/product.php?prod_id=' . h(u($prod_id))));
            }
            else{
                $_SESSION['errors'] = $result;
                redirect_to(url_for('/product.php?prod_id=' . h(u($prod_id))));
            }
        }
        // Review flagged
        elseif(isset($_GET['prod_id']) && isset($_GET['review_id'])){
            $prod_id = $_GET['prod_id'];
            $id = $_GET['review_id'];
            $cur_review = find_review_by_id($id);

            $review = [];
            $review['id'] = $id ?? '';
            $review['userID'] = $_SESSION['user_id'] ?? '';
            $review['productID'] = $prod_id ?? '';
            $review['rating'] = $cur_review['rating'] ?? '';
            $review['title'] = $cur_review['title'] ?? '';
            $review['contents'] = $cur_review['contents'] ?? '';
            $review['reviewMade'] = date("Y-m-d");
            $review['flagged'] = 1;
            $review['reviewed'] = 0;

            $result=update_review($review);

            if($result === true){
                $_SESSION['status'] = "Review flagged.";
                redirect_to(url_for('/product.php?prod_id=' . h(u($prod_id))));
            }
            else{
                $_SESSION['errors'] = $result;
                redirect_to(url_for('/product.php?prod_id=' . h(u($prod_id))));
            }
        }
        // Posted but no get
        else{
            redirect_to(url_for('/index.php'));
        }
    }
    // Not a post
    else{
        redirect_to(url_for('/index.php'));
    }
?>