#ifndef DEFINITIONS_OPENCV_H
#define DEFINITIONS_OPENCV_H
#ifdef OPENCV_FOUND

#define VIDEO 0
#define IMAGE 1

#define OPENCV 0
#define SHITOMASI 1

#define OPTFLOW 0

#include "definitions_template.h"

#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

namespace cvpp
{

using CV  = cv::Mat;
using CVi = cv::Mat_<int>;
using CVf = cv::Mat_<float>;
using CVd = cv::Mat_<double>;
using CVu = cv::Mat_<unsigned int>;
using CVc = cv::Mat_<unsigned char>;

using Size   = cv::Size;
using Scalar = cv::Scalar;

TPL_T using Rect2 = cv::Rect_< T >;
using Rect2i = cv::Rect_<int>;
using Rect2f = cv::Rect_<float>;
using Rect2d = cv::Rect_<double>;

TPL_T using Pt2 = cv::Point_< T >;
using Pt2i = Pt2<int>;
using Pt2f = Pt2<float>;
using Pt2d = Pt2<double>;

TPL_T using Pt3 = cv::Point3_< T >;
using Pt3i = Pt3<int>;
using Pt3f = Pt3<float>;
using Pt3d = Pt3<double>;

using KPts = Seq<cv::KeyPoint>;
using MPts = Seq<cv::DMatch>;

using cvSIFT = cv::xfeatures2d::SIFT;
using cvSURF = cv::xfeatures2d::SURF;
using cvFAST = cv::FastFeatureDetector;

using cvORB = cv::ORB;

using cvFLANN = cv::FlannBasedMatcher;
using cvBRUTE = cv::BFMatcher;

TPL_TC using IMG = cv::Mat_< cv::Vec< T , C > >;
#define CVImage IMG< T , C >

}

#endif
#endif
