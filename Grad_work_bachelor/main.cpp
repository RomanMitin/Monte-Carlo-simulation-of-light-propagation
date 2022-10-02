#include <random>
#include <iostream>
#include <unordered_map>

int main()
{
	std::mt19937 rnd;

	rnd.seed(0);

	std::uniform_real_distribution<> dist(0, 100);



	std::cout << sizeof(dist) << '\n';
	/*int n = 1000000;
	std::unordered_map<int, int> m;
	for (int i = 0; i < n; i++)
	{
		m[std::round(dist(rnd))]++;
	}

	for (auto el : m)
	{
		std::cout << "m[" << el.first << "] = " << el.second << '\n';
	}
	std::cout << '\n';*/
	return 0;
}