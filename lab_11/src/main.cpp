#include <iostream>

#include "employees.h"
#include "bin_manip.h"

int main(){
    std::string func, file_name;
    EmployeesArray array;
    while (1){
        std::cin >> func;
        if (func == "load"){
            std::cin >> file_name;
            std::ifstream ifstr(file_name, std::ios::in | std::ios::binary);
            ifstr >> array;
            if (ifstr.rdstate() == std::ios_base::failbit)
                std::cout << "Invalid read from file\n";
        } else if (func == "save") {
            std::cin >> file_name;
            std::ofstream ofstr(file_name, std::ios::out | std::ios::binary);
            ofstr << array;
        } else if (func == "add") {
            std::cin >> array;
        } else if (func == "list") {
            std::cout << array;
        } else if (func == "exit") {
            return 0;
        } else {
            std::cout << "Invalid command\n";
        }
    }
}