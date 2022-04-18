#include <iostream>
#include <vector>
#include <string>

using namespace std;

void merge(vector<float>& input, int left, int middle, int right) {

    int i = left; //starting index for left subarray
    int j = middle + 1; //starting index for right subarray
    int k = left; //starting array for temporary array;

    int sizeOfTemp = right - left + 1;

    float* temp = new float[sizeOfTemp];

    while (i <= middle && j <= right) {

        if (input[i] <= input[j]) {
            temp[k] = input[i];
            i++;
            k++;
        }
        else {
            temp[k] = input[j];
            j++;
            k++;
        }

    }

    while (i <= middle) {
        temp[k] = input[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = input[j];
        j++;
        k++;
    }

    for (int x = left; x <= right; x++) {
        input[x] = temp[x];
    }

    delete[] temp;


}


void mergeSort(vector<float>& input, int left, int right) {

    if (left < right) {

        int middle = (left + right) / 2;
        mergeSort(input, left, middle);
        mergeSort(input, middle + 1, right);
        merge(input, left, middle, right);
    }

}

int main() {

    vector<float> test = { -52.2, 1.2, 5.1, 12.5, 1.1, 12.4, -0.25, 141.253131 };
    mergeSort(test, 0, test.size() - 1);

    for (int i = 0; i < test.size(); i++) {

        cout << test[i] << endl;

    }

    return 0;
}