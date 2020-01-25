#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>

#include "bin_manip.h"

class Employee {
public:
    Employee();
    virtual ~Employee();
    virtual int salary() const = 0;
    friend std::istream& operator>>(std::istream& istr, Employee& emp);
    friend std::ifstream& operator>>(std::ifstream& istr, Employee& emp);
    friend std::ostream& operator<<(std::ostream& ostr, const Employee& emp);
    friend std::ofstream& operator<<(std::ofstream& ostr, const Employee& emp);

    virtual void print(std::ostream& ostr) const = 0;
    virtual void print_f(std::ofstream& ostr) const = 0;

protected:
    virtual void read(std::istream& istr) = 0;
    virtual void read_f(std::ifstream& istr) = 0;

    char* name_ = (char *)"Employee";
    int32_t base_salary_ = 0;
};

class Developer : public Employee {
public:
    Developer() = default;
    ~Developer() = default;
    int salary() const override;

    void read(std::istream& istr) override;
    void read_f(std::ifstream& istr) override;
    void print(std::ostream& ostr) const override;
    void print_f(std::ofstream& ostr) const override;

    Developer& operator=(const Developer& dev) = delete;

private:
    bool has_bonus_ = false;
};

class SalesManager : public Employee {
public:
    SalesManager() = default;
    ~SalesManager() = default;
    int salary() const override;

    void read(std::istream& istr) override;
    void read_f(std::ifstream& istr) override;
    void print(std::ostream& ostr) const override;
    void print_f(std::ofstream& ostr) const override;

    SalesManager& operator=(const SalesManager& sm) = delete;

private:
    int32_t sold_nm_ = 0;
    int32_t price_ = 0;
};

class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();
    void add(Employee* e);
    int total_salary() const;

    friend std::istream& operator>>(std::istream& istr, EmployeesArray& array);
    friend std::ifstream& operator>>(std::ifstream& istr, EmployeesArray& array);
    friend std::ostream& operator<<(std::ostream& ostr, const EmployeesArray& array);
    friend std::ofstream& operator<<(std::ofstream& ostr, const EmployeesArray& array);

private:
    Employee** employees_;
    int32_t size_, capacity_;
};

#endif