#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>


//reçoit en ligne de com num de port 
int main( int argc, const char *argv[]){
    
    int reuse = 1;
    int received;

    //gets port number 
    int port = atoi(argv[1]);
    //creates socket 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sa;
    socklen_t salen = sizeof(sa);

   
    //attaching socket to port
    if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))<0 ){
        perror("socket failed loser");
        exit(EXIT_FAILURE);
    }

    //he struct socketaddr and attaching socket to port given in arg
    
    sa.sin_family= AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd,(struct sockaddr*)&sa, sizeof(sa) ) < 0){
        perror("bind failed LOSERRR");
        exit(EXIT_FAILURE);
    }

    //listen => kinda waits wait for client to make a move
    if( listen(sockfd, 10)<0){
        perror("listen failed loserrrr");
        exit(EXIT_FAILURE);
    }

    //new socket = fd referring to socket connected to client?
    int new_socket;
    if( new_socket = accept(sockfd, (struct sockaddr*)&sa,&salen) <0){
        perror("accept failed you loser");
        exit(EXIT_FAILURE);
    }

    while(true){
        read(new_socket, &received, sizeof(int));
        std::cout << "received : " << received << std::endl;
        shutdown(new_socket,2);
        close(new_socket);
    }

    close(sockfd);

}