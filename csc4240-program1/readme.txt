CSC 4240 - Program #1
Sumit Khanna

I wrote my program with Java and compiled/debuged it using the Apache Ant build file (build.xml, similar in nature to a Makefile). 

To Compile with ant:
   ant compile

To make a jar file with ant:
   ant jar

You can also compile it without ant by running javac from the root:
   javac sum/driver/Main.java

This will place all the compiled files within the sum and org directories instead of a seperate build directory. For simplicity, a compiled jar file has been included and can be run like this:

java -jar puzzle.jar [-g] <inputfile>

You must specify an inputfile. The -g is optional and will bring up a graphical representation of the nodes for debugging only. Omitting the -g will cause the program to run it's search and output the result to console. You can redirect that output to a file like so:

java -jar puzzle.jar -g sampleinput/sum1.txt > output.txt

If you have any problems, please email me at SKhanna21@tntech.edu

