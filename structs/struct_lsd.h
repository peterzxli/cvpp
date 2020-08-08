#ifndef STRUCT_LSD_H
#define STRUCT_LSD_H

struct GraphKeyframe
{
    int id;
    float pose[7];
};

struct GraphPointcloud
{
    float depth_mean,depth_var;
    unsigned char color[4];
};

struct Constraint
{
    int from,to;
    float err;
};

#endif
