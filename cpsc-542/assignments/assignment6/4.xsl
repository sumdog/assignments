<?xml version="1.0" ?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output omit-xml-declaration="no" method="xml" encoding="UTF-8" />
<xsl:template match="/">
	<classes>
		<xsl:for-each select="qcrssch/TimeTable/Term/Class">
			<class>
				<xsl:attribute name="name">
					<xsl:value-of select="Course" />
				</xsl:attribute>
				<xsl:attribute name="section">
					<xsl:value-of select="Section" />
				</xsl:attribute>
				<xsl:attribute name="instructor">
					<xsl:value-of select="Instructor" />
				</xsl:attribute>
			</class>
		</xsl:for-each>
	</classes>
</xsl:template>
</xsl:transform>