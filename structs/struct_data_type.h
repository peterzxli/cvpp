#ifndef STRUCT_DATA_TYPE_H
#define STRUCT_DATA_TYPE_H

namespace cvpp
{

template <typename T>
class DataType
{
};

template <>
class DataType<unsigned int>
{
public:
    unsigned get() { return 0; }
    unsigned gl() { return 5125; }
    bool isInt() { return false; }
    bool isChar() { return false; }
    bool isFloat() { return false; }
    bool isDouble() { return false; }
    bool isUnsigned() { return true; }
};

template <>
class DataType<float>
{
public:
    unsigned get() { return 1; }
    unsigned gl() { return 5126; }
    bool isInt() { return false; }
    bool isChar() { return false; }
    bool isFloat() { return true; }
    bool isDouble() { return false; }
    bool isUnsigned() { return false; }
};

template <>
class DataType<double>
{
public:
    unsigned get() { return 2; }
    unsigned gl() { return 5130; }
    bool isInt() { return false; }
    bool isChar() { return false; }
    bool isFloat() { return false; }
    bool isDouble() { return true; }
    bool isUnsigned() { return false; }
};

template <>
class DataType<int>
{
public:
    unsigned get() { return 3; }
    unsigned gl() { return 5124; }
    bool isInt() { return true; }
    bool isChar() { return false; }
    bool isFloat() { return false; }
    bool isDouble() { return false; }
    bool isUnsigned() { return false; }
};

template <>
class DataType<unsigned char>
{
public:
    unsigned get() { return 4; }
    bool isInt() { return false; }
    bool isChar() { return true; }
    bool isFloat() { return false; }
    bool isDouble() { return false; }
    bool isUnsigned() { return false; }
};

}

#endif
