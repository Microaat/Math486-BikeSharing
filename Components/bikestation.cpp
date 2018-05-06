#include "bikestation.h"
#include <chrono>

BikeStation::BikeStation():
    mName(""),
    mInventory(0),
    mDocks(0),
    mAvgArrival(0.0),
    mProbRental(0.0),
    mLastRentedCount(0),
    mLastReturnedCount(0),
    mRandGenerator(std::chrono::system_clock::now().time_since_epoch().count()),
    mPosDistrArrival(0.0)
{}

BikeStation::BikeStation(const QString & name, int inventory, double avg_arrival, double prob_rental):
    mName(name),
    mInventory(inventory),
    mDocks(inventory),
    mAvgArrival(avg_arrival),
    mProbRental(prob_rental),
    mLastRentedCount(0),
    mLastReturnedCount(0),
    mRandGenerator(std::chrono::system_clock::now().time_since_epoch().count()),
    mPosDistrArrival(avg_arrival)
{
    setProbRental(prob_rental);
}

BikeStation::BikeStation(const QString & name, int inventory, int docks, double avg_arrival, double prob_rental):
    mName(name),
    mInventory(inventory),
    mDocks(docks),
    mAvgArrival(avg_arrival),
    mProbRental(prob_rental),
    mLastRentedCount(0),
    mLastReturnedCount(0),
    mRandGenerator(std::chrono::system_clock::now().time_since_epoch().count()),
    mPosDistrArrival(avg_arrival)
{
    setDocks(docks);
    setProbRental(prob_rental);
}

void BikeStation::setDocks(int docks){
    mDocks = (docks < mInventory)? mInventory : docks;
}

void BikeStation::setAvgArrival(double value){
    mAvgArrival = value;
    mPosDistrArrival.param(std::poisson_distribution<int>::param_type(value));
}

int BikeStation::amountRented(){
    int rented = 0;
    std::binomial_distribution<int> actual_rentals(getActualArrival(), mProbRental);
    rented = actual_rentals(mRandGenerator);
    mInventory -= rented;

    return rented;
}

int BikeStation::amountReturned(int amount){
    mInventory += amount;
    amount = mInventory - mDocks;
    mInventory = mDocks;

    return (amount < 0) ? 0 : amount;
}


std::ostream& operator<<(std::ostream& out, const BikeStation& bs){
    out << QString("Bike Station (%1): Inventory=%2, Docks=%3")
           .arg(bs.getName(), QString::number(bs.getInventory()), QString::number(bs.getDocks()))
           .toStdString();

    return out;
}
