<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
  <title>Application for Candidacy</title>
  <meta http-equiv="content-type" content="text/html;charset=iso-8859-1" />
</head>
<body>

<script type="text/javascript" src="rows.js"></script>
<h1>Application for Candidacy</h1>
<form action="generate.php" method="post">
  <h2>Student Information</h2>
  <div id="info">
   <table id="infotable">
    <tr>
      <td><label for="name">Name</label></td>
      <td><input type="text" size="50" name="name" id="name"/></td>
      <td><label for="utcid">UTC ID</label></td>
      <td><input type="text" size="50" name="utcid" id="utcid"/></td>
    </tr>
    <tr>
      <td><label for="address1">Address</label></td>
      <td><input type="text" size="50" name="address1" id="address1" /></td>
      <td><label for="address2">Phone</label></td>
      <td><input type="text" size="50" name="phone" id="phone" /></td>
    </tr>
    <tr>
      <td><label for="address2">Address</label></td>
      <td><input type="text" size="50" name="address2" id="address2" /></td>
      <td><label for="utcemail">UTC E-mail</label></td>
      <td><input type="text" size="50" name="utcemail" id="utcemail" /></td>
    </tr>
    <tr>
      <td>Degree Type</td>
      <td>
        <label for="Master">Master</label>
        <input type="radio" size="50" name="degreetype" value="Master" id="Master" />
        <label for="Specialist">Specialist</label>
        <input type="radio" size="50" name="degreetype" value="Specialist" id="Specialist" />
        <label for="Doctor">Doctor</label> 
        <input type="radio" size="50" name="degreetype" value="Doctor" id="Doctor" />
      </td>
      <td><label for="major">Major</label></td>
      <td><input type="text" size="50" name="major" id="major"/></td>
    </tr>
    <tr>
      <td><label for="concentration">Concentration</label></td>
      <td><input type="text" size="50" name="concentration" id="concentration"/></td>
      <td><label for="graduationdate">Graduation Date</label></td>
      <td><input type="text" size="50" name="graduationdate" id="graduationdate"/></td>
    </tr>
   </table>
  </div>
  <h2>Courses</h2>
  <div id="courses">
    <table id="coursestable">
    <tr><td>Term</td><td>Hours</td><td>Grade</td><td>Department</td><td>Course</td><td>Title</td></tr>
      <?php for($x=0; $x<5; $x++) { ?>
      <tr>
       <td><input type="text" size="4" name="term<?=$x?>" id="term<?=$x?>" /></td>
       <td><input type="text" size="3" name="hours<?=$x?>" id="hours<?=$x?>" /></td>
       <td><input type="text" size="4" name="grade<?=$x?>" id="grade<?=$x?>" /></td>
       <td><input type="text" size="20" name="dep<?=$x?>" id="dep<?=$x?>" /></td>
       <td><input type="text" size="20" name="course<?=$x?>" id="course<?=$x?>" /></td>
       <td><input type="text" size="20" name="title<?=$x?>" id="title<?=$x?>" /></td>
      </tr>
      <?php } ?>
    </table><br />
  </div>
  <h2>Transfered Courses</h2>
  <div id="tcourses">
    <table id="tcoursestable">
    <tr><td>Term</td><td>Hours</td><td>Grade</td><td>Department</td><td>Course</td><td>Title</td></tr>
      <?php for($x=0; $x<5; $x++) { ?>
      <tr>
       <td><input type="text" size="4" name="tterm<?=$x?>" id="tterm<?=$x?>" /></td>
       <td><input type="text" size="3" name="thours<?=$x?>" id="thours<?=$x?>" /></td>
       <td><input type="text" size="4" name="tgrade<?=$x?>" id="tgrade<?=$x?>" /></td>
       <td><input type="text" size="20" name="tdep<?=$x?>" id="tdep<?=$x?>" /></td>
       <td><input type="text" size="20" name="tcourse<?=$x?>" id="tcourse<?=$x?>" /></td>
       <td><input type="text" size="20" name="ttitle<?=$x?>" id="ttitle<?=$x?>" /></td>
      </tr>
      <?php } ?>
    </table><br />
  </div>
  <div id="miscopts">
    <br />
    <label for="totalhours">Total Hours</label>
    <input type="text" size="10" name="totalhours" id="totalhours" />
    <br /><br />
    <label for="examreq">Exam Required</label>
    <select id="examreq" name="examreq">
      <option value="yes">Yes</option>
      <option value="no">No</option>
    </select>
  </div>
  <h2>Signatures</h2>
  <div id="sigs">
    <table id="sigtabl">
      <tr>
         <td><label for="sigapp">Applicant</label></td>
         <td><input type="text" name="sigapp" id="sigapp" size="20" /></td>
      </tr>
      <tr>
         <td><label for="sigadv">Advisor</label></td>
         <td><input type="text" name="sigadv" id="sigadv" size="20" /></td>
      </tr>
      <tr>
         <td><label for="sigdir">Director</label></td>
         <td><input type="text" name="sigdir" id="sigdir" size="20" /></td>
      </tr>
      <tr>
         <td><label for="sigdean">Dean</label></td>
         <td><input type="text" name="sigdean" id="sigdean" size="20" /></td>
      </tr>
    </table>
  </div>

  <p><input type="submit" value="Create XML" /></p>
</form>

</body>
</html>
