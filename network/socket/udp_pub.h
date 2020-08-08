
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <cvpp/auxiliar/macros_base.h>

namespace cvpp
{

class UDPpub
{

protected:

    int sockfd , portno ;
    unsigned serverlen;

    struct sockaddr_in serveraddr;
    struct hostent *server;

    char *hostname;

public:

public:

    UDPpub( const char* h , const char* p )
    {
        hostname = (char*)h;
        portno = atoi( p );

        sockfd = socket( AF_INET , SOCK_DGRAM , 0 );
        if( sockfd < 0 ) disp( "ERROR OPENING SOCKET" , portno );

        server = gethostbyname( hostname );
        if( server == NULL ) disp( "ERROR FINDING HOST" , hostname );

        bzero( (char*)&serveraddr , sizeof(serveraddr) );
        serveraddr.sin_family = AF_INET;

        bcopy( (char*)server->h_addr ,
               (char*)&serveraddr.sin_addr.s_addr , server->h_length );
        serveraddr.sin_port = htons(portno);
        serverlen = sizeof(serveraddr);
    }

    const void send( const char* buf )
    {
        disp( buf , strlen(buf) );
        sendto( sockfd , buf , strlen(buf) , 0 ,
                (struct sockaddr*)&serveraddr , serverlen );
    }

};

}
