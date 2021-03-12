#pragma once
#include "shape.h"
class triangle : public shape, MI5_DERIVE(triangle, shape) {
	MI5_INJECT(triangle);
public:
	using base = shape;
	triangle(const wxRect& box, const std::array<wxRealPoint, 3> points, wxPoint middle, const wxPen& pen, const wxBrush& brush) :base(box, points, middle, pen, brush) {

	}

protected:
	using context_t = ml5::paint_event::context_t;

	void do_draw(context_t& context) const override {	
		std::vector<wxPoint> points{};
		points.insert(points.begin(), std::begin(m_points), std::end(m_points));
		context.DrawPolygon(m_points.size(), points.data());
	}
};