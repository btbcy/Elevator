#include <chrono>
#include <iostream>
#include "elevator.h"

Elevator::Elevator() {
	state_items[0] = new Floor1State(this);
	state_items[1] = new Floor2State(this);
	state_items[2] = new Floor1to2State(this);
	state_items[3] = new Floor2to1State(this);
	state_items[4] = new Floor1OpenState(this);
	state_items[5] = new Floor2OpenState(this);

	curr_state = state_items[STATE_FLOOR_1];
	next_state = nullptr;
	expiration_time = std::chrono::system_clock::now();
	reset_button();
}

Elevator::~Elevator() {
	for (int idx = 0; idx < 6; ++idx) {
		delete state_items[idx];
	}
}

void Elevator::show_status() {
	std::string floor_status = curr_state->get_status_string();
	std::string button_status = ", button status (UP, DOWN, FLOOR_1, FLOOR_2): ";
	for (int idx = 0; idx < 4; ++idx) {
		if (button[idx]) {
			button_status += "T";
		} else {
			button_status += "F";
		}
	}
	std::cout << floor_status << " " << button_status << std::endl;
}

void Elevator::action() {
	auto operation = curr_state->select_action();
	if (operation == ButtonType::NO_OPERATION) {
		return;
	} else if (operation == ButtonType::UP) {
		curr_state->handle_up();
	} else if (operation == ButtonType::DOWN) {
		curr_state->handle_down();
	} else if (operation == ButtonType::FLOOR_1) {
		curr_state->handle_floor1();
	} else if (operation == ButtonType::FLOOR_2) {
		curr_state->handle_floor2();
	}
}

void Elevator::set_next_state(State* state) {
	this->next_state = state;
}

void Elevator::update_state() {
	auto current_time = std::chrono::system_clock::now();
	if (this->next_state != nullptr && current_time >= expiration_time) {
		this->curr_state = this->next_state;
		this->next_state = nullptr;
		this->curr_state->enter_state();
	}
}

State* Elevator::get_state_item(StateType type) {
	return state_items[type];
}

void Elevator::set_expiration_time(int seconds) {
	auto current_time = std::chrono::system_clock::now();
	this->expiration_time = current_time + std::chrono::seconds(seconds);
}

void Elevator::press_button(ButtonType type) {
	if (type != ButtonType::NO_OPERATION) {
		button[type] = true;
	}
}

void Elevator::reset_button() {
	for (int idx = 0; idx < 4; ++idx) {
		button[idx] = false;
	}
}

void Elevator::reset_button(ButtonType type) {
	if (type != ButtonType::NO_OPERATION) {
		button[type] = false;
	}
}

bool* Elevator::get_button() {
	return button;
}
