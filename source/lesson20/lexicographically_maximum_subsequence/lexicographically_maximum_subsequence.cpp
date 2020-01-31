#include <iostream> 

/*
    The solution can be found in a greedy fashion scanning the input string
    from right to left char by char. We take the first char and we no longer
    take smaller chars we found. Each time we find a greater char we update
    the maximum char encountered and fron thap point on no smaller values are
    taken. The solution runs in O(n) in time, where n is the length of th
    input string.
*/

std::string lms(const std::string& st) {
    std::string res;
    char max = st[st.length() - 1];
    res.push_back(max);
    for(int i = st.length() - 2; i >= 0; --i) {
        if(st[i] >= max) {
            if(st[i] > max) max = st[i];
            res.push_back(max);
        }
    }

    std::string s;
    for(int i = res.length() - 1; i>=0; --i) s.push_back(res[i]);
    return s;
}

int main() {
    std::string st;
    std::cin >> st;

    std::string res = lms(st);

    std::cout << res << std::endl;
}
