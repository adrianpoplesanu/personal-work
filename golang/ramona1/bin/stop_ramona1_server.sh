# command to kill ramona1 process
pkill -9 -f "/home/ubuntu/tmp/go/bin/go run /home/ubuntu/Documents/git-projects/personal-work/golang/ramona1/main.go" ;
ps ax | grep 'go-build' | awk -F ' ' '{print $1}' | xargs sudo kill -9 ;
#pkill -9 go-build ;
echo "stop command finished"
