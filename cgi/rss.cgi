#!/bin/sh

num=$RANDOM
num1=$RANDOM
num2=$RANDOM

echo '' | ./site --parse > ../tmp/xml.xml.$num.$num1.$num2
# printf "Content-Encoding: gzip\n"
printf "Content-type: application/rss+xml; charset=utf-8\n\n"
# printf "Content-type: application/xml; charset=utf-8\n\n"
xsltproc ../rss.xsl ../tmp/xml.xml.$num.$num1.$num2
# xsltproc ../rss.xsl ../tmp/xml.xml.$num.$num1.$num2 | gzip - -f
rm ../tmp/xml.xml.$num.$num1.$num2
