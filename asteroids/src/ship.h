#pragma once
#include "shape.h"
#include "utils.h"
#include "constants.h"
#include "projectile.h"
#include <vector>
class ship : public shape, MI5_DERIVE(ship, shape) {
	MI5_INJECT(ship);
public:
	using base = shape;

	ship(const wxRect& box, const std::array<wxRealPoint, 3> points, const wxPen& pen, const wxBrush& brush) : 
		 base(box, pen, brush), 
		m_points{points}
	{}
	ship(const std::array<wxRealPoint, 3> points, const wxPen& pen, const wxBrush& brush, int speed) :
		base(pen, brush),
		m_points{ points },
		m_speed{ speed }{
		
	}

	void move(const int offset){
		wxRealPoint center = utils::get_center(std::vector<wxRealPoint>{ std::begin(m_points), std::end(m_points) });
		for (size_t i = 0; i < m_points.size(); i++)
		{
			wxRealPoint position = m_points[i];
			m_points[i] = rotate(center, position.x - center.x, position.y - center.y, offset);
		}
		set_rotation(offset);
	}
	void move_forward() override;
	void check_position(wxRealPoint& point) {
		utils::is_point_valid_x(point);
		utils::is_point_valid_y(point);
	}
	bool is_valid_position(std::vector<wxRealPoint> v) {
		for (wxRealPoint& point : v) {
			if (utils::is_point_valid(point)) {
				return true;
			}
		}
		return false;
		
	}

	bool collision(wxRegion other_region) {
		wxRealPoint center = utils::get_center(std::vector<wxRealPoint>{ std::begin(m_points), std::end(m_points) });
		wxRegion current_region{ (wxCoord)center.x- (SHIP_SIZE / 2), (wxCoord)center.y - (SHIP_SIZE/2), SHIP_SIZE,  SHIP_SIZE};
		other_region.Intersect(current_region);
		return !other_region.IsEmpty();
	}
	void accelerate() {
		if (m_speed <= 3) {
			m_speed++;
		}
	}

	void deaccelerate() {
		if (m_speed >= 0) {
			m_speed--;
		}
	}
	void stop() {
		m_speed=0;
	}
	projectile shoot() {
		utils::play_shoot_sound();
		return projectile { this->m_pen, *wxRED_BRUSH, this->get_speed() + 3 ,
						   this->get_position(), (double)this->get_rotation() };
		
 	}
	int get_speed() {
		return m_speed;
	}
	double get_rotation() {
		return rotation;
	}
	wxRealPoint get_position() {
		return utils::get_center(std::vector<wxRealPoint>{ std::begin(m_points), std::end(m_points) });
	}
protected:
	using context_t = ml5::paint_event::context_t;

	void do_draw(context_t& context) const override {	
		std::vector<wxPoint> points{};
		points.insert(points.begin(), std::begin(m_points), std::end(m_points));
		context.DrawPolygon(m_points.size(), points.data());
	}
	
private:
	

	
	inline void set_rotation(const int offset) {
		rotation += offset;
	}
	inline wxRealPoint rotate(wxRealPoint p, double Cx, double Cy, int angle) {
		double	Rx = (Cx * cos(utils::degree_rad(angle)) - (Cy * sin(utils::degree_rad(angle))));
		double	Ry = (Cx * sin(utils::degree_rad(angle)) + (Cy * cos(utils::degree_rad(angle))));
		return wxRealPoint(std::round(Rx) + p.x, std::round(Ry) + p.y);
	};
	int rotation{0};
	int m_speed;
	std::array<wxRealPoint, 3> m_points{};
};