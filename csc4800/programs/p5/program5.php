<?php
  function create_input($name,$size) {
    echo "<input type=\"text\" value=\"{$_POST[$name]}\" name=\"$name\" />";
  }
?>
<!DOCTYPE >
<html>
<head>
  <title>Sumit Khanna's CSC4800 Program #5</title>
</head>
<body>

<?php
 if( !isset($_GET['register']) ) {
?>
<h1>Please Register</h1>
<form method="post" action="program5.php">

</form>
<?php
 } else {
 ?>

 <?php } ?>

</body>
</html>
