#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
main()
{
	struct sockaddr_in local_server,client;
	int sock_client,n,port;
	char a[1000],ip[1000],msg[1000],b[1000];
	sock_client=socket(AF_INET,SOCK_DGRAM,0);
	local_server.sin_family=AF_INET;
	local_server.sin_port=3006;
	local_server.sin_addr.s_addr=inet_addr("127.0.0.1");
	n=sizeof(local_server);
	printf("enter hostname:\n");
	scanf("%s %s",b,a);
	sendto(sock_client,a,sizeof(a),0,(struct sockaddr *)&local_server,n);
	//printf("sent\n");
	recvfrom(sock_client,msg,sizeof msg,0,(struct sockaddr *)&local_server,&n);
	recvfrom(sock_client,ip,sizeof ip,0,(struct sockaddr *)&local_server,&n);
	recvfrom(sock_client,&port,sizeof port,0,(struct sockaddr *)&local_server,&n);
	if(msg!=NULL){
		printf("%s\n",msg);
	}
	if(port!=0)
	printf("IP:%s \n",ip);
}
