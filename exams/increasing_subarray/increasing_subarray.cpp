#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

struct subarray{
    int len;
    std::vector<int>::const_iterator it;

    subarray(int len, std::vector<int>::const_iterator it) : len(len), it(it) {}
};

std::vector<subarray> get_subarrays(const std::vector<int> &nums) {
    std::vector<subarray> subarrs;
    int len = 1, start = 0;
    for(int i = 1; i<nums.size(); ++i) {
        if(nums[i] > nums[i-1]) {
            len++;
        } else {
            subarrs.emplace_back(len, nums.begin() + start);
            start = i;
            len = 1;
        }
    }
    subarrs.emplace_back(len, nums.begin() + start);

    return subarrs;
}

int max_err_subarray(const std::vector<subarray> &subarrs) {
    int max = subarrs[0].len + (subarrs.size() > 1 ? 1 : 0);

    for(int i = 1; i<subarrs.size(); ++i) {
        if( ( i + 1 < subarrs.size() || (i + 1 == subarrs.size() && *(subarrs[i].it) > 0) ) && subarrs[i].len + 1 > max ) 
            max = subarrs[i].len + 1;
        
        if(subarrs[i-1].len == 1) {
            if(*(subarrs[i].it) > 0) {
                if(subarrs[i-1].len + subarrs[i].len > max) max = subarrs[i-1].len + subarrs[i].len;
            }
        } else if(subarrs[i].len == 1 && subarrs[i-1].len > 1) {
            if(subarrs[i-1].len + subarrs[i].len > max) max = subarrs[i-1].len + subarrs[i].len;
        } else {
            if( *(subarrs[i-1].it + subarrs[i-1].len - 1) + 1 < *(subarrs[i].it + 1) || 
                *(subarrs[i].it) - 1 > *(subarrs[i-1].it + subarrs[i-1].len - 2) ) {
                    if(subarrs[i-1].len + subarrs[i].len > max) max = subarrs[i-1].len + subarrs[i].len;
                }
        }
    }

    return max;
}

int main(int argc, char** argv) {
    if(argc < 2) return 1;
    std::ifstream in;
    in.open(argv[1]);

    int n = 0;
    in >> n;
    std::vector<int> nums;
    for(int i = 0; i<n && !in.eof(); ++i) {
        int x;
        in >> x;
        nums.push_back(x);
    }

    in.close();

    std::vector<subarray> subarrs = get_subarrays(nums);

    std::cout << max_err_subarray(subarrs) << std::endl;
}
