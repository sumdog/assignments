CSC3400/4800 Program #4 (Dr. Rogers)
Sumit Khanna

My CSC3400 program consists of two scripts

tag.tcl - The original Tag Agent
shieldtag.tcl - Tag Agent with shields and visited list

Usage:

./tag.tcl <number of agents> [computers ...]
./shieldtag.tcl <level of shield> <number of agents> [computers ...]

Example:

./tag.tcl 5 raphael rocksteady donatello

(*and yes I have DNS and yes all my computers are in fact named after characters from the Teenage Mutant Ninja Turtles cartoon show)

The programs will produce an output file called taggame.log. It's best of this file resides on a shared file system (NFS for example) so that all the agents can write to one log file)


Strategy for sheidltag:

Really there's nothing that I tried that really improved the shielded agent's success rate. What helps is to give the sheildtag an extra computer in its command like argument that you don't give the regular agent. This provides it an extra "safe" computer for it to migrate to.


Testing:
I tested my program using three Linux boxes (two ix86 and one ppc) all of which ran Gentoo Linux.
