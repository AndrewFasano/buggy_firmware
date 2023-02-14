 // Server side implementation of UDP client-server model. With bugs
 // Based on https://www.geeksforgeeks.org/udp-server-client-implementation-c/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   
#define MAXLINE 128
   
// Driver code
int main(int argc, char** argv) {
    int sockfd;
    char buffer[MAXLINE];
    char *b;
    struct sockaddr_in servaddr, cliaddr;

    // USAGE: ./udp_server port key
    int port = atoi(argv[1]);
    char *key = argv[2];
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        puts("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        puts("bind failed");
        exit(EXIT_FAILURE);
    }
       
    socklen_t len;
  int n;
   
    len = sizeof(cliaddr);  //len is value/result
   
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);

    if (strncmp(key, buffer, strlen(key)) != 0) {
      printf("Ignoring input with bad key: %s\n", buffer);
      return 0;
    }

    b = (char*) (&buffer[strlen(key)]);

    // Let's foolishly assume the first int worth of data is a size
    uint32_t provided_size = ((uint32_t*)b)[0];

    printf("Client size is %u\n", provided_size);

    // Then advance past that
    b += sizeof(uint32_t);

    // And null terminate there
    b[provided_size] = '\0';

    printf("Client payload is: %s\n", b);

    return 0;
} 
