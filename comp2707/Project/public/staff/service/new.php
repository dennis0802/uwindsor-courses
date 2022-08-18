<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Create Customer Service Request'; 

    if(is_post_request()){
        $service = [];
        $service['userID'] = $_POST['userID'] ?? '';
        $service['requestMade'] = date("Y-m-d");
        $service['requestLastAction'] = date("Y-m-d");
        $service['requestSubject'] = $_POST['requestSubject'] ?? '';
        $service['requestDetails'] = $_POST['requestDetails'] ?? '';
        $service['requestResponse'] = '';
        $service['resolved'] = 0;

        $result=insert_service($service);

        if($result === true){
            $new_id = mysqli_insert_id($db);
            $_SESSION['status'] = "The service request was added successfully.";
            redirect_to(url_for('/staff/service/show.php?id=' . $new_id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $service = [];
        $service['userID'] = '';
        $service['requestSubject'] = '';
        $service['requestDetails'] = '';
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/service/index.php'); ?>">&laquo; Back to Service Requests</a>

            <div>
                <h1>Create Customer Service Request</h1>

                <?php echo display_errors($errors); ?>
                
                <form action="<?php echo url_for('staff/service/new.php'); ?>" method="post">
                    <dl>
                        <dt>Request from User ID</dt>
                        <dd>
                            <select name="userID">
                                <?php
                                    $user_set = find_all_users();
                                    while($user = mysqli_fetch_assoc($user_set)){
                                        echo "<option value=\"" . h($user['id']) . "\"";
                                        if($service["userID"] == $user['id']){
                                            echo " selected";
                                        }
                                        echo ">" . h($user['userID']) . "</option>";
                                    }
                                ?>
                            </select>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Request Subject</dt>
                        <dd><input type="text" name="requestSubject" value="<?php echo h($service['requestSubject']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Request Details</dt>
                        <dd>                    
                            <textarea name="requestDetails" cols="60" rows="20"><?php echo h($service['requestDetails']); ?></textarea>
                        </dd>
                    </dl>

                    <div id="operations">
                        <input type="submit" value="Create Service Request" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>