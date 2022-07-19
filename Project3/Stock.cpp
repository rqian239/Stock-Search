#include "Stock.h"


Stock::Stock() {}
Stock::Stock(string _ticker) {
    ticker = _ticker;
}
void Stock::AddDate(int date, DayData data) {
    dates[date] = data;
}

string Stock::ReturnTicker() {
    return ticker;

}

map<int, DayData>& Stock::ReturnDates() {
    return dates;
}

Stock::~Stock() {

    dates.clear();

}
