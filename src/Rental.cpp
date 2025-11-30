#include "Rental.h"
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

Rental::Rental(int id,
               std::shared_ptr<Vehicle> vehicle,
               std::shared_ptr<Customer> customer,
               const std::string &startDate)
    : id(id), vehicle(vehicle), customer(customer), startDate(startDate), endDate(""), status(RentalStatus::ONGOING)
{
    if (vehicle)
        vehicle->setAvailable(false);
}

int Rental::getId() const { return id; }
std::shared_ptr<Vehicle> Rental::getVehicle() const { return vehicle; }
std::shared_ptr<Customer> Rental::getCustomer() const { return customer; }
std::string Rental::getStartDate() const { return startDate; }
std::string Rental::getEndDate() const { return endDate; }
RentalStatus Rental::getStatus() const { return status; }

std::time_t Rental::parseDate(const std::string &ymd)
{
    std::tm tm = {};
    std::istringstream ss(ymd);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail())
    {
        return -1;
    }
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    return std::mktime(&tm);
}

int Rental::daysBetween(const std::string &startYMD, const std::string &endYMD)
{
    std::time_t t1 = parseDate(startYMD);
    std::time_t t2 = parseDate(endYMD);
    if (t1 == -1 || t2 == -1)
        return 0;
    double diff = std::difftime(t2, t1);
    int days = static_cast<int>(diff / (60 * 60 * 24));
    if (days < 0)
        days = 0;
    // count at least 1 day if same day -> charge 1 day
    if (days == 0)
        days = 1;
    return days;
}

double Rental::endRental(const std::string &endDate)
{
    if (status == RentalStatus::RETURNED)
        return 0.0;
    int days = daysBetween(startDate, endDate);
    double rate = vehicle ? vehicle->getRate() : 0.0;
    double total = days * rate;
    this->endDate = endDate;
    this->status = RentalStatus::RETURNED;
    if (vehicle)
        vehicle->setAvailable(true);
    return total;
}

std::string Rental::toString() const
{
    std::ostringstream os;
    os << "Rental #" << id << " | Vehicle: " << (vehicle ? vehicle->getMake() + " " + vehicle->getModel() : "N/A")
       << " | Customer: " << (customer ? customer->getName() : "N/A")
       << " | Start: " << startDate << " | End: " << (endDate.empty() ? "-" : endDate)
       << " | Status: " << (status == RentalStatus::ONGOING ? "ONGOING" : "RETURNED");
    return os.str();
}
