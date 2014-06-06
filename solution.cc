// Implement strStr().

// Returns a pointer to the first occurrence of needle in haystack, or null if needle is not part of haystack.

class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        assert(haystack && needle);
        int n = strlen(needle);
        if(n == 0) return haystack;
        vector<int> table(n, 0);
        compPrefixTable(needle, table);
        int m = 0, i = 0;
        while(*(haystack+m+i)) {
            if(*(haystack+m+i) == *(needle+i)) {
                if(i == n-1) {
                    return haystack+m;
                }
                ++i;
            } else {
                int fallback = table[i];
                if(fallback < 0) {
                    ++m;
                    i = 0;
                } else {
                    m = m+i-fallback;
                    i = fallback;
                }
            }
        }
        return NULL;
    }
    
    void compPrefixTable(char *needle, vector<int> &table) {
        table[0] = -1;
        int pos = 2;
        int mark = 0;
        while(pos < table.size()) {
            if(*(needle+pos-1) == *(needle+mark)) {
                table[pos] = ++mark;
                ++pos;
            } else if(mark > 0) {
                mark = table[mark];
            } else {
                table[pos] = 0;
                ++pos;
            }
        }
    }
};
