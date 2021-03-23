#pragma once
#include <ml5/ml5.h>
#include <vector>
#include "game_engine.h"
class shape :public ml5::object, MI5_DERIVE(shape, ml5::object) {
	MI5_INJECT(shape);
protected:
	using context_t = ml5::paint_event::context_t;
public:

	
	explicit shape(const wxRect& box, const wxPen& pen, const wxBrush& brush) :
		m_brush{ brush },
		m_pen{ pen },
		m_box{ box },
		m_window_size{ game_engine::getInstance().get_window_size() }
	{
	}
	explicit shape( const wxPen& pen, const wxBrush& brush) :
		m_pen{ pen },
		m_brush{ brush},
		m_window_size{ game_engine::getInstance().get_window_size() }
	{
	}
	void draw(context_t& context) const {
		context.SetBrush(m_brush);
		context.SetPen(m_pen);
		do_draw(context);
	}
	
	virtual void move_forward()= 0;
protected:
	wxBrush m_brush{};
	wxPen m_pen{};
	wxRect m_box{};

protected:
	

	virtual void do_draw(context_t& context) const = 0;
	wxSize get_window_size() {
		return m_window_size;
	}

	/*bool is_point_valid(wxRealPoint& point) {
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
	}*/
	
private:
	wxSize m_window_size;

};