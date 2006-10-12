<?xml version="1.0" ?>
<xsl:transform version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output omit-xml-declaration="no" method="html" encoding="UTF-8" doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" />
<xsl:template match="/">
  <html>
  <head>
    <title>Class Schedule</title>
  </head>
  <body>
    <xsl:for-each select="qcrssch/TimeTable/Term">
     <h1><xsl:value-of select="TermName"/></h1><br />

     
     <table border="1">
     <xsl:for-each select="Class">
     <tr><td colspan="4"><xsl:value-of select="Course" /></td></tr>
     
       <tr>
         <th>Name</th>
         <th>Section</th>
         <th>Day</th>
         <th>Begin</th>
       </tr>
     </xsl:for-each>
     </table>
     
    </xsl:for-each>
  </body>
  </html>
</xsl:template>
</xsl:transform>