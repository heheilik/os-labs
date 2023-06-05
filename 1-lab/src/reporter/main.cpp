#include <iostream>
#include <fstream>
#include <cstring>
#include "../employee.hpp"

bool employee_comparator(employee &first, employee &second)
{
        return first.num < second.num;
}

void print_report(std::ostream &out, std::vector<employee> &data, int revenue_per_hour)
{
        out << "+------------+------------+------------+------------+" << std::endl;
        out << "|        num |       name |      hours |      total |" << std::endl;
        out << "+------------+------------+------------+------------+" << std::endl;

        for (const employee &e : data)
        {
                out << "| "
                    << std::setw(10) << e.num << " | "
                    << std::setw(10) << e.name << " | "
                    << std::setw(10) << e.hours << " | "
                    << std::setw(10) << e.hours * revenue_per_hour / 100.0 << " |"
                    << std::endl;
        }

        out << "+------------+------------+------------+------------+" << std::endl;
}

int main(int argc, char **argv)
{
        std::ofstream fout(argv[2]);

        std::string data_file_name = argv[1];
        std::size_t slash_position = data_file_name.rfind('/') + 1;
        data_file_name = data_file_name.substr(slash_position);

        fout << "Report for file \"" << data_file_name << "\"." << std::endl;


        std::vector<employee> employees;
        int num;
        char name[10];
        double hours;
        std::ifstream fin(argv[1]);
        fin >> num >> name >> hours;
        while (!fin.eof())
        {
                employee temp;
                temp.num = num;
                memcpy(temp.name, name, strlen(name));
                temp.hours = hours;
                employees.push_back(temp);
                fin >> num >> name >> hours;
        }

        std::sort(employees.begin(), employees.end(), employee_comparator);

        print_report(fout, employees, atoi(argv[3]));
        return 0;
}
