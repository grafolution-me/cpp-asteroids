#pragma once
#include <ml5/ml5.h>
#include <vector>
#include <ml5/container/vector.h>
#include <vector>
class shape :public ml5::object, MI5_DERIVE(shape, ml5::object) {
	MI5_INJECT(shape);
protected:
	using context_t = ml5::paint_event::context_t;
public:

	explicit shape(const wxRect& box, const wxPen& pen, const wxBrush& brush) :
		m_brush{ brush },
		m_pen{ pen },
		m_box{ box } {
	}
	explicit shape(const wxRect& box, const	std::array<wxPoint, 3> m_points, wxPoint middle, const wxPen& pen, const wxBrush& brush) :
		m_brush{ brush },
		m_pen{ pen },
		m_box{ box },
		m_points{ m_points },
		m_middle{ middle }
	{
	}

	void draw(context_t& context) const {
		context.SetBrush(m_brush);
		context.SetPen(m_pen);
		do_draw(context);
	}
	wxPoint& rotate(wxRealPoint p, double Cx, double Cy, int angle) {
		double	Rx = (Cx * cos(angle * (M_PI / 180)) - (Cy * sin(angle * (M_PI / 180))));
		double	Ry = (Cx * sin(angle * (M_PI / 180)) + (Cy * cos(angle * (M_PI / 180))));

		wxPoint  p_return(std::round(Rx) + p.x, std::round(Ry) + p.y) ;
		return p_return;
	}
	void move(const int offset) {

		double center_x = 0;
		double center_y = 0;
		for (size_t i = 0; i < m_points.size(); i++)
		{
			center_x += m_points[i].x;
			center_y += m_points[i].y;

		}
		wxRealPoint center{ center_x / 3, center_y / 3 };
		for (size_t i = 0; i < m_points.size(); i++)
		{
			wxRealPoint position = m_points[i];
			m_points[i] = rotate(center, position.x - center.x, position.y - center.y, offset);
		}
	/*	wxPoint p_bottom_left = m_box.GetBottomLeft();
		wxPoint p_bottom_right = m_box.GetBottomRight();
		wxPoint p_top_left = m_box.GetTopLeft();
		wxPoint p_top_right = m_box.GetTopRight();
		ml5::vector<wxPoint> v_points{};
		v_points.add(p_bottom_left);
		v_points.add(p_bottom_right);
		v_points.add(p_top_left);
		v_points.add(p_top_right);
		center_x = 0;
		center_y = 0;
		for (wxPoint point : v_points)
		{
			center_x += point.x;
			center_y += point.y;
		}
		wxPoint center_box{ center_x / 4, center_y / 4 };
		m_box.SetBottomLeft(rotate(center, p_bottom_left.x - center_box.x, p_bottom_left.y - center_box.y, offset));
		m_box.SetBottomRight(rotate(center, p_bottom_right.x - center_box.x, p_bottom_right.y - center_box.y, offset));
		m_box.SetTopLeft(rotate(center, p_top_left.x - center_box.x, p_top_left.y - center_box.y, offset));
		m_box.SetTopRight(rotate(center, p_top_right.x - center_box.x, p_top_right.y - center_box.y, offset));
		*/
	}
	void move_x(const int offset) {
		//for (size_t i = 0; i < m_points.size(); i++)
		//{
		//	wxPoint position = m_points[i]-x + offset;
		//	
		//}

	}
	int get_left() {
		return m_box.GetLeft();
	}
	int  get_right() {
		return m_box.GetRight();
	}
	int  get_top() {
		return m_box.GetTop();
	}
	int  get_bottom() {
		return m_box.GetBottom();
	}



protected:
	wxBrush m_brush{};
	wxPen m_pen{};
	wxRect m_box{};
	std::array<wxPoint, 3> m_points{};
	wxPoint m_middle{};
	virtual void do_draw(context_t& context) const = 0;
};