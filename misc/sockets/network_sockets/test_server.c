// https://man7.org/linux/man-pages/man3/getaddrinfo.3.html

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *addr_info;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
    int err = getaddrinfo(NULL, "3490", &hints, &addr_info);
  
    int sfd = socket(addr_info->ai_family, addr_info->ai_socktype, addr_info->ai_protocol);
    bind(sfd, addr_info->ai_addr, addr_info->ai_addrlen);
    freeaddrinfo(addr_info);


    struct sockaddr_storage remote_addr;
    socklen_t remote_addr_len = sizeof(remote_addr);
    ssize_t nread;
    char buf[BUF_SIZE];

    char host[NI_MAXHOST], service[NI_MAXSERV];
    
    /* Read datagrams and echo them back to sender. */
    for (;;) {
        nread = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &remote_addr, &remote_addr_len);
        if (nread == -1) continue;

        err = getnameinfo((struct sockaddr *) &remote_addr, remote_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
	if (err == 0) printf("Received %zd bytes from %s:%s\n", nread, host, service);
        else fprintf(stderr, "getnameinfo: %s\n", gai_strerror(err));

        if (sendto(sfd, buf, nread, 0, (struct sockaddr *) &remote_addr, remote_addr_len) != nread) {
	    fprintf(stderr, "Error sending response\n");
	}
    }
}
