#include <vector>
#include <algorithm>

#include <iostream>

namespace geometry
{

	typedef int info;
#define ZERO 0
	struct point
	{
		info x, y;
		point(info x, info y)
		{
			this->x = x;
			this->y = y;
		}
		point(info x)//using as 1d
		{
			this->x = x;
			this->y = ZERO;
		}
		point()
		{
			this->x = ZERO;
			this->y = ZERO;
		}

		//+-[]
		info& operator[](int index)
		{
			return (index) ? y : x;
		}
		info operator[](int index) const
		{
			return (index) ? y : x;
		}

		point operator+(const point& other) const
		{
			return point(this->x + other.x, this->y + other.y);
		}
		point& operator+=(const point& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		point operator-(const point& other) const
		{
			return point(this->x - other.x, this->y - other.y);
		}
		point operator-() const
		{
			return point(-x, -y);
		}
		point& operator-=(const point& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		//&,*
		info operator&(const point& other) const//vector prudact
		{
			return x * other.y - y * other.x;
		}
		info operator*(const point& other) const//scalar prudact
		{
			return x * other.x + y * other.y;
		}

		//<,>
		bool operator<(const point& other) const//scalar prudact
		{
			return (x < other.x) || (x == other.x && y < other.y);
		}
		bool operator>(const point& other) const//scalar prudact
		{
			return (x > other.x) || (x == other.x && y > other.y);
		}
	} typedef point;

	typedef std::vector<point> poligon;//dir of <-|
	typedef std::pair< poligon, poligon> aboveAndBelow;//aboveBelow - first is lower and second is upper
	typedef int index;


	aboveAndBelow separatePoligon(const poligon& poly)
	{
		index minIndex = 0, maxindex = 0, i = 0;
		poligon blellow;
		poligon above;
		bool doCont = true;
		for (const point& p : poly)
		{
			if (poly[minIndex] > p)
			{
				minIndex = i;
			}
			else if (poly[maxindex] < p)
			{
				maxindex = i;
			}
			i++;
		}
		for (i = minIndex; doCont; i++)
		{
			if (i == poly.size())
			{
				i = 0;
			}
			if (!blellow.empty() && poly[i].x == blellow.back().x)
			{
				blellow.pop_back();
			}
			blellow.push_back(poly[i]);
			doCont = i != maxindex;

		}
		//blellow.push_back(poly[maxindex]);
		doCont = true;
		for (i = minIndex; doCont; i--)
		{
			if (i + 1 == 0)
			{
				i = poly.size() - 1;
			}
			if (!above.empty() && poly[i].x == above.back().x)
			{
				above.pop_back();
			}
			above.push_back(poly[i]);
			doCont = i != maxindex;
		}
		//above.push_back(poly[maxindex]);
		return aboveAndBelow(blellow, above);
	}

	bool isInPoly(/*Convex*/ const aboveAndBelow& poly, const point& p)//O(logN); inc edjes - for not inc change to >= the >
	{
		poligon::const_iterator pit = std::lower_bound(poly.first.begin(), poly.first.begin(), p);
		if (0 > ((p - *pit) & (p - *(pit + 1))))
		{
			return false;
		}
		pit = std::lower_bound(poly.second.begin(), poly.second.begin(), p);
		if (0 < ((p - *pit) & (p - *(pit + 1))))
		{
			return false;
		}
		else
		{
			return true;
		}
	}


	aboveAndBelow convex(const poligon& poly)/*line will be a double line*/
	{
		poligon upper;
		poligon lower;
		point lastU = poly[0];
		point lastL = poly[0];
		for (const point& p : poly)
		{
			while (!upper.empty() && 0 <= ((upper.back() - lastU)&(upper.back() - p)))
			{
				lastU = upper.back();
				upper.pop_back();
			}
			upper.push_back(lastU);
			lastU = p;

			while (!lower.empty() && 0 >= ((lower.back() - lastL)&(lower.back() - p)))
			{
				lastL = lower.back();
				lower.pop_back();
			}
			lower.push_back(lastL);
			lastL = p;
		}
		lower.push_back(lastL);
		upper.push_back(lastU);
		return aboveAndBelow(lower, upper);
	}

	std::ostream& operator<<(std::ostream &s, point p)
	{
		s << p.x << " " << p.y;
		return s;
	}
}


#if 0
using namespace geometry;
int main()
{
	point o;
	const point q(2,5);
	const point p(1);

	//[] cheeck
	std::cout << q[0] << " " << q[1] << " " << (o[0] = 1) << std::endl;
	o[0] = 0;
	//+- cheek
	std::cout << (p + q) << " " << (p - q) << " " << (- q) << " " << ((o+=p)-=q) << std::endl;
	std::cout << (o) << std::endl;

	//*& cheeck
	std::cout << (p * q) << " " << (p & q) << " "<< (q * q) << " " << (q & q) << std::endl;

	std::cout << (p < q) << std::endl;

	poligon poly = { point(1,0), point(1,1), point(0,1), point(-1,1), point(-1,-1) };
	aboveAndBelow plyAAB = separatePoligon(poly);
	std::cout <<isInPoly(plyAAB,point(0,0)) << isInPoly(plyAAB, point(0, -1)) << isInPoly(plyAAB, point(0, 1))<< isInPoly(plyAAB, point(0, 2)) <<std::endl;
	poligon poly2 = { point(-1,-1), point(-1,0), point(-1,1), point(0,-1), point(0,0), point(0,1), point(1,-1), point(1,0), point(1,1) };

	for (point p : convex(poly2).first)
	{
		std::cout << p << std::endl;
	}
	system("pause");
	return 0;
}
#endif