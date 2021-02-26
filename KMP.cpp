

#include <string>
#include <vector>
namespace KMP
{
	typedef unsigned int natural;
	typedef std::vector<natural>::const_iterator constTable;
	typedef std::vector<natural>::iterator table;

	//assuming there is enoph space in startTable, startPrefix
	natural KMPBuildTabe(const constTable& prifixT, const table& longestMatchT, const char* small, const char* big, bool doUseTable)
	{
		natural j = 0, counter = 0;
		for (natural i = 0; big[i]; i++)
		{
			while ((j) && big[i] != small[j])
			{
				j = prifixT[j - 1];
			}

			if (big[i] == small[j])
			{
				j++;
			}

			if (doUseTable) {
				longestMatchT[i] = j;
			}
			if (!small[j])
			{
				counter++;//match
			}
		}
		return counter;
	}


	natural KMPnumberofmatch(const std::string& small, const std::string& big)
	{
		const char* smlChar = small.c_str();
		std::vector<natural> t(small.size()); t[0] = 0;
		KMPBuildTabe(t.begin(), t.begin() + 1, smlChar, smlChar + 1, true);//prepering prefix
		return KMPBuildTabe(t.begin(), t.begin() /*does not matter - becuse false in the end*/, smlChar, big.c_str(), false);
	}

}


#if 0 //cheecking
using namespace KMP;
#include <iostream>
std::vector<natural> t(100, -1);
int main()
{
	std::string s1 = "aaaaa";
	std::string s2 = "aa";
	t[0] = 0; t[1] = 1;
	KMPBuildTabe(t.begin(), t.begin() + 2, s2.c_str(), s1.c_str(), true);
	for (int i = 0; i < 10; i++)
	{
		std::cout << t[i] << " ";
	}
	std::cout << std::endl;

	std::cout << KMPnumberofmatch("adabad","adadabadabad") <<std::endl;//2
	system("pause");
	return 0;
}
#endif