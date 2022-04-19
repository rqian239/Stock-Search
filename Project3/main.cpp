#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <time.h>
#include "Stock.h"
#include "DayData.h"
#include "Heap.h"
#include "Functions.h"
#include "MergeSort.h"


using namespace std;

int main() {

    cout << "This application allows you to see the top (or worst) performing days of a particular stock for a given criteria." << endl;
    cout << "You will be asked to enter a stock ticker, the criteria to sort by, a date range, as well as how many days to return." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

    bool wantsNewStock = true;
    while (wantsNewStock) {
        cout << "Please enter a valid stock ticker from the Dow 30." << endl;
        cout << "Refer to \'cnbc.com/dow-30\' for available stocks." << endl;
        //cout << "Enter \'EXIT\' at any entry to exit the program." << endl << endl;

        string ticker;
        vector<Stock*> Dow30;
        bool check = true;
        int index = 0;

        while (check) {
            cin >> ticker;
            index = 0;
            bool found = findStock(ticker, Dow30, index);

            if (!found) {

                //Check if this is a valid stock
                string filePath = "../excel/" + ticker + ".csv";
                ifstream excel(filePath);

                if (excel.is_open()) {
                    check = false;
                    excel.close();
                    //create stock class and load data
                    Stock* addedStock = new Stock(ticker);
                    Dow30.push_back(addedStock);
                    index = Dow30.size() - 1;

                    loadData(ticker, Dow30, index);
                }
                else {
                    cout << "\'" + ticker + "\'" << " is not a valid ticker symbol." << endl;
                    cout << "Try again!" << endl;
                }

            }
        }


        //print debugging
        /*
        for(int i = 0; i < Dow30.size(); i++){
            cout << Dow30.at(i)->returnTicker() << endl;
            cout << "Number of Days: " << Dow30.at(i)->returnDates().size() << endl;
        }
         */

        cout << endl << "You will now be asked for two dates which will serve as a range in which your data will be searched" << endl;
        cout << "Data is available from 2017-04-03 to 2022-03-31. Only valid ranges are accepted." << endl;

        //TODO: Validate dates and date range
        string startDate, endDate;
        check = true;
        while (check) {
            cout << "Please enter the first date (in the format YYYY-MM-DD)" << endl;
            cin >> startDate;
            cout << "Please enter the last date (in the format YYYY-MM-DD)" << endl;
            cin >> endDate;

            if (verifyDate(startDate) || verifyDate(endDate)) {
                cout << "This is an invalid input." << endl;
                continue;
            }
            if (dateConverter(startDate) > dateConverter(endDate)) {
                cout << "This is an invalid range." << endl;
                continue;
            }
            check = false;
        }

        cout << "You selected to search from " << startDate << " to " << endDate << "." << endl << endl;

        int menuSelection;
        int numDays;
        int start;
        int end;
        bool valid;
        Stock* stockPtr = Dow30.at(index);
        map<int, DayData>::iterator iterStart = stockPtr->dates.begin();
        map<int, DayData>::iterator iterEnd = stockPtr->dates.begin();
        check = true;

        while (check) {
            cout << "Please select one of the following criteria to search for." << endl;
            cout << "1. Most Returns" << endl;
            cout << "2. Least Returns (Most Losses)" << endl;
            cout << "3. Most Net Change (Measure for Volatility)" << endl;
            cout << "4. Least Net Change (Measure for Stability)" << endl;
            cin >> menuSelection;
            if (menuSelection <= 0 || menuSelection > 4) {
                cout << "Invalid input!" << endl;
                continue;
            }

            //TODO: Check that number of days are valid (can fit in range)
            cout << "Please input the number of days you want to search for. (i.e. Top X days with most returns)" << endl;
            cin >> numDays;


            start = dateConverter(startDate);
            end = dateConverter(endDate);

            iterStart = stockPtr->dates.find(start);
            iterEnd = stockPtr->dates.find(end);
            valid = true;
            check = false;

            if (iterStart == stockPtr->dates.end() || iterEnd == stockPtr->dates.end()) {
                cout << "Your start date is invalid (you chose a day when the market was closed)." << endl << "Try again." << endl;
                check = true;
                valid = false;
            }
        }




        timer clock;

        //HEAP SORT and MERGESORT for each Selection
        if (valid) {

            if (menuSelection == 1) {     //MOST RETURNS

                /* ====== HEAPSORT ====== */
                clock.start();
                MaxHeap* maxH = new MaxHeap();

                //map<int, DayData> copyOfDates = Dow30.at(index)->returnDates();
                //map<int, DayData>::iterator copyIter = copyOfDates.begin();

                iterStart = stockPtr->dates.find(start);

                for (; iterStart != iterEnd; ++iterStart) {

                    pair<float, DayData> temp;
                    temp.first = iterStart->second.percentReturn;
                    temp.second = iterStart->second;
                    maxH->Insert(temp);

                }

                //TODO: Heap destructor and MERGESORT DESTRUCTOR?

                cout << endl << "HEAP SORT:" << endl;
                for (int i = 1; i <= numDays; i++) {

                    pair<float, DayData> temp = maxH->Extract();
                    cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                    cout << fixed << setprecision(5) << temp.second.percentReturn << "%" << endl;

                }
                clock.stop();
                cout << endl << "Time: " << clock.getTime() << " ms" << endl;
                clock.reset();




                //MERGE SORT
                clock.start();
                MergeSort* mrgSrt = new MergeSort();
                iterStart = stockPtr->dates.find(start);

                for (; iterStart != iterEnd; ++iterStart) {

                    pair<float, DayData> temp;
                    temp.first = iterStart->second.percentReturn;
                    temp.second = iterStart->second;
                    mrgSrt->Insert(temp);

                }


                mrgSrt->Sort();
                cout << endl << "MERGE SORT:" << endl;
                for (int i = 1; i <= numDays; i++) {
                    pair<float, DayData> temp = mrgSrt->vec.at(mrgSrt->vec.size() - i);
                    cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                    cout << fixed << setprecision(5) << temp.second.percentReturn << "%" << endl;

                }
                clock.stop();
                cout << endl << "Time: " << clock.getTime() << " ms" << endl;
                clock.reset();



            }
            else if (menuSelection == 2) {

                //HEAP SORT
                clock.start();
                MinHeap* minH = new MinHeap();

                iterStart = stockPtr->dates.find(start);

                for (; iterStart != iterEnd; ++iterStart) {

                    pair<float, DayData> temp;
                    temp.first = iterStart->second.percentReturn;
                    temp.second = iterStart->second;
                    minH->Insert(temp);

                }

                cout << endl << "HEAP SORT:" << endl;
                for (int i = 1; i <= numDays; i++) {

                    pair<float, DayData> temp = minH->Extract();
                    cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                    cout << fixed << setprecision(5) << temp.second.percentReturn << "%" << endl;

                }
                clock.stop();
                cout << endl << "Time: " << clock.getTime() << " ms" << endl;
                clock.reset();

                //MERGE SORT
                clock.start();
                MergeSort* mrgSrt = new MergeSort();
                iterStart = stockPtr->dates.find(start);

                for (; iterStart != iterEnd; ++iterStart) {

                    pair<float, DayData> temp;
                    temp.first = iterStart->second.percentReturn;
                    temp.second = iterStart->second;
                    mrgSrt->Insert(temp);

                }


                mrgSrt->Sort();
                cout << endl << "MERGE SORT:" << endl;
                for (int i = 1; i <= numDays; i++) {
                    pair<float, DayData> temp = mrgSrt->vec.at(i - 1);
                    cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                    cout << fixed << setprecision(5) << temp.second.percentReturn << "%" << endl;

                }
                clock.stop();
                cout << endl << "Time: " << clock.getTime() << " ms" << endl;
                clock.reset();
            }
            else if (menuSelection == 3) {
                clock.start();
                MaxHeap* maxH = new MaxHeap();

                iterStart = stockPtr->dates.find(start);


                for (; iterStart != iterEnd; ++iterStart) {

                    pair<float, DayData> temp;
                    temp.first = iterStart->second.percentNetChange;
                    temp.second = iterStart->second;
                    maxH->Insert(temp);
                }

                //TODO: Heap destructor and MERGESORT DESTRUCTOR?

                cout << endl << "HEAP SORT:" << endl;
                for (int i = 1; i <= numDays; i++) {

                    pair<float, DayData> temp = maxH->Extract();
                    cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                    cout << fixed << setprecision(5) << temp.second.percentNetChange << "%" << endl;

                }
                clock.stop();
                cout << endl << "Time: " << clock.getTime() << " ms" << endl;
                clock.reset();


                //MERGE SORT
                clock.start();
                MergeSort* mrgSrt = new MergeSort();
                iterStart = stockPtr->dates.find(start);

                for (; iterStart != iterEnd; ++iterStart) {

                    pair<float, DayData> temp;
                    temp.first = iterStart->second.percentNetChange;
                    temp.second = iterStart->second;
                    mrgSrt->Insert(temp);

                }


                mrgSrt->Sort();
                cout << endl << "MERGE SORT:" << endl;
                for (int i = 1; i <= numDays; i++) {
                    pair<float, DayData> temp = mrgSrt->vec.at(mrgSrt->vec.size() - i);
                    cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                    cout << fixed << setprecision(5) << temp.second.percentNetChange << "%" << endl;

                }
                clock.stop();
                cout << endl << "Time: " << clock.getTime() << " ms" << endl;
                clock.reset();

            }
            else if (menuSelection == 4) {
                clock.start();
                MinHeap* minH = new MinHeap();

                iterStart = stockPtr->dates.find(start);

                for (; iterStart != iterEnd; ++iterStart) {

                    pair<float, DayData> temp;
                    temp.first = iterStart->second.percentNetChange;
                    temp.second = iterStart->second;
                    minH->Insert(temp);
                }

                //TODO: Heap destructor?

                cout << endl << "HEAP SORT:" << endl;
                for (int i = 1; i <= numDays; i++) {

                    pair<float, DayData> temp = minH->Extract();
                    cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                    cout << fixed << setprecision(5) << temp.second.percentNetChange << "%" << endl;

                }
                clock.stop();
                cout << endl << "Time: " << clock.getTime() << " ms" << endl;
                clock.reset();



                //MERGE SORT
                clock.start();
                MergeSort* mrgSrt = new MergeSort();
                iterStart = stockPtr->dates.find(start);

                for (; iterStart != iterEnd; ++iterStart) {

                    pair<float, DayData> temp;
                    temp.first = iterStart->second.percentNetChange;
                    temp.second = iterStart->second;
                    mrgSrt->Insert(temp);

                }


                mrgSrt->Sort();
                cout << endl << "MERGE SORT:" << endl;
                for (int i = 1; i <= numDays; i++) {
                    pair<float, DayData> temp = mrgSrt->vec.at(i - 1);
                    cout << i << ". " << ticker << " " << convertIntDateToString(temp.second.date) << " ";
                    cout << fixed << setprecision(5) << temp.second.percentNetChange << "%" << endl;

                }
                clock.stop();
                cout << endl << "Time: " << clock.getTime() << " ms" << endl;
                clock.reset();
            }
        }

        cout << "Would you like to "
    }
    

    return 0;
}
