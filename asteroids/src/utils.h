#pragma once
#include <ml5/ml5.h>

namespace utils {

		double degree_rad(int angle) {
			return angle * (M_PI / 180);
		}
		double degree_rad(double angle) {
			return angle * (M_PI / 180);
		}

		wxRealPoint& get_center(std::vector<wxRealPoint>v) {
			double center_x = 0;
			double center_y = 0;
			for (wxRealPoint point : v)
			{
				center_x += point.x;
				center_y += point.y;
			}
			wxRealPoint center{ center_x / v.size(), center_y / v.size() };
			return center;
		}

		
		/**
			this method invokes another method n times
		*/
		template<typename T>
		void create(T v, const int count) {
			if (count > 0) {
				for (size_t i = 0; i < count; i++)
				{
					std::invoke(std::forward<T>(v));
				}
				
			}
		}
};