<?xml version="1.0" ?>
<xsl:transform version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output omit-xml-declaration="no" method="html" encoding="UTF-8" doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" />
<xsl:template match="/">
  <html>
  <head>
    <link rel="StyleSheet" href="app-xsl.css" type="text/css" />
  </head>
  <body>
    <div id="heading">
     <span id="title"><xsl:value-of select="application/head/title"/></span>
     <span id="school"><xsl:value-of select="application/head/school" /></span>
     <span id="university"><xsl:value-of select="application/head/university" /></span>
    </div>
     <h2>Student Information</h2>
     <table>
     <xsl:for-each select="application/information/*">
        <tr>
          <td>
            <xsl:value-of select="name()" /> 
          </td>
          <td>
            <input type="text" />
          </td>
        </tr>
     </xsl:for-each>
     </table>
   
 
    <h2>Courses</h2>
    <table>
       <tr><th>Term</th><th>Hours</th><th>Grade</th><th>Department</th><th>Course</th><th>Title</th></tr>
       <xsl:for-each select="application/courses/course">
         <tr>
            <xsl:for-each select="@*">
              <td><input type="text" /></td>
            </xsl:for-each>
         </tr>
       </xsl:for-each>
    </table>

    <h2>Transfered Courses</h2>
    <table>
       <tr><th>Term</th><th>Hours</th><th>Grade</th><th>Department</th><th>Course</th><th>Title</th></tr>
       <xsl:for-each select="application/transfercourses/course">
         <tr>
            <xsl:for-each select="@*">
              <td><input type="text" /></td>
            </xsl:for-each>
         </tr>
       </xsl:for-each>
     </table>
    <br />
    <br />
       <table>
        <tr>
          <td><label for="exam">Exam</label></td>
          <td><select id="exam"><option>Yes</option><option>No</option></select></td>
          <td><label for="totalhours">Total Hours</label></td>
          <td><input id="totalhours" /></td>
        </tr>

       </table>
    <br />
    <h2>Signatures</h2>
    <table>
       <xsl:for-each select="application/signatures/sig">
         <tr>
           <td><xsl:value-of select="./@type" /></td><td><input type="text" /></td><td>Date</td><td><input type="text" /></td>
         </tr>
       </xsl:for-each>
    </table>
    <br /><br />
    <input type="submit" value="Submit" id="submit" /><br /><br />
    <div class="boldheading"><xsl:value-of select="application/notes/@title"/></div>
    <ul>
      <xsl:for-each select="application/notes/note">
        <li><xsl:value-of select="." /></li>
      </xsl:for-each>
    </ul>

    <div id="footer">
      <xsl:value-of select="application/footer" />
    </div>

  </body>
  </html>
</xsl:template>

</xsl:transform>
