run go main.go

python analyzer.py <file-name.jpg>

POST localhost:9191/upload - file field

fisierele uploadate respecta un naming convention
TODO: naming conventionul sa fie bazat pe time stamp

Requirements:
- dlib, face_recognition python packages installed with pip3
https://gist.github.com/ageitgey/629d75c1baac34dfa5ca2a1928a7aeaf
https://github.com/ageitgey/face_recognition

Install golang 1.12 on Ubuntu:
sudo apt-get update
sudo apt-get -y upgrade
cd /tmp
wget https://dl.google.com/go/go1.12.linux-amd64.tar.gz
sudo tar -xvf go1.11.linux-amd64.tar.gz

Run on ubuntu:
/tmp/go/bin/go run main.go

Or simply:
start_server.sh

To test analyze.py:
python3 analize.py adri.jpg
also:
python3 test_face_recognition2.py adri.jpg
python3 test_face_recognition3.py adri.jpg

.bashrc:
echo "Welcome Adri to the Amazon server!"
export GO_SOURCE='/home/ubuntu/tmp/go/bin'
export GO_EXECUTABLE='/home/ubuntu/tmp/go/bin/go'
export APP_HOME='/home/ubuntu/Documents/git-projects/personal-work/golang/ramona1'
