#!/bin/sh
xsltproc 5.xsl ClassSchedule.xml > fo.xml && fop fo.xml classes.pdf
