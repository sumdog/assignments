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

  </body>
  </html>
</xsl:template>

</xsl:transform>
