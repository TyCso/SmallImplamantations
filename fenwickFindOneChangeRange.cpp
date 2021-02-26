

namespace fenwickFindOneChangeRange
{

#define fr(i, n) for(int i = 0; i < n;i++)


#define NUTURAL -1
	typedef int info;
	typedef int index;
	info combine(info a, info b)//shuld be assusiative
	{
		return (b + 1) ? b : a;//in this exapmle: combine = last update
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
	info valF(index pos, index min, index max, fNode* start)
	{
		if (1 == max - min || !start)
		{
			return valueOf(start);
		}
		else
		{
			index middle = (min + max) / 2;
			int childPlace = ((pos >= middle) ? 1 : 0);
			return combine(valF(pos,
				(childPlace) ? middle : min,//min
				(childPlace) ? max : middle,//max
				start->children[childPlace]),//start
				start->val);
		}
	}

	//update from right f(prevRange, newVal); start is not null
	void rangeUpdateF(index MinPos, index MaxPos, info val, index min, index max, fNode* start)
	{
		if (MaxPos == max && MinPos == min)
		{
			start->val = combine(start->val, val);
		}
		else
		{
			//let other carry curr val
			{
				fr(i, 2)
				{
					if (!start->children[i])
					{
						start->children[i] = new fNode;
					}
					start->children[i]->val = combine(start->children[i]->val, start->val);
				}
				start->val = NUTURAL;
			}

			//propagate forward
			{
				index middle = (min + max) / 2;
				if (MaxPos <= middle)
				{
					rangeUpdateF(MinPos, MaxPos, val, min, middle, start->children[0]);
				}
				else if (MinPos >= middle)
				{
					rangeUpdateF(MinPos, MaxPos, val, middle, max, start->children[1]);
				}
				else
				{
					rangeUpdateF(MinPos, middle, val, min, middle, start->children[0]);
					rangeUpdateF(middle, MaxPos, val, middle, max, start->children[1]);
				}
			}
		}
	}
}

#if 0
using namespace fenwickFindOneChangeRange;
#include <iostream>
int main()
{
	fNode* myTree = new fNode;
#define treeInfo 0, 16, myTree //min, max start
	std::cout << valF(2, treeInfo) << std::endl;//-1 = not an info
	rangeUpdateF(3, 7, 1, treeInfo);
	rangeUpdateF(2, 4, 2, treeInfo);
	rangeUpdateF(0, 1, 3, treeInfo);
	rangeUpdateF(7, 8, 4, treeInfo);

	fr(i, 16)
	{
		std::cout << valF(i, treeInfo) << " ";//all val
	}
	//3 -1 2 2 1 1 1 4 -1 .... -1
	std::cout << std::endl;
	system("pause");
	return 0;
}
#endif