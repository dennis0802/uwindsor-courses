<?php 
    require_once('../../../private/initialize.php');
    require_admin_login();
    $page_title = 'Edit Category'; 

    if(!isset($_GET['id'])){
        redirect_to(url_for('/staff/subjects/index.php'));
    }
    $id = $_GET['id'];

    $category = [];

    if(is_post_request()){
        $category['id'] = $id;
        $category['catName'] = $_POST['catName'] ?? '';
        $category['position'] = $_POST['position'] ?? '';
        $category['visible'] = $_POST['visible'] ?? '';
        $category['description'] = $_POST['description'] ?? '';

        $result=update_category($category);

        if($result === true){
            $_SESSION['status'] = "The category was updated successfully.";
            redirect_to(url_for('/staff/categories/show.php?id=' . $id));
        }
        else{
            $errors = $result;
        }
    }
    else{
        $category = find_category_by_id($id);
    }
    $category_count = count_categories();
?>

<?php include(SHARED_PATH . '/staff_header.php'); ?>
        <div id="content">
            <br />
            <a href="<?php echo url_for('/staff/categories/index.php'); ?>">&laquo; Back to Categories</a>

            <div>
                <h1>Edit Category</h1>

                <?php echo display_errors($errors); ?>
                <form action="<?php echo url_for('staff/categories/edit.php?id=' . h(u($category['id']))); ?>" method="post">
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
                            <textarea name="description" cols="60" rows="20">
                                <?php echo h($category['description']); ?>
                                
                            </textarea>
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
                        <input type="submit" value="Edit Category" />
                    </div>
                </form>
            </div>
        </div>

<?php include(SHARED_PATH . '/staff_footer.php');?>