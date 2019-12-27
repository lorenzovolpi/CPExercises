#include <iostream>
#include <vector>
#include <cmath>

struct node {
	node* p;
	int rank;
	std::vector<node*> children;

	node(int rank) : p(NULL), rank(rank) {};
};

int sqr(int x) { return pow(x, 2); }

std::vector<int> sieve_of_eratosthenes(int n) 
{
	std::vector<int> nums(n+1, 1);
	nums[0] = 0;
	nums[1] = 0;

	int p = 2;
	while (sqr(p) <= n) 
	{
		for (int f = p; f <= (n / p); ++f)
		{
			nums[f * p] = 0;
		}

		for (++p; nums[p] == 0; ++p) {}
	}

	return nums;
}

int blacklist(node* root, int depth, const std::vector<int>& primes)
{
	int bls = 0;

	bls += depth > 0 ? primes[root->rank + depth] : 0;

	for (int i = 0; i<root->children.size(); ++i)
	{
		bls += blacklist(root->children[i], depth + 1, primes);
	}

	return bls;
}

int main()
{
	int test_cases = 0;

	std::cin >> test_cases;
	std::vector<node*> vec;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0;
		std::cin >> n;

		vec.reserve(n);

		for (int j = 1; j <= n; ++j) vec.push_back(new node(j));
		for (int j = 0; j < n; ++j)
		{
			int x = 0;
			std::cin >> x;
			if(x != 0) {
				vec[j]->p = vec[x - 1];
				vec[x-1]->children.push_back(vec[j]);
			}
		}

		node* root = NULL;
		for (int j = 0; j < n; ++j) if(vec[j]->p == NULL) root = vec[j];

		std::vector<int> primes = sieve_of_eratosthenes(2*n);
		int bls = blacklist(root, 0, primes);
		std::cout << bls << std::endl;
		vec.clear();
	}

}