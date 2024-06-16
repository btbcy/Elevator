#pragma once

#include <chrono>
#include "state.h"

class Elevator {
public:
	Elevator();
	~Elevator();
	void show_status();
	void action();
	void set_next_state(State*);
	void update_state();
	State* get_state_item(StateType type);
	void set_expiration_time(int);
	void press_button(ButtonType button);
	void reset_button();
	void reset_button(ButtonType button);
	bool* get_button();

private:
	State* curr_state;
	State* next_state;
	State* state_items[6];
	std::chrono::time_point<std::chrono::system_clock> expiration_time;
	bool button[4];
};

