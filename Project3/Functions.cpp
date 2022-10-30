#include "Functions.h"


void PrintWelcomeMsg() {
    cout << "Welcome to a stock search application created by Dylan DePasquale, Douglas Ta, and Richard Qian." << endl << endl;
    cout
        << "This application allows you to see the best (or worst) performing days of a particular stock for a given criteria."
        << endl;
    cout
        << "You will be asked to enter a stock ticker, the criteria to sort by, a date range, as well as how many days to return."
        << endl << endl;

    cout << "Please enter a valid stock ticker from the Dow 30." << endl;
    cout << "Refer to \'cnbc.com/dow-30\' for available stocks." << endl << endl;
    cout << "Enter all the stocks you want to search. Type \"DONE\" when you are finished." << endl;
}
void EnterStocks(vector<Stock*>& chosenStocks) {

    string ticker;
    int index = 0;

    while (ticker != "DONE") {
        cin >> ticker;
        index = 0;
        bool found = FindStock(ticker, chosenStocks, index);


        //Check if this is a valid stock
        string filePath = "../excel/" + ticker + ".csv";
        ifstream excel(filePath);

        if (excel.is_open()) {
            excel.close();
            //create stock class and load data
            if (!found) {
                Stock* addedStock = new Stock(ticker);
                chosenStocks.push_back(addedStock);
                index = chosenStocks.size() - 1;

                LoadData(ticker, chosenStocks, index);
            }
        }
        else {
            if (ticker != "DONE") {
                cout << "\'" + ticker + "\'" << " is not a valid ticker symbol." << endl;
                cout << "Try again!" << endl;
            }
        }

        if (ticker != "DONE") {
            cout << "Would you like to input another stock? Type \"DONE\" if you're finished." << endl;
        }

    }
}
pair<int, int> EnterDates(vector<Stock*>& chosenStocks) {
    int start, end;
    bool check = true;
    string startDate, endDate;
    Stock* stockPtr = chosenStocks[0];

    cout << endl
        << "You will now be asked for two dates which will serve as a range in which your data will be searched"
        << endl;
    cout << "Data is available from 2017-04-03 to 2022-03-31. Only valid ranges are accepted." << endl << endl;

    while (check) {

        //start
        cout << "Please enter the first date (in the format YYYY-MM-DD)" << endl;
        cin >> startDate;
        if (!IsCorrectFormat(startDate)) {
            cout << "This is an invalid input." << endl;
            continue;
        }
        start = DateConverter(startDate);
        if (stockPtr->ReturnDates().find(start) == stockPtr->ReturnDates().end()) {    //not a valid date
            cout << "You chose an invalid date! (Either the market was closed or this date doesn't exist!)" << endl;
            continue;
        }



        //end
        cout << "Please enter the last date (in the format YYYY-MM-DD)" << endl;
        cin >> endDate;
        if (!IsCorrectFormat(endDate)) {
            cout << "This is an invalid input." << endl;
            continue;
        }
        end = DateConverter(endDate);
        if (stockPtr->ReturnDates().find(end) == stockPtr->ReturnDates().end()) {    //not a valid date
            cout << "You chose an invalid date! (Either the market was closed or this date doesn't exist!)" << endl;
            continue;
        }



        //range
        if (start < 170403 || end > 220331 || start > end) {
            cout << "This is an invalid range." << endl;
            continue;
        }

        check = false;
    }

    cout << "You selected to search from " << startDate << " to " << endDate << "." << endl << endl;
    return pair<int, int>(start, end);
}
int MenuSelection(int& numDays, int numStocks) {
    bool check = true;
    int menuSelection;

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


        //the problem is the date range. 
        bool check2 = true;
        while (check2) {
            cout << "Please input the number of days you want to search for. (i.e. Top X days with most returns)" << endl;
            cin >> numDays;
            
            if (numDays > 1000 || numDays < 1) {
                cout << "You can only display between 1 and 1,000 days!" << endl;
                continue;
            }
            check2 = false;
        }
        
        check = false;
    }
    return menuSelection;
}
void SortHp(bool isPercentReturn, Stock* stockPtr, pair<int, int> dateRange, Heap* heap) {

    map<int, DayData>::iterator iterStart = stockPtr->ReturnDates().find(dateRange.first);
    map<int, DayData>::iterator iterEnd = stockPtr->ReturnDates().find(dateRange.second);
    
    for (; iterStart != iterEnd; ++iterStart) {

        pair<float, DayData> temp;

        if (isPercentReturn) {
            temp.first = iterStart->second.percentReturn;
        }
        else {
            temp.first = iterStart->second.percentNetChange;
        }
        
        temp.second = iterStart->second;
        heap->Insert(temp);
    }
}
void SortMrg(bool isPercentReturn, Stock* stockPtr, pair<int, int> dateRange, MergeSort* mrgSrt) {

    map<int, DayData>::iterator iterStart = stockPtr->ReturnDates().find(dateRange.first);
    map<int, DayData>::iterator iterEnd = stockPtr->ReturnDates().find(dateRange.second);

    for (; iterStart != iterEnd; ++iterStart) {
        pair<float, DayData> temp;

        if (isPercentReturn) {
            temp.first = iterStart->second.percentReturn;
        }
        else {
            temp.first = iterStart->second.percentNetChange;
        }

        temp.second = iterStart->second;
        mrgSrt->Insert(temp);
    }
}
void PrintHeap(Heap* heap, bool isPercentReturn, int numDays) {

    for (int i = 1; i <= numDays; i++) {
        pair<float, DayData> temp = heap->Extract();
        cout << i << ". " << temp.second.ticker << " " << ConvertIntDateToString(temp.second.date) << " ";
        
        if (isPercentReturn) {
            cout << fixed << setprecision(5) << temp.second.percentReturn << "%" << endl;
        }
        else {
            cout << fixed << setprecision(5) << temp.second.percentNetChange << "%" << endl;
        }

    }
}
void PrintMerge(MergeSort* mrgSrt, int menuSelection, int numDays) {

    bool isPercentReturn = false;
    if (menuSelection == 1 || menuSelection == 2) {
        isPercentReturn = true;
    }

    if (menuSelection == 1 || menuSelection == 3) {

        for (int i = 1; i <= numDays; i++) {
            pair<float, DayData> temp = mrgSrt->GetVec().at(mrgSrt->GetVec().size() - i);
            cout << i << ". " << temp.second.ticker << " " << ConvertIntDateToString(temp.second.date) << " ";

            if (isPercentReturn) {
                cout << fixed << setprecision(5) << temp.second.percentReturn << "%" << endl;
            }
            else {
                cout << fixed << setprecision(5) << temp.second.percentNetChange << "%" << endl;
            }
        }
    }
    else {    //Print Backwards

        for (int i = 0; i < numDays; i++) {
            pair<float, DayData> temp = mrgSrt->GetVec().at(i);
            cout << i + 1 << ". " << temp.second.ticker << " " << ConvertIntDateToString(temp.second.date) << " ";

            if (isPercentReturn) {
                cout << fixed << setprecision(5) << temp.second.percentReturn << "%" << endl;
            }
            else {
                cout << fixed << setprecision(5) << temp.second.percentNetChange << "%" << endl;
            }
        }
    }
}

