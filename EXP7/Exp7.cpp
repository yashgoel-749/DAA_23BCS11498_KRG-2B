#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void traceItems(const vector<int>& weights, const vector<int>& profits, int W, const vector<vector<int>>& K, int n) {
    int max_profit = K[n][W];
    int w = W;
    vector<int> selected_items;
    
    for (int i = n; i > 0 && max_profit > 0; i--) {
        if (K[i][w] != K[i - 1][w]) {
            selected_items.push_back(i - 1);
            max_profit = max_profit - profits[i - 1];
            w = w - weights[i - 1];
        }
    }

    cout << "\nSelected Items (Index, Weight, Profit):" << endl;
    reverse(selected_items.begin(), selected_items.end());
    for (int index : selected_items) {
        cout << "Item " << index + 1 << " (W: " << weights[index] << ", P: " << profits[index] << ")" << endl;
    }
}

int knapSack(int W, const vector<int>& profits, const vector<int>& weights) {
    int n = profits.size();
    vector<vector<int>> K(n + 1, vector<int>(W + 1));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                K[i][w] = max(profits[i - 1] + K[i - 1][w - weights[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    cout << "\n--- Dynamic Programming Table K[i][w] ---" << endl;
    cout << setw(8) << "Weight (w): ";
    for (int w = 0; w <= W; ++w) {
        cout << setw(4) << w;
    }
    cout << "\n" << endl;
    
    for (int i = 0; i <= n; i++) {
        cout << "Item " << i << (i == 0 ? " (n=0)" : " (W:" + to_string(weights[i-1]) + ", P:" + to_string(profits[i-1]) + ")");
        cout << (i < 10 ? "\t" : "");
        for (int w = 0; w <= W; w++) {
            cout << setw(4) << K[i][w];
        }
        cout << endl;
    }
    cout << "/n" << endl;

    int max_profit = K[n][W];
    cout << "\nMaximum Profit for Knapsack Capacity W = " << W << ": " << max_profit << endl;

    traceItems(weights, profits, W, K, n);

    return max_profit;
}

int main() {
    // Example from the problem description:
    // Weights: {1, 2, 3}
    // Profits: {10, 15, 40} 
    // Capacity W: 6
    vector<int> profits = {10, 15, 40};
    vector<int> weights = {1, 2, 3};
    int W = 6;
    
    cout << "0/1 Knapsack Problem using Dynamic Programming" << endl;
    cout << endl;
    cout << "Item Count (n): " << profits.size() << endl;
    cout << "Knapsack Capacity (W): " << W << endl;
    cout << "Items (Weight, Profit):" << endl;
    for (size_t i = 0; i < profits.size(); ++i) {
        cout << "Item " << i + 1 << ": (" << weights[i] << ", " << profits[i] << ")" << endl;
    }

    knapSack(W, profits, weights);

    return 0;
}