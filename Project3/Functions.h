#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include "Stock.h"
#include "DayData.h"
#include "Heap.h"
#include "MergeSort.h"
#include "Timer.h"



void PrintWelcomeMsg();
void EnterStocks(vector<Stock*>& chosenStocks);
pair<int, int> EnterDates(vector<Stock*>& chosenStocks);
int MenuSelection(int& numDays, int numStocks);
void SortHp(bool isPercentReturn, Stock* stockPtr, pair<int,int> dateRange, Heap* heap);
void SortMrg(bool isPercentReturn, Stock* stockPtr, pair<int, int> dateRange, MergeSort* mrgSrt);
void PrintHeap(Heap* heap, bool isPercentReturn, int numDays);
void PrintMerge(MergeSort* mrgSrt, int menuSelection, int numDays);

void LoadData(string ticker, vector<Stock*>& Dow30, int index);
bool FindStock(string ticker, vector<Stock*>& Dow30, int& index);
int DateConverter(string date);
string ConvertIntDateToString(int date);
bool IsCorrectFormat(string date);




