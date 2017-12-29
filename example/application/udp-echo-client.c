#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define SERVICE_PORT    12345

#define BUFLEN 2048
#define MSGS 50 /* number of messages to send */

typedef unsigned long long cycle_t;
cycle_t readtime(void)
{
        cycle_t nanosec;
        struct timespec time;
        clock_gettime(CLOCK_REALTIME, &time);
        nanosec = time.tv_nsec;
        return nanosec;
}


char* rand_str(char *s, int number)
{
        char *str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        int i = 0;

        srand((unsigned)readtime());
        for(i = 0; i < number; i++) {
                s[i] = str[(rand()%62)];
        }
//      s[number] = '\0';

        return s;
}


int main(void)
{
        struct sockaddr_in myaddr, remaddr;
        int fd, i, slen=sizeof(remaddr);
        char *server = "10.1.2.2";      /* change this to use a different server */



        char buf[BUFLEN];


        /* create a socket */

        if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
                printf("socket created\n");

        /* bind it to all local addresses and pick any port number */

        memset((char *)&myaddr, 0, sizeof(myaddr));
        myaddr.sin_family = AF_INET;
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        myaddr.sin_port = htons(0);

        if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
                perror("bind failed");
                return 0;
        }

        /* now define remaddr, the address to whom we want to send messages */
        /* For convenience, the host address is expressed as a numeric IP address */
        /* that we will convert to a binary format via inet_aton */

        memset((char *) &remaddr, 0, sizeof(remaddr));
        remaddr.sin_family = AF_INET;
        remaddr.sin_port = htons(SERVICE_PORT);
        if (inet_aton(server, &remaddr.sin_addr)==0) {
                fprintf(stderr, "inet_aton() failed\n");
                exit(1);
        }


        /* now let's send the messages */

        for (i=0; i < MSGS; i++) {
                char *s = malloc(16);
                if(s) {
                        rand_str(s, 16);
                }
//              printf("%d string:  %s  \n", i, s);


                sprintf(buf, "%s", s);
//              printf("buf:%s \n", buf);
                printf("Sending packet %d content %s to %s port %d packetlen: %lu\n", i, buf, server, SERVICE_PORT, strlen(buf));

                if (  sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1)
                        perror("sendto");

                if (recvfrom(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, &slen)==-1) {
                        perror("client receives reply error");
                }
                printf("Server reply %s\n", buf);

                free(s);
                sleep(1);
        }
        close(fd);
        return 0;
}
