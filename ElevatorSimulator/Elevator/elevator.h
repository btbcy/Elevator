#pragma once

#include <array>
#include <chrono>
#include <mutex>
#include "state.h"

class Elevator {
public:
	Elevator();
	~Elevator();
	void show_status();
	void action();
	void set_next_state(State*);
	void update_state();
	State* get_state_item(StateType) const;
	void set_expiration_time(int);
	void press_button(ButtonType);
	void reset_button(ButtonType);
	void reset_button_with_lock(ButtonType);
	std::array<bool, 4> get_button();

private:
	State* curr_state;
	State* next_state;
	State* state_items[6];
	std::chrono::time_point<std::chrono::system_clock> expiration_time;
	std::array<bool, 4> button;
	std::mutex button_mutex;
	std::mutex state_mutex;
};

