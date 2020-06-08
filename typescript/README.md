# How to create a typescript project with npm

mkdir test1
cd test1
npm init
npm install typescript
vim index.ts
./node_modules/typescript/bin/tsc index.ts




in the vim portion i wrote:
console.log("tester");

then executed .js with
node index.js


optionally:
touch compile.sh
echo ./node_modules/typescript/bin/tsc index.ts >> compile.sh
. compile.sh
node index.js
