#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

#define BUFLEN 512

void die(char *s) {
	perror(s);
	exit(1);
}

int main(int argc, char **argv) {
	int opt;
    int port = 8888;
    char *func = NULL;

    while((opt = getopt(argc, argv, "p:f:")) != -1) {
        switch (opt) {
            case 'p':  
                port = strtol(optarg, NULL, 10);
                break;
            case 'f':
                func = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-p] [ Specified port ] "
                                            "[-f] [ .asm file to run on connection (./test) ]\n"
                                            , argv[0]);
                exit(EXIT_FAILURE);
        }
    }

	struct sockaddr_in si_other;
	int s, i, slen = sizeof(si_other) , recv_len;
	char buf[BUFLEN];
	
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) die("socket create");
	
	struct sockaddr_in si_me = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = htonl(INADDR_ANY) 
	};

	if(bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) die("socket bind");

	printf("Server listening on port %d...\n", port);

	while(1) {	
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) die("recvfrom()");
		if(func) system(func);
		
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		
		char *res = "Function executed";
		if (sendto(s, res, 20, 0, (struct sockaddr*) &si_other, slen) == -1) die("sendto()");
	}

	close(s);
	return 0;
}