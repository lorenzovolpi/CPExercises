#include<cstdio>
#include<cmath>
#include<algorithm>

/*
	The algorithm is an application of Mo's algorithm. An array count
	stores the number of occurrences of elements in a given subarray
	of the original one and answer stores the sum of the requires function
	applied to all the values of count.
*/

// source: https://github.com/Waqar-107/Codeforces/blob/master/D-set/86D.Powerful%20Array.cpp

typedef long long int llong;

const int NUM=200005;
const int MAXV=1e6+100;

int blen, n, t, l, r, val;
int a[NUM], vcnt[MAXV];
llong ans[NUM], answer;

struct query {
    
    int l, r, ind;

} qs[NUM];


bool query_cmp(query a,query b) {
    if(a.l / blen != b.l / blen)
        return a.l<b.l;

    return a.r<b.r;
}

int main() {
    
    int i;

    std::scanf("%d%d", &n, &t);

    blen = std::ceil(std::sqrt(n));

    for(i = 0; i<n; ++i) std::scanf("%d", &a[i]);

    for(i = 0; i < t; ++i) {
        std::scanf("%d%d", &l, &r);
        qs[i].l = l-1; 
        qs[i].r = r;
        qs[i].ind = i;
    }

    std::sort(qs, qs + t, query_cmp);

    int ql, qr, cl, cr;

    cl = 0; cr = 0; answer = 0;
    for(i = 0; i < t; ++i) {

        ql=qs[i].l;
        qr=qs[i].r;

        while(cl > ql) {
            cl--;
            val=a[cl];

            answer -= (llong)vcnt[val]*vcnt[val]*val;
            vcnt[val]++;
            answer += (llong)vcnt[val]*vcnt[val]*val;
        }

        while(cl < ql) {
            val=a[cl];

            answer -= (llong)vcnt[val]*vcnt[val]*val;
            vcnt[val]--;
            answer += (llong)vcnt[val]*vcnt[val]*val;

            cl++;
        }

        while(cr < qr) {
            val=a[cr];

            answer -= (llong)vcnt[val]*vcnt[val]*val;
            vcnt[val]++;
            answer += (llong)vcnt[val]*vcnt[val]*val;

            cr++;
        }

        while(cr > qr) {
            cr--;
            val=a[cr];

            answer -= (llong)vcnt[val]*vcnt[val]*val;
            vcnt[val]--;
            answer += (llong)vcnt[val]*vcnt[val]*val;
        }

        ans[qs[i].ind] = answer;
    }

    for(i = 0; i < t; ++i) printf("%I64d\n", ans[i]);

}

