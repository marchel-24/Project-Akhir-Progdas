#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <string>

class Car : public Vehicle
{
public:
    Car(int id = 0, const std::string &make = "", const std::string &model = "", int year = 0, double rate = 0.0, int seats = 4);
    virtual ~Car();

    int getSeats() const;
    void setSeats(int s);

    std::string toString() const override;
    std::string toCSV() const override;
    static Car fromCSV(const std::string &line);

private:
    int seats;
};

#endif // CAR_H
