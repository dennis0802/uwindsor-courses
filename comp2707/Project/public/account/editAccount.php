<?php require_once('../../private/initialize.php') ?>
<?php
    require_user_login();
    
    // Is in public header but page requires it earlier due to redirecting if the id doesn't exist and
    // the page's title is reliant on the id
    if(isset($_GET['searchquery'])){
        $search = $_GET['searchquery'];
        redirect_to(url_for('/search.php?search=' . h(u($search))));
    }

    if(!isset($_GET['id'])){
        redirect_to(url_for('/account/index.php'));
    }
    $id = $_GET['id'];

    $page_title = 'Edit User'; 

    if(is_post_request()){
        $user = [];
        $user['id'] = $id;
        $user['userID'] = $_POST['userID'] ?? '';
        $user['email'] = $_POST['email'] ?? '';
        $user['fname'] = $_POST['fname'] ?? '';
        $user['lname'] = $_POST['lname'] ?? '';
        $user['birthday'] = $_POST['birthday'] ?? '';
        $user['address'] = $_POST['address'] ?? '';
        $user['postCode'] = $_POST['postCode'] ?? '';
        $user['city'] = $_POST['city'] ?? '';
        $user['country'] = $_POST['country'] ?? '';
        $user['password'] = $_POST['password'] ?? '';
        $user['confirmPass'] = $_POST['confirmPass'] ?? '';
        $user['securityQuestion'] = $_POST['securityQuestion'] ?? '';
        $user['answer'] = $_POST['answer'] ?? '';

        $result=update_user($user);

        // If account is succesfully created, also log the user in
        if($result === true){
            $_SESSION['status'] = "Account successfully updated.";
            redirect_to(url_for('/account/index.php'));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $user = find_user_by_id($id);
    }
?>

<?php include(SHARED_PATH . '/public_header.php'); ?>
        <!-- Page contents -->
        <div id="page">
            <h1>Edit Account</h1>
            <?php echo display_errors($errors); ?>
            
            <a href="<?php echo url_for('/account/index.php'); ?>">&laquo; Back to Account</a>
            <form action="<?php echo url_for('account/editAccount.php?id=' . h(u($id))); ?>" method="post">
                <dl>
                    <dt>User ID</dt>
                    <dd><input type="text" name="userID" value="<?php echo h(u($user['userID'])); ?>"/></dd>
                </dl>
                <dl>
                    <dt>Email</dt>
                    <dd><input type="text" name="email" value="<?php echo h(($user['email'])); ?>"/></dd>
                </dl>
                <dl>
                    <dt>First Name</dt>
                    <dd><input type="text" name="fname" value="<?php echo h(u($user['fname'])); ?>"/></dd>
                </dl>
                <dl>
                    <dt>Last Name</dt>
                    <dd><input type="text" name="lname" value="<?php echo h($user['lname']); ?>"/></dd>
                </dl>
                <dl>
                    <dt>Birthday</dt>
                    <dd><input type="date" name="birthday" value="<?php echo h($user['birthday']); ?>"/></dd>
                </dl>
                <dl>
                    <dt>Address</dt>
                    <dd><input type="text" name="address" value="<?php echo h($user['address']); ?>"/></dd>
                </dl>
                <dl>
                    <dt>Postal Code</dt>
                    <dd><input type="text" name="postCode" value="<?php echo h($user['postCode']); ?>"/></dd>
                </dl>
                <dl>
                    <dt>City</dt>
                    <dd><input type="text" name="city" value="<?php echo h($user['city']); ?>"/></dd>
                </dl>
                <dl>
                    <dt>Country</dt>
                    <dd><input type="text" name="country" value="<?php echo h($user['country']); ?>"/></dd>
                </dl>
                <dl>
                    <dt>Password</dt>
                    <dd><input type="password" name="password" value=""/></dd>
                </dl>
                <dl>
                    <dt>Confirm Password</dt>
                    <dd><input type="password" name="confirmPass" value=""/></dd>
                </dl>
                <dl>
                    <dt>Security Question</dt>
                    <dd>Your current security question is: <?php echo $user['securityQuestion'];?></dd>
                    <select name="securityQuestion">
                        <option value="Select a question..." disabled selected>Select a question...</option>
                        <option value="The name of your first pet?">The name of your first pet?</option>
                        <option value="Favourite teacher/professor?">Favourite teacher/professor?</option>
                        <option value="The first concert you attended?">The first concert you attended?</option>
                        <option value="The make and model of your first car?">The make and model of your first car?</option>
                        <option value="Who was your first roommate?">Who was your first roommate?</option>
                        <option value="The first book you read?">The first book you read?</option>
                        <option value="Month and year of your graduation?">Month and year of your graduation?</option>
                        <option value="In what city did your mother and father meet?">In what city did your mother and father meet?</option>
                    </select>
                </dl>
                <dl>
                    <dt>Answer</dt>
                    <dd><input type="text" name="answer" value=""/></dd>
                </dl>

                <p>
                    UserIDs should be between 4-25 characters long and include at least one number.
                    No special characters allowed.
                </p>
                <p>
                    Passwords should be at least 12 characters and include at least one uppercase
                    letter, lowercase letter, number, and symbol. Editing your password is
                    <b>OPTIONAL.</b>
                </p>
                <p>
                    Please remember your answer to the security question in case you forget your password.
                    Without that, you will be unable to retrieve your password. Your answers will be
                    encrypted. Editing your security question and answer is <b>OPTIONAL.</b>
                </p>

                <div id="operations">
                    <input type="submit" value="Edit Account" />
                </div>
            </form>
        </div>

<?php include(SHARED_PATH . '/public_footer.php'); ?>