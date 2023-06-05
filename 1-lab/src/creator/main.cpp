#include <iostream>
#include <fstream>
#include "../employee.hpp"

int main(int argc, char** argv)
{
        int amount_of_entries = atoi(argv[2]);
        std::ofstream fout(argv[1]);

        employee temp;
        for (int i = 0; i < amount_of_entries; ++i)
        {
                std::cout << "Enter employee ID.\n>>> ";
                std::cin >> temp.num;

                std::cout << "Enter employee name.\n>>> ";
                std::cin >> temp.name;

                std::cout << "Enter amount of working hours of employee.\n>>> ";
                std::cin >> temp.hours;

                fout << temp.num << ' ' << temp.name << ' ' << temp.hours << ' ';
        }

        fout.close();

        return 0;
}
