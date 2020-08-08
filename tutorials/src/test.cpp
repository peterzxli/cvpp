
#include <cvpp/interfaces/cpplot.h>

using namespace cvpp;

int main()
{
	CPPlot draw( "Window" );

	Matd mat( 2 , 2 );
	mat.setIncrease().print();
	
	return 0;
}
