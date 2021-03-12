#pragma once
#include "shape.h"
class triangle : public shape, MI5_DERIVE(triangle, shape) {
	MI5_INJECT(triangle);
public:
	using base = shape;
	triangle(const wxRect& box, const std::array<wxPoint, 3> points, wxPoint middle, const wxPen& pen, const wxBrush& brush) :base(box, points, middle, pen, brush) {

	}

protected:
	using context_t = ml5::paint_event::context_t;

	void do_draw(context_t& context) const override {	
		context.DrawPolygon(m_points.size(), m_points.data());
	}
};