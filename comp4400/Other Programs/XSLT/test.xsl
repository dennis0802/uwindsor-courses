<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="test">
    <html> 
        <head>
            <title>COMP-4400 Online Test</title>
        </head>

        <body>
            <h1>COMP-4400 Online Test</h1>
            <form>
                <xsl:apply-templates select="Q"/>
            </form>
        </body>
    </html>
</xsl:template>

<xsl:template match="Q">
    <p><xsl:value-of select="question"/></p>
    <ol type="A">
        <xsl:apply-templates select="item"/>
    </ol>
</xsl:template>

<xsl:template match="item">
    <li><xsl:value-of select="."/></li>
</xsl:template>

<!--
<xsl:template match="item">
    <input type="radio" name="answer">
        <xsl:attribute name="value">
            <xsl:value-of select="."/>
        </xsl:attribute>
        <xsl:attribute name="id">
            <xsl:value-of select="."/>
        </xsl:attribute>
    </input>
    <label>
        <xsl:attribute name="for">
            <xsl:value-of select="."/>
        </xsl:attribute>
        <xsl:value-of select="."/><br></br>
    </label>
</xsl:template>
-->

</xsl:stylesheet>