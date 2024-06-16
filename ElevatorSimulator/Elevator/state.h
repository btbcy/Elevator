#pragma once
#include <string>

class Elevator;

enum StateType {
	STATE_FLOOR_1 = 0,
	STATE_FLOOR_2,
	STATE_FLOOR_1_TO_2,
	STATE_FLOOR_2_TO_1,
	STATE_FLOOR_1_OPEN,
	STATE_FLOOR_2_OPEN
};

enum ButtonType {
	UP = 0,
	DOWN,
	FLOOR_1,
	FLOOR_2,
	NO_OPERATION
};

class State {
public:
	State(Elevator*);
	virtual std::string get_status_string() = 0;
	virtual ButtonType select_action() = 0;
	virtual void enter_state() {};
	virtual void handle_up() = 0;
	virtual void handle_down() = 0;
	virtual void handle_floor1() = 0;
	virtual void handle_floor2() = 0;

protected:
	Elevator* elevator;
};

class Floor1State : public State {
public:
	Floor1State(Elevator*);
	std::string get_status_string() override;
	ButtonType select_action() override;
	void handle_up() override;
	void handle_down() override;
	void handle_floor1() override;
	void handle_floor2() override;
};

class Floor2State : public State {
public:
	Floor2State(Elevator*);
	std::string get_status_string() override;
	ButtonType select_action() override;
	void handle_up() override;
	void handle_down() override;
	void handle_floor1() override;
	void handle_floor2() override;
};

class Floor1to2State : public State {
public:
	Floor1to2State(Elevator*);
	std::string get_status_string() override;
	ButtonType select_action() override;
	void enter_state() override;
	void handle_up() override {}
	void handle_down() override {}
	void handle_floor1() override {}
	void handle_floor2() override {}
};

class Floor2to1State : public State {
public:
	Floor2to1State(Elevator*);
	std::string get_status_string() override;
	ButtonType select_action() override;
	void enter_state() override;
	void handle_up() override {}
	void handle_down() override {}
	void handle_floor1() override {}
	void handle_floor2() override {}
};

class Floor1OpenState : public State {
public:
	Floor1OpenState(Elevator*);
	std::string get_status_string() override;
	ButtonType select_action() override;
	void enter_state() override;
	void handle_up() override;
	void handle_down() override;
	void handle_floor1() override;
	void handle_floor2() override;
};

class Floor2OpenState : public State {
public:
	Floor2OpenState(Elevator*);
	std::string get_status_string() override;
	ButtonType select_action() override;
	void enter_state() override;
	void handle_up() override;
	void handle_down() override;
	void handle_floor1() override;
	void handle_floor2() override;
};