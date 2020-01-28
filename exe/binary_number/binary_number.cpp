#include <iostream>
#include <vector>

int main() {
    std::string s;
    std::cin >> s;

    std::vector<int> d(s.length() + 1, 0);
    for(int i = 0; i<s.length(); ++i) d[i + 1] = (int)(s[i] - '0');

    int sum = 0;
    for(int i = d.size() - 1; i>0; ) {
        if(i == 1) {
            if(d[i] == 0) sum++;
            --i; 
        }
        else {
            int oldi = i;
            while(d[i] == 1) --i;

            if(i == oldi) {
                sum++;
                --i;
            }
            else {
                sum += (oldi - i) + 1;
                d[i] = 1;
            }
        }
    }    

    std::cout << sum << std::endl;
}
