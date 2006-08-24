<?php
  require_once 'lib.php'; 
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
  <title>Sumit Khanna's CPSC-542 Homework Page</title>
  <meta http-equiv="content-type" content="text/html;charset=iso-8859-1" />
  <link rel="StyleSheet" href="main.css" type="text/css" />
</head>
<body>

  <div id="titlebox">Sumit Khanna's <br />CPSC-542 Homework Page</div>

  <div id="contents">
    <table>
      <tr>
         <th>#</th><th>Description</th>
      </tr>
         <?php echo display_assignments(load_assignments()); ?>
    </table>
  </div>

</body>
</html>
