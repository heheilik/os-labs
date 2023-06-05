#include <stdlib.h>
#include <iostream>
#include <boost/thread.hpp>

using std::cin;
using std::cout;
using std::endl;

using boost::mutex;
using boost::unique_lock;
using boost::condition_variable;



mutex              *thread_mutexes;
condition_variable *thread_cvs;
bool               *thread_waits;

mutex              main_m;
condition_variable main_cv;

int current_working_threads = 0;
int working_threads_left = 0;

mutex output_m;
mutex data_change_m;

int termination_id = -1;



void fill_with_zeroes(int*, int);

void sleep(int milliseconds)
{
        boost::this_thread::sleep(boost::posix_time::milliseconds(milliseconds));
}

void marker_thread(int id, int *num_array, int array_size)
{
        srand(id);
        while (id != termination_id)
        {
                {
                        unique_lock<mutex> lk(thread_mutexes[id - 1]);
                        thread_cvs[id - 1].wait(lk, [id] { return !thread_waits[id - 1]; });
                        thread_waits[id - 1] = true;
                }

                int marked_elements_amount = 0;

                int current_index = rand() % array_size;
                while (num_array[current_index] == 0)
                {
                        ++marked_elements_amount;
                        sleep(5);
                        {
                                unique_lock<mutex> lk(data_change_m);
                                num_array[current_index] = id;
                        }
                        sleep(5);
                        current_index = rand() % array_size;
                }

                {
                        unique_lock<mutex> lk(output_m);
                        cout << "ID: " << id << endl;
                        cout << "Amount of marked elements: " << marked_elements_amount << endl;
                        cout << "Index that stopped execution: " << current_index << endl;
                        cout << endl;
                }

                current_working_threads--;
                main_cv.notify_one();
                {
                        unique_lock<mutex> lk(thread_mutexes[id - 1]);
                        thread_cvs[id - 1].wait(lk, [id] { return !thread_waits[id - 1]; });
                }
        }

        for (int i = 0; i < array_size; i++)
        {
                if (num_array[i] == id)
                {
                        num_array[i] = 0;
                }
        }
}

int main(int argc, char **argv)
{
        int array_size = 0;
        cout << "Enter size of the array.\n>>> ";
        cin >> array_size;

        int *num_array = new int[array_size];
        fill_with_zeroes(num_array, array_size);


        int markers_amount = 0;
        cout << "Enter amount of markers.\n>>> ";
        cin >> markers_amount;

        boost::thread *markers = new boost::thread[markers_amount];
        thread_mutexes         = new mutex[markers_amount];
        thread_cvs             = new condition_variable[markers_amount];
        thread_waits           = new bool[markers_amount];
        for (int i = 0; i < markers_amount; i++)
        {
                markers[i] = boost::thread(marker_thread, i + 1, num_array, array_size);
                thread_waits[i] = true;
        }

        working_threads_left = markers_amount;
        while (working_threads_left > 0)
        {
                current_working_threads = working_threads_left--;
                for (int i = 0; i < markers_amount; i++)
                {
                        thread_waits[i] = false;
                        thread_cvs[i].notify_one();
                }

                unique_lock<mutex> lk(main_m);
                main_cv.wait(lk, [] { return current_working_threads == 0; });


                cout << "Enter what thread to terminate.\n>>> ";
                cin >> termination_id;

                thread_waits[termination_id - 1] = false;
                thread_cvs[termination_id - 1].notify_one();
                markers[termination_id - 1].join();

                cout << "Array: ";
                for (int i = 0; i < array_size; i++)
                {
                        cout << num_array[i] << " ";
                }
                cout << endl;
        }

        return 0;

}

void fill_with_zeroes(int *num_array, int array_size)
{
        for (int i = 0; i < array_size; ++i)
        {
                num_array[i] = 0;
        }
}
