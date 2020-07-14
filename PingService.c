/*
 * File: PingService.h
 * Author: J. Edward Carryer
 * Modified: cHOL GRUNT
 *
 * Ping file to set up a simple service to work with the Events and Services
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
#include <peripheral/timer.h>
#include "IO_Ports.h"
#include "ES_Timers.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PingService.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define ECHOpin1 PORTDbits.RD10     //Y06     //PORTDbits.RD8  // PortZ-08
#define ECHOpin2 PORTDbits.RD9      //Y08     // PortY-08
#define TRIG1 LATDbits.LATD5        //Y05     //LATEbits.LATE2    // PortZ-07
#define TRIG2 LATEbits.LATE7        //Y07     //LATEbits.LATE7    // PortY-07

#define NUM_SAMPLEZ 3 // 10
#define MAP1 767
#define MAP2 710
#define OFFSET1 -2125
#define OFFSET2 -2084
#define DIVISION 10

#define UPPER_THRESHOLD 200
#define LOWER_THRESHOLD 34 //38
#define PARALLEL_THRESHOLD 3 // 6
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
//static ES_Event controllerState;

typedef enum {
    TRIGGER1,
    TRIGGER2,
    ECHO1a,
    ECHO2a,
    ECHO1b,
    ECHO2b,
    OFF,
} PingState;


static ES_Event lastState; 
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitPingService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunPingService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitPingService(uint8_t Priority) {
    ES_Event ThisEvent;
    MyPriority = Priority;

   //Tristate registers for ping sensors (setting IO)
    PORTY08_TRIS = 1;
    PORTY06_TRIS = 1;
    PORTY07_TRIS = 0;
    PORTY05_TRIS = 0;

   //Triggers to tell when to send the pulses
    TRIG1 = 0;
    TRIG2 = 0;

   //Setting the uno32 timer3
    OpenTimer3(T3_ON | T3_PS_1_32, (BOARD_GetPBClock()));
    T3CON = 0x8030; // turn timer 2 on
    PR3 = 0xFFFF;
    //T3CON = 0x8000; // turn timer 3 on (for 32 bit mode)

    //Initializing the IC's
    IC3CON = 0b0000001000000110; // initialize the input capture on pin Z7
    IC2CON = 0b0000001000000110; // initialize the input capture on pin Y6

    
    lastState.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostPingService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostPingService(ES_Event ThisEvent) {
    //    printf("%d ", ThisEvent.EventType);
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunPingService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunPingService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    static unsigned int ping1Avg = 0, ping2Avg = 0;
    static uint8_t ping1Samplez = 0, ping2Samplez = 0;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static PingState daState = OFF;
    static int echoEdge = 0;
    static uint16_t PingF_Read = 0;
    static uint16_t PingB_Read = 0;
    static uint16_t PingF_Param = 0;
    static uint16_t PingB_Param = 0;
   
    //This will turn on the ping sensors to bypass the PING_OFF return catch
    if (ThisEvent.EventType == PING_ON) {
        lastState.EventType = PING_ON;
    } 
    
    //Will turn off the ping sensors until the next PING_ON event
    if (lastState.EventType == PING_OFF) {
        return ReturnEvent;
    }
    
    //Top Level State Machine
    switch (ThisEvent.EventType) {
        //Catches any non-event type passes
        case ES_INIT:
            break;

        //Resets and turns off the ping sensors until we turn them back on
        case PING_OFF:
            lastState.EventType = PING_OFF;
            ping1Avg = 0, ping2Avg = 0;
            ping1Samplez = 0, ping2Samplez = 0;
            ES_Timer_StopTimer(PING_TIMER);
            break;

        //Readies for the first ping sensor reading
        case PING_ON:
            ThisEvent.EventType = NEW_PING1;
            PostPingService(ThisEvent);
            break;

        //Resets the trigger and input capture 3 to get a new reading
        //Also starts the timer
        case NEW_PING1:
            TRIG1 = 1;
            IC3CON &= 0x7FFF;
            ES_Timer_InitTimer(PING_TIMER, 1);
            daState = TRIGGER1;
            break;

        //Resets the trigger and input capture 2 to get a new reading
        //Also starts the timer
        case NEW_PING2:
            TRIG2 = 1;
            IC2CON &= 0x7FFF;
            ES_Timer_InitTimer(PING_TIMER, 1);
            daState = TRIGGER2;
            break;

        //On timer elapse, we want to read and calculate distance for each sensor
        case ES_TIMEOUT:
            if (ThisEvent.EventParam == PING_TIMER) {
                switch (daState) {
                    //Ping sensor 1 resets
                    //First reset the timer and ic, then triggers the pulse
                    case TRIGGER1:
                        ES_Timer_InitTimer(PING_TIMER, 1);
                        TMR3 = 0x0000; // reset the timers
                        IC3CON |= 0x8000; // restart input capture
                        TRIG1 = 0;
                        daState = ECHO1a;
                        break;
                      
                    //Sets the starting time for the ping once the pulse is sent
                    case ECHO1a:
                        ES_Timer_InitTimer(PING_TIMER, 1);
                        if (IC3CON & 0x8) {
                            daState = ECHO1b;
                            echoEdge = IC3BUF;
                        }
                        break;
                      
                    //Records total elapsed time and determines distance
                    //Generates events based on measured distances
                    case ECHO1b:
                        ES_Timer_InitTimer(PING_TIMER, 5);
                        //Checking for input capture to be high (indicating we received the pulse bounce-back)
                        if (IC3CON & 0x8) {
                            PingF_Read = IC3BUF - echoEdge; //calculating distance
                            ping1Avg += (PingF_Read * DIVISION + OFFSET1) / MAP1; //mapping to distance in cm
                            ping1Samplez++; // incrementing for our simple averaging filter
                            if (ping1Samplez >= NUM_SAMPLEZ) {
                                PingF_Param = ping1Avg / NUM_SAMPLEZ; //averaging filter to remove potential noise
                                if (PingF_Param >= UPPER_THRESHOLD) {
                                    ReturnEvent.EventType = PINGF_FAR;
                                    ReturnEvent.EventParam = PingF_Param;
                                    PingF_Param = 0;
                                    PostTopLevelHSM(ReturnEvent);
                                }
                                ping1Samplez = 0;
                                ping1Avg = 0;
                            }
                            //Goes to next ping sensor once this one completes
                            ReturnEvent.EventType = NEW_PING2;
                            PostPingService(ReturnEvent);
                        }
                        break;

                    //Ping sensor 2 resets
                    case TRIGGER2:
                        ES_Timer_InitTimer(PING_TIMER, 1);
                        IC2CON |= 0x8000; // restart input capture 1
                        TRIG2 = 0;
                        daState = ECHO2a;
                        break;
                      
                    //Triggers the pulse and records starting time
                    case ECHO2a:
                        ES_Timer_InitTimer(PING_TIMER, 1);
                        if (IC2CON & 0x8) {
                            daState = ECHO2b;
                            echoEdge = IC2BUF;
                        }
                        break;
                      
                    //Same as ping sensor one but with more event checking
                    case ECHO2b:
                        ES_Timer_InitTimer(PING_TIMER, 5);
                        if (IC2CON & 0x8) { //waiting for ping bounceback
                            PingB_Read = IC2BUF - echoEdge; //recording total time
                            ping2Avg += (PingB_Read * DIVISION + OFFSET2) / MAP2; //mapping to cm
                            ping2Samplez++;

                            if (ping2Samplez >= NUM_SAMPLEZ) {
                                PingB_Param = ping2Avg / NUM_SAMPLEZ; //averaging filter
                                if (PingB_Param >= UPPER_THRESHOLD) { //checking far event
                                    ReturnEvent.EventType = PINGB_FAR;
                                    ReturnEvent.EventParam = PingB_Param;
                                    PostTopLevelHSM(ReturnEvent);
                                    PingB_Param = 0;
                                } 
                               //First we check to see if both ping sensors report similar, short distances (eg. close to a wall)
                               else if ((abs(PingF_Param - PingB_Param) <= PARALLEL_THRESHOLD) && (((PingF_Param + PingB_Param) / 2) <= LOWER_THRESHOLD)) {
                                    ReturnEvent.EventType = PARALLEL_CLOSE;
                                    //Next we determine which ping sensor is actually closer so we know how to maneuver around the wall
                                    if (PingF_Param > PingB_Param) { //Front further than back
                                        ReturnEvent.EventParam = 1;
                                    } else if (PingF_Param < PingB_Param) { //Front closer than back
                                        ReturnEvent.EventParam = 2;
                                    } else {    //Front = Back
                                        ReturnEvent.EventParam = 4;
                                    }
                                    PostTopLevelHSM(ReturnEvent);
                                    PingF_Param = 0;
                                    PingB_Param = 0;
                                } 
                               //Then we check if the ping sensor are both reporting similar, far distances (eg. far from wall, no wall detected)
                               else if ((abs(PingF_Param - PingB_Param) <= PARALLEL_THRESHOLD) && (((PingF_Param + PingB_Param) / 2) > LOWER_THRESHOLD)) {
                                    //Here we don't care which ping sensor is closer, we just want to know if we found a parallel surface
                                    ReturnEvent.EventType = PARALLEL_FAR;
                                    ReturnEvent.EventParam = abs(PingF_Param - PingB_Param);
                                    PostTopLevelHSM(ReturnEvent);
                                    PingF_Param = 0;
                                    PingB_Param = 0;
                                }
                                ping2Samplez = 0;
                                ping2Avg = 0;
                            }
                            ReturnEvent.EventType = NEW_PING1;
                            PostPingService(ReturnEvent);
                        }
                        break;
                      
                    default:
                        break;
                }
                break;
            }
    }
    return ReturnEvent;
}
