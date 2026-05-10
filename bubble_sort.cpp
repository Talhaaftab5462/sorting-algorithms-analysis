#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

long long comparisons = 0, swaps = 0;

// Bubble Sort - O(n^2) time, O(1) auxiliary space
// Early exit optimization: if no swaps happen in a pass, the array is already sorted
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break; // no swaps means sorted, stop early
    }
}

// Runs sort 3 times on a copy and returns the average time in microseconds
double timeSort(vector<int> original) {
    double total = 0;
    for (int run = 0; run < 3; run++) {
        vector<int> arr = original;
        comparisons = swaps = 0;
        auto start = high_resolution_clock::now();
        bubbleSort(arr);
        auto end = high_resolution_clock::now();
        total += duration<double, micro>(end - start).count();
    }
    return total / 3.0;
}

int main() {
    // n=5 sorted
    vector<int> s5 = {1, 2, 3, 4, 5};
    comparisons = swaps = 0;
    double t1 = timeSort(s5);
    vector<int> tmp = s5; bubbleSort(tmp);
    cout << "n=5, Sorted     | Time: " << t1 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    // n=5 reversed
    vector<int> r5 = {5, 4, 3, 2, 1};
    comparisons = swaps = 0;
    double t2 = timeSort(r5);
    tmp = r5; bubbleSort(tmp);
    cout << "n=5, Reversed   | Time: " << t2 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    // n=100 sorted and reversed
    vector<int> s100(100), r100(100);
    for (int i = 0; i < 100; i++) { s100[i] = i + 1; r100[i] = 100 - i; }

    comparisons = swaps = 0;
    double t3 = timeSort(s100);
    tmp = s100; bubbleSort(tmp);
    cout << "n=100, Sorted   | Time: " << t3 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    comparisons = swaps = 0;
    double t4 = timeSort(r100);
    tmp = r100; bubbleSort(tmp);
    cout << "n=100, Reversed | Time: " << t4 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    return 0;
}
