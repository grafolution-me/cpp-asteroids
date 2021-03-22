#pragma once
#include <ml5/ml5.h>
#include "random.h"
#include "asteroid_size.h"

using namespace asteroids;
namespace asteroids {
	class game_engine 
	{
	public:
		game_engine(wxSize size) : m_size{ size } {}
		game_engine() : m_size{0, 0 } {}
		~game_engine() {}
		wxSize get_size() {
			return m_size;
		}
		
		wxRealPoint random_window_pos() {
			asteroids::random r{};
			int x = r.get_random_number(0, m_size.x);
			int y = r.get_random_number(0, m_size.y);
			return wxRealPoint(x, y);
		}
		wxRealPoint random_window_pos_edge() {
			wxRealPoint wrp = random_window_pos();
			return ((int)std::max(wrp.x, wrp.y) % 2) ? wxRealPoint(wrp.x, 2) : wxRealPoint(2, wrp.y);
		}
		asteroid_size get_asteroid_size() {
			random r{};
			int rand = r.get_random_number(0, 2);
			if (rand == 0) {
				return asteroid_size::smallest;
			}
			else if (rand == 1) {
				return asteroid_size::medium;
			}
			else {
				return asteroid_size::large;
			}
		}
	private:
		wxSize m_size;

		
	

	};


}

	
