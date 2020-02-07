#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <assert.h>
#include <utility>
#include <exception>

struct length_iters
{
	length_iters() : substrLenght{ 0 }, secondElem1stOccurIt{}, substrEndIt{}{}
	length_iters(unsigned int substrLenght, std::string::iterator secondElem1stOccurIt, std::string::iterator substrEndIt) : substrLenght{ substrLenght }, secondElem1stOccurIt{ secondElem1stOccurIt }, substrEndIt{ substrEndIt }{}

	unsigned int substrLenght;
	std::string::iterator secondElem1stOccurIt;
	std::string::iterator substrEndIt;
};

length_iters get_length_iters(std::string::iterator iter, std::string::iterator end, const int numb)
{
	length_iters result{};
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
std::string get_substring(std::string::iterator begin, std::string::iterator end, const int numb)
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
	return std::string(result.substrEndIt - result.substrLenght, result.substrEndIt);
}



std::pair<int, std::pair<std::string::iterator, std::string::iterator>> makepair_sum_iter_(std::string::iterator iter, std::string::iterator end, const int numb)
{
	int length{};
	auto buffer_iter = iter;
	std::set<char> buffer{};
	while (iter != end)
	{
		auto ok = buffer.insert(*iter);
		++length;
		if (ok.second)
		{
			if (buffer.size() == 2)
				buffer_iter = iter;
			if (buffer.size() > numb)
			{
				buffer.erase(*iter);
				--length;
				break;
			}
		}
		++iter;

	}
	return std::make_pair(length, std::make_pair(buffer_iter, iter));
}
std::string get_substring_(std::string::iterator begin, std::string::iterator end, const int numb)
{
	if (begin > end || numb < 1)
		throw std::runtime_error("Wrong arguments\n");

	auto result = makepair_sum_iter_(begin, end, numb);
	auto iter = result.second.first;

	while (iter != end && std::distance(iter, end) > result.first)
	{ 
		auto buffer = makepair_sum_iter_(iter, end, numb);
		if (result.first < buffer.first)
			result = buffer;
		iter = buffer.second.first;
	}
	return std::string (result.second.second-result.first, result.second.second);
}


void test()
{
	std::vector<std::pair<std::string, std::string>> srs_substr_2elem = { std::make_pair("aaabbbdaaabb", "aaabbb"), std::make_pair("aaabbbaaabb", "aaabbbaaabb"), std::make_pair("abcd", "ab"), std::make_pair("abcdd", "cdd"),
	std::make_pair("aabcdd", "aab"), std::make_pair("abababdabababab", "abababab") };
	for (auto elem : srs_substr_2elem)
	{
		std::cout << elem.second << '\t' << get_substring(elem.first.begin(), elem.first.end(), 2) << std::endl;
		assert(get_substring(elem.first.begin(), elem.first.end(), 2) == elem.second);
	}

	std::vector<std::pair<std::string, std::string>> srs_substr_1elem = { std::make_pair("aaabbbdaaabb", "aaa"), std::make_pair("aaabbbaaabbbb", "bbbb"), std::make_pair("abcd", "a"), std::make_pair("abcdd", "dd"),
	std::make_pair("aabcdd", "aa"), std::make_pair("abababdabababab", "a"), std::make_pair("a", "a") };
	for (auto elem : srs_substr_1elem)
		assert(get_substring(elem.first.begin(), elem.first.end(), 1) == elem.second);

	std::vector<std::pair<std::string, std::string>> srs_substr_3elem = { std::make_pair("aaabbbdaaabb", "aaabbbdaaabb"), std::make_pair("aaabbbadfaabbbb", "aaabbbad"), std::make_pair("abcd", "abc"), std::make_pair("abcdd", "bcdd"),
	std::make_pair("aabcdd", "aabc"), std::make_pair("a", "a") };
	for (auto elem : srs_substr_3elem)
		assert(get_substring(elem.first.begin(), elem.first.end(), 3) == elem.second);

	for (auto elem : srs_substr_3elem)
		assert(get_substring(elem.first.begin(), elem.first.end(), 4) == elem.first);
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