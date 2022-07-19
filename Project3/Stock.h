#pragma once
#include <string>
#include <iostream>
#include <map>
#include "DayData.h"

using namespace std;

class Stock {

    string ticker;

public:
 
    map<int, DayData> dates;     // MAKE PRIVATE


    Stock();
    Stock(string ticker);
    
    void AddDate(int date, DayData data);
    
    string ReturnTicker();
    map<int, DayData>& ReturnDates();      
   
    ~Stock();
};

