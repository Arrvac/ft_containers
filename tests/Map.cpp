#include "tests.hpp"
#include <map>
#include <utility>

template <class T>
void print_map(T map)
{
	typename T::iterator it = map.begin();
	std::cout << " --- Map of size " << map.size() << " ---" << std::endl;
	while (it != map.end())
	{
		std::cout << it->first << ": " << it->second << std::endl;
		it++;
	}
	std::cout << " --- " << std::endl;
}

void test_map(void)
{
	ft::Map<std::string, int> map;
	map.insert(std::make_pair("test", 42));
	map.insert(std::make_pair("a", 0));
	map.insert(std::make_pair("b", 4));
	map.insert(std::make_pair("b", -2));

	std::cout << map.find("test")->second << std::endl;
	std::cout << map.find("a")->second << std::endl;
	std::cout << map.find("b")->second << std::endl;
	std::cout << map["test"] << std::endl;
	map["c"] = -5;
	std::cout << "c: " << map["c"] << std::endl;

	std::cout << "Iterator" << std::endl;
	print_map(map);

	std::cout << map.count("v") << " 'v' found" << std::endl;
	std::cout << map.count("b") << " 'b' found" << std::endl;

	map["a"] = 1;
	map["b"] = 2;
	map["c"] = 3;


	ft::Map<std::string, int> map2;
	map2["x"] = 42;
	map2["y"] = 43;
	map2["z"] = 44;

	map.swap(map2);
	print_map(map);
	print_map(map2);
	
	// std::cout << map2.lower_bound("z")->first << std::endl;

	ft::Map<std::string, int> test;
	test["d"] = 3;
	test["c"] = 2;
	test["b"] = 1;
	test["a"] = 0;
	std::cout << "Lower bounds" << std::endl;
	std::cout << test.lower_bound("a")->first << std::endl;
	std::cout << test.lower_bound("b")->first << std::endl;
	std::cout << test.lower_bound("c")->first << std::endl;
	std::cout << "Upper bounds" << std::endl;
	std::cout << test.upper_bound("a")->first << std::endl;
	std::cout << test.upper_bound("b")->first << std::endl;
	std::cout << test.upper_bound("c")->first << std::endl;

	std::cout << "Equal range" << std::endl;
	std::pair<ft::Map<std::string, int>::iterator, ft::Map<std::string, int>::iterator> a = test.equal_range("c");
	std::cout << a.first->first << " - " << a.second->first << std::endl;

	std::cout << "Erase key" << std::endl;
	print_map(test);
	test.erase("c");
	print_map(test);
	std::cout << "Erase range" << std::endl;
	test.erase(test.begin(), test.end());
	print_map(test);

	std::cout << "Clear" << std::endl;
	test["hey"] = 42;
	test["what's"] = 34;
	test["up"] = 2;
	test["?"] = 35;
	print_map(test);
	test.clear();
	print_map(test);

	std::cout << "Decrementing end()" << std::endl;
	print_map(map);
	ft::Map<std::string, int>::iterator it = map.end();
	--it;
	std::cout << it->first << std::endl;

	std::cout << "Reverse iterator" << std::endl;
	ft::Map<std::string, int>::reverse_iterator rit = map.rbegin();
	while (rit != map.rend())
	{
		std::cout << rit->first << std::endl;
		++rit;
	}
	
	std::cout << "Operators" << std::endl;
	test = map;
	std::cout << "test == map: " << (test == map) << std::endl;
	std::cout << "test > map: " << (test > map) << std::endl;
	std::cout << "test < map: " << (test < map) << std::endl;
	std::cout << "test <= map: " << (test <= map) << std::endl;
	std::cout << "test >= map: " << (test >= map) << std::endl;
	std::cout << "test['test'] = 42" << std::endl;
	test["test"] = 42;
	std::cout << "test == map: " << (test == map) << std::endl;
	std::cout << "test > map: " << (test > map) << std::endl;
	std::cout << "test < map: " << (test < map) << std::endl;
	std::cout << "test <= map: " << (test <= map) << std::endl;
	std::cout << "test >= map: " << (test >= map) << std::endl;
}