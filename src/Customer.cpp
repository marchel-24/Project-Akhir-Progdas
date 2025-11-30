#include "Customer.h"
#include <sstream>
#include <vector>

Customer::Customer(int id, const std::string &name, const std::string &phone)
    : id(id), name(name), phone(phone) {}

int Customer::getId() const { return id; }
std::string Customer::getName() const { return name; }
std::string Customer::getPhone() const { return phone; }

std::string Customer::toString() const
{
    std::ostringstream os;
    os << id << " | " << name << " | " << phone;
    return os.str();
}

std::string Customer::toCSV() const
{
    std::ostringstream os;
    os << id << "," << name << "," << phone;
    return os.str();
}

Customer Customer::fromCSV(const std::string &line)
{
    std::istringstream is(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(is, token, ','))
        parts.push_back(token);

    int id = 0;
    std::string name = "", phone = "";
    if (parts.size() >= 3)
    {
        id = std::stoi(parts[0]);
        name = parts[1];
        phone = parts[2];
    }
    return Customer(id, name, phone);
}
