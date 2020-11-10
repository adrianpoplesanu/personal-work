a test nodejs library written in c++
// https://medium.com/jspoint/a-simple-guide-to-load-c-c-code-into-node-js-javascript-applications-3fcccf54fd32

# install globally node-gyp
npm install -g node-gyp

# dependencies for node-gyp prior to running npm install -g node-gyp
Python v2.7, v3.5, v3.6, v3.7, or v3.8
make
A proper C/C++ compiler toolchain, like GCC

npm init -y

npm install -S node-addon-api

mkdir src
cd src

vim greeting.h
vim greeting.cpp
vim index.cpp

cd ..

node-gyp configure

node-gyp build

vim index.js

#my versions
Adrians-MacBook-Pro:test1 adrianpoplesanu$ node --version
v10.13.0
Adrians-MacBook-Pro:test1 adrianpoplesanu$ npm --version
6.4.1
Adrians-MacBook-Pro:test1 adrianpoplesanu$ g++ --version
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
Apple LLVM version 8.0.0 (clang-800.0.42.1)
Target: x86_64-apple-darwin16.7.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
Adrians-MacBook-Pro:test1 adrianpoplesanu$
