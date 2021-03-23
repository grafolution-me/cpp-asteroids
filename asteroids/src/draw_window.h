#pragma once

#include <ml5/ml5.h>
#include <iostream>
#include "shape.h"
#include "line.h"
#include "ship.h"
#include "ellipse.h"
#include "random.h"
#include "asteroid.h"
#include "constants.h"
#include "game_engine.h"
#include "projectile.h"

class draw_window : public ml5::window, MI5_DERIVE(draw_window, ml5::window){
	MI5_INJECT(draw_window)
		enum key_mapping { left = 314, up = 315, right = 316,  down = 317, w = 119, a  = 97, s = 115, d = 100, space = 32};

public:

	draw_window() : ml5::window("Asteroids") {
		set_prop_allow_resize(false);
		set_prop_initial_size(game_engine::getInstance().get_window_size());
	}
	
	void on_init() override {
		this->set_prop_background_brush(wxBrush{ *wxBLACK_BRUSH }); 
		start_timer(std::chrono::milliseconds{ TIMER_INTERVAL });
		wxPoint point_top_left{ (draw_window::get_width() / 2) - SHIP_SIZE / 2, (draw_window::get_height() / 2) - SHIP_SIZE };
		wxPoint point_top{ (draw_window::get_width() / 2), (draw_window::get_height() / 2) - SHIP_SIZE };
		wxPoint point_bottom_left{ (draw_window::get_width() / 2) - SHIP_SIZE / 2, (draw_window::get_height() / 2) + SHIP_SIZE };
		wxPoint point_bottom_right{ (draw_window::get_width() / 2) + SHIP_SIZE / 2, (draw_window::get_height() / 2) + SHIP_SIZE };
		std::array<wxRealPoint, 3> points{ point_top, point_bottom_right, point_bottom_left };
		m_p_player = std::make_unique<ship>(
			points, 
			m_pen, m_brush, 
			0 // speed
		);
		utils::create([&] {
			asteroids::random r{};
			m_asteroids.push_back(
				std::make_shared<asteroids::asteroid>(
					m_pen,
					*wxGREY_BRUSH,					//window_size, for positioning needed
					r.get_random_number(1, 3),		// speed
					utils::random_window_pos_edge(),//position of astroid in window (edges)
					utils::get_asteroid_size(),		//astroid size
					r.get_random_number(0, 360)		//degree 
					)
				);
			}, asteroids::random{}.get_random_number(12,16));
	}

	virtual void on_key(ml5::key_event const& event) {
		int key_code = event.get_key_code();
		switch (key_code) {
		case key_mapping::left:
		case key_mapping::a:
			if (m_p_player)  m_p_player->move(-30);
			break;
		case key_mapping::right:
		case key_mapping::d:
			if (m_p_player)  m_p_player->move(30);
			break;
		case key_mapping::down:
		case key_mapping::s:
			if (m_p_player) {
					m_p_player->deaccelerate();
			}
			break;
		case key_mapping::up:
		case key_mapping::w:
			if (m_p_player) { 
				m_p_player->accelerate();
			};
			break;
		case key_mapping::space:
			if (m_p_player) {
				m_projectiles.push_back(
					std::make_shared<projectile>(
							m_p_player->shoot()
						)
					);
				
			};
			break;
		}
		refresh();
	}



	void on_timer(const ml5::timer_event& event) override {
		static int counter = 0;
		if (m_p_player->get_speed() > 0) {
			m_p_player->move_forward();
			if (counter >= 36 ) {
				m_p_player->deaccelerate();
				counter = 0;
			}
		}
		
		for (const auto& asteroid : m_asteroids) {
			asteroid->move_forward();
		}
		for (const auto& projectile : m_projectiles)
		{
			if (projectile) {
				if (utils::is_point_valid(projectile->get_position())) {
					projectile->move_forward();
				}
				else {
					m_projectiles.remove(projectile);
					break;
				}
			}
			
		} 
		collision_detection();
		refresh();
		counter++;
	}

private:
	ml5::vector<std::unique_ptr<shape>> m_p_astroids{};
	std::unique_ptr<ship> m_p_player{ nullptr };
	wxBrush	m_brush{ *wxBLUE_BRUSH };
	wxPen m_pen{ *wxWHITE_PEN };
	std::list<std::shared_ptr<asteroid>> m_asteroids{};
	std::list< std::shared_ptr<projectile>> m_projectiles{};
	int points{ 0 };
private:
	
	void collision_spaceship() {
		for (const auto& asteroid : m_asteroids) {
			if (m_p_player->collision(asteroid->region())) {
				statistics_print();
				utils::play_wasted_sound();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				exit(0);
				break;
			}
		}
	}
	void collision_projectile() {

		bool destroyed = false;
		for (const auto& projectile : m_projectiles) {
			for (const auto& a : m_asteroids) {
				if (a->collision(projectile->region())) {
					destroyed = true;
					m_projectiles.remove(projectile);
					random r{};
					utils::create([&] {
						if (a->get_size() != asteroids::asteroid_size::smallest) {
							m_asteroids.push_back(
								std::make_shared<asteroids::asteroid>(
									a->create_new_astroid_from_current()
									)
							);
						}
						}, r.get_random_number(2, 4));
					statistics();
					m_asteroids.remove(a);
					break;
				}
			}
			if (destroyed) {
				destroyed = false;
				break;
			}
		}
	}
	void statistics() {
		points++;
	}
	void statistics_print() {
		std::cout << "You archieved a score of: ";
		std::cout << points;
		std::cout << " Points" << std::endl;
	}

	void collision_detection() {
		collision_projectile();
		collision_spaceship();
	}

	void on_paint(ml5::paint_event const& event)override {
		if (m_p_player) {
			m_p_player->draw(event.get_context());
		}
		for (const auto& asteroid : m_asteroids) {
			asteroid->draw(event.get_context());
		}
		for (const auto& projectile : m_projectiles) {
			projectile->draw(event.get_context());
		}

	}
};