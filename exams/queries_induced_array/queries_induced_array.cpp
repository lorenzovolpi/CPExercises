#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

struct bit
{
	std::vector<int> v;

    bit(int n) : v(n + 1, 0) {};

    bit(int n, int val) : v(n + 1, val)
    {
        v[0] = 0;
        for (int i = 0; (i + (i & -1)) <= n; ++i) { v[i + (i & -i)] += v[i]; }
    };

    bit(std::vector<int> vec) : v(vec.size() + 1)
    {
        v[0] = 0;
        for (int i = 0; i < vec.size(); ++i) { v[i + 1] = vec[i]; }
        for (int i = 1; (i + (i & -i)) <= vec.size(); ++i) { v[i + (i & -i)] += v[i]; }
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

struct elem{
    int v, s = -1, e = -1;

    elem(int v) : v(v){}
};

void counting_sort(std::vector<elem*> &a, int n) {
    std::vector<elem*> b(a.size());
    std::vector<int> c(n, 0);
    for(int i = 0; i<a.size(); ++i) c[a[i]->s]++;
    for(int i = 1; i<n; ++i) c[i] += c[i-1];
    for(int i = a.size() -1; i>=0; --i) {
        b[c[a[i]->s]-1] = a[i];
        c[a[i]->s]--;
    }
    for(int i = 0; i<a.size(); ++i) a[i] = b[i];
}

int main(int argc, char** argv) {
    int n;
    std::cin >> n;
    
    std::vector<elem*> a(n);
    std::vector<int> v(n, 0);
    for(int i = 0; i<n; ++i) a[i] = new elem(i+1);
    bool res = true;
    for(int i = 0; i<n; ++i) {
        int x;
        std::cin >> x;
        if ( x < 0 || x > n ) {
            res = false;
            break;
        }
        if(a[x-1]->s == -1) {
            a[x-1]->s = i;
            a[x-1]->e = i;
        } else a[x-1]->e = i;

        v[i] = x;
    }

    /*
    if(argc < 2) return 1;
    std::ifstream in;

    in.open(argv[1]);

    int n;
    in >> n;
    std::vector<elem*> a(n);
    for(int i = 0; i<n; ++i) a[i] = new elem(i+1);
    bool res = true;
    for(int i = 0; i<n && !in.eof(); ++i) {
        int x;
        in >> x;
        if ( x < 0 || x > n ) {
            res = false;
            break;
        }
        if(a[x-1]->s == -1) {
            a[x-1]->s = i;
            a[x-1]->e = i;
        } else a[x-1]->e = i;
    }

    in.close();
    */

    if(!res) {
        std::cout << "N" << std::endl;
        return 0;
    }

    /*

    std::vector<elem*> p;
    for(int i = 0; i<n; ++i) if(a[i]->s != -1) p.push_back(a[i]);

    
    counting_sort(p, n);

    for(int i = 0; i<p.size() && res; ) {
        int j = i + 1;
        while(j < p.size() && p[j]->s < p[i]->e && res) {
            if(p[j]->e > p[i]->e) {
                res = false;
            } else j++;
        }
        i = j;
    }
    */



    std::deque<int> dq;

    for(int i = 0; i<v.size(); ++i) {
        if(i == a[v[i]-1]->s) {
            if(!dq.empty()) {
                if(v[i] < dq.front()) {
                    res = false;
                    break;
                }
            }
            dq.push_front(v[i]);
        }
        if(i == a[v[i] - 1]->e) {
            if(dq.front() != v[i]) {
                res = false;
                break;
            }
            dq.pop_front();
        }
    }


    std::cout << (res ? "Y" : "N") << std::endl;
}