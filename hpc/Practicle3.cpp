#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Reduction {

    vector<int> arr;

public:

    Reduction(vector<int> a) {
        arr = a;
    }

    void operations() {

        int sum = 0;

        int minVal = arr[0];

        int maxVal = arr[0];

        int n = arr.size();

        // Parallel Sum
        #pragma omp parallel for reduction(+:sum)
        for(int i = 0; i < n; i++) {
            sum += arr[i];
        }

        // Parallel Minimum
        #pragma omp parallel for reduction(min:minVal)
        for(int i = 0; i < n; i++) {

            if(arr[i] < minVal) {
                minVal = arr[i];
            }
        }

        // Parallel Maximum
        #pragma omp parallel for reduction(max:maxVal)
        for(int i = 0; i < n; i++) {

            if(arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }

        double average = (double)sum / n;

        cout << "Sum = " << sum << endl;

        cout << "Minimum = " << minVal << endl;

        cout << "Maximum = " << maxVal << endl;

        cout << "Average = " << average << endl;
    }
};

int main() {

    vector<int> arr = {10,20,30,40,50};

    Reduction r(arr);

    r.operations();

    return 0;
}