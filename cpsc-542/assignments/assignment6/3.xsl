<?xml version="1.0" ?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
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
       <tr>
         <th>Name</th>
         <th>Section</th>
         <th>Day</th>
         <th>Begin</th>
	 <th>Current</th>
	 <th>Limit</th>
       </tr>
     <xsl:for-each select="Class[Current > Limit * .80]">
       <tr>
         <td><xsl:value-of select="Course" /></td>
	 <td><xsl:value-of select="Section" /></td>
	 <td><xsl:value-of select="Meetingtime/Day" /></td>
	 <td><xsl:value-of select="Meetingtime/Begin" /></td>
         <td><xsl:value-of select="Current" /></td>
         <td><xsl:value-of select="Limit" /></td>
       </tr>
     </xsl:for-each>
     </table>
     
    </xsl:for-each>
  </body>
  </html>
</xsl:template>
</xsl:transform>
