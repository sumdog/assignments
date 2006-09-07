<?php
// CPSC 542php file that generates xml

  $xml = "<?xml version=\"1.0\"?>\n"
       . "  <!DOCTYPE application [\n"
       . "  <!ELEMENT application (information,courses,transfercourses,exam,totalhours,signatures)>\n"
       . "  <!ELEMENT information (name,utcid,address,address?,phone,degreetype,major,concentration,graduationdate,utcemail)>\n"
       . "  <!ELEMENT name (#PCDATA)>\n"
	     . "  <!ELEMENT utcid (#PCDATA)>\n"
	     . "  <!ELEMENT address (#PCDATA)>\n"
	     . "  <!ATTLIST address line (1|2) \"1\">\n"
	     . "  <!ELEMENT phone (#PCDATA)>\n"
	     . "  <!ELEMENT degreetype (#PCDATA)>\n"
	     . "  <!ATTLIST degreetype type (Master|Specialist|Doctor) #REQUIRED>\n"
	     . "  <!ELEMENT major (#PCDATA)>\n"
	     . "  <!ELEMENT concentration (#PCDATA)>\n"
	     . "  <!ELEMENT graduationdate (#PCDATA)>\n"
	     . "  <!ELEMENT utcemail (#PCDATA)>\n"
	     . "  <!ELEMENT courses (course*)>\n"
	     . "  <!ELEMENT course EMPTY>\n"
	     . "  <!ATTLIST course term CDATA \"\">\n"
	     . "  <!ATTLIST course hours CDATA \"\">\n"
	     . "  <!ATTLIST course grade CDATA \"\">\n"
	     . "  <!ATTLIST course department CDATA \"\">\n"
	     . "  <!ATTLIST course course CDATA \"\">\n"
	     . "  <!ATTLIST course title CDATA \"\">\n"
	     . "  <!ELEMENT transfercourses (course*)>\n"
	     . "  <!ELEMENT exam EMPTY>\n"
	     . "  <!ATTLIST exam required (Yes|No) \"Yes\">\n"
	     . "  <!ELEMENT totalhours (#PCDATA)>\n"
	     . "  <!ELEMENT signatures (sig*)>\n"
	     . "  <!ELEMENT sig (#PCDATA)>\n"
	     . "  <!ATTLIST sig type (applicant|advisor|director|dean) #IMPLIED>\n"
	     . "  <!ATTLIST sig date CDATA #IMPLIED>\n"
	     . "]>\n"
	     . "<application>\n"
	     . "  <information>\n"
	     . "    <name>" . $_POST["name"] . "</name>\n"
	     . "    <utcid>" . $_POST["utcid"] . "</utcid>\n"
	     . "    <address line=\"" . $_POST["address1"] . "\"/>\n"
	     . "    <address line=\"" . $_POST["address2"] . "\"/>\n"
	     . "    <phone>" . $_POST["phone"] . "</phone>\n"
	     . "    <degreetype type=\"" . $_POST["degreetype"] . "\"/>\n"
	     . "    <major>" . $_POST["major"] . "</major>\n"
	     . "    <concentration>" . $_POST["concentration"] . "</concentration>\n"
	     . "    <graduationdate>" . $_POST["graduationdate"] . "</graduationdate>\n"
	     . "    <utcemail>" . $_POST["utcemail"] . "</utcemail>\n"
	     . "  </information>\n"
	     . "  <courses>\n";
  for ($x=0; $x<5; $x++)
  {
    $xml .= "    <course term=\"" . $_POST["term$x"] . "\" hours=\"" . $_POST["hours$x"] . "\" grade=\"" . $_POST["grade$x"] . "\" department=\"" . $_POST["dep$x"] . "\" course=\"" . $_POST["course$x"] . "\" title=\"" . $_POST["title$x"] . "\"/>\n";
  }
  $xml .= "  </courses>\n"
       .  "  <transfercourses>\n";
  for ($x=0; $x<5; $x++)
  {
    $xml .= "    <course term=\"" . $_POST["tterm$x"] . "\" hours=\"" . $_POST["thours$x"] . "\" grade=\"" . $_POST["tgrade$x"] . "\" department=\"" . $_POST["tdep$x"] . "\" course=\"" . $_POST["tcourse$x"] . "\" title=\"" . $_POST["ttitle$x"] . "\"/>\n";
  }
  
  $xml .= "  </transfercourses>\n"
       .  "  <exam required=\"" . $_POST["examreq"] . "\"/>\n"
       .  "  <totalhours>" . $_POST["totalhours"] . "</totalhours>\n"
       .  "  <signatures>\n"
       .  "    <sig type=\"applicant\" date=\"\"/>\n"
       .  "    <sig type=\"advisor\" date=\"\"/>\n"
       .  "    <sig type=\"director\" date=\"\"/>\n"
       .  "    <sig type=\"dean\" date=\"\"/>\n"
       .  "  </signatures>\n"
       .  "</application>";
  header("Content-type: text/xml");
  echo $xml;  
?>
