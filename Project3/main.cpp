#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <sstream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <utility>
#include "Functions.h"



using namespace std;


int main() {

    bool repeat = true;
    while(repeat) {

        system("CLS");
        PrintWelcomeMsg();

        vector<Stock*> chosenStocks;
        EnterStocks(chosenStocks);


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



        //Heap Extract
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

        //Merge Extract
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
    }
    return 0;
}
