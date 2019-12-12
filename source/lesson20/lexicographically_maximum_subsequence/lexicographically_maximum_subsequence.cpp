#include <iostream> 

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
