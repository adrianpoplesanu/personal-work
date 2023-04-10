// server socket research for Ad
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5003);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);

    while(1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        std::cout<<"someone connected!\n";

        ticks = time(NULL);
        //snprintf(sendBuff, sizeof(sendBuff), "Adrian's MAC time: %.24s\r\n", ctime(&ticks));
        snprintf(sendBuff, sizeof(sendBuff), "buna dimineata!\r\n");
        write(connfd, sendBuff, strlen(sendBuff));

        close(connfd);
        sleep(1);
     }

    return 0;
}