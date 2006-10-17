<?xml version="1.0" ?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
<xsl:output indent="yes" />
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
       </tr>
     <xsl:for-each select="Class">
       <tr>
         <td><xsl:value-of select="Course" /></td>
	 <td><xsl:value-of select="Section" /></td>
	 <td><xsl:value-of select="Meetingtime/Day" /></td>
	 <td><xsl:value-of select="Meetingtime/Begin" /></td>
       </tr>
     </xsl:for-each>
     </table>
     
    </xsl:for-each>
  </body>
  </html>
</xsl:template>
</xsl:transform>
