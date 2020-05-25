#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SpySlime.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SpySlime.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/AD.c ../src/BOARD.c ../src/ES_CheckEvents.c ../src/ES_Framework.c ../src/ES_KeyboardInput.c ../src/ES_PostList.c ../src/ES_Queue.c ../src/ES_TattleTale.c ../src/ES_Timers.c ../src/IO_Ports.c ../src/LED.c ../src/pwm.c ../src/serial.c ../src/timers.c roach.c TemplateES_Main.c TopLevelHSM.c LocateHoleHSM.c TapeSensorService.c BeaconDetectorService.c PingService.c DrivingSubHSM.c BumperService.c DancingSubHSM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/AD.o ${OBJECTDIR}/_ext/1360937237/BOARD.o ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o ${OBJECTDIR}/_ext/1360937237/ES_Framework.o ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1360937237/ES_PostList.o ${OBJECTDIR}/_ext/1360937237/ES_Queue.o ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o ${OBJECTDIR}/_ext/1360937237/ES_Timers.o ${OBJECTDIR}/_ext/1360937237/IO_Ports.o ${OBJECTDIR}/_ext/1360937237/LED.o ${OBJECTDIR}/_ext/1360937237/pwm.o ${OBJECTDIR}/_ext/1360937237/serial.o ${OBJECTDIR}/_ext/1360937237/timers.o ${OBJECTDIR}/roach.o ${OBJECTDIR}/TemplateES_Main.o ${OBJECTDIR}/TopLevelHSM.o ${OBJECTDIR}/LocateHoleHSM.o ${OBJECTDIR}/TapeSensorService.o ${OBJECTDIR}/BeaconDetectorService.o ${OBJECTDIR}/PingService.o ${OBJECTDIR}/DrivingSubHSM.o ${OBJECTDIR}/BumperService.o ${OBJECTDIR}/DancingSubHSM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/AD.o.d ${OBJECTDIR}/_ext/1360937237/BOARD.o.d ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d ${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d ${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d ${OBJECTDIR}/_ext/1360937237/LED.o.d ${OBJECTDIR}/_ext/1360937237/pwm.o.d ${OBJECTDIR}/_ext/1360937237/serial.o.d ${OBJECTDIR}/_ext/1360937237/timers.o.d ${OBJECTDIR}/roach.o.d ${OBJECTDIR}/TemplateES_Main.o.d ${OBJECTDIR}/TopLevelHSM.o.d ${OBJECTDIR}/LocateHoleHSM.o.d ${OBJECTDIR}/TapeSensorService.o.d ${OBJECTDIR}/BeaconDetectorService.o.d ${OBJECTDIR}/PingService.o.d ${OBJECTDIR}/DrivingSubHSM.o.d ${OBJECTDIR}/BumperService.o.d ${OBJECTDIR}/DancingSubHSM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/AD.o ${OBJECTDIR}/_ext/1360937237/BOARD.o ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o ${OBJECTDIR}/_ext/1360937237/ES_Framework.o ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1360937237/ES_PostList.o ${OBJECTDIR}/_ext/1360937237/ES_Queue.o ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o ${OBJECTDIR}/_ext/1360937237/ES_Timers.o ${OBJECTDIR}/_ext/1360937237/IO_Ports.o ${OBJECTDIR}/_ext/1360937237/LED.o ${OBJECTDIR}/_ext/1360937237/pwm.o ${OBJECTDIR}/_ext/1360937237/serial.o ${OBJECTDIR}/_ext/1360937237/timers.o ${OBJECTDIR}/roach.o ${OBJECTDIR}/TemplateES_Main.o ${OBJECTDIR}/TopLevelHSM.o ${OBJECTDIR}/LocateHoleHSM.o ${OBJECTDIR}/TapeSensorService.o ${OBJECTDIR}/BeaconDetectorService.o ${OBJECTDIR}/PingService.o ${OBJECTDIR}/DrivingSubHSM.o ${OBJECTDIR}/BumperService.o ${OBJECTDIR}/DancingSubHSM.o

