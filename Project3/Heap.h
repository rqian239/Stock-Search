#pragma once
#include "Stock.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

//highest returns = max heap
//lowest returns = min heap
//highest net change = max heap
//lowest net change = min heap



class Heap {

protected:
	vector<pair<float, DayData>> vec;

public:
	pair<float, DayData> Extract();
	void Insert(pair<float, DayData> data);

	virtual void HeapifyDown(int rootIndex) = 0;
	virtual void HeapifyUp(int rootIndex) = 0;

	~Heap();
};


struct MinHeap : public Heap {

	void HeapifyDown(int rootIndex);
	void HeapifyUp(int rootIndex);
};

struct MaxHeap : public Heap {

	void HeapifyDown(int rootIndex);
	void HeapifyUp(int rootIndex);
};
