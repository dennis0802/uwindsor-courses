<?php
  /*
   * Developer: Dennis Dao
   * July 18, 2022
   *  v1.0
   * /

   // Various query functions for database communication

  /* Referenced from Kevin Skoglund's PHP with MySQL Essential Training 2 - Build a CMS Course*/
  /* The course was a continuation of A3's course - that was Part 1.
  /* https://www.linkedin.com/learning/php-with-mysql-essential-training-2-build-a-cms*/

    // Insert a staff member
    function insert_staff($staff){
        global $db;

        $errors = validate_staff($staff);
        if(!empty($errors)){
          return $errors;
        }

        // Hash the password to safely store in the database
        $hashed_password = password_hash($staff["password"], PASSWORD_BCRYPT);

        $sql = "INSERT INTO staff ";
        $sql .= "(staffID, email, fname, lname, active, password) ";
        $sql .= "VALUES (";
        $sql .= "'" . db_escape($db, $staff['staffID']) . "',";
        $sql .= "'" . db_escape($db, $staff['email']) . "',";
        $sql .= "'" . db_escape($db, $staff['fname']) . "',";
        $sql .= "'" . db_escape($db, $staff['lname']) . "',";
        $sql .= "'" . db_escape($db, $staff['active']) . "',";
        $sql .= "'" . db_escape($db, $hashed_password) . "'";
        $sql .= ")";

        // Result will be TRUE/FALSE - either query succeeded or failed
        $result = mysqli_query($db, $sql);

        if($result){
            return true;
        }
        else{
            // INSERT failure
            echo mysqli_error($db);
            db_disconnect($db);
            exit;
        }
    }

    // Find staff member by a given ID
    function find_staff_by_id($id){
        global $db;

        $sql = "SELECT * FROM staff ";
        $sql .= "WHERE id='" . db_escape($db, $id) . "' ";
        $sql .= "ORDER BY id ASC ";
        $sql .= "LIMIT 1";
        
        $result = mysqli_query($db, $sql);
        confirm_result_set($result);
  
        $staff = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
  
        return $staff;
    }

    // Find all staff
    function find_all_staff(){
        global $db;

        $sql = "SELECT * FROM staff ";
        $sql .= "ORDER BY id ASC ";

        $result = mysqli_query($db, $sql);
        confirm_result_set($result);
    
        return $result;
    }

    function find_staff_by_staffID($staffID){
      global $db;

      $sql = "SELECT * FROM staff ";
      $sql .= "WHERE staffID='" . db_escape($db, $staffID) . "' ";
      $sql .= "ORDER BY id ASC ";
      $sql .= "LIMIT 1";
      
      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $staff = mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $staff;      
    }

    // Edit a staff member's details
    function update_staff($staff){
        global $db;

        $password_sent = !is_blank($staff['password']);

        $errors = validate_staff($staff, ['password_required' => $password_sent]);
        if(!empty($errors)){
          return $errors;
        }

        $hashed_password = password_hash($staff["password"], PASSWORD_BCRYPT);

        $sql = "UPDATE staff SET ";
        $sql .= "staffID='" . db_escape($db, $staff['staffID']) . "',";
        $sql .= "email='" . db_escape($db, $staff['email']) . "',";
        $sql .= "fname='" . db_escape($db, $staff['fname']) . "',";
        $sql .= "lname='" . db_escape($db, $staff['lname']) . "',";
        if($password_sent){
          $sql .= "password='" . db_escape($db, $hashed_password) . "', ";
        }
        $sql .= "active='" . db_escape($db, $staff['active']) . "'";
        $sql .= "WHERE id='" . db_escape($db, $staff['id']) . "' ";
        $sql .= "LIMIT 1";

        $result = mysqli_query($db, $sql);
        // Result will be true/false
        if($result){
          return true;
        }
        else{
          // UPDATE failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
        }
    }

    // Delete a staff member by id (cannot be the root user)
    function delete_staff($id){
        global $db;

        $sql = "DELETE FROM staff WHERE ";
        $sql .= "id='" . db_escape($db, $id) . "' ";
        $sql .= "LIMIT 1";

        $result = mysqli_query($db, $sql);
        // Result will be true/false
        if($result){
          return true;
        }
        else{
          // DELETE failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
        }
    }

    // User queries
    // Insert a user
    function insert_user($user){
      global $db;

      $errors = validate_user($user);
      if(!empty($errors)){
        return $errors;
      }

      // Hash the password to safely store in the database
      $hashed_password = password_hash($user["password"], PASSWORD_BCRYPT);
      // Hash the answer to safely store
      $hashed_answer = password_hash($user["answer"], PASSWORD_BCRYPT);

      $sql = "INSERT INTO user ";
      $sql .= "(userID, email, fname, lname, birthday, address, city, postCode, country, password, securityQuestion, answer) ";
      $sql .= "VALUES (";
      $sql .= "'" . db_escape($db, $user['userID']) . "',";
      $sql .= "'" . db_escape($db, $user['email']) . "',";
      $sql .= "'" . db_escape($db, $user['fname']) . "',";
      $sql .= "'" . db_escape($db, $user['lname']) . "',";
      $sql .= "'" . db_escape($db, $user['birthday']) . "',";
      $sql .= "'" . db_escape($db, $user['address']) . "',";
      $sql .= "'" . db_escape($db, $user['city']) . "',";
      $sql .= "'" . db_escape($db, $user['postCode']) . "',";
      $sql .= "'" . db_escape($db, $user['country']) . "',";
      $sql .= "'" . db_escape($db, $hashed_password) . "',";
      $sql .= "'" . db_escape($db, $user['securityQuestion']) . "',";
      $sql .= "'" . db_escape($db, $hashed_answer) . "'";
      $sql .= ")";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Find a user by an ID
    function find_user_by_id($id){
      global $db;

      $sql = "SELECT * FROM user ";
      $sql .= "WHERE id='" . db_escape($db, $id) . "' ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $user = mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $user;
    }

    function find_user_by_userID($userID){
      global $db;

      $sql = "SELECT * FROM user ";
      $sql .= "WHERE userID='" . db_escape($db, $userID) . "' ";
      $sql .= "ORDER BY id ASC ";
      $sql .= "LIMIT 1";
      
      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $user = mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $user;      
    }

    function find_user_by_email($email){
      global $db;

      $sql = "SELECT * FROM user ";
      $sql .= "WHERE email='" . db_escape($db, $email) . "' ";
      $sql .= "ORDER BY id ASC ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);
      $user = mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $user;   
    }

    // Find all users
    function find_all_users(){
      global $db;

      $sql = "SELECT * FROM user ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);
  
      return $result;
    }

    // Edit a user's details (password and answer optional)
    function update_user($user){
      global $db;

      $password_sent = !is_blank($user['password']) || !is_blank($user['confirmPass']);
      $answer_sent = !is_blank($user['answer']);
      $question_sent = !is_blank($user['securityQuestion']);

      $errors = validate_user($user, ['password_required' => $password_sent, 'answer_required' => $answer_sent, 'question_required' => $question_sent]);
      
      if(!empty($errors)){
        return $errors;
      }

      $hashed_password = password_hash($user["password"], PASSWORD_BCRYPT);
      $hashed_answer = password_hash($user["answer"], PASSWORD_BCRYPT);

      $sql = "UPDATE user SET ";
      $sql .= "userID='" . db_escape($db, $user['userID']) . "',";
      $sql .= "email='" . db_escape($db, $user['email']) . "',";
      $sql .= "fname='" . db_escape($db, $user['fname']) . "',";
      $sql .= "lname='" . db_escape($db, $user['lname']) . "',";
      $sql .= "birthday='" . db_escape($db, $user['birthday']) . "',";
      $sql .= "address='" . db_escape($db, $user['address']) . "',";
      $sql .= "postCode='" . db_escape($db, $user['postCode']) . "',";
      $sql .= "city='" . db_escape($db, $user['city']) . "',";
      if($password_sent){
        $sql .= "password='" . db_escape($db, $hashed_password) . "', ";
      }
      if($question_sent || $answer_sent){
        $sql .= "securityQuestion='" . db_escape($db, $user['securityQuestion']) . "',";
        $sql .= "answer='" . db_escape($db, $hashed_answer) . "', ";
      }

      $sql .= "country='" . db_escape($db, $user['country']) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $user['id']) . "' ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      // Result will be true/false
      if($result){
        return true;
      }
      else{
        // UPDATE failure
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }

    // Update user - resetting their password (password MUST be filled for this unlike the above function)
    function reset_password($user){
      global $db;

      $errors = validate_user($user, ['password_required' => true]);
      if(!empty($errors)){
        return $errors;
      }
      
      $hashed_password = password_hash($user["password"], PASSWORD_BCRYPT);

      $sql = "UPDATE user SET ";
      $sql .= "password='" . db_escape($db, $hashed_password) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $user['id']) . "' ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      // Result will be true/false
      if($result){
        return true;
      }
      else{
        // UPDATE failure
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }

    // Delete a user by id
    function delete_user($id){
      global $db;

      $errors = validate_user_deletion($id);
      if(!empty($errors)){
        return $errors;
      }

      $sql = "DELETE FROM user WHERE ";
      $sql .= "id='" . db_escape($db, $id) . "' ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      // Result will be true/false
      if($result){
        return true;
      }
      else{
        // DELETE failure
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }

    // Service session queries
    // Insert a customer service session
    function insert_service($service){
      global $db;

      $errors = validate_service($service);
      if(!empty($errors)){
        return $errors;
      }

      $sql = "INSERT INTO service ";
      $sql .= "(userID, requestSubject, requestMade, requestLastAction, requestDetails, requestResponse, resolved) ";
      $sql .= "VALUES (";
      $sql .= "'" . db_escape($db, $service['userID']) . "',";
      $sql .= "'" . db_escape($db, $service['requestSubject']) . "',";
      $sql .= "'" . db_escape($db, $service['requestMade']) . "',";
      $sql .= "'" . db_escape($db, $service['requestLastAction']) . "',";
      $sql .= "'" . db_escape($db, $service['requestDetails']) . "', ";
      $sql .= "'" . db_escape($db, $service['requestResponse']) . "', ";
      $sql .= "'" . db_escape($db, $service['resolved']) . "'";
      $sql .= ")";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Find a customer service session by its id
    function find_service_by_id($id){
      global $db;

      $sql = "SELECT * FROM service ";
      $sql .= "WHERE id='" . db_escape($db, $id) . "' ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $service = mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $service;        
    }

    // Find a customer service session by its user id
    function find_service_by_user_id($user_id){
      global $db;

      $sql = "SELECT * FROM service ";
      $sql .= "WHERE userID='" . db_escape($db, $user_id) . "' ";
      $sql .= "ORDER BY requestLastAction DESC, id DESC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;        
    }

    // Find all customer service
    function find_all_service(){
      global $db;

      $sql = "SELECT * FROM service ";
      $sql .= "ORDER BY requestLastAction DESC, id DESC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;        
    }
    
    // Update customer service session
    function update_service($service){
      global $db;

      $errors = validate_service($service);
      if(!empty($errors)){
        return $errors;
      }

      $sql = "UPDATE service SET ";
      $sql .= "userID='" . db_escape($db, $service['userID']) . "',";
      $sql .= "requestSubject='" . db_escape($db, $service['requestSubject']) . "',";
      $sql .= "requestLastAction='" . db_escape($db, $service['requestLastAction']) . "',";
      $sql .= "requestDetails='" . db_escape($db, $service['requestDetails']) . "',";
      $sql .= "requestResponse='" . db_escape($db, $service['requestResponse']) . "', ";
      $sql .= "resolved='" . db_escape($db, $service['resolved']) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $service['id']) . "' ";
      $sql .= "LIMIT 1";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Delete a customer service session
    function delete_service($id){
      global $db;

      $sql = "DELETE FROM service WHERE ";
      $sql .= "id='" . db_escape($db, $id) . "' ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      // Result will be true/false
      if($result){
        return true;
      }
      else{
        // DELETE failure
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }

    // Category functions
    // Insert a category
    function insert_category($category){
      global $db;

      $errors = validate_category($category);
      if(!empty($errors)){
        return $errors;
      }

      shift_category_positions(0, $category['position']);

      $sql = "INSERT INTO category ";
      $sql .= "(catName, position, totalPurchases, visible, description) ";
      $sql .= "VALUES (";
      $sql .= "'" . db_escape($db, $category['catName']) . "',";
      $sql .= "'" . db_escape($db, $category['position']) . "',";
      $sql .= "'" . db_escape($db, 0) . "', ";
      $sql .= "'" . db_escape($db, $category['visible']) . "',";
      $sql .= "'" . db_escape($db, $category['description']) . "'";
      $sql .= ")";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Find a user by an ID
    function find_category_by_id($id){
      global $db;

      $sql = "SELECT * FROM category ";
      $sql .= "WHERE id='" . db_escape($db, $id) . "' ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $category = mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $category;
    }

    // Find all categories
    function find_all_categories($options=[]){
      global $db;

      $visible = $options['visible'] ?? false;
      $sql = "SELECT * FROM category ";
      if($visible){
        $sql .= "WHERE visible = true ";
      }
      $sql .= "ORDER BY position ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);
  
      return $result;
    }

    // Count categories
    function count_categories(){
      global $db;

      $sql = "SELECT COUNT(id) FROM category ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $count = mysqli_fetch_row($result)[0];
  
      return $count;
    }

    // Update category
    function update_category($category){
      global $db;

      $errors = validate_category($category);
      if(!empty($errors)){
        return $errors;
      }

      $old_category = find_category_by_id($category['id']);
      $old_position = $old_category['position'];
      shift_category_positions($old_position, $category['position'], $category['id']);

      $sql = "UPDATE category SET ";
      $sql .= "catName='" . db_escape($db, $category['catName']) . "',";
      $sql .= "position='" . db_escape($db, $category['position']) . "', ";
      $sql .= "visible='" . db_escape($db, $category['visible']) . "', ";
      $sql .= "description='" . db_escape($db, $category['description']) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $category['id']) . "' ";
      $sql .= "LIMIT 1";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Update the total purchases by category column
    function update_total_purchases($category, $amtPurchased){
      global $db;
      
      $sql = "UPDATE category SET ";
      $sql .= "totalPurchases = totalPurchases + '" . db_escape($db, $amtPurchased) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $category['id']) . "' ";
      $sql .= "LIMIT 1";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Delete a category by ID
    function delete_category($id){
      global $db;

      $old_category = find_category_by_id($id);
      $old_position = $old_category['position'];
      shift_category_positions($old_position, 0, $id);

      $errors = validate_category_deletion($id);
      if(!empty($errors)){
        return $errors;
      }

      $sql = "DELETE FROM category WHERE ";
      $sql .= "id='" . db_escape($db, $id) . "' ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      // Result will be true/false
      if($result){
        return true;
      }
      else{
        // DELETE failure
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }

    // Product queries
    // Insert a product
    function insert_product($product){
      global $db;

      shift_product_positions(0, $product['position'], $product['catID']);
      $errors = validate_product($product);
      if(!empty($errors)){
        return $errors;
      }

      $sql = "INSERT INTO product ";
      $sql .= "(categoryID, name, price, stock, position, purchased, visible, description, imageRef) ";
      $sql .= "VALUES (";
      $sql .= "'" . db_escape($db, $product['catID']) . "',";
      $sql .= "'" . db_escape($db, $product['prodName']) . "',";
      $sql .= "'" . db_escape($db, $product['price']) . "',";
      $sql .= "'" . db_escape($db, $product['stock']) . "',";
      $sql .= "'" . db_escape($db, $product['position']) . "',";
      $sql .= "'" . db_escape($db, $product['purchased']) . "',";
      $sql .= "'" . db_escape($db, $product['visible']) . "',";
      $sql .= "'" . db_escape($db, $product['description']) . "',";
      $sql .= "'" . db_escape($db, $product['imageRef']) . "'";
      $sql .= ")";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Find a product by id
    function find_product_by_id($id){
      global $db;

      $sql = "SELECT * FROM product ";
      $sql .= "WHERE id='" . db_escape($db, $id) . "' ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $product = mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $product;
    }

    // Find all products
    function find_all_products($options=[]){
      global $db;

      $visible = $options['visible'] ?? false;
      $sql = "SELECT * FROM product ";
      if($visible){
        $sql .= "WHERE visible = true ";
      }
      $sql .= "ORDER BY position ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;
    }

    function find_products_by_search($search, $options=[]){
      global $db;

      $visible = $options['visible'] ?? false;
      $sql = "SELECT * FROM product ";
      $sql .= "WHERE name LIKE '%" . db_escape($db, $search) . "%' ";
      if($visible){
        $sql .= "AND visible = true ";
      }
      $sql .= "ORDER BY position ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;      
    }

    // Find products by the category id
    function find_products_by_category_id($category_id, $options=[]){
      global $db;

      $visible = $options['visible'] ?? false;
      $sql = "SELECT * FROM product ";
      $sql .= "WHERE categoryID='" . db_escape($db, $category_id)  . "' ";
      if($visible){
        $sql .= "AND visible = true ";
      }
      $sql .= "ORDER BY position ASC";
      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;
    }

    // Find 3 most recent products
    function find_recent_three_products($options=[]){
      global $db;

      $visible = $options['visible'] ?? false;
      $sql = "SELECT * FROM product ";
      if($visible){
        $sql .= "WHERE visible = true ";
      }
      $sql .= "ORDER BY id DESC ";
      $sql .= "LIMIT 3 ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;
    }

    function count_products_by_category_id($category_id, $options=[]){
      global $db;

      $visible = $options['visible'] ?? false;
      $sql = "SELECT COUNT(id) FROM product ";
      $sql .= "WHERE categoryID='" . db_escape($db, $category_id)  . "' ";
      if($visible){
        $sql .= "AND visible = true ";
      }
      $sql .= "ORDER BY position ASC";
      $result = mysqli_query($db, $sql);
      confirm_result_set($result);
      $row = mysqli_fetch_row($result);
      mysqli_free_result($result);
      $count = $row[0];

      return $count;
    }

    function count_products(){
      global $db;

      $sql = "SELECT COUNT(id) FROM product ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);
      $row = mysqli_fetch_row($result);
      mysqli_free_result($result);
      $count = $row[0];

      return $count;
    }

    // Update product
    function update_product($product){
      global $db;

      $old_product = find_product_by_id($product['id']);
      $old_position = $old_product['position'];
      shift_product_positions($old_position, $product['position'], $product['catID']);

      $errors = validate_product($product);
      if(!empty($errors)){
        return $errors;
      }

      $sql = "UPDATE product SET ";
      $sql .= "categoryID='" . db_escape($db, $product['catID']) . "',";
      $sql .= "name='" . db_escape($db, $product['prodName']) . "', ";
      $sql .= "price='" . db_escape($db, $product['price']) . "', ";
      $sql .= "stock='" . db_escape($db, $product['stock']) . "', ";
      $sql .= "position='" . db_escape($db, $product['position']) . "', ";
      $sql .= "visible='" . db_escape($db, $product['visible']) . "', ";
      $sql .= "description='" . db_escape($db, $product['description']) . "', ";
      $sql .= "imageRef='" . db_escape($db, $product['imageRef']) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $product['id']) . "' ";
      $sql .= "LIMIT 1";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Update the product stock
    function update_product_stock($product, $amtPurchased){
      global $db;

      if(!empty($errors)){
        return $errors;
      }

      $sql = "UPDATE product SET ";
      $sql .= "stock = stock - '" . db_escape($db, $amtPurchased) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $product['id']) . "' ";
      $sql .= "LIMIT 1";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    function update_product_purchase($product, $amtPurchased){
      global $db;

      if(!empty($errors)){
        return $errors;
      }

      $sql = "UPDATE product SET ";
      $sql .= "purchased = purchased + '" . db_escape($db, $amtPurchased) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $product['id']) . "' ";
      $sql .= "LIMIT 1";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Delete a product by ID
    function delete_product($id){
      global $db;

      $old_product = find_product_by_id($id);
      $old_position = $old_product['position'];
      shift_product_positions($old_position, 0, $old_product['catID'], $id);

      $sql = "DELETE FROM product WHERE ";
      $sql .= "id='" . db_escape($db, $id) . "' ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      // Result will be true/false
      if($result){
        return true;
      }
      else{
        // DELETE failure
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }    

    // Order queries
    // Insert an order
    function insert_order($order){
      global $db;

      $errors = validate_order($order);
      if(!empty($errors)){
        return $errors;
      }

      $prodIDs = '';
      for($i = 0; $i < count($order['productIDs']) ; $i++){
        if($i === count($order['productIDs'])-1){
          $prodIDs .= $order['productIDs'][$i];
        }
        else{
          $prodIDs .= $order['productIDs'][$i] . ',';
        }
      }

      $sql = "INSERT INTO orders ";
      $sql .= "(userID, productIDs, amts, orderMade, fulfilled, paid) ";
      $sql .= "VALUES (";
      $sql .= "'" . db_escape($db, $order['userID']) . "',";
      $sql .= "'" . db_escape($db, $prodIDs) . "',";
      $sql .= "'" . db_escape($db, $order['amts']) . "', ";
      $sql .= "'" . db_escape($db, date('Y-m-d')) . "', ";
      $sql .= "'" . db_escape($db, $order['fulfilled']) . "',";
      $sql .= "'" . db_escape($db, $order['paid']) . "'";
      $sql .= ")";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Find an order by id
    function find_order_by_id($id){
      global $db;

      $sql = "SELECT * FROM orders ";
      $sql .= "WHERE id='" . db_escape($db, $id) . "' ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $order= mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $order;
    }

    // Find an order by id
    function find_order_by_user_id($user_id){
      global $db;

      $sql = "SELECT * FROM orders ";
      $sql .= "WHERE userID='" . db_escape($db, $user_id) . "' ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);
      return $result;
    }

    // Find all orders
    function find_all_orders(){
      global $db;

      $sql = "SELECT * FROM orders ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;
    }

    function find_recent_date_by_user_id($user_id){
      global $db;

      $sql = "SELECT orderMade FROM orders ";
      $sql .= "WHERE userID='" . db_escape($db, $user_id)  . "' ";
      $sql .= "ORDER BY orderMade DESC ";
      $sql .= "LIMIT 1";
      $result = mysqli_query($db, $sql);
      confirm_result_set($result);
      $row = mysqli_fetch_row($result);
      mysqli_free_result($result);
      
      if(!empty($row)){
        $date = $row[0];
        return $date;
      }
      else{
        return '';
      }

    }

    function count_orders_by_user_id($user_id){
      global $db;

      $sql = "SELECT COUNT(id) FROM orders ";
      $sql .= "WHERE userID='" . db_escape($db, $user_id)  . "' ";
      $result = mysqli_query($db, $sql);
      confirm_result_set($result);
      $row = mysqli_fetch_row($result);
      mysqli_free_result($result);
      $count = $row[0];

      return $count;
    }

    // Update order
    function update_order($order){
      global $db;

      $errors = validate_order($order);
      if(!empty($errors)){
        return $errors;
      }

      $prodIDs = '';
      foreach($order['productIDs'] as $product){
        $prodIDs .= $product . ',';
      }

      $sql = "UPDATE orders SET ";
      $sql .= "userID='" . db_escape($db, $order['userID']) . "',";
      $sql .= "productIDs='" . db_escape($db, $prodIDs) . "', ";
      $sql .= "amts='" . db_escape($db, $order['amts']) . "', ";
      $sql .= "fulfilled='" . db_escape($db, $order['fulfilled']) . "', ";
      $sql .= "paid='" . db_escape($db, $order['paid']) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $order['id']) . "' ";
      $sql .= "LIMIT 1";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Delete a order by ID
    function delete_order($id){
      global $db;

      $sql = "DELETE FROM orders WHERE ";
      $sql .= "id='" . db_escape($db, $id) . "' ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      // Result will be true/false
      if($result){
        return true;
      }
      else{
        // DELETE failure
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }  

    // Review queries
    // Find all reviews
    function find_all_reviews(){
      global $db;

      $sql = "SELECT * FROM reviews ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;      
    }

    // Find review by id
    function find_review_by_id($id){
      global $db;

      $sql = "SELECT * FROM reviews ";
      $sql .= "WHERE id='" . db_escape($db, $id) . "' ";
      $sql .= "ORDER BY id ASC ";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      $review= mysqli_fetch_assoc($result);
      mysqli_free_result($result);

      return $review;      
    }

    // Find review by id
    function find_reviews_by_product_id($id){
      global $db;

      $sql = "SELECT * FROM reviews ";
      $sql .= "WHERE productID='" . db_escape($db, $id) . "' ";
      $sql .= "ORDER BY reviewMade DESC";

      $result = mysqli_query($db, $sql);
      confirm_result_set($result);

      return $result;      
    }

    // Insert a review
    function insert_review($review){
      global $db;

      $errors = validate_review($review);
      if(!empty($errors)){
        return $errors;
      }

      $sql = "INSERT INTO reviews ";
      $sql .= "(userID, productID, title, rating, contents, reviewMade, flagged, reviewed) ";
      $sql .= "VALUES (";
      $sql .= "'" . db_escape($db, $review['userID']) . "',";
      $sql .= "'" . db_escape($db, $review['productID']) . "',";
      $sql .= "'" . db_escape($db, $review['title']) . "',";
      $sql .= "'" . db_escape($db, $review['rating']) . "', ";
      $sql .= "'" . db_escape($db, $review['contents']) . "', ";
      $sql .= "'" . db_escape($db, $review['reviewMade']) . "',";
      $sql .= "'" . db_escape($db, $review['flagged']) . "', ";
      $sql .= "'" . db_escape($db, $review['reviewed']) . "'";
      $sql .= ")";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Update a review
    function update_review($review){
      global $db;

      $errors = validate_review($review);
      if(!empty($errors)){
        return $errors;
      }

      $sql = "UPDATE reviews SET ";
      $sql .= "userID='" . db_escape($db, $review['userID']) . "',";
      $sql .= "productID='" . db_escape($db, $review['productID']) . "', ";
      $sql .= "title='" . db_escape($db, $review['title']) . "', ";
      $sql .= "rating='" . db_escape($db, $review['rating']) . "', ";
      $sql .= "contents='" . db_escape($db, $review['contents']) . "', ";
      $sql .= "flagged='" . db_escape($db, $review['flagged']) . "', ";
      $sql .= "reviewed='" . db_escape($db, $review['reviewed']) . "' ";
      $sql .= "WHERE id='" . db_escape($db, $review['id']) . "' ";
      $sql .= "LIMIT 1";

      // Result will be TRUE/FALSE - either query succeeded or failed
      $result = mysqli_query($db, $sql);

      if($result){
          return true;
      }
      else{
          // INSERT failure
          echo mysqli_error($db);
          db_disconnect($db);
          exit;
      }
    }

    // Delete a review
    function delete_review($id){
      global $db;

      $sql = "DELETE FROM reviews WHERE ";
      $sql .= "id='" . db_escape($db, $id) . "' ";
      $sql .= "LIMIT 1";

      $result = mysqli_query($db, $sql);
      // Result will be true/false
      if($result){
        return true;
      }
      else{
        // DELETE failure
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }

    // Validating queries
    // When deleting a category, the category must have no products attached to it
    function validate_category_deletion($id){
      $errors = [];

      // Check for products assigned to the category
      if(!has_assigned_products($id)){
        $errors[] = "Assigned products must be deleted or reassigned before deleting the category.";
      }

      return $errors;
    }

    // When deleting a product, there must be no orders attached to it
    function validate_user_deletion($id){  
      $errors = [];

      // Check for orders assigned to the product
      if(!has_user_assigned_orders($id)){
        $errors[] = "Assigned orders must be deleted or reassigned before deleting account.";
      }

      // Check for orders assigned to the product
      if(!has_user_assigned_service($id)){
        $errors[] = "Assigned service must be deleted or reassigned before deleting account.";
      }

      // Check for reviews assigned to the product
      if(!has_user_assigned_reviews($id)){
        $errors[] = "Assigned reviews must be deleted or reassigned before deleting account.";
      }

      return $errors;
    }

    // When deleting a product, there must be no orders attached to it
    function validate_product_deletion($id){  
      $errors = [];

      // Check for orders assigned to the product
      if(!has_product_assigned_orders($id)){
        $errors[] = "Assigned orders must be deleted or reassigned before deleting the product.";
      }

      // Check for orders assigned to the product
      if(!has_product_assigned_reviews($id)){
        $errors[] = "Assigned reviews must be deleted or reassigned before deleting the product.";
      }

      return $errors;
    }

    // Validate staff inputs
    function validate_staff($staff, $options=[]){
      $errors = [];

      $password_required = $options['password_required'] ?? true;

      // StaffID 4-255, unique, characters and digit necessary
      if(is_blank(($staff['staffID']))){
        $errors[] = "Staff ID cannot be blank.";
      }
      else if(!has_length($staff['staffID'], ['min' => 4, 'max' => 25])) {
        $errors[] = "Staff ID must be between 4 and 255 characters.";
      }
      else if(!has_unique_staffID($staff['staffID'], $staff['id'] ?? '0')){
        $errors[] = "Staff ID must be unique";
      }
      else if(!preg_match("/[A-Za-z]/", $staff['staffID'])){
        $errors[] = "Staff ID must have alphabetic characters";
      }
      else if(!preg_match("/[0-9]/", $staff['staffID'])){
        $errors[] = "Staff ID must have at least one digit";
      }

      // email
      if(is_blank(($staff['email']))){
        $errors[] = "Email cannot be blank.";
      }
      else if(!has_valid_email_format($staff['email'])){
        $errors[] = "Email must be in a valid format";
      }
      else if(!has_length($staff['email'], ['max' => 255])){
        $errors[] = "Email can only have a max of 255 characters";
      }
      else if(!has_unique_staffEmail($staff['email'], $staff['id'] ?? '0')){
        $errors[] = "Email is already registered on an account";        
      }

      // first name
      if(is_blank($staff['fname'])) {
        $errors[] = "First name cannot be blank.";
      }
      else if(!has_length($staff['fname'], ['min' => 2, 'max' => 255])) {
        $errors[] = "First name must be between 2 and 255 characters.";
      } 

      // last name
      if(is_blank($staff['lname'])) {
        $errors[] = "Last name cannot be blank.";
      }
      else if(!has_length($staff['lname'], ['min' => 2, 'max' => 255])) {
        $errors[] = "Last name must be between 2 and 255 characters.";
      }

      // Password 12+ chars, 1 upper, 1 lower, 1 number, 1 symbol
      if($password_required){
        if(is_blank(($staff['password']))){
          $errors[] = "Password cannot be blank.";
        }
        else if(!has_length($staff['password'], ['min' => 12])){
          $errors[] = "Password must have at least 12 characters.";
        }
        else{
          if(!preg_match("/\W/", $staff['password'])){
            $errors[] = "Password must have at least one special character";
          }
          if(!preg_match("/[A-Z]/", $staff['password'])){
            $errors[] = "Password must have at least one uppercase character";
          }
          if(!preg_match("/[a-z]/", $staff['password'])){
            $errors[] = "Password must have at least one lowercase character";
          }
          if(!preg_match("/[0-9]/", $staff['password'])){
            $errors[] = "Password must have at least one digit";
          }
        }

        // Confirm password for inserting
        if(is_blank($staff['confirmPass'])) {
          $errors[] = "Password confirmation cannot be blank.";
        }
        else if(!($staff['confirmPass'] === $staff['password'])){
          $errors[] = "Password confirmation does not match.";
        }
      }

      return $errors;
    }

    // Validate user inputs
    function validate_user($user, $options=[]){
      $errors = [];

      $password_required = $options['password_required'] ?? true;
      $question_required = $options['question_required'] ?? true;
      $answer_required = $options['answer_required'] ?? true;
      
      // UserID 4-255, unique, characters and digit necessary
      if(is_blank(($user['userID']))){
        $errors[] = "User ID cannot be blank.";
      }
      else if(!has_length($user['userID'], ['min' => 4, 'max' => 25])) {
        $errors[] = "User ID must be between 4 and 25 characters.";
      }
      else if(!has_unique_userID($user['userID'], $user['id'] ?? '0')){
        $errors[] = "User ID must be unique";
      }
      else if(!preg_match("/[A-Za-z]/", $user['userID'])){
        $errors[] = "User ID must have alphabetic characters";
      }
      else if(!preg_match("/[0-9]/", $user['userID'])){
        $errors[] = "User ID must have at least one digit";
      }

      // email
      if(is_blank(($user['email']))){
        $errors[] = "Email cannot be blank.";
      }
      else if(!has_valid_email_format($user['email'])){
        $errors[] = "Email must be in a valid format";
      }
      else if(!has_length($user['email'], ['max' => 255])){
        $errors[] = "Email can only have a max of 255 characters";
      }
      else if(!has_unique_userEmail($user['email'], $user['id'] ?? '0')){
        $errors[] = "Email is already registered on an account";        
      }

      // first name
      if(is_blank($user['fname'])) {
        $errors[] = "First name cannot be blank.";
      }
      else if(!has_length($user['fname'], ['min' => 2, 'max' => 255])) {
        $errors[] = "First name must be between 2 and 255 characters.";
      } 

      // last name
      if(is_blank($user['lname'])) {
        $errors[] = "Last name cannot be blank.";
      }
      else if(!has_length($user['lname'], ['min' => 2, 'max' => 255])) {
        $errors[] = "Last name must be between 2 and 255 characters.";
      }

      // birthday
      if(is_blank($user['birthday'])) {
        $errors[] = "Birthday cannot be blank.";
      }
      else if($user['birthday'] > date("Y-m-d")){
        $errors[] = "Birthday cannot be a day that hasn't occurred.";
      }

      // address
      if(is_blank($user['address'])) {
        $errors[] = "Address cannot be blank.";
      }
      else if(!has_length($user['address'], ['min' => 2, 'max' => 255])) {
        $errors[] = "Address must be between 2 and 255 characters.";
      }

      // postal code
      if(is_blank($user['postCode'])) {
        $errors[] = "Postal code cannot be blank.";
      }
      else if(!has_length($user['postCode'], ['min' => 2, 'max' => 255])) {
        $errors[] = "Postal code must be between 2 and 255 characters.";
      }

      // city
      if(is_blank($user['city'])) {
        $errors[] = "City cannot be blank.";
      }
      else if(!has_length($user['city'], ['min' => 2, 'max' => 255])) {
        $errors[] = "City must be between 2 and 255 characters.";
      }

      // country
      if(is_blank($user['country'])) {
        $errors[] = "Country cannot be blank.";
      }
      else if(!has_length($user['country'], ['min' => 2, 'max' => 255])) {
        $errors[] = "Country must be between 2 and 255 characters.";
      }

      // Password 12+ chars, 1 upper, 1 lower, 1 number, 1 symbol
      if($password_required){
        if(is_blank(($user['password']))){
          $errors[] = "Password cannot be blank.";
        }
        else if(!has_length($user['password'], ['min' => 12])){
          $errors[] = "Password must have at least 12 characters.";
        }
        else{
          if(!preg_match("/\W/", $user['password'])){
            $errors[] = "Password must have at least one special character";
          }
          if(!preg_match("/[A-Z]/", $user['password'])){
            $errors[] = "Password must have at least one uppercase character";
          }
          if(!preg_match("/[a-z]/", $user['password'])){
            $errors[] = "Password must have at least one lowercase character";
          }
          if(!preg_match("/[0-9]/", $user['password'])){
            $errors[] = "Password must have at least one digit";
          }
        }

        // Confirm password for inserting
        if(is_blank($user['confirmPass'])) {
          $errors[] = "Password confirmation cannot be blank.";
        }
        else if(!($user['confirmPass'] === $user['password'])){
          $errors[] = "Password confirmation does not match.";
        }
      }

      // Security question and answer
      if($question_required || $answer_required){
        if($question_required && is_blank($user['securityQuestion'])){
          $errors[] = "Security question must be selected.";
        }

        if(is_blank($user['answer'])) {
          $errors[] = "The answer to the security question cannot be blank.";
        }
        else if(!has_length($user['answer'], ['max' => 255])) {
          $errors[] = "Answer must be less than 255 characters.";
        }
      }

      return $errors;
    }

    // Validate category inputs
    function validate_category($category){
      $errors = [];
      // category name
      if(is_blank($category['catName'])) {
        $errors[] = "Category name cannot be blank.";
      }
      else if(!has_length($category['catName'], ['min' => 4, 'max' => 255])){
        $errors[] = "Category name must be between 4 and 255 characters.";
      }

      // position
      // Make sure we are working with an integer
      $postion_int = (int) $category['position'];
      if($postion_int <= 0) {
        $errors[] = "Position must be greater than zero.";
      }
      if($postion_int > 999) {
        $errors[] = "Position must be less than 999.";
      }

      // description
      if(is_blank($category['description'])) {
        $errors[] = "Description cannot be blank.";
      }
      
      return $errors;
    }

    // Validate product inputs
    function validate_product($product){
      $errors = [];

      if(is_blank($product['catID'])){
        $errors[] = "Category cannot be blank.";
      }

      // product name
      if(is_blank($product['prodName'])) {
        $errors[] = "Product name cannot be blank.";
      }
      else if(!has_length($product['prodName'], ['min' => 2, 'max' => 255])){
        $errors[] = "Product name must be between 2 and 255 characters.";
      }

      // price
      // Make sure we are working with an double
      $price = (double) $product['price'];
      if($price<= 0) {
        $errors[] = "Price must be greater than zero.";
      }
      if($price > 999) {
        $errors[] = "Price must be less than 999.";
      }

      // stock
      // Make sure we are working with an integer
      $stock_int = (int) $product['stock'];
      if($stock_int < 0) {
        $errors[] = "Stock cannot be negative.";
      }
      if($stock_int > 999) {
        $errors[] = "Stock must be less than 999.";
      }

      // position
      // Make sure we are working with an integer
      $postion_int = (int) $product['position'];
      if($postion_int <= 0) {
        $errors[] = "Position must be greater than zero.";
      }
      if($postion_int > 999) {
        $errors[] = "Position must be less than 999.";
      }

      // description
      if(is_blank($product['description'])) {
        $errors[] = "Description cannot be blank.";
      }

      // description
      if(is_blank($product['imageRef'])) {
        $errors[] = "Image reference cannot be blank.";
      }

      return $errors;
    }

    // Validate order inputs
    function validate_order($order){
      $errors = [];

      // userID
      if(is_blank($order['userID'])){
        $errors[] = "UserID cannot be blank.";
      }

      // product IDs
      // If the order is empty, it is not an array of products
      if(empty($order['productIDs'])){
        $errors[] = "Products cannot be blank.";
      }

      return $errors;
    }

    // Validate service inputs
    function validate_service($service){
      $errors = [];

      // userID
      if(is_blank($service['userID'])){
        $errors[] = "UserID cannot be blank.";
      }

      // request subject
      if(is_blank($service['requestSubject'])) {
        $errors[] = "Request subject cannot be blank.";
      }

      // request details
      if(is_blank($service['requestDetails'])) {
        $errors[] = "Request details cannot be blank.";
      }

      return $errors;
    }

    function validate_review($review){
      $errors = [];
      // UserID
      if(is_blank($review['userID'])){
        $errors[] = "UserID cannot be blank.";
      }

      // ProductID
      if(is_blank($review['productID'])){
        $errors[] = "Product cannot be blank.";
      }

      // Title
      if(is_blank($review['title'])){
        $errors[] = "Title cannot be blank.";
      }
      else if(!has_length($review['title'], ['max' => 255])){
        $errors[] = "Title cannot have more than 255 characters";
      }

      // Content
      if(is_blank($review['contents'])){
        $errors[] = "Content cannot be blank.";
      }

      // Rating
      // Make sure we are working with an double
      $rating= (double) $review['rating'];
      if($rating< 0) {
        $errors[] = "Rating must be from 0.0-5.0";
      }
      else if($rating > 5) {
        $errors[] = "Rating must be from 0.0-5.0";
      }

      return $errors;
    }

    function shift_category_positions($start_pos, $end_pos, $current_id=0) {
      global $db;
  
      if($start_pos == $end_pos) { return; }
  
      $sql = "UPDATE category ";
      if($start_pos == 0) {
        // new item, +1 to items greater than $end_pos
        $sql .= "SET position = position + 1 ";
        $sql .= "WHERE position >= '" . db_escape($db, $end_pos) . "' ";
      } elseif($end_pos == 0) {
        // delete item, -1 from items greater than $start_pos
        $sql .= "SET position = position - 1 ";
        $sql .= "WHERE position > '" . db_escape($db, $start_pos) . "' ";
      } elseif($start_pos < $end_pos) {
        // move later, -1 from items between (including $end_pos)
        $sql .= "SET position = position - 1 ";
        $sql .= "WHERE position > '" . db_escape($db, $start_pos) . "' ";
        $sql .= "AND position <= '" . db_escape($db, $end_pos) . "' ";
      } elseif($start_pos > $end_pos) {
        // move earlier, +1 to items between (including $end_pos)
        $sql .= "SET position = position + 1 ";
        $sql .= "WHERE position >= '" . db_escape($db, $end_pos) . "' ";
        $sql .= "AND position < '" . db_escape($db, $start_pos) . "' ";
      }
      // Exclude the current_id in the SQL WHERE clause
      $sql .= "AND id != '" . db_escape($db, $current_id) . "' ";
  
      $result = mysqli_query($db, $sql);
      // For UPDATE statements, $result is true/false
      if($result) {
        return true;
      } else {
        // UPDATE failed
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }

    function shift_product_positions($start_pos, $end_pos, $cat_id, $current_id=0) {
      global $db;
  
      if($start_pos == $end_pos) { return; }
  
      $sql = "UPDATE product ";
      if($start_pos == 0) {
        // new item, +1 to items greater than $end_pos
        $sql .= "SET position = position + 1 ";
        $sql .= "WHERE position >= '" . db_escape($db, $end_pos) . "' ";
      } elseif($end_pos == 0) {
        // delete item, -1 from items greater than $start_pos
        $sql .= "SET position = position - 1 ";
        $sql .= "WHERE position > '" . db_escape($db, $start_pos) . "' ";
      } elseif($start_pos < $end_pos) {
        // move later, -1 from items between (including $end_pos)
        $sql .= "SET position = position - 1 ";
        $sql .= "WHERE position > '" . db_escape($db, $start_pos) . "' ";
        $sql .= "AND position <= '" . db_escape($db, $end_pos) . "' ";
      } elseif($start_pos > $end_pos) {
        // move earlier, +1 to items between (including $end_pos)
        $sql .= "SET position = position + 1 ";
        $sql .= "WHERE position >= '" . db_escape($db, $end_pos) . "' ";
        $sql .= "AND position < '" . db_escape($db, $start_pos) . "' ";
      }
      // Exclude the current_id in the SQL WHERE clause
      $sql .= "AND id != '" . db_escape($db, $current_id) . "' ";
      $sql .= "AND categoryID = '" . db_escape($db, $cat_id) . "'";
  
      $result = mysqli_query($db, $sql);
      // For UPDATE statements, $result is true/false
      if($result) {
        return true;
      } else {
        // UPDATE failed
        echo mysqli_error($db);
        db_disconnect($db);
        exit;
      }
    }
?>
