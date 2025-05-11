#include <iostream>
#include <vector>
#include <numeric> 

using namespace std;

void first_fit(const vector<int>& items, int bin_capacity, vector<int>& bins, vector<vector<int>>& bin_contents) {
    for (int item : items) {
        bool placed = false;
        for (size_t i = 0; i < bins.size(); ++i) {
            if (bins[i] + item <= bin_capacity) {
                bins[i] += item;
                bin_contents[i].push_back(item);
                placed = true;
                break;
            }
        }
        if (!placed) {
            bins.push_back(item);
            bin_contents.push_back(vector<int>{item});
        }
    }
}

int main() {
    vector<int> items = {2, 5, 4, 7, 1, 3, 6, 10, 9, 1, 3, 6, 20, 15, 11, 18, 2, 5, 6, 7};
    int bin_capacity = 20;
    vector<int> bins;
    vector<vector<int>> bin_contents;

    first_fit(items, bin_capacity, bins, bin_contents);

    cout << "Number of bins used: " << bins.size() << endl;
    for (size_t i = 0; i < bin_contents.size(); ++i) {
        cout << "Bin " << (i + 1) << ": ";
        cout << "(";
        for (int item : bin_contents[i]) {
            cout << item << " ";
        }
        int sum = accumulate(bin_contents[i].begin(), bin_contents[i].end(), 0);
        cout << ")";
        cout << "... Sum: " << sum << endl;
    }

    return 0;
}