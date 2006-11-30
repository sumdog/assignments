#!/bin/sh

for i in plays/*.xml; do
  CLASSPATH=".:./xercesImpl.jar" java Search SAX $i $1
done
