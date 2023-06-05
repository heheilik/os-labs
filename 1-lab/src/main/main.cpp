#include <iostream>
#include <fstream>
#include <boost/process.hpp>

namespace bp = boost::process;

void print_file(std::string path_to_file);

int main()
{
        std::cout << "Enter data file name.\n>>> ";
        std::string path_to_data_file;
        std::cin >> path_to_data_file;
        path_to_data_file = ".build/data/" + path_to_data_file;

        std::cout << "Enter amount of entries.\n>>> ";
        int amount_of_entries;
        std::cin >> amount_of_entries;

        bp::child creator(
                ".build/bin/creator",
                path_to_data_file,
                std::to_string(amount_of_entries)
        );
        creator.wait();

        print_file(path_to_data_file);
        std::cout << std::endl;


        std::cout << "Enter report file name.\n>>> ";
        std::string path_to_report_file;
        std::cin >> path_to_report_file;
        path_to_report_file = ".build/data/" + path_to_report_file;

        std::cout << "Enter revenue per hour (in cents).\n>>> ";
        int revenue_per_hour;
        std::cin >> revenue_per_hour;

        bp::child reporter(
                ".build/bin/reporter",
                path_to_data_file,
                path_to_report_file,
                std::to_string(revenue_per_hour)
        );
        reporter.wait();

        print_file(path_to_report_file);


        return 0;
}

void print_file(std::string path_to_file)
{
        std::ifstream fin(path_to_file);
        std::cout << fin.rdbuf();
        fin.close();
}
