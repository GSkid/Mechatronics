/*
 * File: LocateHoleHSM.c
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
#include "LocateHoleHSM.h"
#include "serial.h"
#include "IO_Ports.h"
#include "AD.h"
#include "ES_Timers.h"
#include <stdio.h>
#include "PingService.h"
#include "DancingSubHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    Dance,
    SquirtingDatSweetSlime,
    Ride_At_Dawn,
    Retreat,
    Give_Me_A_Sec,
} LocateHoleHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Dance",
	"SquirtingDatSweetSlime",
	"Ride_At_Dawn",
	"Retreat",
	"Give_Me_A_Sec",
};

typedef enum {
    Init,
    Rest1,
    Back,
    Rest2,
    Forward,
} JiggleWidIt;


#define sec_2 2500
#define msec_300 300

#define TAPE_SENSOR_LEFT PORTV03_BIT
#define TAPE_SENSOR_CENTER PORTV04_BIT
#define TAPE_SENSOR_RIGHT PORTV05_BIT
#define TAPE_THRESHOLD 600
#define ALL_TAPE_SENSORS 0b00111000
#define LEFT_SHOOTER 0b00001000  //PortW4
#define CENTER_SHOOTER 0b00010000 //PortW5
#define RIGHT_SHOOTER 0b00100000 //PortW6
#define RETREAT_TICKS 650


#define GoTo_Ride_At_Dawn nextState = Ride_At_Dawn;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DISPENSE_TIMER, 1);\
                JiggleLength = 1;\
                JiggleState = Rest1
#define GoTo_Retreat nextState = Retreat;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DISPENSE_TIMER, RETREAT_TICKS)
#define GoTo_Squirting_Dat_Sweet_Slime nextState = SquirtingDatSweetSlime;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DISPENSE_TIMER, sec_2)
#define GoTo_Give_Me_A_Sec nextState = Give_Me_A_Sec;\
                makeTransition = TRUE;\
                ES_Timer_InitTimer(DISPENSE_TIMER, 500)
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

static LocateHoleHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static JiggleWidIt JiggleState = Init;
static int JiggleLength = 1;
static int JiggleCount = 0;
static uint8_t MyPriority;
static Tape_Flag = 0;
static Ping_Flag = 0;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitLocateHoleHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitLocateHoleHSM(void) {
    ES_Event returnEvent;
    PORTV03_TRIS = 1;
    PORTV04_TRIS = 1;
    PORTV05_TRIS = 1;

    PORTW04_TRIS = 0;
    PORTW05_TRIS = 0;
    PORTW06_TRIS = 0;

    PORTW04_LAT = 0;
    PORTW05_LAT = 0;
    PORTW06_LAT = 0;
    CurrentState = InitPSubState;


    returnEvent = RunLocateHoleHSM(INIT_EVENT, 0);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunLocateHoleHSM(ES_Event ThisEvent)
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
ES_Event RunLocateHoleHSM(ES_Event ThisEvent, uint8_t Ping_Param) {
    uint8_t makeTransition = FALSE; // use to flag transition
    LocateHoleHSMState_t nextState; // <- change type to correct enum
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                IO_PortsClearPortBits(PORTW, ALL_TAPE_SENSORS);
                ES_Timer_InitTimer(DISPENSE_TIMER, msec_300);
                nextState = Dance;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Dance:
            switch (ThisEvent.EventType) {
                case ES_INIT:
                    break;
                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    Tape_Flag = TAPE_SENSOR_CENTER << 1; // TAPE_SENSOR_LEFT << 2 | | TAPE_SENSOR_RIGHT
                    Ping_Flag = Ping_Param;

                    //                    printf("Tape: %i\r\n", Tape_Flag);
                    if (Tape_Flag == 0b100) { //Left Tape Sensor    
                        GoTo_Ride_At_Dawn;
                        JiggleState = Init;
                    } else if (Tape_Flag == 0b010) { //Center Tape Sensor    
                        GoTo_Ride_At_Dawn;
                        JiggleState = Init;
                    } else if (Tape_Flag == 0b001) { //Right Tape Sensor    
                        GoTo_Ride_At_Dawn;
                        JiggleState = Init;
                    } else if (ThisEvent.EventParam == DISPENSE_TIMER) {
                        switch (JiggleState) {
                            case Init:
                                ES_Timer_InitTimer(DISPENSE_TIMER, 50);
                                if (Ping_Flag == 1) {
                                    TankTurn_R();
                                } else if (Ping_Flag == 2) {
                                    TankTurn_L();
                                } else {
                                    Roach_LeftMtrSpeed(0);
                                    Roach_RightMtrSpeed(0);
                                }
                                JiggleState = Rest1;
                                break;
                                
                            case Rest1:
                                ES_Timer_InitTimer(DISPENSE_TIMER, 100);
                                Roach_LeftMtrSpeed(0);
                                Roach_RightMtrSpeed(0);
                                JiggleState = Forward;
                                break;

                            case Forward:
                                JiggleCount++;
                                ES_Timer_InitTimer(DISPENSE_TIMER, 3);
                                Roach_LeftMtrSpeed(29);
                                Roach_RightMtrSpeed(30);
                                if (JiggleCount >= JiggleLength * 11) {
                                    JiggleState = Rest2;
                                    JiggleLength += 1;
                                    JiggleCount = 0;
                                }
                                break;

                            case Rest2:
                                ES_Timer_InitTimer(DISPENSE_TIMER, 100);
                                Roach_LeftMtrSpeed(0);
                                Roach_RightMtrSpeed(0);
                                JiggleState = Back;
                                break;

                            case Back:
                                JiggleCount++;
                                ES_Timer_InitTimer(DISPENSE_TIMER, 3);
                                Roach_LeftMtrSpeed(-25);
                                Roach_RightMtrSpeed(-25);
                                if (JiggleCount >= JiggleLength * 10) {
                                    JiggleState = Rest1;
                                    JiggleLength += 1;
                                    JiggleCount = 0;
                                }
                                break;
                        }
                    } else {
                        ES_Timer_InitTimer(Generic_Timer, 5);
                    }
                    break;
            }
            break;


        case Ride_At_Dawn:
            Roach_LeftMtrSpeed(23);
            Roach_RightMtrSpeed(22);
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == DISPENSE_TIMER)) {

                printf("Tape: %i\r\n", Tape_Flag);
                ES_Timer_InitTimer(DISPENSE_TIMER, 1);
                if (Tape_Flag == 0b100) {
                    if (!TAPE_SENSOR_LEFT) {
                        GoTo_Retreat;
                    }
                } else if (Tape_Flag == 0b010) {
                    if (!TAPE_SENSOR_CENTER) {
                        GoTo_Retreat;
                    }
                } else if (Tape_Flag == 0b001) {
                    if (!TAPE_SENSOR_RIGHT) {
                        GoTo_Retreat;
                    }
                }
            }
            break;


        case Retreat:
            Roach_LeftMtrSpeed(-24);
            Roach_RightMtrSpeed(-24);
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == DISPENSE_TIMER)) {
                Motors_Off();
                GoTo_Give_Me_A_Sec;
            }
            break;

        case Give_Me_A_Sec:
            Motors_Off();
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == DISPENSE_TIMER)) {
                GoTo_Squirting_Dat_Sweet_Slime;
                if (Tape_Flag == 0b100) {
                    PORTW04_LAT = 1;
                } else if (Tape_Flag == 0b010) {
                    PORTW05_LAT = 1;
                } else if (Tape_Flag == 0b001) {
                    PORTW06_LAT = 1;
                }
                Tape_Flag = 0;
            }
            break;

        case SquirtingDatSweetSlime: // 
            Motors_Off();
            if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == DISPENSE_TIMER)) {
                // initiate the ping sensor
                //ES_Timer_InitTimer(PING_TIMER, 1);

                PORTW04_LAT = 0;
                PORTW05_LAT = 0;
                PORTW06_LAT = 0;
                ES_Timer_InitTimer(DISPENSE_TIMER, sec_2);
                nextState = Dance;
                makeTransition = TRUE;
                ThisEvent.EventType = BALL_DISPENSED;
                //                RunDancingSubHSM(ThisEvent);
                PostTopLevelHSM(ThisEvent);
            }
            break;

    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunLocateHoleHSM(EXIT_EVENT, 0); // <- rename to your own Run function
        CurrentState = nextState;
        RunLocateHoleHSM(ENTRY_EVENT, 0); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

