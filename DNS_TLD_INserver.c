#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
main()
{
	struct sockaddr_in local_server,client,root_server,tld_server,auth_server;
	int tld_socket,n,portt,comp,sent=0;
	FILE *fp;
	fp=fopen("tldin.txt","r");
	char a[1000],b[1000],c[1000],ip[100];
	tld_socket=socket(AF_INET,SOCK_DGRAM,0);
	tld_server.sin_family=AF_INET;
	tld_server.sin_port=5000;
	tld_server.sin_addr.s_addr=inet_addr("127.0.0.16");
	bind(tld_socket,(struct sockaddr *)&tld_server,sizeof(tld_server));
	n=sizeof(local_server);
	recvfrom(tld_socket,a,sizeof a,0,(struct sockaddr *)&local_server,&n);
	//printf("%s\n",a);


	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d",b,ip,&portt);
		comp=strcmp(a,b);
		if(comp==0)
		{
			//sendto("");
			sendto(tld_socket,ip,sizeof(ip),0,(struct sockaddr *)&local_server,n);
			sendto(tld_socket,&portt,sizeof(portt),0,(struct sockaddr *)&local_server,n);
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
			sendto(tld_socket,ip,sizeof(ip),0,(struct sockaddr *)&local_server,n);
			sendto(tld_socket,&portt,sizeof(portt),0,(struct sockaddr *)&local_server,n);

	}
	
}


