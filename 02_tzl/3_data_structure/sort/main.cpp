#include <iostream>
#include "sort.h"

using namespace std;
using namespace DTLib;

int main(int argc, char **argv)
{
    int array[] = {3,1,2,5,4};
    //Sort::Select(array, 5, 0);
    Sort::Insert(array, 5, 1);

    for (int i = 0; i < 5; i++) {
        cout << array[i] << endl;
    }


    return 0;
}