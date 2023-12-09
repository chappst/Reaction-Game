CFLAGS=-std=c99 -D _POSIX_C_SOURCE=200809L -Werror -static -pthread

TARGET_DIR=~/cmpt433/public/myApps/

PROJ_NAME=reaction_game
EXEC_HOST=${PROJ_NAME}_host.o
EXEC_TARGET=${PROJ_NAME}_target.hex

SRC=*.c lib/*.c

all: target host
	echo ${SRC}


target: 
	arm-linux-gnueabihf-gcc ${CFLAGS} -g ${SRC} -o ${EXEC_TARGET}

	cp ${EXEC_TARGET} ${TARGET_DIR}
	rm ${EXEC_TARGET}
host: 
	gcc ${CFLAGS} -o  ${EXEC_HOST} ${SRC}

clean: 
	rm -f *.o *.bin *.hex *_host *_target
