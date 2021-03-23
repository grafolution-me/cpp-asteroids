#pragma once
#include <ml5/ml5.h>
#include "random.h"
#include "asteroid_size.h"
#include "game_engine.h"
#include <wx/sound.h>
using namespace asteroids;
namespace utils {

		inline double degree_rad(int angle) {
			return angle * (M_PI / 180);
		}
		inline double degree_rad(double angle) {
			return angle * (M_PI / 180);
		}
		
		/**
			this method invokes another method n times
		*/
		template<typename T>
		inline void create(T v, const int count) {
			if (count > 0) {
				for (size_t i = 0; i < count; i++)
				{
					std::invoke(std::forward<T>(v));
				}
				
			}
		}
		inline bool is_point_valid(wxRealPoint& point) {
			if ((point.x >= 0 && point.x <= game_engine::getInstance().get_window_size().x) &&
				(point.y >= 0 && point.y <= game_engine::getInstance().get_window_size().y)) {
				return true;
			}
			else return false;

		}
		inline bool is_point_valid(const wxRealPoint& point) {
			if ((point.x >= 0 && point.x <= game_engine::getInstance().get_window_size().x) &&
				(point.y >= 0 && point.y <= game_engine::getInstance().get_window_size().y)) {
				return true;
			}
			else return false;

		}
		inline void is_point_valid_x(wxRealPoint& point) {
			if (point.x <= 0) {
				point.x = point.x + game_engine::getInstance().get_window_size().x;
			}
			else {
				point.x = (int)point.x % game_engine::getInstance().get_window_size().x;
			}

		}
		inline void is_point_valid_y(wxRealPoint& point) {
			if (point.y <= 0) {
				point.y = point.y + game_engine::getInstance().get_window_size().y;
			}
			else {
				point.y = (int)point.y % game_engine::getInstance().get_window_size().y;
			}
		}
		inline void play_shoot_sound()
		{
			wxSound sound("./sounds/shoot.wav");
 			sound.Play();
		}
		inline void play_wasted_sound()
		{
			wxSound sound("./sounds/wasted.wav");
			sound.Play();
		}
		wxRealPoint get_center(std::vector<wxRealPoint>v);
		wxRealPoint random_window_pos_edge();
		wxRealPoint random_window_pos();
		asteroid_size get_asteroid_size();
		asteroid_size get_asteroid_size(int size);
};