<?xml version='1.0'?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"> 
<xsl:template match="para">
    <p><xsl:apply-templates/></p>
</xsl:template> 
<xsl:template match="emphasis"> 
    <i><xsl:apply-templates/></i> 
</xsl:template>
<xsl:template match="strong">
    <b><xsl:apply-templates/></b>
</xsl:template>

</xsl:stylesheet>