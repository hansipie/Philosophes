#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <thread>

using namespace std;

mutex g_display_mutex;
vector<mutex *> g_sticks;

void display(int id, string msg, int life)
{
    //g_display_mutex.lock();
    cout << "Philosopher " << id << " " << msg << " (life:" << life << ")" << endl;
    //g_display_mutex.unlock();
}

void philosopher(int id)
{
    // get left and right sticks
    mutex &left = *g_sticks[id];
    mutex &right = *g_sticks[(id + 1) % g_sticks.size()];
    int life = 2 * (g_sticks.size() - 1); 

    while (true)
    {
        // check if sticks are available
        bool left_stick = left.try_lock();
        bool right_stick = right.try_lock();

        if (life <= 0)
        {
            display(id, "dies", life);
            break;
        }

        //if (left_stick)
        //    display(id, "gets left stick", life);
        //if (right_stick)
        //    display(id, "gets right stick", life);

        if (left_stick && right_stick)
        {
            // eat for a while
            display(id, "is eating...", life);    
            sleep(5);
            life++;
            // release sticks
            left.unlock();
            right.unlock();
            //display(id, "ends eating", life);
        }
        else if (left_stick || right_stick)
        {
            // think for a while
            display(id, "is thinking...", life);
            life--; 
            sleep(5);

            if (left_stick)
                left.unlock();
            else
                right.unlock();
            //display(id, "ends thinking", life);
        }
        else
        {
            // sleep for a while
            life--;
            display(id, "is sleeping...", life);
            sleep(5);
            //display(id, "ends sleeping", life);
        }
    }
}

int main(int argc, char **argv)
{
    // get number of philosophers
    int num_philosophers = 0;
    cout << "Enter number of philosophers: ";
    cin >> num_philosophers;

    // initialize philosophers and forks
    for (int i = 0; i < (num_philosophers + 1); i++)
        g_sticks.push_back(new mutex());

    // create threads for each philosopher
    vector<thread> threads;
    for (int i = 0; i < num_philosophers; i++)
        threads.push_back(thread(philosopher, i));

    // wait for threads to finish
    for (auto &t : threads)
        t.join();    
    return 0;
}