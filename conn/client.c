/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

unsigned short remote_port = 4242;
char *ip = "127.0.0.1";

int main(void)
{
        int s;
        int rc;
        int sockfd;
        struct hostent *hent;
        struct sockaddr_in server_addr;
        struct timespec t;
        static char buffer[BUFSIZ];

        /* Create socket. */
        sockfd = socket(PF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
                exit(1);

        hent = gethostbyname(ip);
        if (hent == NULL)
                exit(2);

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(remote_port);
        memcpy(&server_addr.sin_addr.s_addr,
                        hent->h_addr,
                        sizeof(server_addr.sin_addr.s_addr));

        rc = connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
        if(rc < 0)
               exit(3);
        t.tv_sec  = 0;
        t.tv_nsec = 500000000L;

        while (1) {
                printf("Start communication\n");
                memset(buffer, 0, BUFSIZ);
                rc = recv(sockfd, buffer, BUFSIZ, 0);
                printf(buffer);

                if (rc <= 0)
                        break;

                memset(buffer, 0, BUFSIZ);
                memcpy(buffer, "Pong", 4);
                rc = send(sockfd, buffer, BUFSIZ, 0);

                nanosleep(&t, NULL);
                if (rc < 0)
                        break;

        }

        close(sockfd);

        return 0;
}
