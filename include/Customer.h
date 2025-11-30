#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
public:
    Customer(int id = 0, const std::string &name = "", const std::string &phone = "");
    int getId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string toString() const;

    std::string toCSV() const;
    static Customer fromCSV(const std::string &line);

private:
    int id;
    std::string name;
    std::string phone;
};

#endif // CUSTOMER_H
