/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef BUFSIZ
#define BUFSIZ          256
#endif

#define LISTEN_BACKLOG  10

unsigned short port = 4242;

int main(void)
{
        int rc;
        int sock_opt;
        int listenfd, sockfd;
        struct sockaddr_in address;
        struct sockaddr_in raddr;
        socklen_t raddrlen;
        static char buffer[BUFSIZ];

        /* Create socket. */
        listenfd = socket(PF_INET, SOCK_STREAM, 0);

        sock_opt = 1;
        rc = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
                                &sock_opt, sizeof(int));

        memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;

        rc = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
        rc = listen(listenfd, LISTEN_BACKLOG);

        /* Accept connection. */
        raddrlen = sizeof(raddr);
        sockfd = accept(listenfd, (struct sockaddr *) &raddr, &raddrlen);

        while (1) {
                memset(buffer, 0, BUFSIZ);
                memcpy(buffer, "Ping", 4);

                rc = send(sockfd, buffer, BUFSIZ, 0);
                if (rc < 0)
                        break;

                rc = recv(sockfd, buffer, BUFSIZ, 0);

                if (rc <= 0)
                        break;

        }

        close(sockfd);

        return 0;
}
