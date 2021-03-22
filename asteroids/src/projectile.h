#pragma once

#include "game_object.hpp"
#include "utils.hpp"

#define PROJECTILE_SIZE 3

namespace asteroids {

	class projectile : public game_object {

	public:
		projectile(wxPoint position, double degree)
			: game_object{ position, degree } {
			speed_ = 5;
		}

		void draw(context& context) override {
			context.SetBrush(*wxGREEN_BRUSH);
			context.SetPen(*wxGREEN_PEN);
			context.DrawCircle(position_, PROJECTILE_SIZE);
		}

		void move(const wxSize& size) override {
			position_.x += sin(degree_to_radian(degree_)) * speed_;
			position_.y += -cos(degree_to_radian(degree_)) * speed_;
		}
	};
}