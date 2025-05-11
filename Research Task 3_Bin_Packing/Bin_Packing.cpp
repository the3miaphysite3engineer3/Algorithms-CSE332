#include <iostream>
#include <vector>
#include <numeric> 

using namespace std;

void first_fit(const vector<int>& items, int bin_capacity, 
               vector<int>& bins, vector<vector<int>>& bin_contents,
               vector<vector<int>>& illegal_bins, vector<int>& illegal_items) {
    for (int item : items) {
        if (item > bin_capacity) {
            // Handle oversized items
            illegal_bins.push_back(vector<int>{item});
            illegal_items.push_back(item);
            continue;
        }

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
    vector<int> items = {25, 2, 5, 4, 7, 30, 1, 3, 6, 10, 9, 1, 3, 6, 20, 15, 11, 18, 2, 5, 6, 7};
    int bin_capacity = 20;
    
    vector<int> bins;
    vector<vector<int>> bin_contents;
    vector<vector<int>> illegal_bins;
    vector<int> illegal_items;

    first_fit(items, bin_capacity, bins, bin_contents, illegal_bins, illegal_items);

    // Print regular bins
    cout << "Number of regular bins used: " << bins.size() << endl;
    for (size_t i = 0; i < bin_contents.size(); ++i) {
        cout << "Bin " << (i + 1) << ": (";
        for (int item : bin_contents[i]) {
            cout << item << " ";
        }
        int sum = accumulate(bin_contents[i].begin(), bin_contents[i].end(), 0);
        cout << ")... Sum: " << sum << endl;
    }

    // Print illegal items and bins
    if (!illegal_items.empty()) {
        cout << "\nIllegal items handling:" << endl;
        cout << "Number of illegal bins: " << illegal_bins.size() << endl;
        for (size_t i = 0; i < illegal_items.size(); ++i) {
            cout << "Error: Item " << illegal_items[i] 
                 << " cannot be placed in any bin (exceeds capacity)" << endl;
        }
    }

    return 0;
}
