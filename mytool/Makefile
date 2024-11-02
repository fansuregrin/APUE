ROOT_DIR = ..
PLATFORM = $(shell ${ROOT_DIR}/systype.sh)
include ${ROOT_DIR}/${PLATFORM}.defines.mk
INCLUDE_PATH += -I${ROOT_DIR}/include

SRC_DIR = ${ROOT_DIR}/mytool
LIB_DIR = ${ROOT_DIR}/output/lib/release
LIB_DIR_DEBUG = ${ROOT_DIR}/output/lib/debug
OBJ_DIR = ${ROOT_DIR}/output/obj
LIB_NAME = mytool
TARGET = ${LIB_DIR}/lib${LIB_NAME}.a
TARGET_DEBUG = ${LIB_DIR_DEBUG}/lib${LIB_NAME}.a
SRC_FILES = $(wildcard ${SRC_DIR}/*.c)
OBJ_FILES = $(patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRC_FILES})
OBJ_FILES_DEBUG = $(patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.debug.o, ${SRC_FILES})

all: ${TARGET} ${TARGET_DEBUG}

debug: ${TARGET_DEBUG}

release: ${TARGET}

${TARGET}: ${OBJ_FILES}
	if [ ! -d ${LIB_DIR} ];then ${MKDIR} -p ${LIB_DIR};fi
	${AR} rcs ${TARGET} ${OBJ_FILES}

${TARGET_DEBUG}: ${OBJ_FILES_DEBUG}
	if [ ! -d ${LIB_DIR_DEBUG} ];then ${MKDIR} -p ${LIB_DIR_DEBUG};fi
	${AR} rcs ${TARGET_DEBUG} ${OBJ_FILES_DEBUG}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	if [ ! -d ${OBJ_DIR} ];then ${MKDIR} -p ${OBJ_DIR};fi
	${CC} $< -o $@ -c ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} ${LIB}

${OBJ_DIR}/%.debug.o: ${SRC_DIR}/%.c
	if [ ! -d ${OBJ_DIR} ];then ${MKDIR} -p ${OBJ_DIR};fi
	${CC} $< -o $@ -c ${CFLAGS} -g ${INCLUDE_PATH} ${LIB_PATH} ${LIB}

clean:
	${RM} -rf ${TARGET} ${OBJ_FILES}
	${RM$ -rf ${TARGET_DEBUG} {OBJ_FILES_DEBUG}

.PHONY: all clean debug release