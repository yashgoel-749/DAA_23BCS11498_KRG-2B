class Solution {
  public:
    vector<int> preGreaterEle(vector<int>& arr) {
    vector<int> ans;
    stack<int> st;

    for(int x : arr) {
        while(!st.empty() && st.top() <= x)
            st.pop();

        if(st.empty()) ans.push_back(-1);
        else ans.push_back(st.top());

        st.push(x);
    }
    return ans;
    }
};
