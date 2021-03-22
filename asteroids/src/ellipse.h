#pragma once
#include "shape.h"
class ellipse : public shape, MI5_DERIVE(ellipse, shape) {
	MI5_INJECT(ellipse);
	using context_t = ml5::paint_event::context_t;
public:
	using base = shape;
	 ellipse(const wxRect& box, const wxPen& pen, const wxBrush& brush) :base(box, pen, brush) {

	}
	 void do_draw(context_t& context) const override {
		 context.DrawEllipse(m_box);
	 }
};