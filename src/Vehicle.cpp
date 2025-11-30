#include "Vehicle.h"
#include <sstream>
#include <vector>
#include <iomanip>

Vehicle::Vehicle(int id, const std::string &make, const std::string &model, int year, double rate)
    : id(id), make(make), model(model), year(year), ratePerDay(rate), available(true) {}

Vehicle::~Vehicle() = default;

int Vehicle::getId() const { return id; }
std::string Vehicle::getMake() const { return make; }
std::string Vehicle::getModel() const { return model; }
int Vehicle::getYear() const { return year; }
double Vehicle::getRate() const { return ratePerDay; }
bool Vehicle::isAvailable() const { return available; }
void Vehicle::setAvailable(bool avail) { available = avail; }

std::string Vehicle::toString() const
{
    std::ostringstream os;
    os << id << " | " << make << " " << model << " (" << year << ") - rate: " << ratePerDay
       << " - " << (available ? "available" : "rented");
    return os.str();
}

std::string Vehicle::toCSV() const
{
    std::ostringstream os;
    os << id << "," << make << "," << model << "," << year << "," << std::fixed << std::setprecision(2)
       << ratePerDay << "," << (available ? 1 : 0);
    return os.str();
}

Vehicle Vehicle::fromCSV(const std::string &line)
{
    std::istringstream is(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(is, token, ','))
        parts.push_back(token);

    int id = 0, year = 0;
    double rate = 0.0;
    int avail = 1;
    std::string make = "", model = "";
    if (parts.size() >= 6)
    {
        id = std::stoi(parts[0]);
        make = parts[1];
        model = parts[2];
        year = std::stoi(parts[3]);
        rate = std::stod(parts[4]);
        avail = std::stoi(parts[5]);
    }
    Vehicle v(id, make, model, year, rate);
    v.setAvailable(avail == 1);
    return v;
}
