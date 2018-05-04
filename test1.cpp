/*
In this program I attempt to simulate the probability that individuals rent and return a bike to one 
particular station each hour. In this attempt I use a Poisson distribution to generate random integers 
which represent the number of bikes rented and returned to the station. 

A problem that in this program is that if the rate in > rate out and vice versa, then this station's 
inventory is either full or empty.
*/

#include <iostream>
#include <chrono>
#include <random>

int main(int argc, char** argv){
    using namespace std;

    //QCoreApplication app(argc, argv);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    unsigned max_iter = 0;
    int inventory = 0;
    int docks = 0;
    unsigned in = 0;
    unsigned out = 0;
    double demand = 0.0;

    cout << "Enter starting inventory of station: ";
    cin >> inventory;
    cout << "Enter demand of station (between 0 and 1): ";
    cin >> demand;
    cout << "Max Interation: ";
    cin >> max_iter;
    
    // For the moment docks will equal the starting inventory of the station.
    docks = inventory;
    // Make sure that demand is in between 0 and 1
    demand = (demand < 0)? 0 : (demand > 1)? 1: demand;

    poisson_distribution<int> rate_in(inventory * demand);
    poisson_distribution<int> rate_out(inventory * (1.0 - demand));

    cout << "Average Rate In = " << inventory * demand << " bikes per hour\n"
         << "Average Rate Out = " << inventory * (1.0 - demand) << " bikes per hour\n" << endl;

    for(int i = 0; i < max_iter; ++i){
        in = rate_in(generator);
        out = rate_out(generator);

        cout << ">> Iteration: " << i + 1 << "\n"
             << "Bikes Returned = " << in << " | Bikes Rented = " << out << endl;
        
        // Calculate the current inventory
        inventory += in - out;
        inventory = (inventory < 0)? 0 : (docks < inventory)? docks : inventory;
        
        cout << "Current Inventory = " << inventory << "\n" << endl;
    }


    return 1;
}
