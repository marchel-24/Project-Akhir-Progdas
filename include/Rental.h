#ifndef RENTAL_H
#define RENTAL_H

#include <string>
#include <memory>
#include "Vehicle.h"
#include "Customer.h"

enum class RentalStatus
{
    ONGOING,
    RETURNED
};

class Rental
{
public:
    Rental(int id,
           std::shared_ptr<Vehicle> vehicle,
           std::shared_ptr<Customer> customer,
           const std::string &startDate);

    int getId() const;
    std::shared_ptr<Vehicle> getVehicle() const;
    std::shared_ptr<Customer> getCustomer() const;
    std::string getStartDate() const;
    std::string getEndDate() const;
    RentalStatus getStatus() const;

    // End rental by providing endDate in YYYY-MM-DD; returns total cost
    double endRental(const std::string &endDate);

    std::string toString() const;

private:
    int id;
    std::shared_ptr<Vehicle> vehicle;
    std::shared_ptr<Customer> customer;
    std::string startDate;
    std::string endDate;
    RentalStatus status;

    // helper - parse date string to time_t (midnight)
    static time_t parseDate(const std::string &ymd);
    static int daysBetween(const std::string &startYMD, const std::string &endYMD);
};

#endif // RENTAL_H
