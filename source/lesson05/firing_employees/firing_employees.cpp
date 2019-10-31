#include <iostream>
#include <vector>
#include <cmath>

class node {
private:

	node* p;
	int val, pi;
	std::vector<node*> children;

public:
	
	node() : p(NULL), val(-1), pi(0) {};

	node(int value, int parent_index) : p(NULL), val(value), pi(parent_index) {};
	
	int get_rank() { return this->val; }

	int get_parent_index() { return this->pi; }

	void set_parent(node* parent) 
	{
		this->p = parent;
	}

	std::vector<node*> get_children()
	{
		return this->children;
	}

	void add_child(node* child)
	{
		children.push_back(child);
	}

};

int sqr(int x) { return pow(x, 2); }

std::vector<int> sieve_of_eratosthenes(int n) 
{
	std::vector<int> nums;
	nums.reserve(n + 1);

	for (int i = 0; i <= n; ++i) { nums.push_back(i > 1 ? 1 : 0); }

	int p = 2;
	while (sqr(p) <= n) 
	{
		for (int f = p; f <= (n / p); ++f)
		{
			nums[f * p] = 0;
		}

		for (++p; nums[p] == 0; ++p) {}
	}

	std::vector<int> res;
	for (int i = 0; i <= n; ++i)
	{
		if (nums[i] == 1) res.push_back(i);
	}

	return res;
}

int binary_search(const std::vector<int>& vec, int f, int l, int n)
{
	if (f > l) return 0;

	int h = f + ((l - f) / 2);

	if (n < vec[h]) return binary_search(vec, f, h - 1, n);
	if (n > vec[h]) return binary_search(vec, h + 1, l, n);
	if (n == vec[h]) return 1;
}

int is_prime(const std::vector<int>& primes, int n)
{
	return binary_search(primes, 0, primes.size() - 1, n);
}

int blacklist(node* root, int depth, const std::vector<int>& primes)
{
	int bls = 0;

	if (depth > 0) 
	{
		bls += is_prime(primes, root->get_rank() + depth);
	}

	std::vector<node*> children = root->get_children();
	++depth;
	for (int i = 0; i<children.size(); ++i)
	{
		bls += blacklist(children[i], depth, primes);
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

		for (int j = 1; j <= n; ++j)
		{
			int x = 0;
			std::cin >> x;
			node* nd = new node(j, x);
			vec.push_back(nd);
		}

		node* root = NULL;

		for (int j = 0; j < n; ++j)
		{
			int pi = vec[j]->get_parent_index() - 1;
			if (pi >= 0) 
			{
				node* parent = vec[pi];
				vec[j]->set_parent(parent);
				parent->add_child(vec[j]);
			}
			else
			{
				root = vec[j];
			}
		}

		std::vector<int> primes = sieve_of_eratosthenes(n);
		int bls = blacklist(root, 0, primes);
		std::cout << bls << std::endl;
		vec.clear();
	}

}