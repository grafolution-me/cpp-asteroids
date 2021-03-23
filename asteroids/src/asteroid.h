
#pragma once

#include <ml5/ml5.h>
#include "shape.h"
#include "asteroid_size.h"
#include "utils.h"
#include "constants.h"

namespace asteroids {

	class asteroid : public shape {

	protected:
		
		using base = shape;
	public:
		asteroid(const wxRect& box, const wxPen& pen, const wxBrush& brush, int speed, wxRealPoint pos, asteroid_size size, int rotation) :
			base(box, pen, brush),
			m_speed{ speed },
			m_position{ pos },
			m_size{size},
			m_rotation{rotation}
		{
		}
		asteroid( const wxPen& pen, const wxBrush& brush, int speed, wxRealPoint pos, 
			asteroid_size size, int rotation) :
			base( pen, brush),

			m_speed{ speed },
			m_position{ pos },
			m_size{ size },
			m_rotation{ rotation }
		{
		}
		asteroid(const asteroid& a) :
			base(a.m_pen, a.m_brush),
			m_speed{ a.m_speed },
			m_position{ a.m_position },
			m_size{ a.m_size },
			m_rotation{ a.m_rotation }
		{
		}
		auto asteroid_size() const {
			return m_size;
		}

		auto region() const {
			wxCoord r = (int)m_size;
			wxCoord width = r * 2;


			wxCoord y = m_position.y - r;
			wxCoord x = m_position.x - r;
			
			return wxRegion{ x, y, width, width };
		}

		void do_draw(context_t& context) const override {
			context.DrawCircle(m_position, (wxCoord)m_size);
		}
		
		bool collision(wxRegion their_region) {
			wxRegion this_region{ (wxCoord)m_position.x - ((int)m_size / 2), (wxCoord)m_position.y - ((int)m_size / 2), (int)m_size,  (int)m_size };
			their_region.Intersect(this_region);
			return !their_region.IsEmpty();
		}
		void move_forward() override;
		asteroid create_new_astroid_from_current() {
			random r{};
			if (m_size != asteroid_size::smallest) {
				if (m_size == asteroid_size::medium) {
					return asteroid{ this->m_pen, this->m_brush, r.get_random_number(1,3),  this->m_position,
									 asteroid_size::smallest, r.get_random_number(0, 360) };
				}
				if (m_size == asteroid_size::large) {
					return asteroid{ this->m_pen, this->m_brush, r.get_random_number(1,3),  this->m_position,
									 asteroid_size::medium, r.get_random_number(0, 360) };
				}
				if (m_size == asteroid_size::xlarge) {
					return asteroid{ this->m_pen, this->m_brush, r.get_random_number(1,3),  this->m_position,
									 asteroid_size::large, r.get_random_number(0, 360) };
				}
			}
			else {
				return *this;
			}
		}
		asteroids::asteroid_size get_size() {
			return m_size;
		}
	private:
		asteroids::asteroid_size m_size{asteroid_size::smallest};
		int m_speed{ 0 };
		wxRealPoint m_position{ 0, 0 };
		int m_rotation{0};
	};
}