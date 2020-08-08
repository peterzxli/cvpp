#ifndef DEFINITIONS_STANDARD_H
#define DEFINITIONS_STANDARD_H

#include "definitions_template.h"

#include <iomanip>
#include <bitset>

#include <fstream>
#include <iostream>

#include <memory>
#include <vector>
#include <list>

namespace cvpp
{

using String  = std::string;
using SStream = std::stringstream;

using IFile = std::ifstream;
using OFile = std::ofstream;

TPL_T using Pointer = std::shared_ptr< T >;

TPL_D using Seq = std::vector< D >;
using Seqi = Seq<int>;
using Seqf = Seq<float>;
using Seqd = Seq<double>;
using Sequ = Seq<unsigned int>;
using Seqc = Seq<unsigned char>;

TPL_T using SSeq = std::vector< std::vector< T > >;
using SSeqi = SSeq<int>;
using SSeqf = SSeq<float>;
using SSeqd = SSeq<double>;
using SSequ = SSeq<unsigned>;

TPL_D using LST = std::list< D >;
using LSTi = LST<int>;
using LSTf = LST<float>;
using LSTd = LST<double>;
using LSTu = LST<unsigned int>;
using LSTc = LST<unsigned char>;

}

#endif
