#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

void printSubset(const vector<int>& arr, int target, const vector<vector<bool>>& dp) {
    int n = arr.size();
    int r = n;
    int c = target;
    vector<int> subset;

    if (!dp[n][target]) {
        cout << "No subset found that sums to " << target << "." << endl;
        return;
    }
    
    while (r > 0 && c > 0) {
        int current_element = arr[r - 1];

        if (dp[r - 1][c] == true) {
            r--;
        } 
        
        else if (dp[r - 1][c - current_element] == true) {
            subset.push_back(current_element);
            c = c - current_element;
            r--;
        } 
        else {
            break; 
        }
    }

    if (c == 0) {
        cout << "Subset found with sum " << target << ": { ";
        for (size_t i = 0; i < subset.size(); ++i) {
            cout << subset[i] << (i == subset.size() - 1 ? "" : ", ");
        }
        cout << " }" << endl;
    } else {
        cout << "Error during backtracking: Subset sum not fully accounted for." << endl;
    }
}

bool isSubsetSum(const vector<int>& arr, int target) {
    int n = arr.size();
    
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1)); 

    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            
            int current_element = arr[i - 1];

            dp[i][j] = dp[i - 1][j];

            if (current_element <= j) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - current_element];
            }
        }
    }

    bool result = dp[n][target];

    cout << "\n--- Dynamic Programming Table (True = 1, False = 0) ---" << endl;
    cout << "Sum (j):   0\t";
    for(int j = 1; j <= target; ++j) cout << j << (j < 10 ? "\t" : " ");
    cout << "\n" << endl;
    
    for (int i = 0; i <= n; i++) {
        cout << (i == 0 ? "A[0]" : "A[" + to_string(i) + "] (" + to_string(arr[i-1]) + ")");
        cout << (i < 10 ? "\t" : "");
        for (int j = 0; j <= target; j++) {
            cout << (dp[i][j] ? "1" : "0") << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    if (result) {
        printSubset(arr, target, dp);
    } else {
        cout << "Result: False. No subset of the given array sums to " << target << "." << endl;
    }
    
    return result;
}

int main() {
    vector<int> arr = {3, 2, 7, 1};
    int target_sum = 6;

    cout << "Given Set: { ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    cout << " }" << endl;
    cout << "Target Sum (S): " << target_sum << endl;

    isSubsetSum(arr, target_sum);

    return 0;
}