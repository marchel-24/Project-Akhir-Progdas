#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include "Fleet.h"
#include "FileManager.h"
#include "Customer.h"
#include "Rental.h"

static int nextVehicleId(const Fleet &fleet)
{
    int mx = 0;
    for (auto &v : fleet.listAll())
        if (v->getId() > mx)
            mx = v->getId();
    return mx + 1;
}
static int nextCustomerId(const std::vector<std::shared_ptr<Customer>> &customers)
{
    int mx = 0;
    for (auto &c : customers)
        if (c->getId() > mx)
            mx = c->getId();
    return mx + 1;
}
static int nextRentalId(const std::vector<std::shared_ptr<Rental>> &rentals)
{
    int mx = 0;
    for (auto &r : rentals)
        if (r->getId() > mx)
            mx = r->getId();
    return mx + 1;
}

void pause()
{
    std::cout << "Tekan Enter untuk kembali...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    Fleet fleet;
    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<Rental>> rentals;

    // default data file paths
    const std::string vehiclesInputFile = "data/input.txt";
    const std::string customersInputFile = "data/customers.txt";

    const std::string vehiclesOutputFile = "data/output.txt";            // hasil simpan
    const std::string customersOutputFile = "data/customers_output.txt"; // hasil simpan customers

    // try load initial data
    // try load initial data (always from input files)
    auto loaded = FileManager::loadVehicles(vehiclesInputFile);
    for (auto &v : loaded)
        fleet.addVehicle(v);
    customers = FileManager::loadCustomers(customersInputFile);

    bool running = true;
    while (running)
    {
        std::cout << "\n=== Aplikasi Rental Mobil (Demo) ===\n";
        std::cout << "1. Tambah kendaraan\n";
        std::cout << "2. Edit kendaraan (rate)\n";
        std::cout << "3. Hapus kendaraan\n";
        std::cout << "4. List semua kendaraan\n";
        std::cout << "5. List kendaraan tersedia\n";
        std::cout << "6. Tambah customer\n";
        std::cout << "7. List customers\n";
        std::cout << "8. Sewa kendaraan\n";
        std::cout << "9. Kembalikan kendaraan\n";
        std::cout << "10. Simpan data\n";
        std::cout << "11. Muat ulang data dari file\n";
        std::cout << "0. Keluar\n";
        std::cout << "Pilih: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            int id = nextVehicleId(fleet);
            std::string make, model;
            int year;
            double rate;
            std::cout << "Make: ";
            std::getline(std::cin, make);
            std::cout << "Model: ";
            std::getline(std::cin, model);
            std::cout << "Year: ";
            std::cin >> year;
            std::cout << "\nRate per day: ";
            std::cin >> rate;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            auto v = std::make_shared<Vehicle>(id, make, model, year, rate);
            fleet.addVehicle(v);
            std::cout << "Kendaraan ditambahkan (ID=" << id << ")\n";
            pause();
        }
        else if (choice == 2)
        {
            std::cout << "Masukkan ID kendaraan: ";
            int id;
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            auto v = fleet.findById(id);
            if (!v)
            {
                std::cout << "Tidak ditemukan.\n";
                pause();
                continue;
            }
            std::cout << "Rate lama: " << v->getRate() << "\nMasukkan rate baru: ";
            double r;
            std::cin >> r;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // no setter for rate in Vehicle; simplest - recreate object or cast: we'll set via copy
            // For simplicity, create a new Vehicle object with same id/make/model/year and replace in fleet
            auto newV = std::make_shared<Vehicle>(v->getId(), v->getMake(), v->getModel(), v->getYear(), r);
            newV->setAvailable(v->isAvailable());
            fleet.removeVehicleById(id);
            fleet.addVehicle(newV);
            std::cout << "Rate diperbarui.\n";
            pause();
        }
        else if (choice == 3)
        {
            std::cout << "Masukkan ID kendaraan untuk dihapus: ";
            int id;
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (fleet.removeVehicleById(id))
                std::cout << "Dihapus.\n";
            else
                std::cout << "Tidak ditemukan.\n";
            pause();
        }
        else if (choice == 4)
        {
            auto all = fleet.listAll();
            if (all.empty())
                std::cout << "Tidak ada kendaraan.\n";
            for (auto &v : all)
                std::cout << v->toString() << "\n";
            pause();
        }
        else if (choice == 5)
        {
            auto avail = fleet.listAvailable();
            if (avail.empty())
                std::cout << "Tidak ada kendaraan tersedia.\n";
            for (auto &v : avail)
                std::cout << v->toString() << "\n";
            pause();
        }
        else if (choice == 6)
        {
            int id = nextCustomerId(customers);
            std::string name, phone;
            std::cout << "Nama: ";
            std::getline(std::cin, name);
            std::cout << "Phone: ";
            std::getline(std::cin, phone);
            auto c = std::make_shared<Customer>(id, name, phone);
            customers.push_back(c);
            std::cout << "Customer ditambahkan ID=" << id << "\n";
            pause();
        }
        else if (choice == 7)
        {
            if (customers.empty())
                std::cout << "Belum ada customer.\n";
            for (auto &c : customers)
                std::cout << c->toString() << "\n";
            pause();
        }
        else if (choice == 8)
        {
            std::cout << "Masukkan ID customer: ";
            int cid;
            std::cin >> cid;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::shared_ptr<Customer> cust = nullptr;
            for (auto &c : customers)
                if (c->getId() == cid)
                {
                    cust = c;
                    break;
                }
            if (!cust)
            {
                std::cout << "Customer tidak ditemukan.\n";
                pause();
                continue;
            }
            std::cout << "Masukkan ID kendaraan: ";
            int vid;
            std::cin >> vid;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            auto veh = fleet.findById(vid);
            if (!veh)
            {
                std::cout << "Kendaraan tidak ditemukan.\n";
                pause();
                continue;
            }
            if (!veh->isAvailable())
            {
                std::cout << "Kendaraan sedang tidak tersedia.\n";
                pause();
                continue;
            }
            std::string start;
            std::cout << "Tanggal mulai (YYYY-MM-DD): ";
            std::getline(std::cin, start);
            int rid = nextRentalId(rentals);
            auto r = std::make_shared<Rental>(rid, veh, cust, start);
            rentals.push_back(r);
            std::cout << "Sewa dibuat (Rental ID=" << rid << ")\n";
            pause();
        }
        else if (choice == 9)
        {
            std::cout << "Masukkan Rental ID untuk dikembalikan: ";
            int rid;
            std::cin >> rid;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::shared_ptr<Rental> found = nullptr;
            for (auto &r : rentals)
                if (r->getId() == rid)
                {
                    found = r;
                    break;
                }
            if (!found)
            {
                std::cout << "Rental tidak ditemukan.\n";
                pause();
                continue;
            }
            if (found->getStatus() == RentalStatus::RETURNED)
            {
                std::cout << "Sudah dikembalikan.\n";
                pause();
                continue;
            }
            std::string endDate;
            std::cout << "Tanggal kembali (YYYY-MM-DD): ";
            std::getline(std::cin, endDate);
            double total = found->endRental(endDate);
            std::cout << "Total biaya: " << total << "\n";
            pause();
        }
        else if (choice == 10)
        {
            // gather vehicles
            auto all = fleet.listAll();
            // save to output files (do not overwrite input.txt)
            if (FileManager::saveVehicles(vehiclesOutputFile, all))
                std::cout << "Kendaraan disimpan ke " << vehiclesOutputFile << "\n";
            else
                std::cout << "Gagal menyimpan kendaraan ke " << vehiclesOutputFile << "\n";

            if (FileManager::saveCustomers(customersOutputFile, customers))
                std::cout << "Customers disimpan ke " << customersOutputFile << "\n";
            else
                std::cout << "Gagal menyimpan customers ke " << customersOutputFile << "\n";

            pause();
        }
        else if (choice == 11)
        {
            fleet = Fleet();
            customers.clear();
            auto l = FileManager::loadVehicles(vehiclesInputFile); // load from input (fresh copy)
            for (auto &v : l)
                fleet.addVehicle(v);
            customers = FileManager::loadCustomers(customersInputFile);
            std::cout << "Data dimuat ulang dari file input (" << vehiclesInputFile << " / " << customersInputFile << ").\n";
            pause();
        }
        else if (choice == 0)
        {
            running = false;
        }
        else
        {
            std::cout << "Pilihan tidak valid\n";
        }
    }

    std::cout << "Keluar. Sampai jumpa.\n";
    return 0;
}
