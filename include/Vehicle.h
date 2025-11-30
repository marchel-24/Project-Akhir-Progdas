#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle
{
public:
    Vehicle(int id = 0, const std::string &make = "", const std::string &model = "", int year = 0, double rate = 0.0);
    virtual ~Vehicle();

    int getId() const;
    std::string getMake() const;
    std::string getModel() const;
    int getYear() const;
    double getRate() const;
    bool isAvailable() const;
    void setAvailable(bool avail);

    virtual std::string toString() const;

    // For file IO as CSV
    virtual std::string toCSV() const;
    static Vehicle fromCSV(const std::string &line);

protected:
    int id;
    std::string make;
    std::string model;
    int year;
    double ratePerDay;
    bool available;
};

#endif // VEHICLE_H
