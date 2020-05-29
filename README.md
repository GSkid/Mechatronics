# Mechatronics
Fall 2019 Semi-annual Mechatronics Competition at UCSC

This is a program that runs a hierarchical state machine on a Uno32 microprocessor to control an autonomous robot. The hierarchical state machine uses an events and services framework originally developed by J Edward Carryer of Stanford University. Such a framework allows for event-driven control of the robot so that processes handled in events (like bumper events) and services (like ultrasonic ping sensors, the infrared sensor, and the EM sensor) trigger a reaction somewhere in the hierarchical state machine. The hierarchical nature also separates the different stages of the robot's movement into different levels in the hierarchy. Overall, the software control of the robot reacts quickly and efficiently so that we can accomplish our task as fast as possible.

Speed did actually play a large role in the development of the robot. As part of the challenge, the robot needs to beat other team's robot by performing a specific task faster so having a more responsive and efficient method of responding to individual events is paramount. The hierarchical state machine handles events from the bottom up, this means that the when the external sensors or internal software trigger an event, that event gets sent to the lowest level (most specific) of the state machine first. This state machine will check if it can use that event in its state machine and consume the event if used. If not used, the event moves on to any other state machines at the same level. If the event still is not consumed, it passes up to the next level and so on until it reaches the highest level where it will be removed if not consumed. This happens when we are waiting for events from specific signals, like looking for the end of a wall, and does not negatively influence the rest of the program flow.

If you want to check out the hierarchical state machine, please refer to the following 4 files: 
TopLevelHSM.c, DrivingSubHSM.c, DancingSubHSM.c, LocateHoleHSM.c
  
If you want to check out the events & services framework, please refer to the following files: 
BallDispenserService.c, BeaconDetectorService.c, BumperService.c, PingService.c, TapeSensorService.c
  
If you want to see how we interfaced with the events and services framework, please refer to: 
ES_Configure.h
