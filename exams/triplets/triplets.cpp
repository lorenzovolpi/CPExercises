#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

struct val{
    int64_t v, nv = 0, i, gt = 0, lt = 0;

    val(int64_t v, int64_t i) : v(v), i(i) {}
};

struct bit
{
	std::vector<int64_t> v;

    bit(int64_t n) : v(n + 1, 0) {};

    bit(int64_t n, int64_t val) : v(n + 1, val)
    {
        v[0] = 0;
        for (int64_t i = 0; (i + (i & -1)) <= n; ++i) { v[i + (i & -i)] += v[i]; }
    };

    bit(std::vector<int64_t> vec) : v(vec.size() + 1)
    {
        v[0] = 0;
        for (int64_t i = 0; i < vec.size(); ++i) { v[i + 1] = vec[i]; }
        for (int64_t i = 1; (i + (i & -i)) <= vec.size(); ++i) { v[i + (i & -i)] += v[i]; }
    };

    void add(int64_t k, int64_t val)
    {
        for (++k; k < v.size(); k += k & -k) { v[k] += val; }
    }

    int64_t sum(int64_t k)
    {
        int64_t s = 0;
        for (++k; k > 0; k -= k & -k) { s += v[k]; }
        return s;
    }
};

int64_t normalize(std::vector<val> &nums) {
    std::sort(nums.begin(), nums.end(), [](val v1, val v2) {
        return v1.v < v2.v;
    });

    int64_t fact = 0;
    nums[0].nv = fact;
    for(int64_t i = 1; i<nums.size(); ++i) {
        if(nums[i].v > nums[i-1].v) nums[i].nv = ++fact;
        else nums[i].nv = fact;
    }

    std::sort(nums.begin(), nums.end(), [](val v1, val v2) {
        return v1.i < v2.i;
    });

    return fact + 1;
}

int main(int argc, char** argv) {
    if(argc < 2) return 1;
    
    std::ifstream in;
    in.open(argv[1]);
    
    int64_t n = 0;
    in >> n;
    std::vector<val> nums;
    nums.reserve(n);
    for(int64_t i = 0; i<n && !in.eof(); ++i) {
        int64_t x;
        in >> x;
        nums.emplace_back(x, i);
    }

    in.close();    

    int64_t fvals = normalize(nums);

    bit ltbit(fvals, 0), gtbit(fvals, 0);

    for(int64_t i = 0; i<nums.size(); ++i) {
        nums[i].lt = ltbit.sum(nums[i].nv);
        ltbit.add(nums[i].nv + 1, 1);
    }

    for(int64_t i = nums.size() - 1; i>=0; --i) {
        nums[i].gt = gtbit.sum(nums[i].nv);
        gtbit.add(0, 1);
        gtbit.add(nums[i].nv, -1);
    }

    int64_t res = 0;
    for(int64_t i = 0; i<nums.size(); ++i) {
        res += nums[i].lt * nums[i].gt;
    }

    std::cout << res << std::endl;
}
