CSC 4800/3400 Program #2
Sumit Khanna

The goal of this program is to make an address book server in C/C++ for U*ix and a client for the server in Java that will run on any platform.

For the impatient:

To build and run the server:
	cd server
	./configure
	make
	cd src
	./csc4800server <port>

To build and run the client:
	cd client
	ant jar
	java -jar ./csc4800client

To compile the server, you will need the GNU build tools.
To compile the client, you will need Apache ant*.

*(if you do not have a copy of ant installed, a precompiled jar file has been supplied in the client directory.)

Directory Breakdown

server - autoconf files for building the server
	src - source code and eventual location of built binary
client - build.xml for ant, precompiled jar
	src - source code
	bin - build class files (created after ant is run)
	doc - javadoc documentation (created if you run ant doc)


That's all there is to it. If you don't have ant, you can run "apt-get ant" in Debian or "emerge ant" in Gentoo. Here are the tool versions I have tested the client and server on with my Gentoo Linux system:

ant-1.6.2-r6
blackdown-jdk-1.4.2_rc1-r1
autoconf-2.59-r4
make-3.80
gcc-3.3.4-r1
glibc-2.3.3.20040420-r1
I have extensively debugged this program and have run it through the valgrind memory debugger. If you have any questions, feel free to email me at sumdog@gmail.com