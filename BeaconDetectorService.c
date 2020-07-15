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
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BeaconDetectorService.h"
#include <stdio.h>
#include "ES_Timers.h"
#include "TopLevelHSM.h"

#include "ES_Events.h"
#include "ES_CheckEvents.h"
#include "ES_General.h"
#include "ES_KeyboardInput.h"
#include "ES_Queue.h"
#include "ES_ServiceHeaders.h"
#include "ES_TattleTale.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BEACON_TIMER_SEEKING 10
#define BEACON_TIMER_DEBOUNCING 75
#define BEACON_INPUT AD_PORTV6
#define BEACON_THRESHOLD 700

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

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

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
uint8_t InitBeaconDetectorService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    ES_Timer_InitTimer(BEACON_TIMER, BEACON_TIMER_SEEKING);
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
uint8_t PostBeaconDetectorService(ES_Event ThisEvent) {
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
ES_Event RunBeaconDetectorService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static ES_EventTyp_t lastEvent = BEACON_LOST;
    static uint8_t debounceCounter = 0x0; //counter to reduce impacts of noise
    uint16_t detectorRead = 0x0; //beacon signal

    
    switch (ThisEvent.EventType) {
        case ES_INIT:
            ES_Timer_InitTimer(BEACON_TIMER, BEACON_TIMER_SEEKING);
          
            break;
        case ES_TIMERACTIVE:
        case ES_TIMERSTOPPED:
            break;
        case ES_TIMEOUT:
            //First read the IR beacon signal
            detectorRead = AD_ReadADPin(BEACON_INPUT);
            ThisEvent.EventType = ES_NO_EVENT;

            //Then we check the beacon signal strength to verify we did pick up on a tower
            //We also only want to post a single event, so we check if we previously did not have the beacon
            if ((detectorRead > BEACON_THRESHOLD) && (lastEvent == BEACON_LOST)) {
                //The signal goes through 3 cycles of debouncing before the signal is verified
                //This is to reduce the impacts of noise at the cost of response time
                if (debounceCounter == 0x0) {
                    debounceCounter++;
                    ES_Timer_InitTimer(BEACON_TIMER, BEACON_TIMER_DEBOUNCING);
                } else if (debounceCounter == 0x1) {
                    debounceCounter++;
                    ES_Timer_InitTimer(BEACON_TIMER, BEACON_TIMER_DEBOUNCING);
                } else if (debounceCounter == 0x2) {
                    debounceCounter = 0x0;
                    //Now we post the event to the top level
                    ReturnEvent.EventType = BEACON_FOUND;
                    lastEvent = BEACON_FOUND;
                    ES_Timer_InitTimer(BEACON_TIMER, 1);
                    PostTopLevelHSM(ReturnEvent);
                } else {
                    ES_Timer_InitTimer(BEACON_TIMER, 1);
                }
            } 
            //We also check if the beaon signal is below the threshold to see if we lost the beacon signal
            //This assumes we previously were detecting the beacon
            else if ((detectorRead < BEACON_THRESHOLD) && (lastEvent == BEACON_FOUND)) {
                ReturnEvent.EventType = BEACON_LOST;
                lastEvent = BEACON_LOST;
                ES_Timer_InitTimer(BEACON_TIMER, 1);
                PostTopLevelHSM(ReturnEvent);
            } else {
                ES_Timer_InitTimer(BEACON_TIMER, 1);
              
            }
            break;
    }
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

