#ifndef FSM_H
#define FSM_H

// FSM state types
enum FSM_STATES 
	{ 
		FSM_STATE_NONE,
		FSM_FOLLOW_QUEEN,
		FSM_ATTACK_ENEMY,
		FSM_QUEEN_TARGETENEMY,
		FSM_QUEEN_SELECTSOLDIERS,
		FSM_QUEEN_SELECTGATHERERS,
		FSM_ENEMY_WANDER,
		FSM_ENEMY_DRAGONFLY_ATTACK,
		FSM_ENEMY_LOCUST_ATTACK,
		FSM_ENEMY_BOSS_ATTACK,
		FSM_GATHER_HONEY
	};


#endif