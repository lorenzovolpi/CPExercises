#include <iostream>
#include <vector>
#include <algorithm>

/*
	The idea is to store for each paire the relative strength, then sort the array by decreasing strength
	and parse the array. For each pair if neither first and sacond member are already matched, match them
	with each other. The algorithm runs in O(nlogn).
*/

struct team 
{
	int member1, 
		member2, 
		strength;

	team(int m1, int m2, int s) : 
		member1(m1),
		member2(m2),
		strength(s) { }
};

bool team_comp(team t1, team t2) 
{
	return t1.strength >= t2.strength;
}

std::vector<int> find_matches(std::vector<team> vect, int members)
{
	std::sort(vect.begin(), vect.end(), team_comp);

	std::vector<int> matches(members, 0);

	for (auto it = vect.begin(); it != vect.end(); ++it)
	{
		team match = *it;

		if (matches[match.member1] == 0 && matches[match.member2] == 0) {
			matches[match.member1] = match.member2 + 1;
			matches[match.member2] = match.member1 + 1;
		}
	}

	return matches;
}

int main()
{
	int teams_count = 0;
	std::cin >> teams_count;

	std::vector<team> vect;
	vect.reserve(teams_count * ((2 * teams_count) - 1));

	for (int i = 1; i < 2 * teams_count; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			int s = 0;
			std::cin >> s;
			vect.emplace_back(i, j, s);
		}
	}
	
	std::vector<int> matches = find_matches(vect, teams_count * 2);

	for (auto it = matches.begin(); it != matches.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";
}