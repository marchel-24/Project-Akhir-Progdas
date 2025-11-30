#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <memory>
#include <vector>
#include "Vehicle.h"
#include "Customer.h"

class FileManager
{
public:
    // vehicle file format: id,make,model,year,rate,available (available:1 or 0)
    static std::vector<std::shared_ptr<Vehicle>> loadVehicles(const std::string &filepath);
    static bool saveVehicles(const std::string &filepath, const std::vector<std::shared_ptr<Vehicle>> &vehicles);

    // customers file format: id,name,phone
    static std::vector<std::shared_ptr<Customer>> loadCustomers(const std::string &filepath);
    static bool saveCustomers(const std::string &filepath, const std::vector<std::shared_ptr<Customer>> &customers);
};

#endif // FILEMANAGER_H
