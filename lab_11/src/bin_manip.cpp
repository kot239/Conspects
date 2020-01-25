#include <iostream>
#include <cstdint>
#include <fstream>

#include "bin_manip.h"

write_le_int32::write_le_int32(int32_t x): value_(x) {};

std::basic_ostream<char>& write_le_int32::operator()(std::basic_ostream<char>& ostr) const {
    ostr.write((char *)& value_, sizeof(value_));
    return ostr;
};

std::basic_ostream<char>& operator << (std::basic_ostream<char>& strm, const write_le_int32& le){
    return le(strm);
};

read_le_int32::read_le_int32(int32_t& x) : value_(x) {};

std::basic_istream<char>& read_le_int32::operator()(std::basic_istream<char>& istr) const {
    istr.read((char *)& value_, sizeof(value_));
    return istr;
};

std::basic_istream<char>& operator >> (std::basic_istream<char>& strm, const read_le_int32& le){
    return le(strm);
};

write_bool::write_bool(bool x): value_(x) {};

std::basic_ostream<char>& write_bool::operator()(std::basic_ostream<char>& ostr) const {
    int8_t temp;
    temp = value_ ? 1 : 0;
    ostr.write((char *)& temp, sizeof(temp));
    return ostr;
};

std::basic_ostream<char>& operator << (std::basic_ostream<char>& strm, const write_bool& b_str){
    return b_str(strm);
};

read_bool::read_bool(bool& x) : value_(x) {};

std::basic_istream<char>& read_bool::operator()(std::basic_istream<char>& istr) const {
    int8_t temp;
    istr.read((char *)& temp, sizeof(temp));
    if (temp == 1){
        value_ = true;
    } else if (temp == 0){
        value_ = false;
    } else {
        istr.setstate(std::ios_base::failbit);
    }
    return istr;
};

std::basic_istream<char>& operator >> (std::basic_istream<char>& strm, const read_bool& b_str){
    return b_str(strm);
};

write_c_str::write_c_str(char* x): value_(x) {};

std::basic_ostream<char>& write_c_str::operator()(std::basic_ostream<char>& ostr) const {
    int32_t i = 0;
    while (value_[i] != '\0') {
        ostr.write((char *)& value_[i], sizeof(char));
        i++;
    }
    ostr.write((char *)& value_[i], sizeof(char));
    return ostr;
};

std::basic_ostream<char>& operator << (std::basic_ostream<char>& strm, const write_c_str& c_str){
    return c_str(strm);
};

read_c_str::read_c_str(char* x, int32_t size) : value_(x), size_(size) {};

std::basic_istream<char>& read_c_str::operator()(std::basic_istream<char>& istr) const {
    int32_t i = 0;
    char buffer;
    while (i < size_) {
        istr.read((char *)& buffer, sizeof(char));
        value_[i] = buffer;
        if (value_[i] == '\0')
            break;
        i++;
    }
    if (i == size_)
        istr.setstate(std::ios_base::failbit);
    return istr;
};

std::basic_istream<char>& operator >> (std::basic_istream<char>& strm, const read_c_str& c_str){
    return c_str(strm);
};