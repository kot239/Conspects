#include <iostream>
#include <sstream>
#include <memory>

struct hex_wrapper{

    struct wrapped_istream{
        wrapped_istream(std::istream& strm) : strm(strm) {}
        std::istream& strm;
    };
        std::istream& operator ()(std::istream& strm) {
            strm.setf(std::ios_base::hex, std::ios_base::basefield);
            return {strm};
        }
};

struct istream_wrapper {
    istream_wrapper(std::istream& strm) : strm(strm) {};
    std::istream& strm;
};

std::istream& operator >> (const istream_wrapper& strm, int& x){
    strm.strm >> x;
    strm.strm.setf(std::ios_base::dec, std::ios_base::basefield);
    return strm.strm;
}

struct one_hex {};

istream_wrapper operator >> (std::istream& strm, one_hex){
    strm.setf(std::ios_base::hex, std::ios_base::basefield);
    return {strm};
}

int main() {
    int x = 0;
    int y = 0;

    std::cin >> hex_wrapper >> x >> y;

    std::cout << x << " " << y << "\n";

    return EXIT_SUCCESS;
}