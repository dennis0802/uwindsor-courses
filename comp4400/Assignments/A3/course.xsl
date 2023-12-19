<!--
    Student Name: Dennis Dao
    Student Number: 110010116
    Date: Oct 16, 2023
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="courses">
<html>
    <head>
        <title>University Courses</title>
        <script>
            function addDisplay (details) {
                document.write(details);
            }
        </script>
    </head>
    <body>
        <table border="1">
        <tr>
            <th>Course No.</th>
            <th>Course Title</th>
            <th>Prof</th>
            <th>Year</th>
            <th>Days</th>
            <th>Time</th>
            <th>Location</th>
        </tr>
            <xsl:apply-templates select="course[@acad_year &gt; 2002]"/>
        </table>
    </body>
</html>
</xsl:template>

<xsl:template match="course">
<tr>
    <td><xsl:apply-templates select="course_num"/></td>
    <td><a>
        <xsl:attribute name="href">JavaScript:addDisplay('<xsl:value-of select="description"/>');
        </xsl:attribute>
        <xsl:value-of select="title"/>
        </a>
    </td>
    <td><xsl:apply-templates select="course_head/person/person_name"/></td>
    <td><xsl:value-of select="@acad_year"/></td>
    <td><xsl:apply-templates select="meeting/meeting_days"/></td>
    <td><xsl:apply-templates select="meeting/meeting_begin"/> - <xsl:apply-templates select="meeting/meeting_end"/></td>
    <td><xsl:apply-templates select="meeting/location"/></td>

</tr>
</xsl:template>

<xsl:template match="course_head/person/person_name | course_num">
    <xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if>
    <xsl:if test="position()!=last()"><xsl:value-of select="."/>, </xsl:if>
</xsl:template>

<xsl:template match="meeting/*">
    <xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>

