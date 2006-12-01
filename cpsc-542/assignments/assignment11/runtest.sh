#!/bin/sh

echo "Play,SAX,DOM";
for i in plays/*.xml; do
  CLASSPATH=".:./xercesImpl.jar" java Search $i lord 1> /dev/null
done
