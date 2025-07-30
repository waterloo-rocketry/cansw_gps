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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/cansw_gps.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/cansw_gps.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=canlib/pic18f26k83/pic18f26k83_can.c canlib/util/can_tx_buffer.c canlib/util/safe_ring_buffer.c canlib/util/timing_util.c canlib/message/msg_actuator.c canlib/message/msg_common.c canlib/message/msg_general.c canlib/message/msg_gps.c canlib/message/msg_recovery.c canlib/message/msg_sensor.c canlib/message/msg_state_est.c rocketlib/pic18f26k83/timer.c mcc_generated_files/fvr.c mcc_generated_files/adcc.c main.c gps_general.c gps_module.c error_checks.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1 ${OBJECTDIR}/canlib/util/can_tx_buffer.p1 ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1 ${OBJECTDIR}/canlib/util/timing_util.p1 ${OBJECTDIR}/canlib/message/msg_actuator.p1 ${OBJECTDIR}/canlib/message/msg_common.p1 ${OBJECTDIR}/canlib/message/msg_general.p1 ${OBJECTDIR}/canlib/message/msg_gps.p1 ${OBJECTDIR}/canlib/message/msg_recovery.p1 ${OBJECTDIR}/canlib/message/msg_sensor.p1 ${OBJECTDIR}/canlib/message/msg_state_est.p1 ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1 ${OBJECTDIR}/mcc_generated_files/fvr.p1 ${OBJECTDIR}/mcc_generated_files/adcc.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/gps_general.p1 ${OBJECTDIR}/gps_module.p1 ${OBJECTDIR}/error_checks.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1.d ${OBJECTDIR}/canlib/util/can_tx_buffer.p1.d ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1.d ${OBJECTDIR}/canlib/util/timing_util.p1.d ${OBJECTDIR}/canlib/message/msg_actuator.p1.d ${OBJECTDIR}/canlib/message/msg_common.p1.d ${OBJECTDIR}/canlib/message/msg_general.p1.d ${OBJECTDIR}/canlib/message/msg_gps.p1.d ${OBJECTDIR}/canlib/message/msg_recovery.p1.d ${OBJECTDIR}/canlib/message/msg_sensor.p1.d ${OBJECTDIR}/canlib/message/msg_state_est.p1.d ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d ${OBJECTDIR}/mcc_generated_files/adcc.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/gps_general.p1.d ${OBJECTDIR}/gps_module.p1.d ${OBJECTDIR}/error_checks.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1 ${OBJECTDIR}/canlib/util/can_tx_buffer.p1 ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1 ${OBJECTDIR}/canlib/util/timing_util.p1 ${OBJECTDIR}/canlib/message/msg_actuator.p1 ${OBJECTDIR}/canlib/message/msg_common.p1 ${OBJECTDIR}/canlib/message/msg_general.p1 ${OBJECTDIR}/canlib/message/msg_gps.p1 ${OBJECTDIR}/canlib/message/msg_recovery.p1 ${OBJECTDIR}/canlib/message/msg_sensor.p1 ${OBJECTDIR}/canlib/message/msg_state_est.p1 ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1 ${OBJECTDIR}/mcc_generated_files/fvr.p1 ${OBJECTDIR}/mcc_generated_files/adcc.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/gps_general.p1 ${OBJECTDIR}/gps_module.p1 ${OBJECTDIR}/error_checks.p1

