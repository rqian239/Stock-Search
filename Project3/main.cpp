#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Stock.h"
#include "DayData.h"
#include "Heap.h"
#include "Functions.h"

using namespace std;

//hello
int main() {

    cout << "This application allows you to see the top (or worst) performing days of a particular stock for a given criteria." << endl;
    cout << "You will be asked to enter a stock ticker, the criteria to sort by, a date range, as well as how many days to return." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

    cout << "Please enter a valid stock ticker from the Dow 30." << endl;
    cout << "Refer to \'cnbc.com/dow-30\' for available stocks." << endl;
    //cout << "Enter \'EXIT\' at any entry to exit the program." << endl << endl;

    string ticker;
    vector<Stock*> Dow30;
    cin >> ticker;


    int index = 0;
    bool found = findStock(ticker, Dow30, index);

    if (!found) {

        //Check if this is a valid stock
        string filePath = "../excel/" + ticker + ".csv";
        ifstream excel(filePath);

        if (excel.is_open()) {
            excel.close();

            //create stock class and load data
            Stock* addedStock = new Stock(ticker);
            Dow30.push_back(addedStock);
            index = Dow30.size() - 1;

            loadData(ticker, Dow30, index);
        }
        else {
            cout << "\'" + ticker + "\'" << " is not a valid ticker symbol." << endl;
        }

    }


    //print debugging
    /*
    for(int i = 0; i < Dow30.size(); i++){
        cout << Dow30.at(i)->returnTicker() << endl;
        cout << "Number of Days: " << Dow30.at(i)->returnDates().size() << endl;
    }
     */

    cout << "You will now be asked for two dates which will serve as a range in which your data will be searched" << endl;
    cout << "Data is available from 2017-04-03 to 2022-03-31. Only valid ranges are accepted." << endl;

    //TODO: Validate dates and date range

    string startDate, endDate;
    cout << "Please enter the first date (in the format YYYY-MM-DD)" << endl;
    cin >> startDate;
    cout << "Please enter the last date (in the format YYYY-MM-DD)" << endl << endl;
    cin >> endDate;

    cout << "You selected to search from " << startDate << " to " << endDate << "." << endl << endl;


    int menuSelection;
    cout << "Please select one of the following criteria to search for." << endl;
    cout << "1. Most Returns" << endl;
    cout << "2. Least Returns (Most Losses)" << endl;
    cout << "3. Most Net Change (Measure for Volatility)" << endl;
    cout << "4. Least Net Change (Measure for Stability)" << endl;
    cin >> menuSelection;

    //TODO: Check that number of days are valid (can fit in range)
    int numDays;
    cout << "Please input the number of days you want to search for. (i.e. Top X days with most returns)" << endl;
    cin >> numDays;

    int algoSelection;
    cout << "Please choose which algorithm you want to execute." << endl;
    cout << "1. Heap Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cin >> algoSelection;

    int start = dateConverter(startDate);
    int end = dateConverter(endDate);

    //HEAP SORT
    if (menuSelection == 1) {     //MOST RETURNS

        Stock* stockPtr = Dow30.at(index);
        //map<int, DayData>::iterator iterStart = Dow30.at(index)->returnDates().begin();
        //map<int, DayData>::iterator iterEnd = Dow30.at(index)->returnDates().begin();

        map<int, DayData>::iterator iterStart = stockPtr->dates.begin();
        map<int, DayData>::iterator iterEnd = stockPtr->dates.begin();

        iterStart = stockPtr->dates.find(start);
        iterEnd = stockPtr->dates.find(end);
        bool valid = true;

        if (iterStart == stockPtr->dates.end()) {
            cout << "Your start date is invalid (you chose a day when the market was closed)." << endl;
            valid = false;
        }
        if (iterEnd == stockPtr->dates.end()) {
            cout << "Your end date is invalid (you chose a day when the market was closed)." << endl;
            valid = false;
        }

        if (valid) {

            MaxHeap* maxH = new MaxHeap();

            //map<int, DayData> copyOfDates = Dow30.at(index)->returnDates();
            //map<int, DayData>::iterator copyIter = copyOfDates.begin();

            iterStart = stockPtr->dates.find(start);
            cout << iterStart->first << endl;

            for (; iterStart != iterEnd; ++iterStart) {

                pair<float, DayData> temp;
                temp.first = iterStart->second.percentReturn;
                temp.second = iterStart->second;
                maxH->Insert(temp);

            }

            //TODO: Heap destructor?


            for (int i = 1; i <= numDays; i++) {

                pair<float, DayData> temp = maxH->Extract();
                cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                cout << fixed << setprecision(5) << temp.second.percentReturn << "%" << endl;

            }

        }



    }
    else if (menuSelection == 2) {

    }
    else if (menuSelection == 3) {

    }
    else if (menuSelection == 4) {

    }



    return 0;
}
