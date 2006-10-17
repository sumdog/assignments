<?xml version="1.0" ?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
<xsl:output indent="yes" />
<xsl:template match="/">
<fo:root>
  <fo:layout-master-set>
     <fo:simple-page-master master-name="classes" page-width="8.5in" page-height="11in" margin="0.25in">
	    <fo:region-body margin="0.5in"/>
     </fo:simple-page-master>
  </fo:layout-master-set>
  <fo:page-sequence master-reference="classes">
     <fo:flow flow-name="xsl-region-body">
	    <fo:table table-layout="fixed">
		  <fo:table-column column-width="100px"/>
		  <fo:table-column column-width="100px"/>
		  <fo:table-column column-width="100px"/>
		  <fo:table-column column-width="100px"/>
		  <fo:table-header>
			<fo:table-row>
			  <fo:table-cell>
			    <fo:block font-weight="bold">Name</fo:block>
			  </fo:table-cell>
			  <fo:table-cell>
			    <fo:block font-weight="bold">Section</fo:block>
			  </fo:table-cell>
			  <fo:table-cell>
			    <fo:block font-weight="bold">Day</fo:block>
			  </fo:table-cell>
			  <fo:table-cell>
			    <fo:block font-weight="bold">Begin</fo:block>
			  </fo:table-cell>
			</fo:table-row>
		  </fo:table-header>
		  <fo:table-body>
		  <xsl:for-each select="qcrssch/TimeTable/Term">
			<xsl:for-each select="Class">
				<fo:table-row>
					<fo:table-cell>
						<fo:block><xsl:value-of select="Course" /></fo:block>
					</fo:table-cell>
					<fo:table-cell>
						<fo:block><xsl:value-of select="Section" /></fo:block>
					</fo:table-cell>
					<fo:table-cell>
						<fo:block><xsl:value-of select="Meetingtime/Day" /></fo:block>
					</fo:table-cell>
					<fo:table-cell>
						<fo:block><xsl:value-of select="Meetingtime/Begin" /></fo:block>
					</fo:table-cell>
				</fo:table-row>
			</xsl:for-each>
		  </xsl:for-each>	
		  </fo:table-body>
		</fo:table>
     </fo:flow>
  </fo:page-sequence>
</fo:root>
</xsl:template>
</xsl:transform>

<!--
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
-->