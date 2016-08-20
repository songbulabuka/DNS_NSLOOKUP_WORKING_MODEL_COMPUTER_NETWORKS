#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
main()
{
	struct sockaddr_in local_server,client,root_server,tld_server,auth_server;
	int auth_socket,n,comp,sent=0,bd,portt;
	FILE *fp;
	fp=fopen("auth.txt","r");
	char a[1000],b[1000],c[1000],ip[100];
	auth_socket=socket(AF_INET,SOCK_DGRAM,0);
	auth_server.sin_family=AF_INET;
	auth_server.sin_port=4000;
	auth_server.sin_addr.s_addr=inet_addr("127.0.0.10");
	bd=bind(auth_socket,(struct sockaddr *)&auth_server,sizeof(auth_server));
	if(bd<0)
	{
		printf("Binding error\n");
		exit(0);
	}
	
	n=sizeof(local_server);
	recvfrom(auth_socket,a,sizeof a,0,(struct sockaddr *)&local_server,&n);
	//printf("%s\n",a);

	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d",b,ip,&portt);
		comp=strcmp(a,b);
		if(comp==0)
		{
			//sendto("");
			sendto(auth_socket,ip,sizeof(ip),0,(struct sockaddr *)&local_server,n);
			sendto(auth_socket,&portt,sizeof(portt),0,(struct sockaddr *)&local_server,n);
			sent=1;
			break;
		}
	}
	fclose(fp);
	if(sent==0)
	{
		//printf("NOT found\n");
	
			portt=0;
		//	strcpy(ip,"N");
			sendto(auth_socket,ip,sizeof(ip),0,(struct sockaddr *)&local_server,n);
			sendto(auth_socket,&portt,sizeof(portt),0,(struct sockaddr *)&local_server,n);
	}


}


