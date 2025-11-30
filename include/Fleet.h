#ifndef FLEET_H
#define FLEET_H

#include <vector>
#include <memory>
#include "Vehicle.h"

class Fleet
{
public:
    Fleet() = default;

    void addVehicle(std::shared_ptr<Vehicle> v);
    bool removeVehicleById(int id);
    std::shared_ptr<Vehicle> findById(int id) const;
    std::vector<std::shared_ptr<Vehicle>> listAvailable() const;
    std::vector<std::shared_ptr<Vehicle>> listAll() const;

private:
    std::vector<std::shared_ptr<Vehicle>> vehicles;
};

#endif // FLEET_H
