#include <chrono>
#include "elevator.h"

Elevator::Elevator() {
	state_items[0] = new Floor1State(this);
	for (int idx = 1; idx < 6; ++idx) {
		state_items[idx] = new Floor1State(this);
	}
	/*
	TODO: more states
	state_items[1] = new Floor2State(this);
	state_items[2] = new Floor1to2State(this);
	state_items[3] = new Floor2to1State(this);
	state_items[4] = new Floor1OpenState(this);
	state_items[5] = new Floor2OpenState(this);
	*/

	curr_state = state_items[STATE_FLOOR_1];
	next_state = nullptr;
	reset_timer();
	reset_button();
}

Elevator::~Elevator() {
	for (int idx = 0; idx < 6; ++idx) {
		delete state_items[idx];
	}
}

void Elevator::show_status() {
	curr_state->show_status();
}

void Elevator::set_next_state(State* state) {
	this->next_state = nullptr;
	this->curr_state = state;
	reset_timer();
}

void Elevator::set_next_state(
		State* state, 
		std::chrono::time_point<std::chrono::system_clock> expiration_time
	) {
	this->next_state = state;
	this->expiration_time = expiration_time;
}

void Elevator::update_state() {
	auto current_time = std::chrono::system_clock::now();
	if (this->next_state != nullptr && current_time >= expiration_time) {
		this->curr_state = this->next_state;
		this->next_state = nullptr;
		reset_timer();
	}
}

State* Elevator::get_state_item(StateType type) {
	return state_items[type];
}

void Elevator::reset_timer() {
	expiration_time = std::chrono::system_clock::now();
}

void Elevator::press_button(ButtonType type) {
	button[type] = true;
}

void Elevator::reset_button() {
	for (int idx = 0; idx < 4; ++idx) {
		button[idx] = false;
	}
}

bool* Elevator::get_button() {
	return button;
}
