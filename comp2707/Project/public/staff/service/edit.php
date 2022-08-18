<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Edit Customer Service Request'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/service/index.php'));
    }
    $id = $_GET['id'];

    if(is_post_request()){
        $service = [];
        $service['id'] = $id;
        $service['userID'] = $_POST['userID'] ?? '';
        $service['requestLastAction'] = date("Y-m-d");
        $service['requestSubject'] = $_POST['requestSubject'];
        $service['requestDetails'] = $_POST['requestDetails'] ?? '';
        $service['requestResponse'] = $_POST['requestResponse'] ?? '';
        $service['resolved'] = $_POST['resolved'] ?? '';

        $result=update_service($service);

        if($result === true){
            $_SESSION['status'] = "The service request was edited successfully.";
            redirect_to(url_for('/staff/service/show.php?id=' . $id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $service = find_service_by_id($id);
    }
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/service/index.php'); ?>">&laquo; Back to Service Requests</a>

            <div>
                <h1>Edit Customer Service Request</h1>

                <?php echo display_errors($errors); ?>
                
                <form action="<?php echo url_for('staff/service/edit.php?id=' . h(u($id))); ?>" method="post">
                    <dl>
                        <dt>User ID</dt>
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
                            <textarea name="requestDetails" cols="60" rows="20">
                                <?php echo h($service['requestDetails']); ?>
                            
                            </textarea>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Request Response</dt>
                        <dd>                    
                            <textarea name="requestResponse" cols="60" rows="20">
                                <?php echo h($service['requestResponse']); ?>
                        
                            </textarea>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Resolved?</dt>
                        <input type="hidden" name="resolved" value="0" />
                        <input type="checkbox" name="resolved" value="1" <?php if($service['resolved'] == "1"){echo " checked";}?>/>
                    </dl>

                    <div id="operations">
                        <input type="submit" value="Edit Service Request" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>