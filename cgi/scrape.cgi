#!/bin/sh

printf "Content-Encoding: gzip\n"
printf "Content-type: text/plain\n\n"
echo '' | ../../bin/scrape | gzip - -f
