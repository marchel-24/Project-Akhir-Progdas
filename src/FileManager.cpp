#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::shared_ptr<Vehicle>> FileManager::loadVehicles(const std::string &filepath)
{
    std::vector<std::shared_ptr<Vehicle>> out;
    std::ifstream infile(filepath);
    if (!infile.is_open())
    {
        // file not found - return empty
        return out;
    }
    std::string line;
    while (std::getline(infile, line))
    {
        if (line.empty())
            continue;
        // we try to detect Car vs Vehicle by field count: if 7 fields -> Car
        std::istringstream ss(line);
        std::string tmp;
        int fields = 0;
        while (std::getline(ss, tmp, ','))
            fields++;
        if (fields >= 7)
        {
            // Car
            // Use Car::fromCSV - but include header here
            // To avoid include cycle, parse fields manually and construct Vehicle
            std::istringstream is2(line);
            std::string token;
            std::vector<std::string> parts;
            while (std::getline(is2, token, ','))
                parts.push_back(token);
            int id = std::stoi(parts[0]);
            std::string make = parts[1];
            std::string model = parts[2];
            int year = std::stoi(parts[3]);
            double rate = std::stod(parts[4]);
            int avail = std::stoi(parts[5]);
            int seats = std::stoi(parts[6]);
            // create as Vehicle but we can create Car if header included. Simpler: create Vehicle and ignore seats
            auto v = std::make_shared<Vehicle>(id, make, model, year, rate);
            v->setAvailable(avail == 1);
            out.push_back(v);
        }
        else
        {
            // Vehicle basic
            Vehicle v = Vehicle::fromCSV(line);
            auto vp = std::make_shared<Vehicle>(v);
            out.push_back(vp);
        }
    }
    infile.close();
    return out;
}

bool FileManager::saveVehicles(const std::string &filepath, const std::vector<std::shared_ptr<Vehicle>> &vehicles)
{
    std::ofstream ofs(filepath);
    if (!ofs.is_open())
        return false;
    for (auto &v : vehicles)
    {
        ofs << v->toCSV() << "\n";
    }
    ofs.close();
    return true;
}

std::vector<std::shared_ptr<Customer>> FileManager::loadCustomers(const std::string &filepath)
{
    std::vector<std::shared_ptr<Customer>> out;
    std::ifstream infile(filepath);
    if (!infile.is_open())
    {
        return out;
    }
    std::string line;
    while (std::getline(infile, line))
    {
        if (line.empty())
            continue;
        Customer c = Customer::fromCSV(line);
        out.push_back(std::make_shared<Customer>(c));
    }
    infile.close();
    return out;
}

bool FileManager::saveCustomers(const std::string &filepath, const std::vector<std::shared_ptr<Customer>> &customers)
{
    std::ofstream ofs(filepath);
    if (!ofs.is_open())
        return false;
    for (auto &c : customers)
    {
        ofs << c->toCSV() << "\n";
    }
    ofs.close();
    return true;
}
