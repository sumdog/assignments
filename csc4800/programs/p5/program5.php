<?php

  function create_input($name,$size) {
    echo "<input type=\"text\" size=\"$size\" value=\"{$_POST[$name]}\" name=\"$name\" />";
  }
?>
<!DOCTYPE >
<html>
<head>
  <title>Sumit Khanna's CSC4800 Program #5</title>
</head>
<body>

<?php
 if( isset($_GET['register']) ) {
   
?>
<h1>Please Register</h1>
<form method="post" action="program5.php">
 <?php
      echo "First";
      create_input("fname",20);
      echo "Last";
      create_input("lname",20);
      echo "<br />";
      echo "SSN";
      create_input("ssn1",3);
      create_input("ssn2",2);
      create_input("ssn3",4);
      echo "<br />";
      echo "Address";
      create_input("add1",20);
      echo "<br />";
      echo "Address";
      create_input("add2",20);
      echo "<br />";
      echo "City";
      create_input("city",10);
      echo "State";
      create_input("state",2);
      echo "<br />";
      echo "Email";
      create_input("email",20);
 ?>
<input type="submit" value="Register" />
</form>
<?php
 } else {
 ?>

 <?php } ?>

</body>
</html>
