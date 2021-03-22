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
		m_box{ box }
	{
	}	
	explicit shape(const wxRect& box, const wxPen& pen, const wxBrush& brush, wxSize size) :
		m_brush{ brush },
		m_pen{ pen },
		m_box{ box },
		m_window_size{ size }
	{
	}
	explicit shape( const wxPen& pen, const wxBrush& brush, wxSize size) :
		m_pen{ pen },
		m_brush{ brush},
		m_window_size{ size }
	{
	}
	explicit shape(const wxRect& box, const	std::array<wxRealPoint, 3> m_points, const wxPen& pen, const wxBrush& brush, wxSize size) :
		m_brush{ brush },
		m_pen{ pen },
		m_box{ box },
		m_points{ m_points },
		m_window_size{ size }
	{
	}
	explicit shape( const std::array<wxRealPoint, 3> m_points, const wxPen& pen, const wxBrush& brush, wxSize size) :
		m_brush{ brush },
		m_pen{ pen },
		m_points{ m_points },
		m_window_size{ size }
	{
	}
	

	void draw(context_t& context) const {
		context.SetBrush(m_brush);
		context.SetPen(m_pen);
		do_draw(context);
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
	
	virtual void move_forward()= 0;
	virtual void move(const int offset) = 0;
protected:
	void set_rotation(const int offset) {
		rotation += offset;
	}
	wxBrush m_brush{};
	wxPen m_pen{};
	wxRect m_box{};
	std::array<wxRealPoint, 3> m_points{};
	virtual void do_draw(context_t& context) const = 0;
	wxSize get_window_size() {
		return m_window_size;
	}

	bool is_point_valid(wxRealPoint& point) {
		if ((point.x >= 0 && point.x <= this->get_window_size().x) &&
			(point.y >= 0 && point.y <= this->get_window_size().y)) {
			return true;
		}
		else return false;

	}
	void is_point_valid_x(wxRealPoint& point) {
		if (point.x <= 0) {
			point.x = point.x + get_window_size().x;
		}
		else {
			point.x = (int)point.x % get_window_size().x;
		}

	}
	void is_point_valid_y(wxRealPoint& point) {
		if (point.y <= 0) {
			point.y = point.y + get_window_size().y;
		}
		else {
			point.y = (int)point.y % get_window_size().y;
		}
	}
	
private:
	int rotation;
	wxSize m_window_size;

};