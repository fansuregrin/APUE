ROOT_DIR = ..
PLATFORM = $(shell ${ROOT_DIR}/systype.sh)
include ${ROOT_DIR}/${PLATFORM}.defines.mk

INCLUDE_PATH += -I${ROOT_DIR}/include
LIB += -lmytool
SRC_DIR = ${ROOT_DIR}/tests
BIN_DIR_DEBUG = ${ROOT_DIR}/output/bin/debug
BIN_DIR_RELEASE = ${ROOT_DIR}/output/bin/release
SRC_FILES = $(wildcard ${SRC_DIR}/*.c)
BIN_FILES_DEBUG = $(patsubst ${SRC_DIR}/%.c, ${BIN_DIR_DEBUG}/%, ${SRC_FILES})
BIN_FILES_RELEASE = $(patsubst ${SRC_DIR}/%.c, ${BIN_DIR_RELEASE}/%, ${SRC_FILES})

all: ${BIN_FILES_DEBUG} ${BIN_FILES_RELEASE}

debug: ${BIN_FILES_DEBUG}

release: ${BIN_DIR_RELEASE}

${BIN_DIR_DEBUG}/%: ${SRC_DIR}/%.c
	if [ ! -d ${BIN_DIR_DEBUG} ];then ${MKDIR} -p ${BIN_DIR_DEBUG};fi
	$(CC) $< -o $@ ${CFLAGS} -g ${INCLUDE_PATH} ${LIB_PATH} \
		-L${ROOT_DIR}/output/lib/debug ${LIB}

${BIN_DIR_RELEASE}/%: ${SRC_DIR}/%.c
	if [ ! -d ${BIN_DIR_RELEASE} ];then ${MKDIR} -p ${BIN_DIR_RELEASE};fi
	$(CC) $< -o $@ ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} \
		-L${ROOT_DIR}/output/lib/release ${LIB}

clean:
	${RM} -rf ${BIN_FILES_DEBUG}
	${RM} -rf ${BIN_FILES_RELEASE}

.PHONY: clean all debug release