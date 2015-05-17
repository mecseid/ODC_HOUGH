#ifndef LINEINTERSECT_H_
#define LINEINTERSECT_H_

#include "includes.h"
#include <limits>

/*
 * Vonalmetszet meghatározása
 *
 * P1(x1,y1)
 * P2(x2,y2)
 * P3(x3,y3)
 * P4(x4,y4)
 * (x-x1)*(y2-y1) = (x2-x1)*(y-y1)
 * (x-x3)*(y4-y3) = (x4-x3)*(y-y3)
 *
 */
position LinesIntersect(position one, position two, position three, position four)
{
	position res;
	if ((two.x - one.x) * (four.y - three.y) - (four.x - three.x) * (two.y - one.y) != 0)
	{
		res.y = ((three.x - one.x) * (two.y - one.y) * (four.y - three.y) + one.y * (two.x - one.x) * (four.y - three.y)
				- three.y * (four.x - three.x) * (two.y - one.y))
				/ ((two.x - one.x) * (four.y - three.y) - (four.x - three.x) * (two.y - one.y));
		if ((two.y - one.y) != 0)
		{
			res.x = ((two.x - one.x) * (res.y - one.y) + one.x * (two.y - one.y)) / (two.y - one.y);
		}
		else
		{
			res.x = ((four.x - three.x) * (res.y - three.y) + three.x * (four.y - three.y)) / (four.y - three.y);
		}
	}
	else
	{
		res.x = std::numeric_limits<int>::infinity();
		res.y = std::numeric_limits<int>::infinity();
	}
	return res;
}

#endif
