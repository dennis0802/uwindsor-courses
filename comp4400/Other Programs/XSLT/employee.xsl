<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- For this xsl, comment out whatever I don't want to actively run -->
<!-- EX. 1 alternate -->
<!--
<xsl:template match="employee/supervisor">
    <xsl:value-of select="firstName"/>  <xsl:value-of select="surName"/>
</xsl:template>
-->

<!-- Axis -->
<!--
<xsl:template match="supervisor/employee">
 ancestor node of <xsl:value-of select="firstName"/> is 
 <xsl:value-of select="ancestor::employee/firstName"/>
 </xsl:template>
 <xsl:template match="employee">
 <xsl:apply-templates select="supervisor/employee"/>
 </xsl:template>
-->

<!-- Predicates -->
<!--
<xsl:template match="source">
 <xsl:for-each select="employee[1]">
 <xsl:value-of select="firstName"/>
 </xsl:for-each>
 </xsl:template>
 -->

<!-- XPath expression -->
<!--
<xsl:template match="source">
 <xsl:for-each select= "//employee"> 
 <tr> <xsl:apply-templates select="surName"/>
 <xsl:apply-templates select="firstName"/>
 </tr>
</xsl:for-each>
</xsl:template>
<xsl:template match="surName | firstName">
 <td> <xsl:value-of select="."/> </td>
</xsl:template>
-->

<!-- More than one case-->
<!--
<xsl:template match="source">
 <xsl:for-each select="employee/supervisor/employee | employee"> 
 <tr> <xsl:apply-templates select="surName"/>
 <xsl:apply-templates select="firstName"/>
 </tr>
 </xsl:for-each>
</xsl:template>
<xsl:template match="surName | firstName">
 <td> <xsl:value-of select="."/> </td>
</xsl:template>
-->

<!-- XPaths select relative nodes to its context-->
<!--
<xsl:template match="source">
 <xsl:for-each select="employee/supervisor/employee"> 
 <tr> <xsl:apply-templates select="surName"/></tr>
 </xsl:for-each>
</xsl:template>
<xsl:template match="surName">
 <td> <xsl:value-of select="."/> </td>
</xsl:template>
-->

<!-- XPaths and foreach-->
<!--
<xsl:template match="source">
 <xsl:for-each select="employee"> 
 <tr> <xsl:apply-templates select="surName"/></tr>
 </xsl:for-each>
</xsl:template>
<xsl:template match="surName">
 <td> <xsl:value-of select="."/> </td>
</xsl:template>
-->

<!-- Priority rules-->
<!--
<xsl:template match="employee"> 
     doing this
</xsl:template>
<xsl:template match="source/employee"> 
    doing that
</xsl:template>
-->

<!-- Selecting employees and their names -->
<!--
<xsl:template match="employee">
    <tr> <xsl:apply-templates /> </tr>
</xsl:template>
<xsl:template match="surName">
    <td> <xsl:value-of select="."/> </td>
</xsl:template>
<xsl:template match="firstName">
    <td> <xsl:value-of select="."/> </td>
</xsl:template>
-->

<!-- Only employees -->
<!--
<xsl:template match="employee">
    <tr> <xsl:apply-templates select="surName" /> 
    <xsl:apply-templates select="firstName" /> 
    </tr>
</xsl:template>

<xsl:template match="surName | firstName">
    <td> <xsl:value-of select="."/> </td>
</xsl:template>
-->

<!-- For employees who are supervisors -->
<!--<xsl:template match="employee">
    <xsl:apply-templates select="supervisor"/>
</xsl:template>

<xsl:template match="employee/supervisor/employee">
    first name is <xsl:value-of select="firstName"/>
</xsl:template>-->

<!-- Extracting 1st names under supervisors -->
<!--
<xsl:template match="source">
    <xsl:apply-templates select="employee"/>
</xsl:template>

<xsl:template match="source/employee">
    <xsl:apply-templates select="supervisor"/>
</xsl:template>

<xsl:template match="supervisor">
    <xsl:apply-templates select="employee"/>
</xsl:template>

<xsl:template match="supervisor/employee[1]">
    <xsl:value-of select="firstName"/>
</xsl:template>

<xsl:template match="supervisor/employee[position()>1]">
    ,<xsl:value-of select="firstName"/>
</xsl:template>-->

<!-- Midterm example -->
<xsl:template match="source/employee">
</xsl:template>

<xsl:template match="employee/supervisor/employee">
    first name is <xsl:value-of select="firstName"/>
</xsl:template>

</xsl:stylesheet>