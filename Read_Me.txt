/*
Read Me:

Summary:
This is an implementation of a combined graph (Graff) and hashtable (HasTble).
Compile and run the Main function, with the necessary linking of the Graff and HasTble functions.
The vector and queue libraries are necessary for this implementation to work (you should already
have them).  This program is designed to determine distances between objects, which are either
input with a file, or manually.  It was written on a unix machine, but any C++ compiler should
be capable of handling it.

How to Run:
Run the Main function either with the name of a file of similar format to zombieCities.txt (see
below for more details) or with no command-line arguments.  The menu will appear and explain
possible inputs.  You may exit anytime after the menu appears by pressing '0' or 'quit'.  The
menu will appear when a function has finished running.  Of course, in many systems  ctr+c should
exit the program should it crash for any reason.

Dependencies:
This program currently uses vector and queue libraries, as well as other standard C++ libraries.
All necessary libraries should be included in any modern C++ compiler.

System Requirements:
Should be able to run on any system after compiled.

Open Issues/Bugs:
Depth-first search currently not working, returns erroneous results - shows every node except the one
that is started from.


Appendix:
expected txt file format:

nodetype,city1,city2,city3
city1,0,-1,5
city2,-1,0,9
city3,5,9,-1



*/
