<?xml version="1.0" ?>
<xsl:transform version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
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
     <xsl:for-each select="application/information">
        
     </xsl:for-each>
    </div>
    
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

    <div class="boldheading"><xsl:value-of select="application/notes/@title"/></div>
    <ul>
      <xsl:for-each select="application/notes/note">
        <li><xsl:value-of select="." /></li>
      </xsl:for-each>
    </ul>

  </body>
  </html>
</xsl:template>

</xsl:transform>
