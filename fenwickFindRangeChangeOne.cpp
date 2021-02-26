
namespace fenwickFindRangeChangeOne
{
#define fr(i, n) for(int i = 0; i < n;i++)


#define NUTURAL 0
	typedef int info;
	typedef int index;
	info combine(info a, info b)//shuld be assusiative
	{
		return a + b;
	}

	struct fNode
	{
		fNode* children[2];
		info val;
		fNode()
		{
			this->val = NUTURAL; this->children[0] = this->children[1] = nullptr;
		}
		~fNode()
		{
			fr(i, 2)
			{
				if (this->children[i])
				{
					this->children[i]->~fNode();
				}
			}
		}
	} typedef fNode;

	inline info valueOf(fNode* curr)
	{
		return (curr) ? curr->val : NUTURAL;
	}

	//range always include min and not max; start is not null
	void updateF(index pos, info val, index min, index max, fNode* start)
	{
		if (1 == max - min)
		{
			start->val = val;
		}
		else
		{
			index middle = (min + max) / 2;
			int childPlace = ((pos >= middle) ? 1 : 0);
			(start->children[childPlace] == nullptr) ? start->children[childPlace] = new fNode : nullptr;//nonn null child
			updateF(pos, val,
				(childPlace) ? middle : min,//min
				(childPlace) ? max : middle,//max
				start->children[childPlace]);//start
			start->val = combine(valueOf(start->children[0]), valueOf(start->children[1]));
		}
	}


	info rangeValF(index MinPos, index MaxPos, index min, index max, fNode* start)
	{
		if (!start)
		{
			return NUTURAL;
		}
		else if (MaxPos == max && MinPos == min)
		{
			return start->val;
		}
		else
		{
			index middle = (min + max) / 2;
			if (MaxPos <= middle)
			{
				return rangeValF(MinPos, MaxPos, min, middle, start->children[0]);
			}
			else if (MinPos >= middle)
			{
				return rangeValF(MinPos, MaxPos, middle, max, start->children[1]);
			}
			else
			{
				return combine(
					rangeValF(MinPos, middle, min, middle, start->children[0]),
					rangeValF(middle, MaxPos, middle, max, start->children[1]));
			}
		}
	}
}

#if 0 // cheek
#include <iostream>
using namespace fenwickFindRangeChangeOne;
int main()
{
	fNode* myTree = new fNode;
#define treeInfo 0, 16, myTree //min, max start
	std::cout << rangeValF(2, 5, treeInfo) << std::endl;//0
	updateF(3, 4, treeInfo);
	updateF(5, 7, treeInfo);
	std::cout << rangeValF(2, 3, treeInfo) << std::endl;//0
	std::cout << rangeValF(2, 5, treeInfo) << std::endl;//4
	std::cout << rangeValF(3, 5, treeInfo) << std::endl;//4
	std::cout << rangeValF(3, 6, treeInfo) << std::endl;//11
	system("pause");
	return 0;
	}
#endif