#include "ship.h"
#include "utils.h"

void ship::move_forward()

{
	for (wxRealPoint& point : m_points) {
		point.x += sin(utils::degree_rad(get_rotation())) * m_speed;
		point.y += -cos(utils::degree_rad(get_rotation())) * m_speed;
	}
	if (!is_valid_position(std::vector<wxRealPoint>{
		std::begin(m_points), std::end(m_points)
	})) {
		for (wxRealPoint& point : m_points) {
			check_position(point);
		}
	}
}
