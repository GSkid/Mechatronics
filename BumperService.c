/*
 * File: TemplateService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Timers.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BumperService.h"
#include "IO_Ports.h"
#include <stdio.h>
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define BUMPER_DELAY 5 // 5 ms as delay to run 200 times per 1000 ms?
#define FRONT_RIGHT_BUMPER PORTZ03_BIT
#define FRONT_BUMPER       PORTZ04_BIT
#define FRONT_LEFT_BUMPER  PORTZ05_BIT
#define REAR_LEFT_BUMPER   PORTZ06_BIT


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */

static uint8_t MyPriority;
static uint8_t measuredState;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

uint8_t ReadBumpers(void);

/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitBumperService(uint8_t Priority) {
    ES_Event ThisEvent;
    MyPriority = Priority;

    // initialization code
    ES_Timer_InitTimer(BUMPER_TIMER, BUMPER_DELAY);

    PORTZ03_TRIS = 1;
    PORTZ04_TRIS = 1;
    PORTZ05_TRIS = 1;
    PORTZ06_TRIS = 1;

    measuredState = 0x0;

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostBumperService(ES_Event ThisEvent) {
    //printf(" %i", ThisEvent.EventType);
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunBumperService(ES_Event ThisEvent) {
    //    ES_Event ReturnEvent;
    //    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    // run motors backward as result of service?
    static uint32_t lastStates;
    ES_EventTyp_t curEvent;
    ES_Event returnEvent;
    uint8_t i;
    uint8_t thisState = ReadBumpers();
    uint8_t mask;
    uint8_t stateChanges;

    returnEvent.EventType = ThisEvent.EventType;

    switch (ThisEvent.EventType) {
        case ES_INIT:
            // This section is used to reset service for some reason
            break;
        case ES_TIMERACTIVE:
        case ES_TIMERSTOPPED:
            break;
        case ES_TIMEOUT:

            stateChanges = measuredState ^ thisState; // check for any changed states, xor toggles each bit

            lastStates = lastStates << 1; // shift over bitstream
            lastStates &= 0xFEfeFEfe; // clear space for the next readings

            for (i = 0; i < 4; i++) { // for each of the buttons
                lastStates |= ((thisState >> i) & 0x01) << (8 * i); // add each of the new button readings to the bitstream
                if (stateChanges & (0x01 << i)) { // only check if this button does not match its recorded state
                    mask = (lastStates & (0xFF << (8 * i))) >> (8 * i); // mask each of the button's individual bitstreams
                    if (mask == 0b01111111) { // button pressed event
                        curEvent = FR_BUMPER_HIT + i;
                        measuredState |= 0x01 << i; // update the recorded state
                    } else if (mask == 0b10000000) { // button released event
                        curEvent = FR_BUMPER_RELEASED + i;
                        measuredState &= ~(0x01 << i);
                    } else continue;

                    returnEvent.EventType = curEvent;
                    returnEvent.EventParam = measuredState;
                    PostBumperService(returnEvent);
                    PostTopLevelHSM(returnEvent); // for part 8
                }
            }
            ES_Timer_InitTimer(BUMPER_TIMER, BUMPER_DELAY); //reset the timer so we continually check the bumpers
            break;
    }
    return returnEvent;
}

uint8_t ReadBumpers(void) {
    //printf("%i %i %i %i\r\n", FRONT_RIGHT_BUMPER, FRONT_BUMPER, FRONT_LEFT_BUMPER, REAR_LEFT_BUMPER);
    return ( 0xFF & (FRONT_RIGHT_BUMPER | (FRONT_BUMPER << 1) | (FRONT_LEFT_BUMPER << 2) | (REAR_LEFT_BUMPER << 3)));
}


/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/
