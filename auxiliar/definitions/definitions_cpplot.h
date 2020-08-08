#ifndef CPPLOT_DEFINITIONS_H
#define CPPLOT_DEFINITIONS_H

#define FONT_MEDIUM 2
#define FONT_SMALL  1
#define FONT_TINY   0

#define BUFFER_IDX         0
#define BUFFER_DATA_FLOAT  1
#define BUFFER_DATA_DOUBLE 2
#define BUFFER_DATA_INT    3

#define DRAW_PTS    0
#define DRAW_SEGS   1
#define DRAW_LINE   2
#define DRAW_LOOP   3
#define DRAW_GRID   4
#define DRAW_WGRID  5
#define DRAW_SURF2  6
#define DRAW_SURF3  7
#define DRAW_WSURF3 8
#define DRAW_TRIANG 9
#define DRAW_TRID   10
#define DRAW_WTRID  11

#define IMAGE_2D 0
#define WORLD_3D 1
#define   POV_3D 2
#define  PLOT_2D 3
#define  PLOT_3D 4

#define LEFT   0
#define RIGHT  1
#define CENTRE 2

#define BLACK   cv::Scalar( 0.0 , 0.0 , 0.0 )
#define WHITE   cv::Scalar( 1.0 , 1.0 , 1.0 )
#define RED     cv::Scalar( 1.0 , 0.0 , 0.0 )
#define GREEN   cv::Scalar( 0.0 , 1.0 , 0.0 )
#define BLUE    cv::Scalar( 0.0 , 0.0 , 1.0 )
#define YELLOW  cv::Scalar( 1.0 , 1.0 , 0.0 )
#define CYAN    cv::Scalar( 0.0 , 1.0 , 1.0 )
#define MAGENTA cv::Scalar( 1.0 , 0.0 , 1.0 )
#define PURPLE  cv::Scalar( 0.5 , 0.0 , 0.5 )
#define BROWN   cv::Scalar( 0.5 , 0.5 , 0.0 )
#define NAVY    cv::Scalar( 0.0 , 0.5 , 0.5 )

#define BLA BLACK
#define WHI WHITE
#define GRE GREEN
#define BLU BLUE
#define YEL YELLOW
#define CYA CYAN
#define MAG MAGENTA
#define PUR PURPLE
#define BRO BROWN
#define NAV NAVY

#define REDBLUE(x)   cv::Scalar( 1.0 - x , 0.0 , x )
#define BLUERED(x)   cv::Scalar( x , 0.0 , 1.0 - x )
#define REDGREEN(x)  cv::Scalar( 1.0 - x , x , 0.0 )
#define GREENRED(x)  cv::Scalar( x , 1.0 - x , 0.0 )
#define GREENBLUE(x) cv::Scalar( 0.0 , 1.0 - x , x )
#define BLUEGREEN(x) cv::Scalar( 0.0 , x , 1.0 - x )

#endif
