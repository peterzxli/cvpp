
#include <cvpp/containers/matrix.h>
#include <cvpp/containers/device.h>

using namespace cvpp;

int main()
{
    // SELECT SEED

    randomise(1);

    // PARAMETERS 

    int n = 2000; // Matrix size
    int m = 10;   // Number of multiplications

    // START TIMER

    Timer t;

    // CREATE CPU MATRICES 

    Matd mat1( n , n ); mat1.setRand(1);
    Matd mat2( n , n ); mat2.setRand(1);
    t.ptick( "Creating CPU matrices" );

    // UPLOAD MATRICES TO GPU 

    Devd dev1 = mat1;
    Devd dev2 = mat2;
    t.ptick( "Uploading data to GPU" );

    // CPU PROCESS

    forLOOPi( m )
        mat1 *= mat2;
    t.ptick( "CPU processing time" );

    // GPU PROCESS

    forLOOPi( m )
        dev1 *= dev2;
    t.ptick( "GPU processing time" );

    // SUM FOR COMPARISON 

    disp( "Sum" , "CPU" , mat1.sum() , "GPU" , dev1.sum() );

    return 0;
}



