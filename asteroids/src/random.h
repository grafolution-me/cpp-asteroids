#pragma once
#include <ml5/ml5.h>
namespace asteroids {
	class random
	{
	public:
		random(){}
		~random(){}
		int get_random_number(const int num_min = 0, const int num_max = 0) {
			return get_random_uniform(num_min, num_max);
		}
	private:
		template<typename E = std::mt19937_64>
		int get_random_uniform(int const l, int const u) {
			static E generator{ std::random_device{} () }; //seed erzeugen, ist nicht determistisch zufällig. atomzerfall
			return std::uniform_int_distribution{ l, u }(generator);
		}
	};
}



