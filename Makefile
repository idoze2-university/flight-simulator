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

OUTFILE_MAIN= a.out
OUTFILE_LEXER=lexer.out
OUTFILES=*.out
COMPILER=g++
COMPILER_ARGS= -ggdb3 -std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pthread
TARGET_FILE_MAIN=main.cpp
TARGET_FILE_LEXER=lexer*.cpp
TARGET_FILES=*.cpp

clean:
	@rm -f *.out

compile_main:
	@$(COMPILER) $(TARGET_FILE_MAIN) $(COMPILER_ARGS) -o $(OUTFILE_MAIN) ${COMPILER_EXTRA_ARGS}

run_main:
	@./$(OUTFILE_MAIN) $(file)

run: compile_main run_main clean

compile_lexer:
	@$(COMPILER) $(TARGET_FILE_LEXER) $(COMPILER_ARGS) -o $(OUTFILE_LEXER) ${COMPILER_EXTRA_ARGS}

run_lexer:
	@./$(OUTFILE_LEXER) $(file)

run_l: compile_lexer run_lexer clean

copy_protocol:
	cp $(PROTOCOL_FILENAME_NOEX).xml $(FG_PATH)/Protocol/

run_simulator:
	@$(FG) $(FG_ARGS) $(FG_EXTRA_ARGS)

run_simulator_mini:
	@$(FG) $(FG_ARGS) $(FG_ARGS_MINI)
