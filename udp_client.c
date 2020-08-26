#include "sock_include.h"

void err(const char *str)
{
	perror(str);
	exit(1);
}

int main()
{
	int sockfd, n;
	char buf[BUFSIZ];

	struct sockaddr_in serv_addr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
		err("socket error");
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	while((fgets(buf, sizeof(buf), stdin)) != NULL)
		{	
			n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&serv_addr, 
																 sizeof(serv_addr));
			if(n < 0)
				err("sendto error");
			n = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, 0);
			if(n < 0)
				err("recvfrom error");
			
			write(STDOUT_FILENO, buf, n);
		}
	close(sockfd);
	return 0;
}