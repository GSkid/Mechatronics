/*
 * File: LocateHoleHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel Elkaim and Soja-Marie Morgens
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is another template file for the SubHSM's that is slightly differet, and
 * should be used for all of the subordinate state machines (flat or heirarchical)
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
#include "Roach.h"
#include "AD.h"
#include "IO_Ports.h"
#include "TopLevelHSM.h"
#include "LocateHoleHSM.h" //#include all sub state machines called
#include "DrivingSubHSM.h"
#include "DancingSubHSM.h"
#include "ES_Timers.h"
#include "ES_Events.h"

#include <stdio.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do
#define BUFFER_TICKS 1900
#define RELOCATING_TICKS 20000
#define MINI_RELOCATING_TICKS 4250

#define BUMPER_EVENT ((ThisEvent.EventType == FR_BUMPER_HIT) || (ThisEvent.EventType == F_BUMPER_HIT) \
        || (ThisEvent.EventType == FL_BUMPER_HIT) || (ThisEvent.EventType == RL_BUMPER_HIT))

#define CLEAR_EVENT ThisEvent.EventType = ES_NO_EVENT;\
        ThisEvent.EventParam = 0
// The right motor should be connected to Y12 and the left motor should be 
// connected to Y10 according to the roach.c file

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/


typedef enum {
    InitPState,
    LocateBeaconInit,
    DriveBuffer,
    DriveToBeacon,
    ReLocating,
    Wandering,
    Dancing,
    DriveBuffer2,
    ReLocatingButLikeOnlyForThatOneCaseWhereShitJustIsntWorking,
} TopLevelHSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"LocateBeaconInit",
	"DriveBuffer",
	"DriveToBeacon",
	"ReLocating",
	"Wandering",
	"Dancing",
	"DriveBuffer2",
	"ReLocatingButLikeOnlyForThatOneCaseWhereShitJustIsntWorking",
};

enum {
    LEFT,
    RIGHT,
    NONE,
};
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine
 */
uint8_t TankTurn_R(void);
uint8_t TankTurn_L(void);
uint8_t TankTurn_R_Fast(void);
uint8_t TankTurn_L_Fast(void);
uint8_t Motors_Off(void);
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TopLevelHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;
static uint8_t tapeDirection = NONE;
static ES_Event An_Event;
static uint8_t Fire_Flag = 0;
static uint8_t Fire_Flag_Triggered = 0;
static uint8_t Transition_Flag = 0;
static uint8_t movingState = 0;
static uint8_t Mr_Frog = 0;

