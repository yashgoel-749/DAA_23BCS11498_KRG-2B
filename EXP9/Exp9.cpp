#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void computeLPSArray(const string& pat, int M, vector<int>& lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(const string& pat, const string& txt) {
    int M = pat.length();
    int N = txt.length();
    vector<int> lps(M);
    
    computeLPSArray(pat, M, lps);

    int txtIdx = 0;
    int patIdx = 0;
    vector<int> found_indices;

    while ((N - txtIdx) >= (M - patIdx)) {
        if (pat[patIdx] == txt[txtIdx]) {
            txtIdx++;
            patIdx++;
        }

        if (patIdx == M) {
            found_indices.push_back(txtIdx - patIdx);
            patIdx = lps[patIdx - 1];
        } else if (txtIdx < N && pat[patIdx] != txt[txtIdx]) {
            if (patIdx != 0) {
                patIdx = lps[patIdx - 1];
            } else {
                txtIdx++;
            }
        }
    }
    
    cout << "String S: " << txt << endl;
    cout << "Pattern P: " << pat << endl;

    if (found_indices.empty()) {
        cout << "Pattern not found in the string." << endl;
    } else {
        cout << "Pattern found at the following indices:" << endl;
        for (int index : found_indices) {
            cout << index << endl;
        }
    }
}

int main() {
    string txt = "ABABDABACDABABCABAB";
    string pat = "ABABCABAB";
    
    KMPSearch(pat, txt);

    return 0;
}