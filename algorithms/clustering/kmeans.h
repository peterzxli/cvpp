#ifndef KMEANS_H
#define KMEANS_H

#include "./kmeans/kmeans_init.h"
#include "./kmeans/kmeans_opt.h"

namespace cvpp
{

class KMeans : public KMeansBase
{

protected:

    KMinit* init;
    KMopt* opt;

    bool flag_init,flag_opt,flag_done;
    bool flag_loop;

public:

    double timer;

    KMeans( KMinit* , KMopt* );
    ~KMeans();

    Matd ctr() const { return flag_init ? Z().ru( c() ) : Z() ; }
    int iter() const { return c() ; }

    bool isInit() const { return flag_init; }
    bool isOpt()  const { return flag_opt;  }
    bool isDone() const { return flag_done; }

    const void init_start( const Matd& , const int& );
    const bool init_loop();
    const void init_finish();

    const void initialise( const Matd& , const int& );
    const void initialise( const Matd& , const Matd& );

    const void opt_start();
    const bool opt_loop();
    const void opt_finish();

    const void optimise( int = 1e6 );

    const void start( const Matd& , const int& );
    const void loop();
    const void finish();

    const void run( const Matd& , const int& , const int& = 1e6 );

};

}

#endif
