<?php
  header("Content-Type: text/html; charset=ISO-8859-1");

  $datadir = "/tmp";


  function create_input($name,$size) {
    echo "<input type=\"text\" size=\"$size\" value=\"{$_POST[$name]}\" name=\"$name\" />";
  }
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strictl.dtd">
<html>
<head>
  <title>Sumit Khanna's CSC4800 Program #5</title>
</head>
<body>

<?php
   $err = Array();
  
   if(!is_numeric($_POST['ssn1']) || !is_numeric($_POST['ssn2']) || !is_numeric($_POST['ssn3']) ||
        strlen($_POST['ssn1']) != 3 || strlen($_POST['ssn2']) != 2 || strlen($_POST['ssn3']) != 4 ) {
     $err[] = "Invalid Social Security Number";
   }

   if(!ctype_alpha($_POST['fname'])) { $err[] = "Invalid First Name"; }
   if(!ctype_alpha($_POST['lname'])) { $err[] = "Invalid Last Name"; }
   if(!is_numeric($_POST['zip']))    { $err[] = "Invalid Zip Code"; }
   if(!ctype_alpha($_POST['state']) && strlen($_POST['state']) != 2) { $err[] = "Invalid State"; }

 if( !isset($_GET['register']) || count($err) > 0 ) {
?>
<h1>Please Register</h1>
<form method="post" action="program5.php?register=1"><p>
 <?php
      if(count($err)>0 && isset($_GET['register'])) {
        foreach ($err as $e) {
          echo "<span style=\"color: red\">Error: $e<br/></span>";
	}
        echo "<br /><br />";	
      }
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
      echo "Zip";
      create_input("zip",5);
      echo "<br />";
      echo "Email";
      create_input("email",20);
      echo "<br />";
 ?>
<input type="submit" value="Register" />
</p></form>
<?php
 } else {
   echo "<p>Data Posted</p>";
   $fd = fopen($datadir."/".$_POST['ssn1'].$_POST['ssn2'].$_POST['ssn3'],"w");
   fwrite($fd,"Last Name:".$_POST['lname']."\n");
   fwrite($fd,"First Name:".$_POST['fname']."\n");
   fwrite($fd,"Address:".$_POST['add1']."\n");
   fwrite($fd,"Address:".$_POST['add2']."\n");
   fwrite($fd,"City:".$_POST['city']."\n");
   fwrite($fd,"State:".$_POST['state']."\n");
   fwrite($fd,"Zip:".$_POST['zip']."\n");
   fwrite($fd,"Email:".$_POST['email']."\n");
   fflush($fd);
   fclose($fd);
    
 }
 ?>


</body>
</html>
