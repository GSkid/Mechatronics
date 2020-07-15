/*
 * File: TemplateSubHSM.c
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
#include "ES_Timers.h"
#include "BOARD.h"
#include "TopLevelHSM.h"
#include "DrivingSubHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    Forward,
    L_Turning,
    R_Turning,
    Reversing,
    Uturn,
} DrivingSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Forward",
	"L_Turning",
	"R_Turning",
	"Reversing",
	"Uturn",
};


#define DRIVING_TICKS 350
#define U_TURN_TICKS 2700
#define DIRECTION_R 
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static DrivingSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static R_Tape_Flag = 0x0; //tracks the status of the FR tape sensor
static L_Tape_Flag = 0x0; //tracks the status of the FL tape sensor
static B_Tape_Flag = 0x0; //tracks the status of the B tape sensor
static TimeoutFlag = 0x0;
static ES_Event AnEvent;


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
uint8_t InitDrivingSubHSM(void) {
    ES_Event returnEvent;
    //sets driving pins to outputs

    CurrentState = InitPSubState;
    returnEvent = RunDrivingSubHSM(INIT_EVENT, 0);
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
ES_Event RunDrivingSubHSM(ES_Event ThisEvent, int Lost_Flag) {
    uint8_t makeTransition = FALSE; // use to flag transition
    DrivingSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

	
    /* The purpose of this state machine is to maneuver the bot to the tower and avoid tape,
    staying on the battlefield due to inputs from the tape sensors*/
	
    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

	//Here we just want to drive forward
	//However, we can drive in a specific direction is told to do so based on previous tape sensor events
	//  so that we can get around the tape in the middle of the battlefield
        case Forward:
            if (Lost_Flag == 1) {
                Roach_LeftMtrSpeed(50);
                Roach_RightMtrSpeed(80);
            } else if (Lost_Flag == 2) {
                Roach_LeftMtrSpeed(80);
                Roach_RightMtrSpeed(50);
            } else {
                Roach_LeftMtrSpeed(70);
                Roach_RightMtrSpeed(70);
            }

            if (ThisEvent.EventType == TAPE_SENSOR_TRIPPED) {
		//Post this event to the top-level so it knows we lost the beacon
                AnEvent.EventType = FIREWALKER;
                PostTopLevelHSM(AnEvent);
		    
		// checks for a left tape sensor tripped event
                if (ThisEvent.EventParam == 0x1) {
                    L_Tape_Flag = 0x1;
                    ThisEvent.EventType = ES_NO_EVENT;
                    ThisEvent.EventParam = 0x0;
                    nextState = L_Turning;
                    makeTransition = TRUE;
                    ES_Timer_InitTimer(DRIVING_TIMER, DRIVING_TICKS);
                } 
                // checks for a right tape sensor tripped event
		else if (ThisEvent.EventParam == 0x2) {
                    R_Tape_Flag = 0x1;
                    ThisEvent.EventType = ES_NO_EVENT;
                    ThisEvent.EventParam = 0x0;
                    nextState = R_Turning;
                    makeTransition = TRUE;
                    ES_Timer_InitTimer(DRIVING_TIMER, DRIVING_TICKS);
                }
            }
            break;
		    
	//Here we reverse to the back-left to avoid tape on the left
        case L_Turning:
            Roach_LeftMtrSpeed(-35);
            Roach_RightMtrSpeed(-90);
		    
            // checks for a right tape sensor clear event
            if ((ThisEvent.EventType == TAPE_SENSOR_CLR) && (ThisEvent.EventParam == 0x1)) {
                L_Tape_Flag = 0x0;
                ThisEvent.EventType = ES_NO_EVENT;
                ThisEvent.EventParam = 0x0;
            }
		    
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x5)) {
                TimeoutFlag = 0x1;
            }
		    
	    // Checks for a timeout event or back tape sensor trigger as well as a right tape sensor clear event
            if ((TimeoutFlag || ((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 0x4))) && (L_Tape_Flag == 0x0)) {
		//Here we clear the firewalker flag and let the top level know
                AnEvent.EventType = FIREWALKER_CLR;
                PostTopLevelHSM(AnEvent);
                nextState = Forward;
                makeTransition = TRUE;
                TimeoutFlag = 0x0;
                L_Tape_Flag = 0x0;
                ThisEvent.EventType = ES_NO_EVENT;
                ThisEvent.EventParam = 0x0;
            } 
	    //If we are moving back-left and trip the right tape sensor, then we go into a full reverse	    
	    else if ((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 0x2)) {
                ES_Timer_InitTimer(DRIVING_TIMER, DRIVING_TICKS);
                nextState = Reversing;
                makeTransition = TRUE;
                TimeoutFlag = 0x0;
                L_Tape_Flag = 0x0;
                ThisEvent.EventType = ES_NO_EVENT;
                ThisEvent.EventParam = 0x0;
            }
            break;
		    
	//This is basically identical to the previous state but swapped for the right tape sensor
        case R_Turning:
            Roach_LeftMtrSpeed(-90);
            Roach_RightMtrSpeed(-35);
		    
            // checks for a right tape sensor clear event
            if ((ThisEvent.EventType == TAPE_SENSOR_CLR) && (ThisEvent.EventParam == 0x2)) {
                R_Tape_Flag = 0x0;
                ThisEvent.EventType = ES_NO_EVENT;
                ThisEvent.EventParam = 0x0;
            }
		    
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == 0x5)) {
                TimeoutFlag = 0x1;
            }
		    
	    // Checks for a timeout event or back tape sensor trigger as well as a right tape sensor clear event	    
            if ((TimeoutFlag || ((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 0x4))) && (R_Tape_Flag == 0x0)) {
                AnEvent.EventType = FIREWALKER_CLR;
                PostTopLevelHSM(AnEvent);
                nextState = Forward;
                makeTransition = TRUE;
                TimeoutFlag = 0x0;
                R_Tape_Flag = 0x0;
                ThisEvent.EventType = ES_NO_EVENT;
                ThisEvent.EventParam = 0x0;
            }
	    //If we are moving back-right and trip the left tape sensor, then we go into a full reverse
	    else if ((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 0x1)) {
                TimeoutFlag = 0x0;
                ES_Timer_InitTimer(DRIVING_TIMER, DRIVING_TICKS);
                R_Tape_Flag = 0x0;
                nextState = Reversing;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                ThisEvent.EventParam = 0x0;
            }
            break;
		    
	//This is a full reverse if both tape sensors are tripped at the same time
        case Reversing:
            Roach_LeftMtrSpeed(-70);
            Roach_RightMtrSpeed(-70);
            if (((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 0x4)) || (ThisEvent.EventType == ES_TIMEOUT)) {
                ES_Timer_InitTimer(DRIVING_TIMER, U_TURN_TICKS);
                nextState = Uturn;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                ThisEvent.EventParam = 0x0;
            }
            break;
		    
	// After our full reverse, we u-turn to go in the opposite direction
        case Uturn:
            TankTurn_L_Fast();
            if (((ThisEvent.EventType == TAPE_SENSOR_TRIPPED) && (ThisEvent.EventParam == 0x4)) || (ThisEvent.EventType == ES_TIMEOUT)) {
                AnEvent.EventType = FIREWALKER_CLR;
                PostTopLevelHSM(AnEvent);
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                ThisEvent.EventParam = 0x0;
            }
            break;
		    
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunDrivingSubHSM(EXIT_EVENT, Lost_Flag); // <- rename to your own Run function
        CurrentState = nextState;
        RunDrivingSubHSM(ENTRY_EVENT, Lost_Flag); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

