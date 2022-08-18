<?php
  /*
   * Developer: Dennis Dao
   * July 18, 2022
   *  v1.0
   * /

   // Various validation functions for form data

  /* Referenced from Kevin Skoglund's PHP with MySQL Essential Training 2 - Build a CMS Course*/
  /* The course was a continuation of A3's course - that was Part 1.
  /* https://www.linkedin.com/learning/php-with-mysql-essential-training-2-build-a-cms*/

  // is_blank('abcd')
  // * validate data presence
  // * uses trim() so empty spaces don't count
  // * uses === to avoid false positives
  // * better than empty() which considers "0" to be empty
  function is_blank($value) {
    return !isset($value) || trim($value) === '';
  }

  // has_presence('abcd')
  // * validate data presence
  // * reverse of is_blank()
  // * I prefer validation names with "has_"
  function has_presence($value) {
    return !is_blank($value);
  }

  // has_length_greater_than('abcd', 3)
  // * validate string length
  // * spaces count towards length
  // * use trim() if spaces should not count
  function has_length_greater_than($value, $min) {
    $length = strlen($value);
    return $length > $min;
  }

  // has_length_less_than('abcd', 5)
  // * validate string length
  // * spaces count towards length
  // * use trim() if spaces should not count
  function has_length_less_than($value, $max) {
    $length = strlen($value);
    return $length < $max;
  }

  // has_length_exactly('abcd', 4)
  // * validate string length
  // * spaces count towards length
  // * use trim() if spaces should not count
  function has_length_exactly($value, $exact) {
    $length = strlen($value);
    return $length == $exact;
  }

  // has_length('abcd', ['min' => 3, 'max' => 5])
  // * validate string length
  // * combines functions_greater_than, _less_than, _exactly
  // * spaces count towards length
  // * use trim() if spaces should not count
  function has_length($value, $options) {
    if(isset($options['min']) && !has_length_greater_than($value, $options['min'] - 1)) {
      return false;
    } elseif(isset($options['max']) && !has_length_less_than($value, $options['max'] + 1)) {
      return false;
    } elseif(isset($options['exact']) && !has_length_exactly($value, $options['exact'])) {
      return false;
    } else {
      return true;
    }
  }

  // has_inclusion_of( 5, [1,3,5,7,9] )
  // * validate inclusion in a set
  function has_inclusion_of($value, $set) {
  	return in_array($value, $set);
  }

  // has_exclusion_of( 5, [1,3,5,7,9] )
  // * validate exclusion from a set
  function has_exclusion_of($value, $set) {
    return !in_array($value, $set);
  }

  // has_string('nobody@nowhere.com', '.com')
  // * validate inclusion of character(s)
  // * strpos returns string start position or false
  // * uses !== to prevent position 0 from being considered false
  // * strpos is faster than preg_match()
  function has_string($value, $required_string) {
    return strpos($value, $required_string) !== false;
  }

  // has_valid_email_format('nobody@nowhere.com')
  // * validate correct format for email addresses
  // * format: [chars]@[chars].[2+ letters]
  // * preg_match is helpful, uses a regular expression
  //    returns 1 for a match, 0 for no match
  //    http://php.net/manual/en/function.preg-match.php
  function has_valid_email_format($value) {
    $email_regex = '/\A[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}\Z/i';
    return preg_match($email_regex, $value) === 1;
  }

  // has_assigned_products('1')
  // Validates if produts are attached to the category
  function has_assigned_products($id){
    global $db;

    $sql = "SELECT * FROM category ";
    $sql .= "WHERE id='" . db_escape($db, $id) . "' and id in ";
    $sql .= "(SELECT categoryID FROM product)";

    // IF the id in question returns results (check for the specific id in categories and that it is in 
    // the products table as a userid value, there is a product attached)
    $category_set = mysqli_query($db, $sql);
    $category_count = mysqli_num_rows($category_set);
    mysqli_free_result($category_set);

    return $category_count === 0;
  }

    // has_user_assigned_orders('1')
  // Validates if orders are attached to the user
  function has_user_assigned_orders($id){
    global $db;

    $sql = "SELECT * FROM user ";
    $sql .= "WHERE id='" . db_escape($db, $id) . "' and id in ";
    $sql .= "(SELECT userID FROM orders)";

    // IF the id in question returns results (check for the specific id in users and that it is in 
    // the orders table as a userid value, there is an order attached)
    $user_set = mysqli_query($db, $sql);
    $order_count = mysqli_num_rows($user_set);
    mysqli_free_result($user_set);

    return $order_count === 0;
  }

      // has_assigned_service('1')
  // Validates if orders are attached to the user
  function has_user_assigned_service($id){
    global $db;

    $sql = "SELECT * FROM user ";
    $sql .= "WHERE id='" . db_escape($db, $id) . "' and id in ";
    $sql .= "(SELECT userID FROM service)";

    // IF the id in question returns results (check for the specific id in users and that it is in 
    // the service table as a userid value, there is service attached)
    $user_set = mysqli_query($db, $sql);
    $service_count = mysqli_num_rows($user_set);
    mysqli_free_result($user_set);

    return $service_count === 0;
  }

      // has_user_assigned_reviews('1')
  // Validates if reviews are attached to the user
  function has_user_assigned_reviews($id){
    global $db;

    $sql = "SELECT * FROM user ";
    $sql .= "WHERE id='" . db_escape($db, $id) . "' and id in ";
    $sql .= "(SELECT userID FROM reviews)";

    // IF the id in question returns results (check for the specific id in users and that it is in 
    // the review table as a userid value, there is an review attached)
    $user_set = mysqli_query($db, $sql);
    $review_count = mysqli_num_rows($user_set);
    mysqli_free_result($user_set);

    return $review_count === 0;
  }

    // has_product_assigned_orders('1')
  // Validates if orders are attached to the product
  function has_product_assigned_orders($id){
    global $db;

    $sql = "SELECT * FROM product ";
    $sql .= "WHERE id='" . db_escape($db, $id) . "' and id in ";
    $sql .= "(SELECT productID FROM orders)";

    // IF the id in question returns results (check for the specific id in products and that it is in 
    // the orders table as a product_id value, there is a product attached)
    $product_set = mysqli_query($db, $sql);
    $order_count = mysqli_num_rows($product_set);
    mysqli_free_result($product_set);

    return $order_count === 0;
  }

      // has_product_assigned_reviews('1')
  // Validates if reviews are attached to the product
  function has_product_assigned_reviews($id){
    global $db;

    $sql = "SELECT * FROM product ";
    $sql .= "WHERE id='" . db_escape($db, $id) . "' and id in ";
    $sql .= "(SELECT productID FROM reviews)";

    // IF the id in question returns results (check for the specific id in products and that it is in 
    // the review table as a product_id value, there is a review attached)
    $product_set = mysqli_query($db, $sql);
    $review_count = mysqli_num_rows($product_set);
    mysqli_free_result($product_set);

    return $review_count === 0;
  } 

    // has_unique_staffID('History')
  // Validates uniqueness of admins staffID
  // * For new records, provide only the username
  // * For existing records, provide current ID as second argument
  //   has unique_username('History', 4)
  function has_unique_staffID($staffID, $current_id="0"){
    global $db;

    $sql = "SELECT * FROM staff ";
    $sql .= "WHERE staffID='" . db_escape($db, $staffID) . "' ";
    $sql .= "AND id != '" . db_escape($db, $current_id) . "'";

    $staff_set = mysqli_query($db, $sql);
    $staff_count = mysqli_num_rows($staff_set);
    mysqli_free_result($staff_set);

    return $staff_count === 0;
  }

      // has_unique_userID('History')
  // Validates uniqueness of user's userID
  // * For new records, provide only the username
  // * For existing records, provide current ID as second argument
  //   has unique_username('History', 4)
  function has_unique_userID($userID, $current_id="0"){
    global $db;

    $sql = "SELECT * FROM user ";
    $sql .= "WHERE userID='" . db_escape($db, $userID) . "' ";
    $sql .= "AND id != '" . db_escape($db, $current_id) . "'";

    $user_set = mysqli_query($db, $sql);
    $user_count = mysqli_num_rows($user_set);
    mysqli_free_result($user_set);

    return $user_count === 0;
  }

        // has_unique_staffEmail('History')
  // Validates uniqueness of admin's email
  // * For new records, provide only the email
  // * For existing records, provide current email as second argument
  //   has unique_username('History', 4)
  function has_unique_staffEmail($email, $current_id="0"){
    global $db;

    $sql = "SELECT * FROM staff ";
    $sql .= "WHERE email='" . db_escape($db, $email) . "' ";
    $sql .= "AND id != '" . db_escape($db, $current_id) . "'";

    $staff_set = mysqli_query($db, $sql);
    $staff_count = mysqli_num_rows($staff_set);
    mysqli_free_result($staff_set);

    return $staff_count === 0;
  }

          // has_unique_userEmail('History')
  // Validates uniqueness of user's email
  // * For new records, provide only the email
  // * For existing records, provide current email as second argument
  //   has unique_username('History', 4)
  function has_unique_userEmail($email, $current_id="0"){
    global $db;

    $sql = "SELECT * FROM user ";
    $sql .= "WHERE email='" . db_escape($db, $email) . "' ";
    $sql .= "AND id != '" . db_escape($db, $current_id) . "'";

    $user_set = mysqli_query($db, $sql);
    $user_count = mysqli_num_rows($user_set);
    mysqli_free_result($user_set);

    return $user_count === 0;
  }

  // Check for a valid credit card number - 15-16 of only digits
  function has_valid_credit($value) {
    $credit_regex = '/^[0-9]{15}$|^[0-9]{16}$/';
    return preg_match($credit_regex, $value) === 1;
  }

?>
