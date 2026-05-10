#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

long long comparisons = 0, swaps = 0;

// Partition helper - uses last element as pivot
// Places pivot at correct position and returns its index
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            swaps++;
        }
    }
    swap(arr[i + 1], arr[high]); // put pivot in correct spot
    swaps++;
    return i + 1;
}

// Quick Sort - O(n log n) average, O(n^2) worst case, O(log n) stack space on average
// Worst case happens when input is already sorted and last element is always picked as pivot
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Runs sort 3 times on a copy and returns the average time in microseconds
double timeSort(vector<int> original) {
    double total = 0;
    for (int run = 0; run < 3; run++) {
        vector<int> arr = original;
        comparisons = swaps = 0;
        auto start = high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
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
    vector<int> tmp = s5; quickSort(tmp, 0, tmp.size() - 1);
    cout << "n=5, Sorted     | Time: " << t1 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    // n=5 reversed
    vector<int> r5 = {5, 4, 3, 2, 1};
    comparisons = swaps = 0;
    double t2 = timeSort(r5);
    tmp = r5; quickSort(tmp, 0, tmp.size() - 1);
    cout << "n=5, Reversed   | Time: " << t2 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    // n=100 sorted and reversed
    vector<int> s100(100), r100(100);
    for (int i = 0; i < 100; i++) { s100[i] = i + 1; r100[i] = 100 - i; }

    comparisons = swaps = 0;
    double t3 = timeSort(s100);
    tmp = s100; quickSort(tmp, 0, tmp.size() - 1);
    cout << "n=100, Sorted   | Time: " << t3 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    comparisons = swaps = 0;
    double t4 = timeSort(r100);
    tmp = r100; quickSort(tmp, 0, tmp.size() - 1);
    cout << "n=100, Reversed | Time: " << t4 << " us | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;

    return 0;
}
