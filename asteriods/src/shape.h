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
	explicit shape(const wxRect& box, const	std::array<wxRealPoint, 3> m_points, const wxPen& pen, const wxBrush& brush) :
		m_brush{ brush },
		m_pen{ pen },
		m_box{ box },
		m_points{ m_points }
	{
	}

	void draw(context_t& context) const {
		context.SetBrush(m_brush);
		context.SetPen(m_pen);
		do_draw(context);
	}
	wxRealPoint& rotate(wxRealPoint p, double Cx, double Cy, int angle) {
		double	Rx = (Cx * cos(angle * (M_PI / 180)) - (Cy * sin(angle * (M_PI / 180))));
		double	Ry = (Cx * sin(angle * (M_PI / 180)) + (Cy * cos(angle * (M_PI / 180))));
		wxRealPoint  p_return(std::round(Rx) + p.x, std::round(Ry) + p.y) ;
		return p_return;
	}
	wxRealPoint& get_center_shape(std::vector<wxRealPoint>v) {
		double center_x = 0;
		double center_y = 0;
		for (wxRealPoint point : v)
		{
			center_x += point.x;
			center_y += point.y;
		}
		wxRealPoint center{ center_x / v.size(), center_y / v.size() };
		return center;
	}
	void move(const int offset) {
		wxRealPoint center = get_center_shape(std::vector<wxRealPoint>{ std::begin(m_points), std::end(m_points) });
		for (size_t i = 0; i < m_points.size(); i++)
		{
			wxRealPoint position = m_points[i];
			m_points[i] = rotate(center, position.x - center.x, position.y - center.y, offset);
		}
		set_rotation(offset);
	}
	
	int get_rotation() {
		return rotation;
	}
	void move_x(const int offset) {
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
	void set_rotation(const int offset) {
		rotation += offset;
	}
	wxBrush m_brush{};
	wxPen m_pen{};
	wxRect m_box{};
	std::array<wxRealPoint, 3> m_points{};
	virtual void do_draw(context_t& context) const = 0;
private:
	int rotation;
};