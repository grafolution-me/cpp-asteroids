#include "asteroid.h"
#include "utils.h"
void asteroids::asteroid::move_forward()
{
	m_position.x += sin(utils::degree_rad(m_rotation)) * m_speed;
	m_position.y += -cos(utils::degree_rad(m_rotation)) * m_speed;
	//draw_window::get_size;
	if (!utils::is_point_valid(m_position)) {
		//move point to valid position
		utils::is_point_valid_x(m_position);
		utils::is_point_valid_y(m_position);
	}
}