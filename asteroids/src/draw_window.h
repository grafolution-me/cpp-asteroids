#pragma once

#include <ml5/ml5.h>
#include <iostream>
#include "shape.h"
#include "rectangle.h"
#include "line.h"
#include "ship.h"
#include "ellipse.h"
#include "random.h"
#include "game_engine.h"
#include "asteroid.h"
#include "constants.h"
class draw_window : public ml5::window, MI5_DERIVE(draw_window, ml5::window){
	MI5_INJECT(draw_window)
		enum key_mapping { left = 314, up = 315, right = 316,  down = 317, w = 119, a  = 97, s = 115, d = 100 };

public:

	draw_window() : ml5::window("Asteroids"), ge{ { 1280, 720 } } {
		set_prop_allow_resize(false);
		set_prop_initial_size({ 1280, 720 });
	}
	//static wxSize get_screen_size() {
	//	return screen_size;
	//}
	void on_mouse_down(ml5::mouse_event const& event)override {
	}
	void on_init() override {
		this->set_prop_background_brush(wxBrush{ *wxBLACK_BRUSH });
		//screen_size = get_size();
		start_timer(std::chrono::milliseconds{ TIMER_INTERVAL });
		wxPoint point_top_left{ (draw_window::get_width() / 2) - SHIP_SIZE / 2, (draw_window::get_height() / 2) - SHIP_SIZE };
		wxPoint point_top{ (draw_window::get_width() / 2), (draw_window::get_height() / 2) - SHIP_SIZE };
		wxPoint point_bottom_left{ (draw_window::get_width() / 2) - SHIP_SIZE / 2, (draw_window::get_height() / 2) + SHIP_SIZE };
		wxPoint point_bottom_right{ (draw_window::get_width() / 2) + SHIP_SIZE / 2, (draw_window::get_height() / 2) + SHIP_SIZE };
		std::array<wxRealPoint, 3> points{ point_top, point_bottom_right, point_bottom_left };
		m_p_player = std::make_unique<ship>(
			points, 
			m_pen, m_brush, 
			get_size(),
			0 // speed
		);
		utils::create([&] {
			asteroids::random r{};
			wxRealPoint astroid_pos = ge.random_window_pos_edge();
			m_asteroids.push_back(
				std::make_shared<asteroids::asteroid>(
					m_pen,
					*wxGREY_BRUSH,
					get_size(),						//window_size, for positioning needed
					r.get_random_number(1, 3),		// speed
					ge.random_window_pos_edge(),	//position of astroid in window (edges)
					ge.get_asteroid_size(),			//astroid size
					r.get_random_number(0, 180)		//degree 
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
			
		}
		refresh();
	}

	void check_spaceship_collision() {
		// check asteroid spaceship collision

		bool had_collision = false;

		for (const auto& asteroid : m_asteroids) {
			if (m_p_player->collision(asteroid->region())) {
				had_collision = true;
				exit(0);
				break;
			}
		}
	}
	void collision_detection() {
		//check_projectile_collision();
		check_spaceship_collision();
		//remove_projectiles();
	}
	void on_menu(ml5::menu_event const& event)override {
	}

	void on_mouse_up(ml5::mouse_event const& event)override {
	}

	void on_mouse_move(ml5::mouse_event const& event)override {
	}

	void on_paint(ml5::paint_event const& event)override {
		if (m_p_player) {
			m_p_player->draw(event.get_context());
		}
		for (const auto& asteroid : m_asteroids) {
			asteroid->draw(event.get_context());
		}

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
		collision_detection();
		refresh();
		counter++;
	}

	void draw_background(ml5::paint_event const& event) {
		// bei der Initialisierung der Anwendung
		wxImage::AddHandler(new wxPNGHandler);
		//wxImage asteroid_image;
		//asteroid_image.LoadFile(wxT(".\\images\\astroid.png"), wxBITMAP_TYPE_PNG);
		//asteroid_image.Rescale(24, 24);
		//// in on_paint
		//auto& context = event.get_context();
		//context.DrawBitmap(asteroid_image, wxPoint(0,0));
		//// beim Beenden der Anwendung
		//wxImage::CleanUpHandlers();
	}


private:
	ml5::vector<std::unique_ptr<shape>> m_p_astroids{};
	std::unique_ptr<ship> m_p_player{ nullptr };
	wxBrush	m_brush{ *wxBLUE_BRUSH };
	wxPen m_pen{ *wxWHITE_PEN };
	asteroids::game_engine ge{};
	std::vector<std::shared_ptr<asteroid>> m_asteroids{};
	//static wxSize screen_size;
};