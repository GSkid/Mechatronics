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
#include "IO_Ports.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TapeSensorService.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define FRONT_LEFT_SENSOR AD_PORTV7
#define FRONT_RIGHT_SENSOR AD_PORTV8
#define BACK_SENSOR AD_PORTW3
#define TAPE_SENSOR_TICKS 5
#define WAIT_TIME 4
#define DEBOUNCE_THRESHOLD 50
#define TAPE_THRESHOLD 200

enum {
    OFF_TAPE,
    ON_TAPE,
};
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

static uint8_t MyPriority; //used for event handling
static uint8_t sunnyRead_FL = 0x0; //front left first reading
static uint8_t sunnyRead_FR = 0x0; //front right first reading
static uint8_t sunnyRead_B = 0x0; //back first reading
static uint8_t cloudyRead_FL = 0x0; //front left second reading
static uint8_t cloudyRead_FR = 0x0; //front right second reading
static uint8_t cloudyRead_B = 0x0; //back second reading
static uint8_t tapeTracker_FL = OFF_TAPE; //keeps track of where the bot is (FL)
static uint8_t tapeTracker_FR = OFF_TAPE; //keeps track of where the bot is (FR)
static uint8_t tapeTracker_B = OFF_TAPE; //keeps track of where the bot is (B)

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
uint8_t InitTapeSensorService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;
    //ES_Timer_InitTimer(TAPE_SENSOR_TIMER, TAPE_SENSOR_TICKS); // sets a short timer
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
uint8_t PostTapeSensorService(ES_Event ThisEvent) {
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
ES_Event RunTapeSensorService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static uint8_t readCounter = 0x0;

    switch (ThisEvent.EventType) {
        case ES_INIT:
            ES_Timer_InitTimer(TAPE_SENSOR_TIMER, TAPE_SENSOR_TICKS); // sets a short timer
            break;
        case ES_TIMERACTIVE:
        case ES_TIMERSTOPPED:
            break;
        case ES_TIMEOUT: 
            
            /*
            The statemachine waits for a timeout event, then reads the sensor output
            and once it has read the value twice, it checks to see if the difference between
            the reading with the LEDs on and LEDs is high or low
            */
            
            if (readCounter == 0x0) {
                sunnyRead_FL = AD_ReadADPin(FRONT_LEFT_SENSOR); //reads tape sensor FL
                sunnyRead_FR = AD_ReadADPin(FRONT_RIGHT_SENSOR); //reads tape sensor Fr
                sunnyRead_B = AD_ReadADPin(BACK_SENSOR); //reads tape sensor B
                readCounter++;
                ES_Timer_InitTimer(TAPE_SENSOR_TIMER, TAPE_SENSOR_TICKS); // sets a short timer
            } 
            
            else if (readCounter = 0x1) {
                cloudyRead_FL = AD_ReadADPin(FRONT_LEFT_SENSOR); //reads tape sensor FL
                cloudyRead_FR = AD_ReadADPin(FRONT_RIGHT_SENSOR); //reads tape sensor FR
                cloudyRead_B = AD_ReadADPin(BACK_SENSOR); //reads tape sensor B
                readCounter = 0x0;
                ES_Timer_InitTimer(TAPE_SENSOR_TIMER, WAIT_TIME); // sets a longer timer
                
                //Checks the front left tape sensor
                if ((sunnyRead_FL - cloudyRead_FL) < DEBOUNCE_THRESHOLD) { //this checks if we got a tape event on the FL sensor
                    //First checks if the bot moved off tape --> on tape
                    if ((sunnyRead_FL > TAPE_THRESHOLD) && (tapeTracker_FL == OFF_TAPE)) {
                        tapeTracker_FL = ON_TAPE;
                        ReturnEvent.EventType = TAPE_SENSOR_TRIPPED;
                        ReturnEvent.EventParam = 0x1;
                        PostTopLevelHSM(ReturnEvent);
                    } 
                    //Then checks if the bot moved on tape --> off tape
                    else if ((sunnyRead_FL < TAPE_THRESHOLD) && (tapeTracker_FL == ON_TAPE)) {
                        tapeTracker_FL = OFF_TAPE;
                        ReturnEvent.EventType = TAPE_SENSOR_CLR;
                        ReturnEvent.EventParam = 0x1;
                        PostTopLevelHSM(ReturnEvent);
                    }
                }
                
                //Checks the front right tape sensor
                if ((sunnyRead_FR - cloudyRead_FR) < DEBOUNCE_THRESHOLD) { //this checks if we got a tape event on the FR sensor
                    //First checks if the bot moved off tape --> on tape
                    if ((sunnyRead_FR > TAPE_THRESHOLD) && (tapeTracker_FR == OFF_TAPE)) {
                        tapeTracker_FR = ON_TAPE;
                        ReturnEvent.EventType = TAPE_SENSOR_TRIPPED;
                        ReturnEvent.EventParam = 0x2;
                        PostTopLevelHSM(ReturnEvent);
                    } 
                    //Then checks if the bot moved on tape --> off tape
                    else if ((sunnyRead_FR < TAPE_THRESHOLD) && (tapeTracker_FR == ON_TAPE)) {
                        tapeTracker_FR = OFF_TAPE;
                        ReturnEvent.EventType = TAPE_SENSOR_CLR;
                        ReturnEvent.EventParam = 0x2;
                        PostTopLevelHSM(ReturnEvent);
                    }
                }
                
                //Checks the back tape sensor
                if ((sunnyRead_B - cloudyRead_B) < DEBOUNCE_THRESHOLD) { //this checks if we got a tape event on the B sensor
                    //First checks if the bot moved off tape --> on tape
                    if ((sunnyRead_B > TAPE_THRESHOLD) && (tapeTracker_B == OFF_TAPE)) {
                        tapeTracker_B = ON_TAPE;
                        ReturnEvent.EventType = TAPE_SENSOR_TRIPPED;
                        ReturnEvent.EventParam = 0x4;
                        PostTopLevelHSM(ReturnEvent);
                    } 
                    //Then checks if the bot moved on tape --> off tape
                    else if ((sunnyRead_B < TAPE_THRESHOLD) && (tapeTracker_B == ON_TAPE)) {
                        tapeTracker_B = OFF_TAPE;
                        ReturnEvent.EventType = TAPE_SENSOR_CLR;
                        ReturnEvent.EventParam = 0x4;
                        PostTopLevelHSM(ReturnEvent);
                    }
                }
            }
            
            //Reset if the read counter got messed up
            else {
               readCounter = 0x0;   
            }
            break;
    }
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

