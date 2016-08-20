#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
main()
{
	struct sockaddr_in local_server,client,root_server,tlp_server,auth_server;
	int root_socket,n,portt,comp,bd,sent=0;
	FILE *fp;
	char a[1000],b[1000],c[1000],ip[1000];
	fp=fopen("root.txt","r");
	root_socket=socket(AF_INET,SOCK_DGRAM,0);
	root_server.sin_family=AF_INET;
	root_server.sin_port=3001;
	root_server.sin_addr.s_addr=inet_addr("127.0.0.2");
	bd=bind(root_socket,(struct sockaddr *)&root_server,sizeof(root_server));
	if(bd<0)
	{
		printf("Binding error\n");
		exit(0);
	}
	n=sizeof(client);
	recvfrom(root_socket,a,sizeof a,0,(struct sockaddr *)&local_server,&n);
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d",b,ip,&portt);
		comp=strcmp(a,b);
		if(comp==0)
		{
			//sendto("");
			sendto(root_socket,ip,sizeof(ip),0,(struct sockaddr *)&local_server,n);
			sendto(root_socket,&portt,sizeof(portt),0,(struct sockaddr *)&local_server,n);
			sent=1;
			break;
		}
	}

	fclose(fp);
	if(sent==0)
	{
		//printf("NOT found\n");
			portt=0;
			//strcpy(ip,"N");
			sendto(root_socket,ip,sizeof(ip),0,(struct sockaddr *)&local_server,n);
			sendto(root_socket,&portt,sizeof(portt),0,(struct sockaddr *)&local_server,n);
	}
	
	//printf("%s\n",a);
}


