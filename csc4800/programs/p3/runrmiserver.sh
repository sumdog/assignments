#!/bin/sh
if [ -f ./RMI.jar ]; then
 echo "Running RMI Server..."
 CLASSPATH="./RMI.jar" rmiregistry
else
 echo "Could not find RMI.jar. Please run 'ant jar' to generate jar file";
fi
