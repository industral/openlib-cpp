#!/bin/bash

SPATH="../.."

num=$RANDOM
num1=$RANDOM
num2=$RANDOM

echo '' | $SPATH/bin/site --parse > $SPATH/tmp/xml.xml.$num.$num1.$num2
printf "Content-Encoding: gzip\n"
printf "Content-type: application/xhtml+xml\n\n"
xsltproc $SPATH/template/content.xsl $SPATH/tmp/xml.xml.$num.$num1.$num2 | gzip - -f
# saxon8 $SPATH/tmp/xml.xml.$num.$num1.$num2 $SPATH/template/xsl.xsl | gzip - -f
rm $SPATH/tmp/xml.xml.$num.$num1.$num2
