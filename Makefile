ifndef file #sets default for 'file' variable.
override file=fly.txt
endif
IN_PORT=5400
OUT_PORT=5402
SERVER_IP=127.0.0.1

FG_PATH=/usr/share/games/flightgear
PROTOCOL_FILENAME_NOEX=generic_small
FGFS:=/usr/games/fgfs
FGFS_ARG_SOCKET_IN=--generic=socket,out,10,$(SERVER_IP),$(IN_PORT),tcp,generic_small
FGFS_ARG_SOCKET_OUT=--telnet=socket,in,10,$(SERVER_IP),$(OUT_PORT),tcp
FGFS_ARGS=$(FGFS_ARG_SOCKET_IN) $(FGFS_ARG_SOCKET_OUT)
FGFS_EXTRA_ARGS=--disable-hud

OUTFILE= a.out
COMPILE_ARGS= -std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pthread
COMPILE_FILES=command.h main.cpp

clean:
	@rm -f $(OUTFILE)

compile_command:
	@g++ $(COMPILE_FILES) $(COMPILE_ARGS) -o $(OUTFILE)

run_command:
	@./$(OUTFILE) $(file)

run_server: compile_command run_command

copy_protocol:
	cp $(PROTOCOL_FILENAME_NOEX).xml $(FG_PATH)/Protocol/

run_simulator:
	@$(FGFS) $(FGFS_ARGS) $(FGFS_EXTRA_ARGS)
