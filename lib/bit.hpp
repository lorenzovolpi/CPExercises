#ifndef _BIT__HPP
#define _BIT__HPP

#include <iostream>
#include <vector>

struct bit
{
	std::vector<int> v;

    bit(int n) : v(n + 1, 0) {};

    bit(int n, int val) : v(n + 1, val)
    {
        v[0] = 0;
        for (int i = 1; i <= n; ++i) 
            if((i + (i & -i)) <= n) 
                v[i + (i & -i)] += v[i]; 
    };

    bit(std::vector<int> vec) : v(vec.size() + 1)
    {
        v[0] = 0;
        for (int i = 0; i < vec.size(); ++i) { v[i + 1] = vec[i]; }
        for (int i = 1; i <= vec.size(); ++i) 
            if((i + (i & -i)) <= vec.size()) 
                v[i + (i & -i)] += v[i];
    };

    void add(int k, int val)
    {
        for (++k; k < v.size(); k += k & -k) { v[k] += val; }
    }

    int sum(int k)
    {
        int s = 0;
        for (++k; k > 0; k -= k & -k) { s += v[k]; }
        return s;
    }
};

#endif