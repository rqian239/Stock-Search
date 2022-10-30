#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <sstream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <utility>
#include "Functions.h"
#include "Timer.h"



using namespace std;

/*
 * This is the main execution for the Stock Search project. A user will be prompted to input a valid stocks
 * from the Dow 30, select a date range, and then select criteria to search for as well as the number of days they
 * want to view. The program will sort the data from the days within the range and return the
 * number of days specified that best fit the criteria (out of the inputted stock tickers). In other words,
 * this application allows you to see the best (or worst) performing days of a particular stock(s) for a given criteria
 * within a date range.
 */

int main() {

    bool repeat = true; // This determines if the user wants to rerun the program
    while(repeat) {

        //system("CLS");

        // Print instructions and welcome message
        PrintWelcomeMsg();

        // Stores Stock objects specified by the user
        vector<Stock*> chosenStocks;
        EnterStocks(chosenStocks);

        if(chosenStocks.size() < 1){
            repeat = false;
            break;
        }

        pair<int, int> dateRange = EnterDates(chosenStocks);

        int numDays;
        int menuSelection = MenuSelection(numDays, chosenStocks.size());
        bool isPercentReturn = false;
        bool isMaxHeap = false;


        if (menuSelection == 1 || menuSelection == 2) {
            isPercentReturn = true;
        }
        if (menuSelection == 1 || menuSelection == 3) {
            isMaxHeap = true;
        }




        MaxHeap* maxH = new MaxHeap();
        MergeSort* mrgSrt = new MergeSort();
        MinHeap* minH = new MinHeap();

        int heapTime = 0;
        int mergeTime = 0;
        Timer clock;

        for (int i = 0; i < chosenStocks.size(); i++) {

            //Heap
            clock.Reset();
            clock.Start();
            if (isMaxHeap) {
                SortHp(isPercentReturn, chosenStocks[i], dateRange, maxH);
            }
            else {
                SortHp(isPercentReturn, chosenStocks[i], dateRange, minH);
            }
            clock.Stop();
            heapTime += clock.GetTime();
            clock.Reset();


            //MergeSrt
            clock.Reset();
            clock.Start();
            SortMrg(isPercentReturn, chosenStocks[i], dateRange, mrgSrt);
            clock.Stop();
            mergeTime += clock.GetTime();
            clock.Reset();
        }



        // Perform Heap Extract and return sorted data
        cout << endl << "HEAP SORT:" << endl;
        clock.Reset();
        clock.Start();
        if (isMaxHeap) {
            PrintHeap(maxH, isPercentReturn, numDays);
        }
        else {
            PrintHeap(minH, isPercentReturn, numDays);
        }
        clock.Stop();
        heapTime += clock.GetTime();
        cout << endl << "Time: " << heapTime << " ms" << endl;
        clock.Reset();

        // Perform Merge Sort and return sorted data
        cout << endl << "Please wait while we calculate Merge Sort..." << endl;
        clock.Reset();
        clock.Start();
        mrgSrt->Sort();
        cout << endl << "MERGE SORT:" << endl;
        PrintMerge(mrgSrt, menuSelection, numDays);
        clock.Stop();
        mergeTime += clock.GetTime();
        cout << endl << "Time: " << mergeTime << " ms" << endl;

        delete mrgSrt;
        delete maxH;
        delete minH;


        
        bool valid = false;
        while (!valid) {
            cout << endl << "Would you like to rerun the program with different entries? Enter \'y\' or \'n\'" << endl;
            string user;
            cin >> user;
            if (user == "n") {
                repeat = false;
                valid = true;
            }
            else if (user == "y") {
                repeat = true;
                valid = true;
            }
            else {
                cout << "Invalid Input, Try again." << endl;
                valid = false;
            }
        }

        for(Stock* stock : chosenStocks){
            delete stock;
        }

        chosenStocks.clear();
    }

    cout << "Thanks for using our program! Have a nice day!" << endl;

    return 0;
}
