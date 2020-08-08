#include "../gp_base.h"

namespace cvpp
{

// Numeric
double
BaseGP::numeric( Seqd& grads )
{
    double step = options.numeric_step;
    double lml1 , lml2 , lml = slikelihood( train_hyps );

    Vecd curr , train_hyps0 = train_hyps.clone();
    for( unsigned i = 0 ; i < grads.size() ; i++ )
    {
        curr = train_hyps0;

        curr[i] -= 1.0 * step; lml1 = slikelihood( curr );
        curr[i] += 2.0 * step; lml2 = slikelihood( curr );

        grads[i] = ( lml2 - lml1 ) / ( 2.0 * step );
    }

    solve( train_hyps0 );
    return lml;
}

// Check Derivatives
const void
BaseGP::checkDerivatives( const Seqd& grads )
{
    if( options.check_derivatives )
    {
        std::cout << "****************************************** Checking Derivatives ... \n";
        Seqd nums( grads.size() ); numeric( nums );

        Matd mat( grads.size() , 4 );
        for( unsigned i = 0 ; i < grads.size() ; i++ )
            mat.row(i) << grads[i] , nums[i] ,
                    fabs( grads[i] - nums[i] ) ,
                    fabs( grads[i] - nums[i] ) / grads[i] ;

        std::cout << mat.eig() << std::endl;
        std::cout << "****************************************** Average Error : "
                  << mat.c(2).sum() / grads.size() << std::endl;

        halt();
    }
}

// Numeric Hyp
const void
BaseGP::numericHyp( Vecd& grads )
{
    double step = options.numeric_step;
    double lml1 , lml2 ;

    Vecd curr , train_hyps0 = train_hyps;
    for( unsigned i = 0 ; i < grads.n() ; i++ )
    {
        curr = train_hyps0;

        curr[i] -= 1.0 * step; lml1 = slikelihood( curr );
        curr[i] += 2.0 * step; lml2 = slikelihood( curr );

        grads[i] = ( lml2 - lml1 ) / ( 2.0 * step );
    }

    solve( train_hyps0 );
}

// Check Hyp Derivatives
const void
BaseGP::checkHypDerivatives( const Vecd& grads )
{
    if( options.check_derivatives )
    {
        std::cout << "****************************************** Checking Hyp Derivatives ... \n";
        Vecd nums( grads.n() ); numericHyp( nums );

        Matd mat( grads.n() , 4 );
        for( unsigned i = 0 ; i < grads.n() ; i++ )
            mat.row(i) << grads[i] , nums[i] ,
                    fabs( grads[i] - nums[i] ) ,
                    fabs( grads[i] - nums[i] ) / grads[i] ;

        std::cout << mat.eig() << std::endl;
        std::cout << "****************************************** Average Error : "
                  << mat.c(2).sum() / grads.n() << std::endl;
    }
}

// Numeric Ind
const void
BaseGP::numericInd( Matd& grads )
{
    double step = options.numeric_step;
    double lml1 , lml2 ;

    Matd Zt0 = Zt.clone();
    for( unsigned i = 0 ; i < grads.r() ; i++ )
    {   for( unsigned j = 0 ; j < grads.c() ; j++ )
        {
            Zt(i,j) = Zt0(i,j) - step; lml1 = slikelihood();
            Zt(i,j) = Zt0(i,j) + step; lml2 = slikelihood();
            Zt(i,j) = Zt0(i,j) ;

            grads(i,j) = ( lml2 - lml1 ) / ( 2.0 * step );
        }
    }

    solve();
}

// Check Derivatives
const void
BaseGP::checkIndDerivatives( const Matd& grads )
{
    if( options.check_derivatives )
    {
        std::cout << "\n****************************************** Checking Ind Derivatives ... \n";
        Matd nums( grads.dims() ); numericInd( nums );

        Matd mat = grads - nums;

        std::cout << grads.appR(nums).appR(nums-grads).eig() << std::endl;
        std::cout << "****************************************** Average Ind Error : "
                  << mat.absum() / mat.s() << std::endl;
    }
}

// Numeric Var
const void
BaseGP::numericVar( Matd& gth1 , Matd& gth2 )
{
}

// Check Var Derivatives
const void
BaseGP::checkVarDerivatives( const Matd& gth1 , const Matd& gth2 )
{
    if( options.check_derivatives )
    {
    }
}

}

