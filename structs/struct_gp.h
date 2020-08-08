#ifndef STRUCT_OPTIONS_H
#define STRUCT_OPTIONS_H

#include <cvpp/auxiliar/definitions.h>
#include <cvpp/auxiliar/definitions/definitions_gp.h>
#include <cvpp/containers/vector.h>

namespace cvpp
{

struct GPoptions
{
    unsigned optimizer = NL_COBYLA;

    unsigned max_evaluation = 500;
    unsigned max_searches = 50;

    unsigned query_batch = 2500;

    double tolerance_rel = 1e-5;
    double tolerance_abs = 1e-5;

    double hyp_lower_bound = -10.0;
    double hyp_upper_bound = +10.0;

    double lrate_hyp = 1e-5 , mom_hyp = 0.9;
    double lrate_ind = 1e-5 , mom_ind = 0.5;
    double lrate_var = 1e-2 , mom_var = 0.9;

    double jitter = 1e-6;
    double numeric_step = 1e-6;

    unsigned epoch_hyp = 5;
    unsigned epoch_ind = 5;
    unsigned epoch_var = 0;

    bool verbose = true;

    bool check_derivatives     = false;
    bool check_hyp_derivatives = false;
    bool check_ind_derivatives = false;
    bool check_var_derivatives = false;

    bool learn_hyp = false;
    bool learn_ind = false;
    bool learn_var = false;

    unsigned screen_width = 640;
    unsigned screen_height = 480;

    unsigned draw_type = NONE;
    unsigned draw_3D_view = ISOMETRIC;
    unsigned error_metric = RMSE;

    bool draw_loop = true;
    bool draw_wire = true;
};

struct GPdata
{
    int training;
    int cnt_eval,cnt_loop;

    double blml;

    Pts2d lmls,errs;
};

struct CovData
{
    Matd S,D,K;
};

}

#endif
