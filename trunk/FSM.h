#ifndef FSM_H
#define FSM_H

enum FSM_STATES 
	{ 
		FSM_STATE_NONE,
		FSM_FOLLOW_QUEEN,
		FSM_ATTACK,
		FSM_DEAD,
		FSM_IDLE,
		FSM_POWERUP
	};

enum FSM_MACHINES
	{
		FSM_MACH_NONE,
		FSM_MACH_QUEEN,
		FSM_MACH_BEE,
		FSM_MACH_ENEMY
	};

#endif