#include <iostream>
#define DIGIT 6
#define NUMERAL 16
#include <sstream>
using namespace std;
char * lookup = "0123456789ABCDEF";

string arrToStr(int * arr, int size);



//inline void addOne(vector<int>& arr){
void addOne(int* arr){

    arr[0] += 1;

    for(int i = 0; i < DIGIT; ++i){
        if (i == DIGIT-1){
            if (arr[i] == NUMERAL){
                arr[i] = 0;
            }
        }
        else if (arr[i] == NUMERAL){
            arr[i] = 0;
            arr[i+1] += 1;
        }else{
            return;
        }
    }
}


void printArr(int* arr, int size){
    for(int i = 0; i < size; ++i){
        cout << arr[i] << '-';
    }
    cout << '\n';
}

int main()
{

    //vector<int> arr = {9, 9, 9, 9, 9, 3};
    int arr[DIGIT] = {9,9,9,9,9,9};

    printArr(arr, DIGIT);
    printArr(arr, DIGIT);

    cout << arrToStr(arr, DIGIT) << '\n';
    addOne(arr);
    cout << arrToStr(arr, DIGIT) << '\n';
    addOne(arr);

    return 0;
}

string arrToStr(int * arr, int size){
    stringstream ss;
    for(int i = size-1; i >= 0; --i){
        ss << lookup[arr[i]];
    }

    return ss.str();
}