
#include <cvpp/network/network_downloader.h>
#include <cvpp/auxiliar/macros.h>

using namespace cvpp;

int main(int argc, char *argv[])
{
    // CREATE DOWNLOAD INTERFACE

    Downloader down;

    // DOWNLOAD FILE

    disp( "Downloading..." );
    bool suc = down.toFile( "https://eigen.tuxfamily.org/dox/AsciiQuickReference.txt" ,
                            "eigen.txt" );

    // CHECK FOR SUCCESS

    if( suc ) disp( "SUCCESS!" );
    else disp( "FAILURE!" );

    // FINALIZE

    return 0;
}
