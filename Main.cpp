#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <assert.h>
#include <utility>
#include <exception>

template<class InputIt>
struct length_iters
{
	length_iters() : substrLenght{ 0 }, secondElem1stOccurIt{}, substrEndIt{}{}
	length_iters(unsigned int substrLenght, InputIt secondElem1stOccurIt, InputIt substrEndIt) : substrLenght{ substrLenght }, secondElem1stOccurIt{ secondElem1stOccurIt }, substrEndIt{ substrEndIt }{}

	unsigned int substrLenght;
	InputIt secondElem1stOccurIt;
	InputIt substrEndIt;
};

template<class InputIt>
length_iters<InputIt> get_length_iters(InputIt iter, InputIt end, const int numb)
{
	length_iters<InputIt> result{};
	result.secondElem1stOccurIt = iter;
	std::set<char> buffer{};
	while (iter != end)
	{
		auto ok = buffer.insert(*iter);
		++result.substrLenght;
		if (ok.second)
		{
			if (buffer.size() == 2)
				result.secondElem1stOccurIt = iter;
			if (buffer.size() > numb)
			{
				buffer.erase(*iter);
				--result.substrLenght;
				break;
			}
		}
		++iter;

	}
	result.substrEndIt = iter;
	return result;
}
template<class ResultValue, class InputIt>
ResultValue get_substring(InputIt begin, InputIt end, const int numb)
{
	if (begin > end || numb < 1)
		throw std::runtime_error("Wrong arguments\n");

	auto result = get_length_iters(begin, end, numb);
	auto iter = result.secondElem1stOccurIt;

	while (iter != end && std::distance(iter, end) > result.substrLenght)
	{
		auto buffer = get_length_iters(iter, end, numb);
		if (result.substrLenght < buffer.substrLenght)
			result = buffer;
		iter = buffer.secondElem1stOccurIt;
	}
	return ResultValue(result.substrEndIt - result.substrLenght, result.substrEndIt);
}

void test()
{
	
	std::vector<std::pair<std::string, std::string>> srs_substr_2elem = { std::make_pair("aaabbbdaaabb", "aaabbb"), std::make_pair("aaabbbaaabb", "aaabbbaaabb"), std::make_pair("abcd", "ab"), std::make_pair("abcdd", "cdd"),
	std::make_pair("aabcdd", "aab"), std::make_pair("abababdabababab", "abababab") };
	for (auto elem : srs_substr_2elem)
		assert(get_substring<std::string>(elem.first.begin(), elem.first.end(), 2) == elem.second);

	std::vector<std::pair<std::string, std::string>> srs_substr_1elem = { std::make_pair("aaabbbdaaabb", "aaa"), std::make_pair("aaabbbaaabbbb", "bbbb"), std::make_pair("abcd", "a"), std::make_pair("abcdd", "dd"),
	std::make_pair("aabcdd", "aa"), std::make_pair("abababdabababab", "a"), std::make_pair("a", "a") };
	for (auto elem : srs_substr_1elem)
		assert(get_substring<std::string>(elem.first.begin(), elem.first.end(), 1) == elem.second);

	std::vector<std::pair<std::string, std::string>> srs_substr_3elem = { std::make_pair("aaabbbdaaabb", "aaabbbdaaabb"), std::make_pair("aaabbbadfaabbbb", "aaabbbad"), std::make_pair("abcd", "abc"), std::make_pair("abcdd", "bcdd"),
	std::make_pair("aabcdd", "aabc"), std::make_pair("a", "a") };
	for (auto elem : srs_substr_3elem)
		assert(get_substring<std::string>(elem.first.begin(), elem.first.end(), 3) == elem.second);

	for (auto elem : srs_substr_3elem)
		assert(get_substring<std::string>(elem.first.begin(), elem.first.end(), 4) == elem.first);

	std::vector <std::vector<int>> srs_numeric = { { 1,1,1,2,2,2,4,1,1,1,2,2 }, {1,1,1,2,2,2,1,1,1,2,2}, {1,2,3,4}, {1,2,3,4,44,4,44}, {0, -5, 0, 5, -5} };
	std::vector <std::vector<int>> res_numeric = { { 1,1,1,2,2,2 }, {1,1,1,2,2,2,1,1,1,2,2}, {1,2}, {4,44,4,44}, {0, -5, 0} };
	for(int i = 0; i< srs_numeric.size(); ++i)
		assert(get_substring<std::vector<int>>(srs_numeric[i].begin(), srs_numeric[i].end(), 2) == res_numeric[i]);
}


int main()
{
	try 
	{
		test();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}

	getchar();
	return 0;
}