# Source Files
SOURCEFILES=canlib/pic18f26k83/pic18f26k83_can.c canlib/util/can_tx_buffer.c canlib/util/safe_ring_buffer.c canlib/util/timing_util.c canlib/message/msg_actuator.c canlib/message/msg_common.c canlib/message/msg_general.c canlib/message/msg_gps.c canlib/message/msg_recovery.c canlib/message/msg_sensor.c canlib/message/msg_state_est.c rocketlib/pic18f26k83/timer.c mcc_generated_files/fvr.c mcc_generated_files/adcc.c main.c gps_general.c gps_module.c error_checks.c



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

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/cansw_gps.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F26K83
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1: canlib/pic18f26k83/pic18f26k83_can.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/pic18f26k83" 
	@${RM} ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1.d 
	@${RM} ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1 canlib/pic18f26k83/pic18f26k83_can.c 
	@-${MV} ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.d ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/util/can_tx_buffer.p1: canlib/util/can_tx_buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/util" 
	@${RM} ${OBJECTDIR}/canlib/util/can_tx_buffer.p1.d 
	@${RM} ${OBJECTDIR}/canlib/util/can_tx_buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/util/can_tx_buffer.p1 canlib/util/can_tx_buffer.c 
	@-${MV} ${OBJECTDIR}/canlib/util/can_tx_buffer.d ${OBJECTDIR}/canlib/util/can_tx_buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/util/can_tx_buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/util/safe_ring_buffer.p1: canlib/util/safe_ring_buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/util" 
	@${RM} ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1.d 
	@${RM} ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1 canlib/util/safe_ring_buffer.c 
	@-${MV} ${OBJECTDIR}/canlib/util/safe_ring_buffer.d ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/util/timing_util.p1: canlib/util/timing_util.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/util" 
	@${RM} ${OBJECTDIR}/canlib/util/timing_util.p1.d 
	@${RM} ${OBJECTDIR}/canlib/util/timing_util.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/util/timing_util.p1 canlib/util/timing_util.c 
	@-${MV} ${OBJECTDIR}/canlib/util/timing_util.d ${OBJECTDIR}/canlib/util/timing_util.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/util/timing_util.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_actuator.p1: canlib/message/msg_actuator.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_actuator.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_actuator.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_actuator.p1 canlib/message/msg_actuator.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_actuator.d ${OBJECTDIR}/canlib/message/msg_actuator.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_actuator.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_common.p1: canlib/message/msg_common.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_common.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_common.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_common.p1 canlib/message/msg_common.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_common.d ${OBJECTDIR}/canlib/message/msg_common.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_common.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_general.p1: canlib/message/msg_general.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_general.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_general.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_general.p1 canlib/message/msg_general.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_general.d ${OBJECTDIR}/canlib/message/msg_general.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_general.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_gps.p1: canlib/message/msg_gps.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_gps.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_gps.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_gps.p1 canlib/message/msg_gps.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_gps.d ${OBJECTDIR}/canlib/message/msg_gps.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_gps.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_recovery.p1: canlib/message/msg_recovery.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_recovery.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_recovery.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_recovery.p1 canlib/message/msg_recovery.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_recovery.d ${OBJECTDIR}/canlib/message/msg_recovery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_recovery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_sensor.p1: canlib/message/msg_sensor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_sensor.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_sensor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_sensor.p1 canlib/message/msg_sensor.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_sensor.d ${OBJECTDIR}/canlib/message/msg_sensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_sensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_state_est.p1: canlib/message/msg_state_est.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_state_est.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_state_est.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_state_est.p1 canlib/message/msg_state_est.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_state_est.d ${OBJECTDIR}/canlib/message/msg_state_est.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_state_est.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1: rocketlib/pic18f26k83/timer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/rocketlib/pic18f26k83" 
	@${RM} ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1.d 
	@${RM} ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1 rocketlib/pic18f26k83/timer.c 
	@-${MV} ${OBJECTDIR}/rocketlib/pic18f26k83/timer.d ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/fvr.p1: mcc_generated_files/fvr.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/fvr.p1 mcc_generated_files/fvr.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/fvr.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/adcc.p1: mcc_generated_files/adcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/adcc.p1 mcc_generated_files/adcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/adcc.d ${OBJECTDIR}/mcc_generated_files/adcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/adcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/gps_general.p1: gps_general.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gps_general.p1.d 
	@${RM} ${OBJECTDIR}/gps_general.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/gps_general.p1 gps_general.c 
	@-${MV} ${OBJECTDIR}/gps_general.d ${OBJECTDIR}/gps_general.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/gps_general.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/gps_module.p1: gps_module.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gps_module.p1.d 
	@${RM} ${OBJECTDIR}/gps_module.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/gps_module.p1 gps_module.c 
	@-${MV} ${OBJECTDIR}/gps_module.d ${OBJECTDIR}/gps_module.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/gps_module.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/error_checks.p1: error_checks.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/error_checks.p1.d 
	@${RM} ${OBJECTDIR}/error_checks.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/error_checks.p1 error_checks.c 
	@-${MV} ${OBJECTDIR}/error_checks.d ${OBJECTDIR}/error_checks.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/error_checks.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1: canlib/pic18f26k83/pic18f26k83_can.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/pic18f26k83" 
	@${RM} ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1.d 
	@${RM} ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1 canlib/pic18f26k83/pic18f26k83_can.c 
	@-${MV} ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.d ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/pic18f26k83/pic18f26k83_can.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/util/can_tx_buffer.p1: canlib/util/can_tx_buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/util" 
	@${RM} ${OBJECTDIR}/canlib/util/can_tx_buffer.p1.d 
	@${RM} ${OBJECTDIR}/canlib/util/can_tx_buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/util/can_tx_buffer.p1 canlib/util/can_tx_buffer.c 
	@-${MV} ${OBJECTDIR}/canlib/util/can_tx_buffer.d ${OBJECTDIR}/canlib/util/can_tx_buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/util/can_tx_buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/util/safe_ring_buffer.p1: canlib/util/safe_ring_buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/util" 
	@${RM} ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1.d 
	@${RM} ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1 canlib/util/safe_ring_buffer.c 
	@-${MV} ${OBJECTDIR}/canlib/util/safe_ring_buffer.d ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/util/safe_ring_buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/util/timing_util.p1: canlib/util/timing_util.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/util" 
	@${RM} ${OBJECTDIR}/canlib/util/timing_util.p1.d 
	@${RM} ${OBJECTDIR}/canlib/util/timing_util.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/util/timing_util.p1 canlib/util/timing_util.c 
	@-${MV} ${OBJECTDIR}/canlib/util/timing_util.d ${OBJECTDIR}/canlib/util/timing_util.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/util/timing_util.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_actuator.p1: canlib/message/msg_actuator.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_actuator.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_actuator.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_actuator.p1 canlib/message/msg_actuator.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_actuator.d ${OBJECTDIR}/canlib/message/msg_actuator.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_actuator.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_common.p1: canlib/message/msg_common.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_common.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_common.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_common.p1 canlib/message/msg_common.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_common.d ${OBJECTDIR}/canlib/message/msg_common.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_common.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_general.p1: canlib/message/msg_general.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_general.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_general.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_general.p1 canlib/message/msg_general.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_general.d ${OBJECTDIR}/canlib/message/msg_general.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_general.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_gps.p1: canlib/message/msg_gps.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_gps.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_gps.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_gps.p1 canlib/message/msg_gps.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_gps.d ${OBJECTDIR}/canlib/message/msg_gps.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_gps.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_recovery.p1: canlib/message/msg_recovery.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_recovery.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_recovery.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_recovery.p1 canlib/message/msg_recovery.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_recovery.d ${OBJECTDIR}/canlib/message/msg_recovery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_recovery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_sensor.p1: canlib/message/msg_sensor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_sensor.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_sensor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_sensor.p1 canlib/message/msg_sensor.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_sensor.d ${OBJECTDIR}/canlib/message/msg_sensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_sensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/canlib/message/msg_state_est.p1: canlib/message/msg_state_est.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/canlib/message" 
	@${RM} ${OBJECTDIR}/canlib/message/msg_state_est.p1.d 
	@${RM} ${OBJECTDIR}/canlib/message/msg_state_est.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/canlib/message/msg_state_est.p1 canlib/message/msg_state_est.c 
	@-${MV} ${OBJECTDIR}/canlib/message/msg_state_est.d ${OBJECTDIR}/canlib/message/msg_state_est.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/canlib/message/msg_state_est.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1: rocketlib/pic18f26k83/timer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/rocketlib/pic18f26k83" 
	@${RM} ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1.d 
	@${RM} ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1 rocketlib/pic18f26k83/timer.c 
	@-${MV} ${OBJECTDIR}/rocketlib/pic18f26k83/timer.d ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/rocketlib/pic18f26k83/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/fvr.p1: mcc_generated_files/fvr.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/fvr.p1 mcc_generated_files/fvr.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/fvr.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/adcc.p1: mcc_generated_files/adcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/adcc.p1 mcc_generated_files/adcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/adcc.d ${OBJECTDIR}/mcc_generated_files/adcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/adcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/gps_general.p1: gps_general.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gps_general.p1.d 
	@${RM} ${OBJECTDIR}/gps_general.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/gps_general.p1 gps_general.c 
	@-${MV} ${OBJECTDIR}/gps_general.d ${OBJECTDIR}/gps_general.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/gps_general.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/gps_module.p1: gps_module.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gps_module.p1.d 
	@${RM} ${OBJECTDIR}/gps_module.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/gps_module.p1 gps_module.c 
	@-${MV} ${OBJECTDIR}/gps_module.d ${OBJECTDIR}/gps_module.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/gps_module.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/error_checks.p1: error_checks.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/error_checks.p1.d 
	@${RM} ${OBJECTDIR}/error_checks.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/error_checks.p1 error_checks.c 
	@-${MV} ${OBJECTDIR}/error_checks.d ${OBJECTDIR}/error_checks.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/error_checks.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/cansw_gps.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/cansw_gps.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/cansw_gps.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/cansw_gps.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/cansw_gps.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/cansw_gps.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -DBOARD_TYPE_UNIQUE_ID=BOARD_TYPE_ID_GPS -DBOARD_INST_UNIQUE_ID=BOARD_INST_ID_ROCKET -xassembler-with-cpp -I"canlib" -I"rocketlib/include" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/cansw_gps.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
