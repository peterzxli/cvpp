
#include <cvpp/network/network_emailer.h>
#include <cvpp/containers/matrix.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // CALCULATE VALUE

    Matd mat( 10 , 10 );
    mat.setRand();

    // CREATE EMAIL INTERFACE

    Emailer email;

    email.setURL( GMAIL ); // GMail URL
    email.setUsername( argv[1] ); // Username + From
    email.setPassword( argv[2] ); // Password

    email.setTo( argv[3] ); // To

    email.setSubject( "CVPP-Mail" ); // Subject
    email.setBody( "Result:\n\n"     // Body
                   "mat.sum() = " + toString( mat.sum() ) + "\n\n"
                   "Sincerely,\n\n"
                   "                       CVPP" );

    // SEND E-MAIL

    disp( "Sending e-mail to " + email.getTo() + "..." );
    bool suc = email.send();

    // CHECK FOR SUCCESS

    if( suc ) disp( "SUCCESS!" );
    else disp( "FAILURE!" );

    // FINALIZE

    return 0;
}
