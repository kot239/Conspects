#include <iostream>

class Point {
public:
    Point() = default;
    Point(int x, int y): x_(x), y_(y) {}

    int Abs() const {
        return x_ * x_ + y_ * y_;
    }

    // friend std::istream& operator >> (std::istream& istr, Point& p); нельзя объявлять как часть класса без friend

    /* std::istream& Read(std::istream& istr){
        return istr >> x_ >> y_;
    }
     */

    // point[x,y]
    // снчала читают целиком строку, затем парсят ее (по канону)
    static auto Read(std::istream& istr){ // static вызывать без объекта
        auto point = std::make_unique<Point>();
        std::string line;
        if (istr >> line){
            if (2 == sscanf(line.c_str(), "point[%d,%d]", &(point->x_), &(point->y_))){
                return point;
            }
            istr.setstate(std::ios_base::badbit);
        }
        point = nullptr;
        return point;
        /*
        if (!(istr >> point->x_ >> point->y_))
            point = nullptr;
        return point;
        */
    }

private:
    int x_ = 0;
    int y_ = 0;
};

std::istream& operator >>(std::istream& istr, Point& p){ //нельзя объявлять как часть класса
    // return p.Read(istr);
   auto ptr = Point::Read(istr);
    if (ptr) { p = *ptr; }
    return istr;
}

int main() {
    Point p;

    if (std::cin >> p) {
        std::cout << p.Abs() << "\n";
    } else {
        if (std::cin.bad()){
            std::cout << "Bad format\n";
            std::cin.clear(std::ios::badbit);
        } else {
            std::cout << "AAAAAAAA\n";
            return EXIT_FAILURE;
        }
    }

    int x;
    if (std::cin >> x){
        std::cout << x << "\n";
    } else {
        std::cout << "bad bit is set\n";
    };

    return EXIT_SUCCESS;
}