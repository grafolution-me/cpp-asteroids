#pragma once

class game_engine
{
public:
	static game_engine& getInstance()
	{
		
		static game_engine instance{}; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
	wxSize& get_window_size() {
		return window_size;
	}
	game_engine(game_engine const&) = delete;
	void operator=(game_engine const&) = delete;
	

private:
	game_engine() {}                    // Constructor? (the {} brackets) are needed here.



	wxSize window_size{1280, 720};
};