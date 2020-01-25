#include <iostream>
#include <string.h>
#include <memory>
#include <fstream>

#include "bin_manip.h"
#include "employees.h"

const int32_t NAME_SIZE = 102;

int32_t Dev_type = 1;
int32_t SM_type = 2;

enum Types {
    DEV_TYPE = 1,
    SALES_TYPE = 2
};

Employee::Employee() {
    this->name_ = new char [NAME_SIZE];
};

Employee::~Employee(){
    delete [] this->name_;
};

std::istream& operator>>(std::istream& istr, Employee& emp) {
    emp.read(istr);
    return istr;
};

std::ifstream& operator>>(std::ifstream& istr, Employee& emp) {
    emp.read_f(istr);
    return istr;
};

std::ostream& operator<<(std::ostream& ostr, Employee& emp) {
    emp.print(ostr);
    return ostr;
};

std::ofstream& operator<<(std::ofstream& ostr, Employee& emp) {
    emp.print_f(ostr);
    return ostr;
};

int Developer::salary() const {
    int salary = base_salary_;
    if (has_bonus_) { salary += 1000; }
    return salary;
};

void Developer::read(std::istream& istr) {
    istr >> name_ >> base_salary_ >> has_bonus_;
    return;
};

void Developer::read_f(std::ifstream& istr) {
    istr >> read_c_str(name_, NAME_SIZE) >> read_le_int32(base_salary_) >> read_bool(has_bonus_);
    return;
};

void Developer::print(std::ostream& ostr) const {
    ostr << "Developer\n";
    ostr << "Name: " << name_ << "\n";
    ostr << "Base Salary: " << base_salary_ << "\n";
    ostr << "Has bonus: " << (has_bonus_ ? '+' : '-') << "\n";
    return;
};

void Developer::print_f(std::ofstream& ostr) const {
    ostr << write_le_int32(Dev_type) << write_c_str(name_) << write_le_int32(base_salary_) << write_bool(has_bonus_);
    return;
};

int SalesManager::salary() const {
    return base_salary_ + sold_nm_ * price_ * 0.01;
};

void SalesManager::read(std::istream& istr) {
    istr >> name_ >> base_salary_ >> sold_nm_ >> price_;
    return;
};

void SalesManager::read_f(std::ifstream& istr) {
    istr >> read_c_str(name_, NAME_SIZE) >> read_le_int32(base_salary_)
                                >> read_le_int32(sold_nm_) >> read_le_int32(price_);
    return;
};

void SalesManager::print(std::ostream& ostr) const {
    ostr << "Sales Manager\n";
    ostr << "Name: " << name_ << "\n";
    ostr << "Base Salary: " << base_salary_ << "\n";
    ostr << "Sold items: " << sold_nm_ << "\n";
    ostr << "Item price: " << price_ << "\n";
    return;
};

void SalesManager::print_f(std::ofstream& ostr) const {
    ostr << write_le_int32(SM_type) << write_c_str(name_)
                    << write_le_int32(base_salary_) << write_le_int32(sold_nm_) << write_le_int32(price_);
    return;
};

EmployeesArray::EmployeesArray(): size_(0), capacity_(1){
    employees_ = new Employee* [capacity_];
};

EmployeesArray::~EmployeesArray(){
    for (int i = 0; i < size_; i++)
        delete employees_[i];
    delete [] employees_;
};

void EmployeesArray::add(Employee* e) {
    if (size_ + 1 > capacity_){
        Employee** temp;
        temp = new Employee* [2 * capacity_];
        memcpy(temp, employees_, capacity_ * sizeof(Employee*));
        capacity_ *= 2;
        delete [] employees_;
        employees_ = temp;
    }
    employees_[size_++] = e;
};

int EmployeesArray::total_salary() const {
    int total = 0;
    for (int i = 0; i < size_; i++)
        total += employees_[i]->salary();
    return total;
};

std::istream& operator>>(std::istream& istr, EmployeesArray& array) {
    int32_t type;
    istr >> type;
    Types type_e = static_cast<Types>(type);
    Employee *emp = nullptr;
    switch(type_e){
        case DEV_TYPE: {
            emp = new Developer;
        }
        break;
        case SALES_TYPE: {
            emp = new SalesManager;
        }
        break;
    }
    istr >> *emp;
    array.add(emp);
    return istr;
};

std::ifstream& operator>>(std::ifstream& istr, EmployeesArray& array) {
    int32_t quantity, type;
    istr >> read_le_int32(quantity);
    for (int i = 0; i < quantity; i++) {
        istr >> read_le_int32(type);
        Types type_e = static_cast<Types>(type);
        Employee *emp = nullptr;
        switch(type_e){
            case DEV_TYPE: {
                emp = new Developer;
            }
                break;
            case SALES_TYPE: {
                emp = new SalesManager;
            }
                break;
        }
        istr >> *emp;
        array.add(emp);
    }
    return istr;
};

std::ostream& operator<<(std::ostream& ostr, const EmployeesArray& array) {
    for (int i = 0; i < array.size_; i++)
        ostr << i + 1 << ". " << *(array.employees_[i]);
    ostr << "== Total salary: " << array.total_salary() << "\n\n";
    return ostr;
};

std::ofstream& operator<<(std::ofstream& ostr, const EmployeesArray& array) {
    ostr << write_le_int32(array.size_);
    for (int i = 0; i < array.size_; i++)
        ostr << *(array.employees_[i]);
    return ostr;
};