# Source Files
SOURCEFILES=../src/AD.c ../src/BOARD.c ../src/ES_CheckEvents.c ../src/ES_Framework.c ../src/ES_KeyboardInput.c ../src/ES_PostList.c ../src/ES_Queue.c ../src/ES_TattleTale.c ../src/ES_Timers.c ../src/IO_Ports.c ../src/LED.c ../src/pwm.c ../src/serial.c ../src/timers.c roach.c TemplateES_Main.c TopLevelHSM.c LocateHoleHSM.c TapeSensorService.c BeaconDetectorService.c PingService.c DrivingSubHSM.c BumperService.c DancingSubHSM.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC32MX320F128H
ProjectDir="C:\Users\gskidmor\MPLABXProjects\SpySlime\SpySlime.X"
ProjectName=SpySlime
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\SpySlime.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="SpySlime.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SpySlime.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="..\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/AD.o: ../src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/AD.o.d" -o ${OBJECTDIR}/_ext/1360937237/AD.o ../src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/BOARD.o: ../src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOARD.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOARD.o ../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o: ../src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o ../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_Framework.o: ../src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Framework.o ../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o: ../src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o ../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_PostList.o: ../src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_PostList.o ../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_Queue.o: ../src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Queue.o ../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o: ../src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o ../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_Timers.o: ../src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Timers.o ../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/IO_Ports.o: ../src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1360937237/IO_Ports.o ../src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/LED.o: ../src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/LED.o.d" -o ${OBJECTDIR}/_ext/1360937237/LED.o ../src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/pwm.o: ../src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pwm.o.d" -o ${OBJECTDIR}/_ext/1360937237/pwm.o ../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/serial.o: ../src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/serial.o.d" -o ${OBJECTDIR}/_ext/1360937237/serial.o ../src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/timers.o: ../src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/timers.o ../src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/roach.o: roach.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/roach.o.d 
	@${RM} ${OBJECTDIR}/roach.o 
	@${FIXDEPS} "${OBJECTDIR}/roach.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/roach.o.d" -o ${OBJECTDIR}/roach.o roach.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TemplateES_Main.o: TemplateES_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/TemplateES_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/TemplateES_Main.o.d" -o ${OBJECTDIR}/TemplateES_Main.o TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TopLevelHSM.o: TopLevelHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TopLevelHSM.o.d 
	@${RM} ${OBJECTDIR}/TopLevelHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/TopLevelHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/TopLevelHSM.o.d" -o ${OBJECTDIR}/TopLevelHSM.o TopLevelHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/LocateHoleHSM.o: LocateHoleHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LocateHoleHSM.o.d 
	@${RM} ${OBJECTDIR}/LocateHoleHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/LocateHoleHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/LocateHoleHSM.o.d" -o ${OBJECTDIR}/LocateHoleHSM.o LocateHoleHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TapeSensorService.o: TapeSensorService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeSensorService.o.d 
	@${RM} ${OBJECTDIR}/TapeSensorService.o 
	@${FIXDEPS} "${OBJECTDIR}/TapeSensorService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/TapeSensorService.o.d" -o ${OBJECTDIR}/TapeSensorService.o TapeSensorService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BeaconDetectorService.o: BeaconDetectorService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BeaconDetectorService.o.d 
	@${RM} ${OBJECTDIR}/BeaconDetectorService.o 
	@${FIXDEPS} "${OBJECTDIR}/BeaconDetectorService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/BeaconDetectorService.o.d" -o ${OBJECTDIR}/BeaconDetectorService.o BeaconDetectorService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/PingService.o: PingService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PingService.o.d 
	@${RM} ${OBJECTDIR}/PingService.o 
	@${FIXDEPS} "${OBJECTDIR}/PingService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/PingService.o.d" -o ${OBJECTDIR}/PingService.o PingService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/DrivingSubHSM.o: DrivingSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DrivingSubHSM.o.d 
	@${RM} ${OBJECTDIR}/DrivingSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/DrivingSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/DrivingSubHSM.o.d" -o ${OBJECTDIR}/DrivingSubHSM.o DrivingSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BumperService.o: BumperService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BumperService.o.d 
	@${RM} ${OBJECTDIR}/BumperService.o 
	@${FIXDEPS} "${OBJECTDIR}/BumperService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/BumperService.o.d" -o ${OBJECTDIR}/BumperService.o BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/DancingSubHSM.o: DancingSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DancingSubHSM.o.d 
	@${RM} ${OBJECTDIR}/DancingSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/DancingSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/DancingSubHSM.o.d" -o ${OBJECTDIR}/DancingSubHSM.o DancingSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1360937237/AD.o: ../src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/AD.o.d" -o ${OBJECTDIR}/_ext/1360937237/AD.o ../src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/BOARD.o: ../src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOARD.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOARD.o ../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o: ../src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o ../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_Framework.o: ../src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Framework.o ../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o: ../src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o ../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_PostList.o: ../src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_PostList.o ../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_Queue.o: ../src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Queue.o ../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o: ../src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o ../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/ES_Timers.o: ../src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Timers.o ../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/IO_Ports.o: ../src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1360937237/IO_Ports.o ../src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/LED.o: ../src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/LED.o.d" -o ${OBJECTDIR}/_ext/1360937237/LED.o ../src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/pwm.o: ../src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pwm.o.d" -o ${OBJECTDIR}/_ext/1360937237/pwm.o ../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/serial.o: ../src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/serial.o.d" -o ${OBJECTDIR}/_ext/1360937237/serial.o ../src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/timers.o: ../src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/_ext/1360937237/timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/timers.o ../src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/roach.o: roach.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/roach.o.d 
	@${RM} ${OBJECTDIR}/roach.o 
	@${FIXDEPS} "${OBJECTDIR}/roach.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/roach.o.d" -o ${OBJECTDIR}/roach.o roach.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TemplateES_Main.o: TemplateES_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/TemplateES_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/TemplateES_Main.o.d" -o ${OBJECTDIR}/TemplateES_Main.o TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TopLevelHSM.o: TopLevelHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TopLevelHSM.o.d 
	@${RM} ${OBJECTDIR}/TopLevelHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/TopLevelHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/TopLevelHSM.o.d" -o ${OBJECTDIR}/TopLevelHSM.o TopLevelHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/LocateHoleHSM.o: LocateHoleHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LocateHoleHSM.o.d 
	@${RM} ${OBJECTDIR}/LocateHoleHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/LocateHoleHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/LocateHoleHSM.o.d" -o ${OBJECTDIR}/LocateHoleHSM.o LocateHoleHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TapeSensorService.o: TapeSensorService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeSensorService.o.d 
	@${RM} ${OBJECTDIR}/TapeSensorService.o 
	@${FIXDEPS} "${OBJECTDIR}/TapeSensorService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/TapeSensorService.o.d" -o ${OBJECTDIR}/TapeSensorService.o TapeSensorService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BeaconDetectorService.o: BeaconDetectorService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BeaconDetectorService.o.d 
	@${RM} ${OBJECTDIR}/BeaconDetectorService.o 
	@${FIXDEPS} "${OBJECTDIR}/BeaconDetectorService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/BeaconDetectorService.o.d" -o ${OBJECTDIR}/BeaconDetectorService.o BeaconDetectorService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/PingService.o: PingService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PingService.o.d 
	@${RM} ${OBJECTDIR}/PingService.o 
	@${FIXDEPS} "${OBJECTDIR}/PingService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/PingService.o.d" -o ${OBJECTDIR}/PingService.o PingService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/DrivingSubHSM.o: DrivingSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DrivingSubHSM.o.d 
	@${RM} ${OBJECTDIR}/DrivingSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/DrivingSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/DrivingSubHSM.o.d" -o ${OBJECTDIR}/DrivingSubHSM.o DrivingSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BumperService.o: BumperService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BumperService.o.d 
	@${RM} ${OBJECTDIR}/BumperService.o 
	@${FIXDEPS} "${OBJECTDIR}/BumperService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/BumperService.o.d" -o ${OBJECTDIR}/BumperService.o BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/DancingSubHSM.o: DancingSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DancingSubHSM.o.d 
	@${RM} ${OBJECTDIR}/DancingSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/DancingSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"." -I"../../SpySlime.X" -MMD -MF "${OBJECTDIR}/DancingSubHSM.o.d" -o ${OBJECTDIR}/DancingSubHSM.o DancingSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SpySlime.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SpySlime.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=11,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SpySlime.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SpySlime.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=11,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SpySlime.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python C:\CMPE118\scripts\Enum_To_String.py]"
	@python C:\CMPE118\scripts\Enum_To_String.py
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
