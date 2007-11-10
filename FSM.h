#ifndef FSM_H
#define FSM_H

enum FSM_STATES 
	{ 
		FSM_STATE_NONE,
		FSM_FOLLOW_QUEEN,
		FSM_ATTACK_BEE,
		FSM_ATTACK_ENEMY,
		FSM_DEAD,
		FSM_BEE_DEAD,
		FSM_ENEMY_DEAD,
		FSM_QUEEN_DEAD,
		FSM_IDLE,
		FSM_POWERUP,
		FSM_QUEEN_WANDER
	};

/*
enum FSM_MACHINES
	{
		FSM_MACH_NONE,
		FSM_MACH_QUEEN,
		FSM_MACH_BEE,
		FSM_MACH_ENEMY
	};
*/

#endif