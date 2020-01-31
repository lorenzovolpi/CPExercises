#include <iostream>
#include <vector>
#include <algorithm>

/*
    The solution can be found firstly sorting the array of meetings in
    increasing order of the ending time. The the first meeting is taken
    and all overlapping meetings are discarded. The the next valid metting
    is taken and so on. The solution is computed in O(nlogn) with n the
    number of the meetings.
*/

struct meeting {
    int i, s, e;

    meeting(int i) : i(i), s(0), e(0) {}
    meeting(int i, int s, int e) : i(i), s(s), e(e) {}
};

std::vector<int> n_meetings(std::vector<meeting>& meetings) {
    std::sort(meetings.begin(), meetings.end(), [](meeting m1, meeting m2) {
        return m1.e < m2.e;
    });

    int last_overlap = -1;
    std::vector<int> ms;
    for(int i = 0; i<meetings.size(); ++i) {
        if(meetings[i].s >= last_overlap) {
            ms.push_back(meetings[i].i + 1);
            last_overlap = meetings[i].e;
        }
    }

    return ms;
}

int main() {
    int test_cases = 0;
    std::cin >> test_cases;
    std::vector<meeting> meetings;
    std::vector<std::vector<int>> outp;
    for(int i = 0; i<test_cases; ++i) {
        int n = 0;
        std::cin >> n;
        for(int j = 0; j<n; ++j) meetings.emplace_back(j);
        for(int j = 0; j<n; ++j) {
            int start = 0;
            std::cin >> start;
            meetings[j].s = start;
        }
        for(int j = 0; j<n; ++j) {
            int end = 0;
            std::cin >> end;
            meetings[j].e = end;
        }

        std::vector<int> ms = n_meetings(meetings);
        outp.push_back(ms);
        meetings.clear();
    }

    for(int i = 0; i<test_cases; ++i) {
        for(int j = 0; j<outp[i].size(); ++j) {
            std::cout << outp[i][j] << " ";
        }
        std::cout << std::endl;
    }
}