ifndef file #sets default for 'file' variable.
override file=fly.txt
endif
IN_PORT=5400
OUT_PORT=5402
SERVER_IP=127.0.0.1

FG_PATH=/usr/share/games/flightgear
PROTOCOL_FILENAME_NOEX=generic_small
FG:=/usr/games/fgfs
FG_ARG_SOCKET_IN=--generic=socket,out,10,$(SERVER_IP),$(IN_PORT),tcp,generic_small
FG_ARG_SOCKET_OUT=--telnet=socket,in,10,$(SERVER_IP),$(OUT_PORT),tcp
FG_ARGS=$(FG_ARG_SOCKET_IN) $(FG_ARG_SOCKET_OUT)
FG_ARGS_MINI=$(shell /bin/cat flag_mini.txt)

OUTFILE= a.out
COMPILER=g++
COMPILER_ARGS= -ggdb3 -std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pthread
TARGET_FILES=*.cpp

clean:
	@rm -f $(OUTFILE)

compile:
	@$(COMPILER) $(TARGET_FILES) $(COMPILER_ARGS) -o $(OUTFILE) ${COMPILER_EXTRA_ARGS}

run_main:
	@./$(OUTFILE) $(file)

run: compile run_main clean

copy_protocol:
	cp $(PROTOCOL_FILENAME_NOEX).xml $(FG_PATH)/Protocol/

run_simulator:
	@$(FG) $(FG_ARGS) $(FG_EXTRA_ARGS)

run_simulator_mini:
	@$(FG) $(FG_ARGS) $(FG_ARGS_MINI)
