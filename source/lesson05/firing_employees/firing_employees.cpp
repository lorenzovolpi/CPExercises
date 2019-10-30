#include <iostream>
#include <vector>

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

void preorder_traversal(node* root)
{
	std::cout << root->get_rank() << " ";
	std::vector<node*> children = root->get_children();
	for (int i = 0; i<children.size(); ++i)
	{
		preorder_traversal(children[i]);
	}
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

		preorder_traversal(root);
		std::cout << std::endl;
		vec.clear();
	}

}