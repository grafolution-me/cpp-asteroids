#pragma once
#include "utils.h"
#include "game_engine.h"
wxRealPoint utils::random_window_pos()
{
	asteroids::random r{};
	wxSize size = game_engine::getInstance().get_window_size();
	int x = r.get_random_number(0, size.x);
	int y = r.get_random_number(0, size.y);
	return wxRealPoint(x, y);
}

wxRealPoint utils::get_center(std::vector<wxRealPoint> v)
{
	double center_x = 0;
	double center_y = 0;
	for (wxRealPoint point : v)
	{
		center_x += point.x;
		center_y += point.y;
	}
	return wxRealPoint { center_x / v.size(), center_y / v.size() };
}

wxRealPoint utils::random_window_pos_edge() {
	wxRealPoint wrp = random_window_pos();
	wxSize size = game_engine::getInstance().get_window_size();
	return ((int)std::max(wrp.x, wrp.y) % 3 == 0) ?		wxRealPoint(wrp.x, 0) :
		((int)std::max(wrp.x, wrp.y) % 3 == 1) ?		wxRealPoint(0, wrp.y) :
		((int)std::max(wrp.x, wrp.y) % 3 == 2) ?		wxRealPoint(wrp.x, size.y) :
														wxRealPoint(size.x, wrp.y);
}

asteroid_size utils::get_asteroid_size() {
	random r{};
	int rand = r.get_random_number(0, 3);
	if (rand == 0) {
		return asteroid_size::smallest;
	}
	else if (rand == 1) {
		return asteroid_size::medium;
	}
	else if(rand == 2) {
		return asteroid_size::large;
	}else {
		return asteroid_size::xlarge;
	}
}

asteroid_size utils::get_asteroid_size(int size) {
     	switch (size) {
	case 1:
		return asteroid_size::smallest;
		break;
	case 2:
		return asteroid_size::medium;
		break;
	case 3:
		return asteroid_size::large;
		break;
	default:
		return asteroid_size::smallest;
		break;
	}
}
