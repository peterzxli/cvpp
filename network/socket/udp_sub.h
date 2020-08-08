
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <cvpp/auxiliar/macros_base.h>

namespace cvpp
{

class UDPsub
{

protected:

    int sockfd , sockbd , portno ;

    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;

    unsigned buf_size ;

public:

    char *buffer;
    int length;

public:

    UDPsub( const char* p )
    {
        buf_size = 1024;
        buffer = new char[buf_size];

        portno = atoi( p );

        sockfd = socket( AF_INET , SOCK_DGRAM , 0 );
        if( sockfd < 0 ) disp( "ERROR OPENING SOCKET" , portno );

        int optval = 1;
        setsockopt( sockfd , SOL_SOCKET , SO_REUSEADDR ,
                        (const void*)&optval , sizeof(int) );

        bzero( (char*)&serveraddr , sizeof(serveraddr) );
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons( (unsigned short)portno );

        sockbd = bind( sockfd , (struct sockaddr*)&serveraddr , sizeof(serveraddr) );
        if( sockbd < 0 ) disp( "ERROR BINDING SOCKET" );
    }

    ~UDPsub()
    {
        delete buffer;
    }

    const void listen()
    {
        bzero( buffer , buf_size );
        length = recv( sockfd , buffer , buf_size , 0 );
    }

};

}
