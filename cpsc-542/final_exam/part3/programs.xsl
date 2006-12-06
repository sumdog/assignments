<?xml version="1.0" ?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output omit-xml-declaration="no" method="html" encoding="UTF-8" doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" />
	<xsl:template match="/">
		<html>
			<head>
			</head>
			<body>
				<h1>Program Listings</h1><br />
				<table style="width: 100%;">
					<tr>
						<th>Show</th>
						<th>Channel</th>
						<th>Start</th>
						<th>End</th>
						<th>Genre</th>
						<th>Staring</th>
					</tr>
					<xsl:for-each select="tvShows/program">
						<tr>
							<td><xsl:value-of select="./item/showTitle" /></td>
							<td><xsl:value-of select="./item/channel/@name" /> (<xsl:value-of select="./item/channel/@number" />)</td>
							<td><xsl:value-of select="./item/startTime" /></td>
							<td><xsl:value-of select="./item/endTime" /></td>
							<td><xsl:value-of select="./info/category" /></td>
							<td>
								<xsl:for-each select="./info/actor" >
								   <xsl:value-of select="." /><xsl:text disable-output-escaping="yes">&amp;</xsl:text>nbsp;
							    </xsl:for-each>
							</td>
						</tr>
					</xsl:for-each>
				</table>
			</body>
		</html>
	</xsl:template>
</xsl:transform>
