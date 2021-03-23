#pragma once

#include "shape.h"
#include <ml5/ml5.h>
#include "constants.h"
#include "utils.h"
namespace asteroids {

	class projectile : public shape {

	protected:
		using base = shape;
	public:
		 projectile( const wxPen& pen, const wxBrush& brush, int speed, wxRealPoint pos, double rotation)
			: base{pen, brush},
				m_speed{speed},
				m_position{pos},
				m_rotation{rotation}
			 {}
		 projectile(const projectile& p)
			: base{ p.m_pen, p.m_brush },
			m_speed{ p.m_speed },
			m_position{ p.m_position },
			m_rotation{ p.m_rotation }
		{}
		 ~projectile() = default;
		void do_draw(context_t& context) const override {
			context.DrawCircle(m_position, SIZE_PROJECTILE);
		}
		void move_forward() override {
			m_position.x += sin(utils::degree_rad(m_rotation)) * m_speed;
			m_position.y += -cos(utils::degree_rad(m_rotation)) * m_speed;
		}
		wxRealPoint get_position() {
			return m_position;
		}

		auto region() const {
			wxCoord radius = (int)SIZE_PROJECTILE;
			wxCoord width = radius * 2;
			wxCoord x = m_position.x - radius;
			wxCoord y = m_position.y - radius;
			return wxRegion{ x, y, width, width };
		}

	private:
		wxRealPoint m_position{};
		int m_speed{ 1 };
		double m_rotation;
	};
}