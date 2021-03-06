/*
 * File: DancingSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopLevelHSM.h"
#include "DancingSubHSM.h"
#include "AD.h"
#include "IO_Ports.h"
#include "ES_Timers.h"
#include "LocateHoleHSM.h"
#include "PingService.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//Enum for all the states in the subHSM
typedef enum {
    InitPSubState,
    Entry,
    RB_Reverse,
    LB_Reverse,
    LB_Buffer,
    She_Cruzin,
    Woah_Nelly,
    Switch_Stance,
    Backup_Dat_Trunk,
    Ramming_Speed,
    Vibe_Check,
    Cha_Cha_Real_Smooth,
    Quickie,
    Straight_Pride,
    Heterophobe,
    D_Flip_Flop,
    Conversion_Therapy,
    Hoe_Songs,
    Daddy_Issues,
    Fuck_This,
    Criss_Cross,
} TemplateSubHSMState_t;

//python-generated array of strings based on the TemplateSuhHSMState_t enum
static const char *StateNames[] = {
	"InitPSubState",
	"Entry",
	"RB_Reverse",
	"LB_Reverse",
	"LB_Buffer",
	"She_Cruzin",
	"Woah_Nelly",
	"Switch_Stance",
	"Backup_Dat_Trunk",
	"Ramming_Speed",
	"Vibe_Check",
	"Cha_Cha_Real_Smooth",
	"Quickie",
	"Straight_Pride",
	"Heterophobe",
	"D_Flip_Flop",
	"Conversion_Therapy",
	"Hoe_Songs",
	"Daddy_Issues",
	"Fuck_This",
	"Criss_Cross",
};

#define CONVERSION_TICKS 350
#define DADDYS_TICKS 250
#define LB_REVERSE_TICKS 150
#define CRISS_CROSS_TICKS 90
#define RETREAT_TICKS 300
#define RB_REVERSE_TICKS 400
#define FLIPPING_TICKS 500
#define FUCKING_TIMER 500
#define DAT_TRUNK_TICKS 700
#define QUICKIE_TICKS 800
#define SWITCHING_TICKS 450
#define QUICKIE_TICKS2 900
#define CRUZIN_TICKS 1300
#define NELLY_TICKS 1600
#define HOE_TIMES 8000
#define HETEROPHOBE_TICKS 5000

#define EM_THRESHOLD 600
#define TRACK_WIRE_THRESH 700 // change these
#define TRACK_WIRE_SENSOR AD_PORTW7

// The following #defines are used to simplify the state machine, they handle all necessary
// state machine variables and timers for each state
#define GoTo_Entry nextState = Entry;\
                makeTransition = TRUE
#define GoTo_LB_Reverse nextState = LB_Reverse;\
                makeTransition = TRUE
#define GoTo_RB_Reverse nextState = RB_Reverse;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, RB_REVERSE_TICKS)
#define GoTo_LB_Buffer nextState = LB_Buffer;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, LB_REVERSE_TICKS)
#define GoTo_Switch_Stance nextState = Switch_Stance;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, SWITCHING_TICKS)
#define GoTo_She_Cruzin nextState = She_Cruzin;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, CRUZIN_TICKS)
#define GoTo_Woah_Nelly nextState = Woah_Nelly;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, NELLY_TICKS)
#define GoTo_Vibe_Check nextState = Vibe_Check;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, 1);\
                Ping_Flag = ThisEvent.EventParam
#define GoTo_Backup_Dat_Trunk nextState = Backup_Dat_Trunk;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, DAT_TRUNK_TICKS)
#define GoTo_Ramming_Speed nextState = Ramming_Speed;\
                makeTransition = TRUE
#define GoTo_Zoom_Zoom nextState = Ramming_Speed;\
                makeTransition = TRUE
#define GoTo_Cha_Cha_Real_Smooth nextState = Cha_Cha_Real_Smooth;\
                makeTransition = TRUE
#define GoTo_Quickie nextState = Quickie;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, QUICKIE_TICKS)
#define GoTo_Quickie2 nextState = Quickie;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, QUICKIE_TICKS2)
#define GoTo_Straight_Pride nextState = Straight_Pride;\
                makeTransition = TRUE
#define GoTo_Heterophobe nextState = Heterophobe;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, HETEROPHOBE_TICKS)
#define GoTo_D_Flip_Flop nextState = D_Flip_Flop;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, FLIPPING_TICKS)
#define GoTo_Conversion_Therapy nextState = Conversion_Therapy;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, CONVERSION_TICKS)
#define GoTo_Hoe_Songs nextState = Hoe_Songs;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, HOE_TIMES)
#define GoTo_Daddy_Issues nextState = Daddy_Issues;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, DADDYS_TICKS)
#define GoTo_Fuck_This nextState = Fuck_This;\
                makeTransition = TRUE
#define GoTo_Criss_Cross nextState = Criss_Cross;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DANCING_TIMER, CRISS_CROSS_TICKS)
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

uint16_t VibeCheck(void);
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TemplateSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static ES_Event PingOnEvent;
static ES_Event PingOffEvent;
static uint8_t Timeout_Flag = 0;
static uint8_t Bumper_Clr_Flag = 0;
static uint8_t Ping_Flag = 0;
static uint8_t Mr_Flag = 0;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitDancingSubHSM(void) {
    ES_Event returnEvent;


    CurrentState = InitPSubState;
    returnEvent = RunDancingSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunDancingSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

	
	/* This state machine is very complicated, for a better in depth look at the state machine (with visuals),
	please refer to the full report. */
    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                PingOnEvent.EventType = PING_ON;
                PingOffEvent.EventType = PING_OFF;
                // now put the machine into the actual initial state
                nextState = Entry;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

	//@Entry
	//Entry state for the dancing subHSM
        case Entry:
            //check for event params coming in from the bumper service
            Ping_Flag = 0;

	    // Probably will never happen, but just check the bumpers here just in case
            if (ThisEvent.EventType == FR_BUMPER_HIT) {
                GoTo_RB_Reverse;
                RunPingService(PingOnEvent);
            } else if (ThisEvent.EventType == F_BUMPER_HIT) {
                GoTo_LB_Reverse;
                RunPingService(PingOnEvent);
            } else if (ThisEvent.EventType == FL_BUMPER_HIT) {
                GoTo_LB_Reverse;
                RunPingService(PingOnEvent);
            }
            break;

	//@Right bumper reverse
	//Simply makes a quick reverse when the right bumper is hit in entry/she_cruzin
	//Always transitions to Switch_Stance on timeout
        case RB_Reverse:
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_Switch_Stance;
            } else if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else {
                Roach_LeftMtrSpeed(-50);
                Roach_RightMtrSpeed(-50);
            }

            break;

	//@Switch_Stance
	//Occurs after RB_Reverse
	//Quickly turns the bot to the right to hopefully reorient the left side of the bot parallel to the wall
        case Switch_Stance:
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_She_Cruzin;
            } else if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else {
                TankTurn_R_Fast();
            }

            break;

	//@Left bumper reverse
	//From any state, if the left bumper is triggered, we want to backup until the bumper is released 
	//Usually transitions to LB_Buffer
        case LB_Reverse:
            if ((ThisEvent.EventType == FL_BUMPER_RELEASED) || (ThisEvent.EventType == F_BUMPER_RELEASED)) {
                GoTo_LB_Buffer;
            } else if (ThisEvent.EventType == RL_BUMPER_HIT) {
                GoTo_Woah_Nelly;
            } else if (ThisEvent.EventType == PARALLEL_CLOSE) {
                GoTo_Vibe_Check;
            } else if (ThisEvent.EventType == PARALLEL_FAR) {
                GoTo_Straight_Pride;
            } else {
                Roach_LeftMtrSpeed(-5);
                Roach_RightMtrSpeed(-50);
            }
            break;

	//@Left bumper Buffer
	//We keep backing up for a set amount of time to move away from the wall
        case LB_Buffer:
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_Criss_Cross;
            } else if (ThisEvent.EventType == PARALLEL_CLOSE) {
                GoTo_Vibe_Check;
            } else if (ThisEvent.EventType == PARALLEL_FAR) {
                GoTo_Straight_Pride;
            } else if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else if (ThisEvent.EventType == RL_BUMPER_HIT) {
                GoTo_Woah_Nelly;
            } else {
                Roach_LeftMtrSpeed(-5);
                Roach_RightMtrSpeed(-50);
            }
            break;

	//@Criss_Cross
	//This is just a short tank turn to the right to hopefully get parallel to the wall
        case Criss_Cross:
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_She_Cruzin;
            } else if (ThisEvent.EventType == PARALLEL_CLOSE) {
                GoTo_Vibe_Check;
            } else if (ThisEvent.EventType == PARALLEL_FAR) {
                GoTo_Straight_Pride;
            } else if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else if (ThisEvent.EventType == RL_BUMPER_HIT) {
                GoTo_Woah_Nelly;
            } else {
                TankTurn_R();
            }
            break;

	//@She_Cruzin
	//The most common state where the bot just moves forward and to the left
	//We're mostly looking for a left bumper event or a parallel close/far event
        case She_Cruzin:
            if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else if (ThisEvent.EventType == FR_BUMPER_HIT) {
                GoTo_RB_Reverse;
            } else if (ThisEvent.EventType == PARALLEL_CLOSE) {
                GoTo_Vibe_Check;
                Motors_Off();
            } else if (ThisEvent.EventType == PARALLEL_FAR) {
                GoTo_Straight_Pride;
            } else if (ThisEvent.EventType == RL_BUMPER_HIT) {
                GoTo_Woah_Nelly;
            } else if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_Quickie;
            } else {
                Roach_LeftMtrSpeed(30);
                Roach_RightMtrSpeed(55);
            }
            break;

	//@Woah_Nelly
	//This is the state we transition to whenever the back bumper is tripped
	//We just want to make another right left turn and then move to She_Cruzin
        case Woah_Nelly:
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_She_Cruzin;
            } else if (ThisEvent.EventType == FL_BUMPER_HIT) {
                GoTo_LB_Reverse;
            } else if (ThisEvent.EventType == PARALLEL_CLOSE) {
                GoTo_Vibe_Check;
            } else if (ThisEvent.EventType == PARALLEL_FAR) {
                GoTo_Straight_Pride;
            } else {
                Roach_LeftMtrSpeed(30);
                Roach_RightMtrSpeed(75);
            }
            break;

	//@Backup_Dat_Trunk
	//This catches errors where the bot trips another bumper event while the FR or C bumper is already tripped
	//In this case, we just want to full-reverse and reset
        case Backup_Dat_Trunk:
            if (ThisEvent.EventType == RL_BUMPER_HIT) {
                GoTo_Woah_Nelly;
            } else if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_Ramming_Speed;
            } else if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else {
                Roach_LeftMtrSpeed(-55);
                Roach_RightMtrSpeed(-55);
            }
            break;

	//@Ramming_Speed
	//After Backup_dat_trunk, we now just want to hopefully slam into the tower with the left bumper
        case Ramming_Speed:
            if (ThisEvent.EventType == FR_BUMPER_HIT) {
                GoTo_RB_Reverse;
            } else if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else {
                Roach_LeftMtrSpeed(25);
                Roach_RightMtrSpeed(55);
            }
            break;
		    
	//@Quickie
	//This is the state we transistion to from She_Cruzin when nothing happens for a while
	//Here we just do a quick tank turn left to hopfully trigger a bumper event
	//Also used to help turn around corners when we move away from the wall without a parallel far event
        case Quickie:
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_She_Cruzin;
            } else if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else {
                TankTurn_L_Fast();
            }
            break;

	//@Vibe_Check
	//This is where we check the EM Signal to ensure we found the right wall
	//The motors are turned off here
        case Vibe_Check:
            Motors_Off();
            switch (ThisEvent.EventType) {
                case ES_TIMEOUT:
                    if (VibeCheck() > EM_THRESHOLD) {
                        GoTo_Cha_Cha_Real_Smooth;
                        RunPingService(PingOffEvent);
                        ES_Timer_InitTimer(DISPENSE_TIMER, 300);
                    } else {
                        GoTo_Straight_Pride;
                    }
                    break;
                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    break;
                default:
                    break;
            }
            break;

	//@Cha_Cha_Real_Smooth
	//If we are on the right wall, then we Cha_Cha for a little bit
	//This state simply runs the RunLocateHoleHSM()
        case Cha_Cha_Real_Smooth:
            switch (ThisEvent.EventType) {
                case ES_TIMERACTIVE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == Generic_Timer) {
                        ES_Timer_InitTimer(Generic_Timer, 300);
                    }
                    break;
            }
            if (ThisEvent.EventType == BALL_DISPENSED) {
                GoTo_Entry;
            } else {
                RunLocateHoleHSM(ThisEvent, Ping_Flag);
            }
            break;

	//@Straight_Pride
	//The name of this state is meant to be ironic for its blatant stupidity
	//Here we determined we are on the wrong wall so we need to go straight until 
	//  the front ping sensor determines we are past the wall and then for an 
	//  empirically determined set amount of time so we can clear the wall and hopefully
	//  be parallel with the next side of the wall once we finish our turn
        case Straight_Pride:
            Roach_LeftMtrSpeed(63);
            Roach_RightMtrSpeed(65);

            if ((ThisEvent.EventType == PINGF_FAR) && (Mr_Flag == 0)) {
                ES_Timer_InitTimer(DANCING_TIMER, 190);
                Mr_Flag = 1;
            }
            
            if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
                Mr_Flag = 0;
            }

            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_Heterophobe;
                Mr_Flag = 0;
            }
            break;

	//@Heterophobe
	//Here we turn after clearing the left wall, waiting until we hit the next side of the wall on the left
	//This can be a dangerous state becaues if we don't hit the wall, we are basically lost 
		// D_Flip_Flop hopes to get us un-lost, but there are no promises
        case Heterophobe:
            if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_D_Flip_Flop;
            } else {
                Roach_LeftMtrSpeed(20);
                Roach_RightMtrSpeed(85);
            }
            break;

	//@D_Flip_Flop
	//If we don't hit a wall in Heterophobe, we have to try to find the wall again
	//So here, we just go and make foward-right maneuver to hopefully clear the wall or reorient ourselves
        case D_Flip_Flop:
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x7)) {
                GoTo_Heterophobe;
            }
            if ((ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT)) {
                GoTo_LB_Reverse;
            } else if (ThisEvent.EventType == FR_BUMPER_HIT) {
                GoTo_RB_Reverse;
            } else {
                Roach_LeftMtrSpeed(65);
                Roach_RightMtrSpeed(40);
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State


    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunDancingSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunDancingSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

uint16_t VibeCheck(void) {
    return (AD_ReadADPin(AD_PORTW7));
}
