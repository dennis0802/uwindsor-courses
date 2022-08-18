<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Create Category'; 
    $category = [];

    if(is_post_request()){
        $category['catName'] = $_POST['catName'] ?? '';
        $category['position'] = $_POST['position'] ?? '';
        $category['visible'] = $_POST['visible'] ?? '';
        $category['description'] = $_POST['description'] ?? '';

        $result=insert_category($category);

        if($result === true){
            $new_id = mysqli_insert_id($db);
            $_SESSION['status'] = "The category was added successfully.";
            redirect_to(url_for('/staff/categories/show.php?id=' . $new_id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $category['catName'] = '';
        $category['visible'] = '';
        $category['description'] = '';
    }

    $category_count = count_categories() + 1;
    $category["position"] = $category_count;
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/categories/index.php'); ?>">&laquo; Back to Categories</a>

            <div>
                <h1>Create Category</h1>

                <?php echo display_errors($errors); ?>

                <form action="<?php echo url_for('staff/categories/new.php'); ?>" method="post">
                    <dl>
                        <dt>Category Name</dt>
                        <dd><input type="text" name="catName" value="<?php echo h($category['catName']); ?>"/></dd>
                    </dl>
                    <dl>
                        <dt>Position</dt>
                        <dd>                    
                            <select name="position">
                                <?php
                                for($i = 1; $i <= $category_count; $i++){
                                    echo "<option value=\"{$i}\"";
                                    if($category["position"] == $i){
                                    echo " selected";
                                    }
                                    echo ">{$i}</option>\n\t\t\t\t\t\t\t\t";
                                }
                                ?>
                                
                            </select>
                        </dd>
                    </dl>

                    <dl>
                        <dt>Description</dt>
                        <dd>                    
                            <textarea name="description" cols="60" rows="20"><?php echo h($category['description']); ?></textarea>
                        </dd>
                    </dl>

                    <dl>
                        <dt>Visible</dt>
                        <dd>
                            <input type="hidden" name="visible" value="0" />
                            <input type="checkbox" name="visible" value="1" <?php if($category['visible'] == "1"){echo " checked";}?>/>
                        </dd>
                    </dl>

                    <div id="operations">
                        <input type="submit" value="Create Category" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>