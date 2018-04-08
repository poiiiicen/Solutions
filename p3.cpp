class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int start = 0;
        int ans = 0;
        int length = s.length();
        map<char, int> occur;
        occur[s[start]] = 1;
        for (auto i = 1; i < length; ++i) {
            if (occur[s[i]]) {
                if (i - start > ans) ans = i - start;
                for (; start < occur[s[i]]; ++start) {
                    occur[s[start]] = 0;
                }
            }
            occur[s[i]] = i + 1;
        }
        if (length - start > ans) ans = length - start;
        return ans;
    }
};