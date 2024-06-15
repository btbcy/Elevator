#pragma once

#include <chrono>
#include "state.h"

class Elevator {
public:
	Elevator();
	~Elevator();
	void show_status();
	void set_next_state(State*);
	void set_next_state(
		State*, 
		std::chrono::time_point<std::chrono::system_clock>);
	void update_state();
	State* get_state_item(StateType type);
	void reset_timer();
	void press_button(ButtonType button);
	void reset_button();
	bool* get_button();

private:
	State* curr_state;
	State* next_state;
	State* state_items[6];
	std::chrono::time_point<std::chrono::system_clock> expiration_time;
	bool button[4];
};

