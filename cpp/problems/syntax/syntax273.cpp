#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    memset(recvBuff, '0', sizeof(recvBuff));
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5003); 
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    std::string text = "";

    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0) {
        recvBuff[n] = 0;
        text += recvBuff;
    }

    std::cout << "hap hap hap:\n" << text << "\n";

    return 0;
}