static uint8_t Tape_Flag = 0;
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTopLevelHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTopLevelHSM(uint8_t Priority) {
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    ES_Timer_Init();

    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTopLevelHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTopLevelHSM(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTopLevelHSM(ES_Event ThisEvent)
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
ES_Event RunTopLevelHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TopLevelHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack


    switch (CurrentState) {
        case InitPState: // If current state is initial Pseudo State
            if (ThisEvent.EventType == ES_INIT) {
                InitLocateHoleHSM(); //Initialize locate hole sub HSM
                InitDrivingSubHSM(); //Initialize the driving HSM
                InitDancingSubHSM(); //Initialize the dancing HSM
                AD_Init(); //Init all ES_Framework files

                //Add all the A/D Pins
                AD_AddPins(AD_PORTV6 | AD_PORTV7 | AD_PORTV8 | AD_PORTW3 | AD_PORTW7);
                //Turn off ping sensors
                An_Event.EventType = PING_OFF;
                PostPingService(An_Event);
                //Sets the next state
                nextState = LocateBeaconInit;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //consumes the event
            }
            break;

        case LocateBeaconInit:
            //Checks if the beacon has been found using the BeaconDetectorService file
            //This state should only be used to find the beacon for the first time as it 
            // goes to the buffer for the next state. Tape sensors will be inactive!!

            //Waits for a beacon found event
            //Otherwise we just TankTurn_L
            if (ThisEvent.EventType == BEACON_FOUND || ThisEvent.EventType == RL_BUMPER_RELEASED) {
                //sets the next state
                nextState = DriveToBeacon;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //consumes the event
                ES_Timer_InitTimer(Generic_Timer, BUFFER_TICKS); //sets the timer for the drive buffer
            } else {
                TankTurn_L();  
            }
            break;

        case DriveToBeacon:
            //Here we want to check for bumper events to tell us when we are at the tower
            //We also want to call the DrivingSubHSM to control how the bot moves
            //  according to the tape sensor inputs

            //Checks if the beacon signal is lost so it can transition to ReLocating
            //Also checks for bumper events to transition to dancing
            //Otherwise, just calls the DrivingSubHSM()
            RunDrivingSubHSM(ThisEvent, 0);

            //check for bumper events and transition to Dancing
            if (BUMPER_EVENT) {
                RunDancingSubHSM(ThisEvent);
                movingState = Dancing;
                Fire_Flag = 0;
                Transition_Flag = 1;
            }

            //Checks for tape events from the DrivingSubHSM, sets a flag when we hit a tape sensor, clears it after it is handled
            //Allows us to respond to tape sensor events without any interruptions
            if (ThisEvent.EventType == FIREWALKER) {
                Fire_Flag = 1;
                Fire_Flag_Triggered = 1;
            } else if (ThisEvent.EventType == FIREWALKER_CLR) {
                Fire_Flag = 0;
                CLEAR_EVENT;
            }

            //We want to respond to beacon lost events only when not responding to tape sensor events
            if (ThisEvent.EventType == BEACON_LOST) {
                if (Fire_Flag_Triggered == 0) {
                    movingState = ReLocating;
                    tapeDirection = RIGHT;
                    Transition_Flag = 1;
                } else if (Fire_Flag_Triggered == 1) {
                    movingState = Wandering;
                    Fire_Flag_Triggered = 0;
                    Transition_Flag = 1;
                    Mr_Frog = 0;
                }
            }

            //Waits for the tape sensor response to finish before transitioning
            if ((Fire_Flag == 0) && (Transition_Flag == 1)) {
                nextState = movingState;
                makeTransition = TRUE;
                Transition_Flag = 0;
                if (movingState == ReLocating) {
                    ES_Timer_InitTimer(Generic_Timer, RELOCATING_TICKS); //sets the timer for relocating
                }
                movingState = 0;
            }
            break;

        case ReLocating:
            //This is the state we transition to when we lose the beacon signal or 
            //  dispense a ping pong ball
            //We simply tank turn in a specific direction to find the beacon
            //If no beacon signal is found in time, we just go to wandering

            //check the tape direction to determine which way to turn (in case of hitting tape)
            if (tapeDirection == LEFT) {
                TankTurn_R();
            } else if (tapeDirection == RIGHT) {
                TankTurn_L();
            } else {
                TankTurn_R(); // should be opposite direction of that in the init locate beacon state
            }

            //check for bumper events and transition to Dancing
            if (BUMPER_EVENT) {
                RunDancingSubHSM(ThisEvent);
                nextState = Dancing;
                makeTransition = TRUE;
                CLEAR_EVENT;
            }

            //check for beacon signals
            if (ThisEvent.EventType == BEACON_FOUND) {
                nextState = DriveToBeacon;
                makeTransition = TRUE;
                CLEAR_EVENT;
            }

            //check for timeout event
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == Generic_Timer)) {
                nextState = Wandering;
                makeTransition = TRUE;
                Mr_Frog = 0;
                CLEAR_EVENT;
            }
            break;

        case Wandering:
            //This is what we want to do when we cannot detect the beacon for whatever reason

            
            //check for tape events
            if ((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 0x1)) {
                Mr_Frog = 1;
            } else if ((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 0x2)) {
                Mr_Frog = 2;
            }
            
            //Just start driving, man
            RunDrivingSubHSM(ThisEvent, Mr_Frog);

            //check for beacon signals
            if (ThisEvent.EventType == BEACON_FOUND) {
                nextState = DriveToBeacon;
                makeTransition = TRUE;
                CLEAR_EVENT;
            }

            //check bumper events
            if (BUMPER_EVENT) {
                RunDancingSubHSM(ThisEvent);
                nextState = Dancing;
                makeTransition = TRUE;
                CLEAR_EVENT;
            }
            break;

        case Dancing:
            //Calls the sub state machine that handles locating the hold and dispensing the balls
            //Resets back to ReLocating when the ball is dispensed, *does not consume event*
		    
	    //Call the subHSM to handle this process
            RunDancingSubHSM(ThisEvent);

	    //Once we are done, we move into DriveBuffer to get away from the tower
            if (ThisEvent.EventType == BALL_DISPENSED) {
                ES_Timer_InitTimer(Generic_Timer, BUFFER_TICKS);
                nextState = DriveBuffer;
                makeTransition = TRUE;
                CLEAR_EVENT;
            }
            break;

        case DriveBuffer:
            //This state should be the buffer period for meatrocket8 to get away from a beacon tower 

            //starts the bot in the reverse direction
            Roach_LeftMtrSpeed(-50);
            Roach_RightMtrSpeed(-50);

            //Checks for a timeout event to actually begin the relocating sequence
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == Generic_Timer)) {
                ES_Timer_InitTimer(Generic_Timer, RELOCATING_TICKS);
                tapeDirection = LEFT; // we want to start searching to the right so that we can almost guarantee we find a different beacon
                nextState = ReLocating; //sets the next state
                makeTransition = TRUE;
                CLEAR_EVENT;
            }
            
            //Checks if the bot hits the back tape sensor, this will direct it to go forward instead
            if (((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 4)) || ((ThisEvent.EventType == TAPE_SENSOR_CLR) && (ThisEvent.EventParam == 4))) {
                nextState = DriveBuffer2;
                makeTransition = TRUE;
                ES_Timer_InitTimer(Generic_Timer, 3000);
            }
            break;
            
        case DriveBuffer2:
            //This is where we go in the forward direction if we hit tape. 
            Roach_LeftMtrSpeed(55);
            Roach_RightMtrSpeed(54);
            
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == Generic_Timer) || (ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 1) || (ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 2)) {
                CLEAR_EVENT;
                nextState = ReLocatingButLikeOnlyForThatOneCaseWhereShitJustIsntWorking;
                makeTransition = TRUE;
                ES_Timer_InitTimer(Generic_Timer, MINI_RELOCATING_TICKS);
            }
            break;
            
        case ReLocatingButLikeOnlyForThatOneCaseWhereShitJustIsntWorking:
            
            TankTurn_R();

            //check for beacon signals
            if (ThisEvent.EventType == BEACON_FOUND) {
                nextState = DriveToBeacon;
                makeTransition = TRUE;
                CLEAR_EVENT;
            }

            //check for timeout event
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == Generic_Timer)) {
                ES_Timer_InitTimer(Generic_Timer, RELOCATING_TICKS);
                tapeDirection = RIGHT; // we want to start searching to the right so that we can almost guarantee we find a different beacon
                nextState = ReLocating; //sets the next state
                makeTransition = TRUE;
                CLEAR_EVENT;
            }
            break;
            
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTopLevelHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTopLevelHSM(ENTRY_EVENT); // <- rename to your own Run function
    }



    ES_Tail(); // trace call stack end
    return ThisEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
uint8_t TankTurn_R(void) {
    return ((Roach_LeftMtrSpeed(-30)) && (Roach_RightMtrSpeed(30)));
}

uint8_t TankTurn_L(void) {
    return ((Roach_LeftMtrSpeed(30)) && (Roach_RightMtrSpeed(-30)));
}

uint8_t TankTurn_R_Fast(void) {
    return ((Roach_LeftMtrSpeed(-60)) && (Roach_RightMtrSpeed(60)));
}

uint8_t TankTurn_L_Fast(void) {
    return ((Roach_LeftMtrSpeed(20)) && (Roach_RightMtrSpeed(-60)));
}

uint8_t Motors_Off(void) {
    return ((Roach_LeftMtrSpeed(0)) && (Roach_RightMtrSpeed(0)));
}
