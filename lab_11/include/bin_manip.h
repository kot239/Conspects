#ifndef LAB11_BIN_MANIP_H_INCLUDED
#define LAB11_BIN_MANIP_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdint>

class write_le_int32 {
public:
    write_le_int32(int32_t x);
    std::basic_ostream<char>& operator()(std::basic_ostream<char>& ostr) const;
private:
    int32_t value_;
};

std::basic_ostream<char>& operator << (std::basic_ostream<char>& strm, const write_le_int32& le);

class read_le_int32 {
public:
    read_le_int32(int32_t& x);
    std::basic_istream<char>& operator()(std::basic_istream<char>& istr) const;
private:
    int32_t& value_;
};

std::basic_istream<char>& operator >> (std::basic_istream<char>& strm, const read_le_int32& le);

class write_bool {
public:
    write_bool(bool x);
    std::basic_ostream<char>& operator()(std::basic_ostream<char>& ostr) const;
private:
    bool value_;
};

std::basic_ostream<char>& operator << (std::basic_ostream<char>& strm, const write_bool& b_str);

class read_bool {
public:
    read_bool(bool& x);
    std::basic_istream<char>& operator()(std::basic_istream<char>& istr) const;
private:
    bool& value_;
};

std::basic_istream<char>& operator >> (std::basic_istream<char>& strm, const read_bool& b_str);

class write_c_str {
public:
    write_c_str(char* x);
    std::basic_ostream<char>& operator()(std::basic_ostream<char>& ostr) const;
private:
    char* value_;
};

std::basic_ostream<char>& operator << (std::basic_ostream<char>& strm, const write_c_str& c_str);

class read_c_str {
public:
    read_c_str(char* x, int32_t size);
    std::basic_istream<char>& operator()(std::basic_istream<char>& istr) const;
private:
    char* value_;
    int32_t size_;
};

std::basic_istream<char>& operator >> (std::basic_istream<char>& strm, const read_c_str& c_str);

#endif
