Goodrich code exerpts

How to run on local machine outside of IDE:
cd src
javac HelloUniverse.java
java HelloUniverse

IMPORTANT! This works if the code is not encapsulated in package. If a package is used then use the IDE to run the code, it's simpler.

TODO IMPORTANT! Find a way to run the code from command line... found a way

From project top level:
192-168-0-105:goodrich adrianpoplesanu$ pwd
/Users/adrianpoplesanu/Documents/git-projects/personal-work/java/goodrich

mkdir classes
192-168-0-105:goodrich adrianpoplesanu$ javac -d classes/ src/chapter1/*.java
192-168-0-105:goodrich adrianpoplesanu$ java -cp classes/ chapter1.CounterDemo