void LoadData(string ticker, vector<Stock*>& Dow30, int index) {

    string filePath = "../excel/" + ticker + ".csv";

    ifstream input(filePath);

    if (input.is_open()) {

        string line;
        getline(input, line);

        while (getline(input, line)) {

            istringstream stream(line);
            string dateString;
            string openString;
            string highString;
            string lowString;
            string closeString;

            int date;
            float open;
            float high;
            float low;
            float close;

            getline(stream, dateString, ',');
            getline(stream, openString, ',');
            getline(stream, highString, ',');
            getline(stream, lowString, ',');
            getline(stream, closeString, ',');

            date = DateConverter(dateString);
            open = stof(openString);
            high = stof(highString);
            low = stof(lowString);
            close = stof(closeString);

            Dow30.at(index)->AddDate(date, DayData(ticker, date, open, close, high, low));

        }

    }
    else {
        cout << "The file failed to open" << endl;
    }

}
bool FindStock(string ticker, vector<Stock*>& Dow30, int& index) {

    for (int i = 0; i < Dow30.size(); i++) {

        if (Dow30.at(i)->ReturnTicker() == ticker) {
            index = i;
            return true;
        }
    }

    index = -1;
    return false;

}
int DateConverter(string date) {
    date = date.substr(2, date.length() - 2);
    for (int i = 0; i < date.length(); i++) {
        if (date[i] == '-') {
            date.erase(i, 1);
        }

    }
    return stoi(date);
}
string ConvertIntDateToString(int date) {

    //Date in the format YY MM DD

    string stringDate = "";

    int tempDigits = date % 100;
    date /= 100;

    if (tempDigits >= 10) {
        stringDate = to_string(tempDigits);
    }
    else {
        stringDate = '0' + to_string(tempDigits);
    }

    tempDigits = date % 100;
    date /= 100;

    if (tempDigits >= 10) {
        stringDate = to_string(tempDigits) + '-' + stringDate;
    }
    else {
        stringDate = '0' + to_string(tempDigits) + '-' + stringDate;
    }

    tempDigits = date % 100;
    date /= 100;
    if (tempDigits >= 10) {
        stringDate = "20" + to_string(tempDigits) + '-' + stringDate;
    }
    else {
        stringDate = "200" + to_string(tempDigits) + '-' + stringDate;
    }

    return stringDate;

}
bool IsCorrectFormat(string date) { //Breaks the date given by user input into different strings to test for specific format
    if (date.length() != 10) {
        return false;
    }
    string year = date.substr(0, 4);
    string month = date.substr(5, 2);
    string day = date.substr(8, 2);

    for (int i = 0; i < year.length(); i++) {
        if (isdigit(year[i]) == false) {
            return false;
        }
    }

    for (int i = 0; i < month.length(); i++) {
        if (isdigit(month[i]) == false) {
            return false;
        }
        if (isdigit(day[i]) == false) {
            return false;
        }

    }

    return true;
}

