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
	struct sockaddr_in local_server,client,root_server,tld_server,auth_server;
	int local_socket,n,port,i,j=0,bd,comp,port1,port2,port3;
	char a[1000],b[1000],c[1000],inp[100],ip[100],msg[1000];
	FILE *fp;
	local_socket=socket(AF_INET,SOCK_DGRAM,0);
	local_server.sin_family=AF_INET;
	local_server.sin_port=3006;
	local_server.sin_addr.s_addr=inet_addr("127.0.0.1");
	root_server.sin_family=AF_INET;
	root_server.sin_port=3001;
	root_server.sin_addr.s_addr=inet_addr("127.0.0.2");

	bd=bind(local_socket,(struct sockaddr *)&local_server,sizeof(local_server));
	if(bd<0)
	{
		printf("Binding error\n");
		exit(0);
	}
	n=sizeof(client);
	recvfrom(local_socket,a,sizeof a,0,(struct sockaddr *)&client,&n);
	//printf("%s\n",a);
	fp=fopen("local.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d",b,ip,&port);
		comp=strcmp(a,b);
		if(comp==0)
		{
			break;
		}

	}
	if(comp==0)
	{
		strcpy(msg,"Cached from local");
		sendto(local_socket,msg,sizeof(msg),0,(struct sockaddr *)&client,n);
	sendto(local_socket,ip,sizeof(ip),0,(struct sockaddr *)&client,n);
	sendto(local_socket,&port,sizeof(port),0,(struct sockaddr *)&client,n);
	fclose(fp);
	}
else
{ 
	fclose(fp);
	fp=fopen("local.txt","a");
	memset(&(c),'\0',100);
	memset(&(b),'\0',100);
	i=strlen(a);
	//printf("length of i=%d\n",i );
	i--;
	j=0;
	while(i>=0)
	{
		b[j]=a[i];
		j++;
		if(a[i]==46)
		{
			//printf("%d .i",i);
			i=-1;
			
			//break;
		} 
		i--;
	}
	j--;
	int l=0;
	//printf("printing c\n");
	for(i=j;i>=0;i--)
	{
		c[l]=b[i];
	//printf("%c-c\n",c[l]);
		
	l++;
	}
	//b[j]=a[i];
	sendto(local_socket,c,sizeof(c),0,(struct sockaddr *)&root_server,n);
	recvfrom(local_socket,ip,sizeof ip,0,(struct sockaddr *)&root_server,&n);
	recvfrom(local_socket,&port,sizeof port,0,(struct sockaddr *)&root_server,&n);
	//printf("IP from root:%s,port:%d\n",ip,port);
	if(port==0)
	{
		strcpy(msg,"Domain not registered in root server");
	sendto(local_socket,msg,sizeof(msg),0,(struct sockaddr *)&client,n);
	sendto(local_socket,ip,sizeof(ip),0,(struct sockaddr *)&client,n);
	sendto(local_socket,&port,sizeof(port),0,(struct sockaddr *)&client,n);
	exit(1);

	}

	tld_server.sin_family=AF_INET;
	tld_server.sin_port=port;
	tld_server.sin_addr.s_addr=inet_addr(ip);
	i=strlen(a);
	//printf("length of i=%d\n",i );
	i--;
	j=0;
	memset(&(c),'\0',100);
	memset(&(b),'\0',100);
	int count=0;
	while(i>=0)
	{
		b[j]=a[i];
		j++;
		if(a[i]==46)
		{
			count++;
		}
		if(a[i]==46 && count==2)
		{
			//printf("%d .i",i);
			i=-1;
			
			//break;
		} 
		i--;
	}
	j--;
	 l=0;
	//printf("printing c\n");
	for(i=j-1;i>=0;i--)
	{
		c[l]=b[i];
	//	printf("%c-c\n",c[l]);
		
	l++;
	}
	//memset(&port,'\0',10);
	sendto(local_socket,c,sizeof(c),0,(struct sockaddr *)&tld_server,n);
	recvfrom(local_socket,ip,sizeof ip,0,(struct sockaddr *)&tld_server,&n);
	recvfrom(local_socket,&port1,sizeof port1,0,(struct sockaddr *)&tld_server,&n);
	//printf("IP from root:%s,port:%d\n",ip,port1);
	if(port1==0)
	{
		strcpy(msg,"Domain not registered in TLD server");
	sendto(local_socket,msg,sizeof(msg),0,(struct sockaddr *)&client,n);
	sendto(local_socket,ip,sizeof(ip),0,(struct sockaddr *)&client,n);
	sendto(local_socket,&port1,sizeof(port1),0,(struct sockaddr *)&client,n);
	exit(1);

	}

	auth_server.sin_family=AF_INET;
	auth_server.sin_port=port1;
	auth_server.sin_addr.s_addr=inet_addr(ip);

	sendto(local_socket,a,sizeof(a),0,(struct sockaddr *)&auth_server,n);
	recvfrom(local_socket,ip,sizeof ip,0,(struct sockaddr *)&auth_server,&n);
	recvfrom(local_socket,&port2,sizeof port2,0,(struct sockaddr *)&auth_server,&n);
	if(port2==0)
	{
		strcpy(msg,"Domain not registered in autherative server");
	sendto(local_socket,msg,sizeof(msg),0,(struct sockaddr *)&client,n);
	sendto(local_socket,ip,sizeof(ip),0,(struct sockaddr *)&client,n);
	sendto(local_socket,&port2,sizeof(port2),0,(struct sockaddr *)&client,n);
	exit(1);

	}
	//printf("IP from root:%s,port:%d\n",ip,port2);
	sendto(local_socket,msg,sizeof(msg),0,(struct sockaddr *)&client,n);
	sendto(local_socket,ip,sizeof(ip),0,(struct sockaddr *)&client,n);
	sendto(local_socket,&port2,sizeof(port2),0,(struct sockaddr *)&client,n);
	fprintf(fp,"%s %s %d\n",a,ip,port2);
	fclose(fp);
}
}

