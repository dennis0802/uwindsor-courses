<?php 
    require_once('../../private/initialize.php');
    
    if(!isset($_GET['id'])){
        redirect_to(url_for("/index.php"));
    }
    $id = $_GET['id'];
    $user = find_user_by_id($id);

    if(is_post_request()){
        $answer = $_POST['answer'];

        // Validations
        if(is_blank($answer)){
            $errors[] = "Answer cannot be blank.";
        }
        else{
            if(password_verify($answer, $user['answer'])){
                $_SESSION['found'] = true;
                redirect_to(url_for("/account/reset_password.php?id=" . h(u($id))));
            }
            else{
                $errors[] = "Wrong answer";
            }
        }
    }


    $page_title = 'Found Account';
?>

<?php include(SHARED_PATH . '/public_header.php'); ?>
        <div id="page">
            <h1>Account Found</h1>
            <?php echo display_errors($errors); ?>
            
            <p>Please enter the answer to your security question:</p>
            <p><?php echo $user['securityQuestion'];?></p>
            
            <form action=<?php echo url_for("/account/found.php?id=" . h(u($id)));?> method="post">
                Answer:<br />
                <input type="text" name="answer" value="" /><br /><br />
                <input type="submit" name="submit" value="Answer Question" />
            </form>
            <br />
        </div>

<?php include(SHARED_PATH . '/public_footer.php'); ?>