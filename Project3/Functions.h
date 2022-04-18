#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Stock.h"

void loadData(string ticker, vector<Stock*>& Dow30, int index);
bool findStock(string ticker, vector<Stock*>& Dow30, int& index);
int dateConverter(string date);
string convertIntDateToString(int date);