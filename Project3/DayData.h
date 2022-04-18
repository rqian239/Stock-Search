#pragma once

struct DayData {
    int date;
    float open;
    float close;
    float high;
    float low;
    float percentReturn; //(close - open) / open
    float percentNetChange; //(high - low) / low

    //Constructor
    DayData(int date, float open, float close, float high, float low);
    DayData();
};