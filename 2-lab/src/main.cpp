#include <iostream>
#include <exception>
#include <boost/thread.hpp>

using std::cout;
using std::cerr;
using std::endl;
using std::exception;

bool are_arguments_correct(int argc, char **argv);
bool fill_array(int *num_array, int array_size, char **argv);

struct min_max
{
        int min, min_index;
        int max, max_index;
};

void find_min_max(boost::promise<min_max> *p, int *num_array, int array_size)
{
        min_max result;
        result.min = num_array[0]; result.min_index = 0;
        result.max = num_array[0]; result.max_index = 0;

        for (int i = 1; i < array_size; ++i)
        {
                if (num_array[i] < result.min)
                {
                        result.min = num_array[i];
                        result.min_index = i;
                }
                boost::this_thread::sleep(boost::posix_time::milliseconds(7));
                if (num_array[i] > result.max)
                {
                        result.max = num_array[i];
                        result.max_index = i;
                }
                boost::this_thread::sleep(boost::posix_time::milliseconds(7));
        }

        p->set_value(result);
}

void find_average(boost::promise<int> *p, int *num_array, int array_size)
{
        int sum = 0;
        for (int i = 0; i < array_size; ++i)
        {
                sum += num_array[i];
                boost::this_thread::sleep(boost::posix_time::milliseconds(12));
        }

        p->set_value(sum / (double)array_size);
}

int main(int argc, char **argv)
{
        if (!are_arguments_correct(argc, argv))
        {
                cerr << "Arguments are incorrect." << endl;
                return 1;
        }

        int array_size = argc - 2;
        int *num_array = new int[array_size];

        if (!fill_array(num_array, array_size, argv))
        {
                cerr << "Failed to parse arguments." << endl;
                return 2;
        }


        boost::promise<min_max> min_max_promise;
        boost::unique_future<min_max> min_max_future = min_max_promise.get_future();
        boost::thread min_max_thread(find_min_max, &min_max_promise, num_array, array_size);

        boost::promise<int> avg_promise;
        boost::unique_future<int> avg_future = avg_promise.get_future();
        boost::thread avg_thread(find_average, &avg_promise, num_array, array_size);


        min_max indice_data = min_max_future.get();
        int average = avg_future.get();

        num_array[indice_data.min_index] = avg_future.get();
        num_array[indice_data.max_index] = avg_future.get();

        for (int i = 0; i < array_size; ++i)
        {
                cout << num_array[i] << " ";
        }
        cout << endl;


        delete[] num_array;
        return 0;
}


bool are_arguments_correct(int argc, char **argv)
{
        if (argc < 3)
        {
                cerr << "Only " << argc << " arguments are present." << endl;
                return false;
        }

        int array_size = 0;
        try
        {
                array_size = atoi(argv[1]);
        }
        catch (exception e)
        {
                cerr << "Can't convert argument " << argv[1] << endl;
                return false;
        }

        if (array_size + 2 != argc)
        {
                cerr << "Not enough elements or too much of them." << endl;
                return false;
        }

        return true;
}
bool fill_array(int *num_array, int array_size, char **argv)
{
        for (int i = 0; i < array_size; i++)
        {
                try
                {
                        num_array[i] = atoi(argv[i + 2]);
                }
                catch (exception e)
                {
                        return false;
                }
        }

        return true;
}
