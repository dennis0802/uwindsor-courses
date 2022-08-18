<?php require_once('../private/initialize.php'); ?>
<?php $page_title = 'Login Selection'; ?>

<?php
    if(is_admin_logged_in()){
        redirect_to(url_for('/staff/index.php'));
    }
    else if(is_user_logged_in()){
        redirect_to(url_for('/account.php'));
    }
?>

<?php include(SHARED_PATH . '/public_header.php');?>

        <!-- Page content -->
        <div id="page">
            <h1>Login Selection</h1>
            <p>Please select to login as staff or store user</p>
            <dl>
                <dt>
                    <b>User Login</b>
                    <dd>
                        <a href="<?php echo url_for('/login_user.php');?>">Login as user</a>
                    </dd>
                    <dd>
                        <a href="<?php echo url_for('/account/register.php'); ?>">Register for an account!</a><br />
                    </dd>
                </dt>
                <dt>
                    <b>Staff Login</b>
                    <dd>
                        <a href="<?php echo url_for('/staff/staff_login.php');?>">Login as staff</a>
                    </dd>
                </dt>
            </dl>

            <!-- https://unsplash.com/photos/QuP5RL_E5oE; Alperen Yazgi -->
            <img src="<?php echo url_for('/images/dice.jpg'); ?>" alt="dice"/>
            <br /><br />
        </div>
<?php include(SHARED_PATH . '/public_footer.php');?>