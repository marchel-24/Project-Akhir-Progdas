#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio> // for mkdir on Windows
#include <sys/stat.h>
#include <direct.h>

static void createDirectoryIfNotExists(const std::string &path)
{
    struct stat info{};
    if (stat(path.c_str(), &info) != 0)
    {
        // Folder tidak ada → buat
        _mkdir(path.c_str());
    }
}

std::vector<std::shared_ptr<Vehicle>> FileManager::loadVehicles(const std::string &filepath)
{
    std::vector<std::shared_ptr<Vehicle>> out;
    std::ifstream infile(filepath);
    if (!infile.is_open())
    {
        std::cerr << "[WARNING] Tidak dapat membuka file: " << filepath << "\n";
        return out;
    }

    std::string line;
    while (std::getline(infile, line))
    {
        if (line.empty())
            continue;
        Vehicle v = Vehicle::fromCSV(line);
        out.push_back(std::make_shared<Vehicle>(v));
    }
    return out;
}

bool FileManager::saveVehicles(const std::string &filepath,
                               const std::vector<std::shared_ptr<Vehicle>> &vehicles)
{
    createDirectoryIfNotExists("data");

    std::ofstream ofs(filepath);
    if (!ofs.is_open())
    {
        std::cerr << "[ERROR] Tidak dapat membuka file untuk ditulis: " << filepath << "\n";
        return false;
    }

    for (auto &v : vehicles)
        ofs << v->toCSV() << "\n";

    return true;
}

std::vector<std::shared_ptr<Customer>> FileManager::loadCustomers(const std::string &filepath)
{
    std::vector<std::shared_ptr<Customer>> out;
    std::ifstream infile(filepath);
    if (!infile.is_open())
    {
        std::cerr << "[WARNING] Tidak dapat membuka file: " << filepath << "\n";
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
    return out;
}

bool FileManager::saveCustomers(const std::string &filepath,
                                const std::vector<std::shared_ptr<Customer>> &customers)
{
    createDirectoryIfNotExists("data");

    std::ofstream ofs(filepath);
    if (!ofs.is_open())
    {
        std::cerr << "[ERROR] Tidak dapat membuka file untuk ditulis: " << filepath << "\n";
        return false;
    }

    for (auto &c : customers)
        ofs << c->toCSV() << "\n";

    return true;
}
