/*
** showip.c -- show IP addresses for a host given on the command line
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>
#include <err.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    struct addrinfo hints, *res, *res0;
    int error;
    int s;
    const char *cause = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    error = getaddrinfo("www.kame.net", "http", &hints, &res0);
    if (error) {
            errx(1, "%s", gai_strerror(error));
            /*NOTREACHED*/
    }
    s = -1;
    for (res = res0; res; res = res->ai_next) {
            s = socket(res->ai_family, res->ai_socktype,
                res->ai_protocol);
            if (s < 0) {
                    cause = "socket";
                    continue;
            }

            if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
                    cause = "connect";
                    close(s);
                    s = -1;
                    continue;
            }

            break;  /* okay we got one */
    }
    if (s < 0) {
            err(1, "%s", cause);
            /*NOTREACHED*/
    }
    freeaddrinfo(res0);
    return 0;
}
