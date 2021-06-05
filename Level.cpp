#include "Level.h"

void Level::SetLevel(std::string filename1, std::string filename2)
{
	polygon.clear();
	check.clear();
	check_copy.clear();
	int x1, y1, x2, y2;
	std::ifstream in;
	in.open(filename1);

	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> x1 >> y1 >> x2 >> y2;
			polygon.push_back(wxPoint(x1, y1));
			polygon.push_back(wxPoint(x2, y2));
		}
	}
	in.close();

	int type = -1;
	in.open(filename2);
	if (in.is_open())
	{
		std::vector<wxPoint> points;
		while (!in.eof())
		{
			int prev = type;
			in >> x1 >> y1 >> type;
			if (prev != type && prev != -1)
			{
				check.push_back(Poly(points, Type(prev)));
				check_copy.push_back(Poly(points, Type(prev)));
				points.clear();
			}
			
			points.push_back(wxPoint(x1, y1));
		}
		check.push_back(Poly(points, Type(type)));
		check_copy.push_back(Poly(points, Type(type)));
	}
	in.close();
}

void Level::Draw(wxAutoBufferedPaintDC& panel)
{
	panel.SetPen(wxColor("black"));
	panel.SetBrush(wxColor("black"));
	panel.DrawPolygon(polygon.size(), polygon.data());

	//panel.SetPen(wxColor("black"));
	//panel.SetBrush(wxColor("grey"));
	//for (auto& poly : check_copy)
	//{
	//	if (poly.type > Type(3))
	//		panel.DrawPolygon(4, poly.points.data());
	//	else
	//		panel.DrawPolygon(3, poly.points.data());
	//}
}

bool Level::CheckLevel(const std::vector<std::unique_ptr<Shape>>& shapes)
{
	wxPoint min = wxPoint(-1, -1);
	bool correct = true;
	for (auto& shape : shapes)
	{
		auto points = shape->GetPoints();
		int n = (shape->type < Type::QUADRANGLE4) ? 3 : 4;
		for (int i = 0; i < n; i++)
		{
			if (min.x == -1)
			{
				min.x = points[i].x;
				min.y = points[i].y;
			}
			else
			{
				if (points[i].x < min.x)
				{
					min.x = points[i].x;
					min.y = points[i].y;
				}
				else if (points[i].x == min.x)
				{
					if (points[i].y < min.y)
					{
						min.x = points[i].x;
						min.y = points[i].y;
					}
				}
			}
		}
	}

	for (auto& poly : check_copy)
	{
		for (auto& point : poly.points)
		{
			point.x += min.x;
			point.y += min.y;
		}

		int n = (poly.type < Type(4)) ? 3 : 4;
		if (poly.type < Type(3))
		{
			wxPoint* points1 = nullptr;
			wxPoint* points2 = nullptr;
			for (auto& shape : shapes)
			{
				if (shape->type == poly.type)
				{
					if (points1 == nullptr)
					{
						points1 = shape->GetPoints();
					}
					else
					{
						points2 = shape->GetPoints();
						break;
					}
				}
			}
			
			bool found1 = true;
			for (int i = 0; i < n; i++)
			{
				bool found = false;
				for (auto& point : poly.points)
				{
					if (points1 && abs(points1[i].x - point.x) <= 23 && abs(points1[i].y - point.y) <= 23)
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					found1 = false;
					break;
				}
			}

			if (!found1)
			{
				for (int i = 0; i < n; i++)
				{
					bool found = false;
					for (auto& point : poly.points)
					{
						if (points2 && abs(points2[i].x - point.x) <= 23 && abs(points2[i].y - point.y) <= 23)
						{
							found = true;
							break;
						}
					}
					if (!found)
					{
						check_copy = check;
						return false;
					}
				}
			}
		}
		else
		{
			wxPoint* points = nullptr;
			for (auto& shape : shapes)
			{
				if (shape->type == poly.type)
				{
					points = shape->GetPoints();
					break;
				}
			}

			for (int i = 0; i < n; i++)
			{
				bool found = false;
				for (auto& point : poly.points)
				{
					if (points && abs(points[i].x - point.x) <= 23 && abs(points[i].y - point.y) <= 23)
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					check_copy = check;
					return false;
				}
			}
		}
		
	}

	check_copy = check;

	return true;
}