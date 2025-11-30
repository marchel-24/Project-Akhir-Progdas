#include "Car.h"
#include <sstream>
#include <vector>

Car::Car(int id, const std::string &make, const std::string &model, int year, double rate, int seats)
    : Vehicle(id, make, model, year, rate), seats(seats) {}

Car::~Car() = default;

int Car::getSeats() const { return seats; }
void Car::setSeats(int s) { seats = s; }

std::string Car::toString() const
{
    std::ostringstream os;
    os << getId() << " | " << getMake() << " " << getModel() << " (" << getYear() << ") "
       << "- seats: " << seats << " - rate: " << getRate() << " - " << (isAvailable() ? "available" : "rented");
    return os.str();
}

std::string Car::toCSV() const
{
    std::ostringstream os;
    // add seats as extra field
    os << getId() << "," << getMake() << "," << getModel() << "," << getYear() << "," << getRate()
       << "," << (isAvailable() ? 1 : 0) << "," << seats;
    return os.str();
}

Car Car::fromCSV(const std::string &line)
{
    std::istringstream is(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(is, token, ','))
        parts.push_back(token);

    int id = 0, year = 0, seats = 4;
    double rate = 0.0;
    int avail = 1;
    std::string make = "", model = "";
    if (parts.size() >= 7)
    {
        id = std::stoi(parts[0]);
        make = parts[1];
        model = parts[2];
        year = std::stoi(parts[3]);
        rate = std::stod(parts[4]);
        avail = std::stoi(parts[5]);
        seats = std::stoi(parts[6]);
    }
    Car c(id, make, model, year, rate, seats);
    c.setAvailable(avail == 1);
    return c;
}
