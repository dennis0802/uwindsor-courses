@echo off

if "%~1"=="" (
    echo No parameters were provided. Provide a file name of the xsl and xml files [1 NAME]
    EXIT /B
)

SET htmlFile=%1.html
del %htmlFile%
SET xslFile=%1.xsl
SET xmlFile=%1.xml
java -classpath xalan.jar org.apache.xalan.xslt.Process -in %xmlFile% -xsl %xslFile% -out %htmlFile%
