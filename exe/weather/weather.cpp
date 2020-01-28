
#include <iostream>
#include <vector>
#include <fstream>

// https://codeforces.com/problemset/problem/234/C

int main() {
    std::ifstream in;
    in.open("input.txt");

    int n;
    in >> n;
    
    std::vector<int> vec(n, 0);

    for(int i = 0; i<n; ++i) in >> vec[i];

    in.close();

    std::vector<int> vtc(n, 0);
    if(vec[0] >= 0) vtc[0]++;
    for(int i = 1; i<n; ++i) {
        if(vec[i] <= 0) vtc[0]++;
    }

    int min = vtc[0];
    for(int k = 1; k<n-1; ++k) {
        vtc[k] = vtc[k - 1];
        if(vec[k] > 0) vtc[k]++;
        else if(vec[k] < 0) vtc[k]--;

        if(vtc[k] < min) min = vtc[k];
    }

    std::ofstream out;
    out.open("output.txt");

    out << min << std::endl;

    out.close();
}
