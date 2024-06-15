#include <iostream>
#include <chrono>
#include "state.h"
#include "elevator.h"

State::State(Elevator* elevator) {
	this->elevator = elevator;
}

Floor1State::Floor1State(Elevator* elevator): State(elevator) {}

void Floor1State::show_status() {
	std::cout << "Elevator is on floor 1: Idle" << std::endl;
}

ButtonType Floor1State::select_action() {
	bool* button = this->elevator->get_button();
	if (button[UP]) {
		return ButtonType::UP;
	} else if (button[FLOOR_1]) {
		return ButtonType::FLOOR_1;
	} else if (button[DOWN]) {
		return ButtonType::DOWN;
	} else {
		return ButtonType::FLOOR_2;
	}
}

void Floor1State::handle_up() {
	elevator->set_next_state(elevator->get_state_item(StateType::STATE_FLOOR_1_OPEN));
	auto current_time = std::chrono::system_clock::now();
	auto expiration_time = current_time + std::chrono::seconds(2);
	elevator->set_next_state(elevator->get_state_item(StateType::STATE_FLOOR_1));
}

void Floor1State::handle_down() {

}

void Floor1State::handle_floor1() {

}

void Floor1State::handle_floor2() {
}

