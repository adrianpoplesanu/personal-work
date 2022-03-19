mai intai am scris CppLibrary2.java

apoi am rulat comenzile:

javac CppLibrary2.java
javah -jni CppLibrary2

ultima comanda a generat un fisier .h
apoi am scris fisierul cpp pe baza headerului creat mai sus si apoi am rulat:

g++ "-I/System/Library/Frameworks/JavaVM.framework/Versions/A/Headers" -c CppLibrary2.cpp
g++ -dynamiclib -o libcpplibrary2.jnilib CppLibrary2.o

apoi am rulat totul cu:
java CppLibrary2
