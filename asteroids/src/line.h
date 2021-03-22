#pragma once
#include "shape.h"
class line : public shape, MI5_DERIVE(line, shape) {
	MI5_INJECT(line);
	using base = shape;
public:
	 line(const wxRect& box, const wxPen& pen, const wxBrush& brush) :base(box, pen, brush) {

	}
	 using context_t = ml5::paint_event::context_t;

	 void do_draw(context_t& context) const override {
		 context.DrawLine(m_box.GetTopLeft(), m_box.GetBottomRight());
	 }
};