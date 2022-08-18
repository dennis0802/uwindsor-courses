<?php require_once('../../private/initialize.php') ?>
<?php include(SHARED_PATH . '/public_header.php'); ?>

<?php
    require_user_login();

    if(!isset($_GET['id'])){
        redirect_to(url_for('/account/index.php'));
    }
    $id = $_GET['id'];

    if(is_post_request()){
        $currentStatus = find_service_by_id($id)['resolved'];

        $service = [];
        $service['id'] = $id;
        $service['userID'] = $_SESSION['user_id'] ?? '';
        $service['requestLastAction'] = date("Y-m-d");
        $service['requestSubject'] = $_POST['requestSubject'];
        $service['requestDetails'] = $_POST['requestDetails'] ?? '';
        $service['requestResponse'] = $_POST['requestResponse'] ?? '';
        $service['resolved'] = $currentStatus;

        $result=update_service($service);

        if($result === true){
            $_SESSION['status'] = "The service request was edited successfully.";
            redirect_to(url_for('/account/showRequest.php?id=' . $id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $service = find_service_by_id($id);
    }
?>
        <!-- Page contents -->
        <div id="page">
            <br />

            <div>
                <h1>Edit Service Request <?php echo "ID#" . h($service['id']);?></h1>

                <?php 
                    echo display_errors($errors); 
                ?>
                
                <form action="<?php echo url_for('/account/editRequest.php?id=' . h(u($id))); ?>" method="post">
                    <dl>
                        <dt>Request Subject</dt>
                        <dd><input type="text" name="requestSubject" value="<?php echo h($service['requestSubject']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Request Details</dt>
                        <dd>                    
                            <textarea name="requestDetails" cols="60" rows="20">
                                <?php 
                                    echo h($service['requestDetails']); 
                                ?>

                            </textarea>
                        </dd>
                    </dl>
                    <dl>
                        <dt>Request Response</dt>
                        <dd>                    
                            <textarea name="requestResponse" cols="60" rows="20" readonly>
                            <?php 
                                echo h($service['requestResponse']); 
                            ?>
                            
                            </textarea>
                        </dd>
                    </dl>

                    <div id="operations">
                        <input type="submit" value="Edit Service Request" />
                    </div>
                </form>
                <a href="<?php echo url_for('/account/index.php'); ?>">&laquo; Back to Account</a><br /><br />
            </div>
        </div>

<?php include(SHARED_PATH . '/public_footer.php'); ?>