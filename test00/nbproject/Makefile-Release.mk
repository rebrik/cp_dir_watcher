#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1360937237/dir_watcher.o \
	${OBJECTDIR}/_ext/1360937237/file_watcher.o \
	${OBJECTDIR}/dir_watcher_tst.o \
	${OBJECTDIR}/file_watcher_tst.o \
	${OBJECTDIR}/test00.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lev

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test00

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test00: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test00 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1360937237/dir_watcher.o: ../src/dir_watcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/dir_watcher.o ../src/dir_watcher.cpp

${OBJECTDIR}/_ext/1360937237/file_watcher.o: ../src/file_watcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/file_watcher.o ../src/file_watcher.cpp

${OBJECTDIR}/dir_watcher_tst.o: dir_watcher_tst.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dir_watcher_tst.o dir_watcher_tst.cpp

${OBJECTDIR}/file_watcher_tst.o: file_watcher_tst.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file_watcher_tst.o file_watcher_tst.cpp

${OBJECTDIR}/test00.o: test00.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test00.o test00.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test00

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
