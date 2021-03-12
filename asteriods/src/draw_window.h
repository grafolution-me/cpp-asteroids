#pragma once

#include <ml5/ml5.h>
#include <iostream>
#include "shape.h"
#include "rectangle.h"
#include "line.h"
#include "triangle.h"
#include "ellipse.h"
#define SHIP_SIZE 16
#define MOVE_SPEED 2

class draw_window : public ml5::window, MI5_DERIVE(draw_window, ml5::window){
	MI5_INJECT(draw_window)
		
	//enum class shape_t{line,rectangle,ellipse};
	enum key_mapping { left = 314, right = 316, up = 317, down = 319};


	void on_mouse_down(ml5::mouse_event const& event)override {
	}
	void on_init() override {
		this->set_prop_background_brush(wxBrush{ *wxBLACK_BRUSH });

		wxPoint point_top_left{ (draw_window::get_width() / 2) - SHIP_SIZE/2, (draw_window::get_height() / 2) - SHIP_SIZE };
		wxPoint point_top{ (draw_window::get_width() / 2), (draw_window::get_height() / 2) - SHIP_SIZE };
		wxPoint point_bottom_left{ (draw_window::get_width() / 2) - SHIP_SIZE/2, (draw_window::get_height() / 2) + SHIP_SIZE };
		wxPoint point_bottom_right{ (draw_window::get_width() / 2) + SHIP_SIZE/2, (draw_window::get_height() / 2) + SHIP_SIZE };
		std::array<wxRealPoint, 3> points{ point_top, point_bottom_right, point_bottom_left };
		m_p_player = std::make_unique<triangle>(wxRect{ point_top_left, point_bottom_right }, points, point_bottom_left, m_pen, m_brush);

	}
	virtual void on_key(ml5::key_event const& event) {
		int key_code = event.get_key_code();
		
		switch (key_code) {
			case key_mapping::left:
				if (m_p_player)  m_p_player->move(-30);
				break;
			case key_mapping::right:
				if (m_p_player && m_p_player->get_right() <= this->get_width())  m_p_player->move(30);
				break;
			case key_mapping::down:
				if (m_p_player && m_p_player->get_bottom() <= this->get_width()){}
				break;
			case key_mapping::up:
				if (m_p_player && m_p_player->get_bottom() <= this->get_width()) { m_p_player->move(30); };
				break;
		}

		refresh();
	}
	
	void on_menu(ml5::menu_event const& event)override{
	}

	void on_mouse_up(ml5::mouse_event const& event)override {
	}

	void on_mouse_move(ml5::mouse_event const& event)override {
		
	}

	void on_paint(ml5::paint_event const& event)override {
		if (m_p_player) {
			m_p_player->draw(event.get_context());
		}
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
		std::unique_ptr<shape> m_p_player{ nullptr };
		wxBrush	m_brush{*wxBLUE_BRUSH};
		wxPen m_pen{ *wxWHITE_PEN };
};