#ifndef BIKESTATION_H
#define BIKESTATION_H

#include <QtGlobal>
#include <QString>
//#include <QMultiMap>

#include <iostream>
#include <random>

class BikeStation {
    QString mName;

    // The number of bikes this station has available
    int mInventory;

    // If mDocks < mInventory, then mDocks = mInventory
    int mDocks;

    // The average arrival of individuals to the station
    double mAvgArrival;

    // The probability that an individual will rent a bike.
    double mProbRental;

    // Keeps track of how many bikes were rented last
    int mLastRentedCount;

    // Keeps track of how many bikes were returned last
    int mLastReturnedCount;

    std::default_random_engine mRandGenerator;
    std::poisson_distribution<int> mPosDistrArrival;

    // The station preference are a list of stations that individuals are most likely to return a bike.
    // If the map is empty, then all stations have equal preference by individuals.
    // QMultiMap<double, BikeStation *> mStationPreference;

public:
    BikeStation();
    BikeStation(const QString& name, int inventory, double avg_arrival, double prob_rental);
    BikeStation(const QString& name, int inventory, int docks, double avg_arrival, double prob_rental);

    const QString& getName() const { return mName; }
    bool isStationFull() const { return (mInventory >= mDocks)? true : false; }
    int getAvailableSpace() const { return isStationFull()? 0 : mDocks - mInventory; }
    int getInventory() const { return mInventory; }
    int getDocks() const { return mDocks; }
    double getAvgArrival() const { return mAvgArrival; }
    double getProbRental() const { return mProbRental; }
    int getActualArrival(){ return mPosDistrArrival(mRandGenerator); }

    void setName(const QString& name){ mName = name; }

    // Set inventory should not be used if bikes are being returned to the station. In that case use returnBikes().
    void setInventory(int inv){ mInventory = inv; }
    void setDocks(int docks);
    void setAvgArrival(double);
    void setProbRental(double value){ mProbRental = (value < 0.0)? 0.0 : (value > 1.0)? 1.0 : value; }

    // This function calculates the amount of bikes that are rented
    int amountRented();

    // This function is used when bikes are returned to this station. It returns the amount of bikes
    // it accepted. -1 is returned if no bikes where accepted to the station meaning the station is full.

    // This function is used when bikes are returned to the station. It returns the amount of bikes that weren't
    // accepted to the station because the station has no free docks left. However, if 0 is returned, then all
    // bikes were accepted into the station.
    int amountReturned(int);
};

std::ostream& operator<<(std::ostream&, const BikeStation&);

#endif // BIKESTATION_H
