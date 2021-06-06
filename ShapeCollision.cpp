#include "ShapeCollision.h"

bool ShapeCollision::isInside(const Shape& shape, wxPoint& mouse, bool on_display)
{
	int n;
	if (shape.type < Type::QUADRANGLE4)
		n = 3;
	else
		n = 4;

	wxPoint border;
	if (on_display)
		border = wxPoint(800, mouse.y);
	else
		border = wxPoint(1280, mouse.y);

	const wxPoint* polygon = shape.GetPoints();

	int count = 0;
	int i = 0;

	do
	{
		int next = (i + 1) % n;

		if (Intersect(polygon[i], polygon[next], mouse, border))
		{
			if (Orientation(polygon[i], mouse, polygon[next]) == 0)
				return Segment(polygon[i], mouse, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	return (count % 2 == 1);
}

bool ShapeCollision::ShapeOverlap(Shape& shape1, Shape& shape2)
{
	Shape* poly1 = &shape1;
	Shape* poly2 = &shape2;

	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = &shape2;
			poly2 = &shape1;
		}

		int n1 = (poly1->type < Type::QUADRANGLE4) ? 3 : 4;
		int n2 = (poly2->type < Type::QUADRANGLE4) ? 3 : 4;

		auto points1 = poly1->GetPoints();
		auto points2 = poly2->GetPoints();

		for (int a = 0; a < n1; a++)
		{
			int b = (a + 1) % n1;
			wxPoint axisProjection = wxPoint(-(points1[b].y - points1[a].y), points1[b].x - points1[a].x);

			double min1, max1;
			for (int i = 0; i < n1; i++)
			{
				double q = points1[i].x * static_cast<double>(axisProjection.x) + points1[i].y * static_cast<double>(axisProjection.y);

				if (i)
				{
					min1 = std::min(min1, q);
					max1 = std::max(max1, q);
				}
				else
				{
					min1 = q;
					max1 = q;
				}
			}

			double min2, max2;
			for (int i = 0; i < n2; i++)
			{
				double q = points2[i].x * static_cast<double>(axisProjection.x) + points2[i].y * static_cast<double>(axisProjection.y);

				if (i)
				{
					min2 = std::min(min2, q);
					max2 = std::max(max2, q);
				}
				else
				{
					min2 = q;
					max2 = q;
				}
			}

			if (!(max2 > min1 && max1 > min2))
				return false;
		}

	}

	return true;
}

bool ShapeCollision::Intersect(const wxPoint& p1, const wxPoint& q1, const wxPoint& p2, const wxPoint& q2)
{
	int o1 = Orientation(p1, q1, p2);
	int o2 = Orientation(p1, q1, q2);
	int o3 = Orientation(p2, q2, p1);
	int o4 = Orientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4)
		return true;

	if (o1 == 0 && Segment(p1, p2, q1))
		return true;

	if (o2 == 0 && Segment(p1, q2, q1))
		return true;

	if (o3 == 0 && Segment(p2, p1, q2))
		return true;

	if (o4 == 0 && Segment(p2, q1, q2))
		return true;

	return false;
}

int ShapeCollision::Orientation(const wxPoint& p, const wxPoint& q, const wxPoint& r)
{
	int a = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (a > 0)
		return 1;
	else if (a < 0)
		return 2;
	else
		return 0;
}

bool ShapeCollision::Segment(const wxPoint& p, const wxPoint& q, const wxPoint& r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;
	return false;
}

