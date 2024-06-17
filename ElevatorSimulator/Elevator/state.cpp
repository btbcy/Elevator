#include <iostream>
#include <chrono>
#include "state.h"
#include "elevator.h"

State::State(Elevator* elevator) {
	this->elevator = elevator;
}

/* ------
 * Floor1State:
 * ------ */
Floor1State::Floor1State(Elevator* elevator): State(elevator) {}

std::string Floor1State::get_status_string() {
	return "Elevator is on floor 1: Idle";
}

ButtonType Floor1State::select_action() {
	auto button = this->elevator->get_button();
	if (button[UP]) {
		return ButtonType::UP;
	} else if (button[FLOOR_1]) {
		return ButtonType::FLOOR_1;
	} else if (button[DOWN]) {
		return ButtonType::DOWN;
	} else if (button[FLOOR_2]) {
		return ButtonType::FLOOR_2;
	} else {
		return ButtonType::NO_OPERATION;
	}
}

void Floor1State::handle_up() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_1_OPEN));
}

void Floor1State::handle_down() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_1_TO_2));
}

void Floor1State::handle_floor1() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_1_OPEN));
}

void Floor1State::handle_floor2() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_1_TO_2));
}

/* ------
 * Floor2State:
 * ------ */

Floor2State::Floor2State(Elevator* elevator): State(elevator) {}

std::string Floor2State::get_status_string() {
	return "Elevator is on floor 2: Idle";
}

ButtonType Floor2State::select_action() {
	auto button = this->elevator->get_button();
	if (button[DOWN]) {
		return ButtonType::DOWN;
	} else if (button[FLOOR_2]) {
		return ButtonType::FLOOR_2;
	} else if (button[UP]) {
		return ButtonType::UP;
	} else if (button[FLOOR_1]) {
		return ButtonType::FLOOR_1;
	} else {
		return ButtonType::NO_OPERATION;
	}
}

void Floor2State::handle_up() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_2_TO_1));
}

void Floor2State::handle_down() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_2_OPEN));
}

void Floor2State::handle_floor1() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_2_TO_1));
}

void Floor2State::handle_floor2() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_2_OPEN));
}

/* ------
 * Floor1to2State:
 * ------ */

Floor1to2State::Floor1to2State(Elevator* elevator): State(elevator) {}

std::string Floor1to2State::get_status_string() {
	return "Elevator is moving from floor 1 to floor 2";
}

ButtonType Floor1to2State::select_action() {
	return ButtonType::NO_OPERATION;
}

void Floor1to2State::enter_state() {
	elevator->set_expiration_time(5);
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_2_OPEN));
}

/* ------
 * Floor2to1State:
 * ------ */

Floor2to1State::Floor2to1State(Elevator* elevator): State(elevator) {}

std::string Floor2to1State::get_status_string() {
	return "Elevator is moving from floor 2 to floor 1";
}

ButtonType Floor2to1State::select_action() {
	return ButtonType::NO_OPERATION;
}

void Floor2to1State::enter_state() {
	elevator->set_expiration_time(5);
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_1_OPEN));
}

/* ------
 * Floor1OpenState:
 * ------ */

Floor1OpenState::Floor1OpenState(Elevator* elevator): State(elevator) {}

std::string Floor1OpenState::get_status_string() {
	return "Elevator is on floor 1: Open";
}

ButtonType Floor1OpenState::select_action() {
	auto button = this->elevator->get_button();
	if (button[UP]) {
		return ButtonType::UP;
	} else if (button[FLOOR_1]) {
		return ButtonType::FLOOR_1;
	} else if (button[DOWN]) {
		return ButtonType::DOWN;
	} else if (button[FLOOR_2]) {
		return ButtonType::FLOOR_2;
	} else {
		return ButtonType::NO_OPERATION;
	}
}

void Floor1OpenState::enter_state() {
	elevator->reset_button(ButtonType::FLOOR_1);
	elevator->reset_button(ButtonType::UP);
	elevator->set_expiration_time(2);
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_1));
}

void Floor1OpenState::handle_up() {
	elevator->reset_button_with_lock(ButtonType::FLOOR_1);
	elevator->reset_button_with_lock(ButtonType::UP);
	elevator->set_expiration_time(2);
}

void Floor1OpenState::handle_down() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_1_TO_2));
}

void Floor1OpenState::handle_floor1() {
	elevator->reset_button_with_lock(ButtonType::FLOOR_1);
	elevator->reset_button_with_lock(ButtonType::UP);
	elevator->set_expiration_time(2);
}

void Floor1OpenState::handle_floor2() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_1_TO_2));
}

/* ------
 * Floor2OpenState:
 * ------ */

Floor2OpenState::Floor2OpenState(Elevator* elevator): State(elevator) {}

std::string Floor2OpenState::get_status_string() {
	return "Elevator is on floor 2: Open";
}

ButtonType Floor2OpenState::select_action() {
	auto button = this->elevator->get_button();
	if (button[DOWN]) {
		return ButtonType::DOWN;
	} else if (button[FLOOR_2]) {
		return ButtonType::FLOOR_2;
	} else if (button[UP]) {
		return ButtonType::UP;
	} else if (button[FLOOR_1]) {
		return ButtonType::FLOOR_1;
	} else {
		return ButtonType::NO_OPERATION;
	}
}

void Floor2OpenState::enter_state() {
	elevator->reset_button(ButtonType::FLOOR_2);
	elevator->reset_button(ButtonType::DOWN);
	elevator->set_expiration_time(2);
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_2));
}

void Floor2OpenState::handle_up() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_2_TO_1));
}

void Floor2OpenState::handle_down() {
	elevator->reset_button_with_lock(ButtonType::FLOOR_2);
	elevator->reset_button_with_lock(ButtonType::DOWN);
	elevator->set_expiration_time(2);
}

void Floor2OpenState::handle_floor1() {
	elevator->set_next_state(
		elevator->get_state_item(StateType::STATE_FLOOR_2_TO_1));
}

void Floor2OpenState::handle_floor2() {
	elevator->reset_button_with_lock(ButtonType::FLOOR_2);
	elevator->reset_button_with_lock(ButtonType::DOWN);
	elevator->set_expiration_time(2);
}
