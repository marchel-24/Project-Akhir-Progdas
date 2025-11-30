#include "Fleet.h"
#include <algorithm>

void Fleet::addVehicle(std::shared_ptr<Vehicle> v)
{
    vehicles.push_back(v);
}

bool Fleet::removeVehicleById(int id)
{
    auto it = std::remove_if(vehicles.begin(), vehicles.end(), [id](const std::shared_ptr<Vehicle> &v)
                             { return v->getId() == id; });
    if (it != vehicles.end())
    {
        vehicles.erase(it, vehicles.end());
        return true;
    }
    return false;
}

std::shared_ptr<Vehicle> Fleet::findById(int id) const
{
    for (auto &v : vehicles)
    {
        if (v->getId() == id)
            return v;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Vehicle>> Fleet::listAvailable() const
{
    std::vector<std::shared_ptr<Vehicle>> out;
    for (auto &v : vehicles)
    {
        if (v->isAvailable())
            out.push_back(v);
    }
    return out;
}

std::vector<std::shared_ptr<Vehicle>> Fleet::listAll() const
{
    return vehicles;
}
