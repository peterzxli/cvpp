#ifndef DEFINITIONS_EIGEN_H
#define DEFINITIONS_EIGEN_H

#define SPARSE 0
#define DENSE  1

#define COPY false
#define SHARE true

#include "definitions_template.h"
#include "definitions_standard.h"

#ifdef MKL_FOUND
#define EIGEN_USE_MKL_ALL
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <Eigen/LU>
#include <Eigen/Cholesky>

#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <Eigen/SparseCholesky>

#pragma GCC diagnostic pop

namespace cvpp
{

TPL_T using Quat = Eigen::Quaternion< T >;
using Quatf = Quat<float>;
using Quatd = Quat<double>;

TPL_T using Triplet = Eigen::Triplet< T >;
using Trif = Triplet<float>;
using Trid = Triplet<double>;

TPL_T using TripletList = Seq< Triplet< T > >;
using TriListf = TripletList<float>;
using TriListd = TripletList<double>;

TPL_T using EIG = Eigen::Matrix< T , -1 , -1 , Eigen::RowMajor >;
#define DEigen EIG< T >

TPL_T using SEIG = Eigen::SparseMatrix< T , Eigen::RowMajor >;
#define SEigen SEIG< T >

TPL_TF using FEIG = Eigen::Matrix< T , NR , NC , Eigen::RowMajor , MR , MC >;
#define FEigen FEIG< T , NR , NC , MR , MC >

TPL_TB using BEIG = Eigen::Block< FEIG< T , NR , NC , MR , MC > , BR , BC , FL >;
#define BEigen BEIG< T , NR , NC , BR , BC , MR , MC , FL >

TPL_T using MEIG = Eigen::Map< EIG<T> , Eigen::DontAlign , Eigen::Stride< -1 ,  1 > >;
#define MEigen MEIG< T >

TPL_T using REIG = Eigen::Block< Eigen::Map< Eigen::Matrix< T , -1 , -1 , 1 , -1 , -1 > , 2 , Eigen::Stride< -1 , 1 > > , 1 , -1 , true >;
#define REigen REIG< T >

TPL_T using IEIG = Eigen::Map< EIG<T> , Eigen::DontAlign , Eigen::Stride< -1 , -1 > >;
#define IEigen IEIG< T >

using  Eigf =  EIG<float>; using  Eigd =  EIG<double>; using  Eigi =  EIG<int>;
using SEigf = SEIG<float>; using SEigd = SEIG<double>; using SEigi = SEIG<int>;

TPL_T using EigRow = Eigen::Matrix<T,1,-1,Eigen::RowMajor>; using EigRowf = EigRow<float>; using EigRowd = EigRow<double>; using EigRowi = EigRow<int>;
TPL_T using EigCol = Eigen::Matrix<T,-1,1,Eigen::ColMajor>; using EigColf = EigCol<float>; using EigCold = EigCol<double>; using EigColi = EigCol<int>;

TPL_T using Eig1 = Eigen::Matrix<T,2,1,Eigen::ColMajor>; using Eig1f = Eig1<float>; using Eig1d = Eig1<double>;
TPL_T using Eig2 = Eigen::Matrix<T,2,1,Eigen::ColMajor>; using Eig2f = Eig2<float>; using Eig2d = Eig2<double>;
TPL_T using Eig3 = Eigen::Matrix<T,3,1,Eigen::ColMajor>; using Eig3f = Eig3<float>; using Eig3d = Eig3<double>;
TPL_T using Eig4 = Eigen::Matrix<T,4,1,Eigen::ColMajor>; using Eig4f = Eig4<float>; using Eig4d = Eig4<double>;

TPL_T using Eig11 = Eigen::Matrix<T,1,1,Eigen::RowMajor>; using Eig11f = Eig11<float>; using Eig11d = Eig11<double>;

TPL_T using Eig12 = Eigen::Matrix<T,1,2,Eigen::RowMajor>; using Eig12f = Eig12<float>; using Eig12d = Eig12<double>;
TPL_T using Eig13 = Eigen::Matrix<T,1,3,Eigen::RowMajor>; using Eig13f = Eig13<float>; using Eig13d = Eig13<double>;
TPL_T using Eig14 = Eigen::Matrix<T,1,4,Eigen::RowMajor>; using Eig14f = Eig14<float>; using Eig14d = Eig14<double>;

TPL_T using Eig21 = Eigen::Matrix<T,2,1,Eigen::ColMajor>; using Eig21f = Eig21<float>; using Eig21d = Eig21<double>;
TPL_T using Eig31 = Eigen::Matrix<T,3,1,Eigen::ColMajor>; using Eig31f = Eig31<float>; using Eig31d = Eig31<double>;
TPL_T using Eig41 = Eigen::Matrix<T,4,1,Eigen::ColMajor>; using Eig41f = Eig41<float>; using Eig41d = Eig41<double>;

TPL_T using Eig22 = Eigen::Matrix<T,2,2,Eigen::RowMajor>; using Eig22f = Eig22<float>; using Eig22d = Eig22<double>;
TPL_T using Eig33 = Eigen::Matrix<T,3,3,Eigen::RowMajor>; using Eig33f = Eig33<float>; using Eig33d = Eig33<double>;
TPL_T using Eig44 = Eigen::Matrix<T,4,4,Eigen::RowMajor>; using Eig44f = Eig44<float>; using Eig44d = Eig44<double>;

}

#endif
