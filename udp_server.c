#include "sock_include.h"

void err(const char *str)
{
	perror(str);
	exit(1);
}

int main()
{
	int sockfd, ret, n, i;
	char buf[BUFSIZ], clie_buf[BUFSIZ];
	socklen_t clie_addr_len;
	struct sockaddr_in serv_addr, clie_addr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
		err("socket error");
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	ret = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(ret < 0)
		err("bind error");

	while(1)
		{
			clie_addr_len = sizeof(clie_addr);
			n = recvfrom(sockfd, buf, sizeof(buf), 0,
			             (struct sockaddr *)&clie_addr, &clie_addr_len);
			if(n == -1)
				err("recvfrom error");
			printf("client IP:%s, port is:%d\n",inet_ntop(AF_INET,
			       &clie_addr.sin_addr.s_addr, clie_buf, sizeof(clie_buf)),
			       ntohs(clie_addr.sin_port));

			for(i = 0; i < n; i++)
				buf[i] = toupper(buf[i]);

			n = sendto(sockfd, buf, n, 0, (struct sockaddr *)&clie_addr, 
													sizeof(clie_addr));
			if(n < 0)
				err("sendto error");
		}
	close(sockfd);
	return 0;
}