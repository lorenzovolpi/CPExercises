#include <iostream>
#include <vector>
#include <fstream>

template <typename T>
using matrix = std::vector<std::vector<T>>;

struct query{
    int r1, c1, r2, c2;

    query(int r1, int c1, int r2, int c2) : r1(r1 - 1), c1(c1 - 1), r2(r2 - 1), c2(c2 - 1) {}
};

matrix<int> build_subsquare(const matrix<char> &chart, int h, int w) {
    matrix<int> subsquare(h, std::vector<int>(w, 0));

    for(int j = 1; j<w; ++j) {
        if(chart[0][j] == '.' && chart[0][j-1] == '.') subsquare[0][j] = subsquare[0][j-1] + 1;
        else subsquare[0][j] = subsquare[0][j-1];
    }
    for(int i = 1; i<h; ++i) {
        if(chart[i][0] == '.' && chart[i-1][0] == '.') subsquare[i][0] = subsquare[i-1][0] + 1;
        else subsquare[i][0] = subsquare[i-1][0];
    }

    for(int i = 1; i<h; ++i) {
        for(int j = 1; j<w; ++j) {
            int val = subsquare[i-1][j] + subsquare[i][j-1];
            if(chart[i][j] == '.') {
                if(chart[i-1][j] == '.') val++;
                if(chart[i][j-1] == '.') val++;
            }
            subsquare[i][j] = val;
        }
    }

    return subsquare;
}

int main(int argc, char** argv) {
    if(argc < 2) return 1;

    std::ifstream in;
    in.open(argv[1]);

    int h, w;
    in >> h;
    in >> w;
    std::string str;
    std::getline(in, str);

    matrix<char> chart(h, std::vector<char>(w));
    for(int i = 0; i<h; ++i) {
        std::getline(in, str);
        std::copy(str.begin(), str.end(), chart[i].begin());
    }

    int q;
    in >> q;
    std::vector<query> qs;
    for(int i = 0; i<q; ++i) {
        int r1, c1, r2, c2;
        in >> r1; in >> c1; in >> r2; in >> c2;
        qs.emplace_back(r1, c1, r2, c2);
    }

    in.close();

    matrix<int> subsquare = build_subsquare(chart, h, w);

    

}
