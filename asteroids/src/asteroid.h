
#pragma once

#include <ml5/ml5.h>
#include "shape.h"
#include "asteroid_size.h"
#include "utils.h"
#define MIN_SPEED 0.2
#define PROJECTILE_SIZE 3
namespace asteroids {

	class asteroid : public shape {

	protected:
		
		using base = shape;
	public:
		asteroid(const wxRect& box, const wxPen& pen, const wxBrush& brush, int speed, wxRealPoint pos, asteroid_size size, wxSize window_size, int rotation) :
			base(box, pen, brush, window_size),
			m_speed{ speed },
			m_position{ pos },
			m_size{size},
			m_rotation{rotation}
		{
		}
		asteroid( const wxPen& pen, const wxBrush& brush, wxSize window_size, int speed, wxRealPoint pos, 
			asteroid_size size, int rotation) :
			base( pen, brush, window_size),

			m_speed{ speed },
			m_position{ pos },
			m_size{ size },
			m_rotation{ rotation }
		{
		}
		auto asteroid_size() const {
			return m_size;
		}

		auto region() const -> wxRegion {
			wxCoord radius = (int)m_size;
			wxCoord width = radius * 2;
			wxCoord x = m_position.x - radius;
			wxCoord y = m_position.y - radius;
			return wxRegion{ x, y, width, width };
		}

		void do_draw(context_t& context) const override {
			context.DrawCircle(m_position, (wxCoord)m_size);
		}
		
		bool has_collision(const wxRealPoint& position) {
			wxRegion combined_region = region();
			combined_region.Intersect(position.x, position.y, PROJECTILE_SIZE, PROJECTILE_SIZE);
			return !combined_region.IsEmpty();
		}

		void move(const int f) override {
			/*m_position.x += -cos(utils::degree_rad(get_rotation()));
			m_position.y += -sin(utils::degree_rad(get_rotation()));*/
		}
		void move_forward() override {
			m_position.x += sin(utils::degree_rad(m_rotation)) * m_speed;
			m_position.y += -cos(utils::degree_rad(m_rotation)) * m_speed;
			if (!is_point_valid(m_position)) {
				is_point_valid_x(m_position);
				is_point_valid_y(m_position);
			}
		}
	private:
		asteroids::asteroid_size 
		m_size{asteroid_size::smallest};
		int m_speed{ 0 };
		wxRealPoint m_position{ 0, 0 };
		int m_rotation{0};
	};
}