# DEFINE DATA DIR #################################################################################
PROJECT_DATA_DIR=Project_Data

# COMPILATION #####################################################################################
ifndef file #sets default for 'file' variable.
override file=fly.txt
endif

COMPILER=g++
CFLAGS= -ggdb3 -std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pthread
MAIN_DIR=.
clean:
	@rm -fr ./*.out */*.o *.o

%.o : %.cpp
	g++ -g -o $@ -c $< $(CFLAGS)

# DEPENDENCIES ####################################################################################
COMMAND_LIST = $(shell ls Commands |grep .cpp| sed -e 's/\.cpp//g' | awk '{ print "Commands/" $$0 }')
ALL_DEPENDENCIES = $(foreach d,parser parse_value command lexer DB $(COMMAND_LIST),$(d).o)

DEPENDENCIES_LEXER=$(foreach d,lexer command,$(d).o) lexer_main.cpp
DEPENDENCIES_PARSER=$(ALL_DEPENDENCIES) parser_main.cpp
DEPENDENCIES_MAIN=$(ALL_DEPENDENCIES) main.cpp

# LEXER (Allen) ###################################################################################
OUTFILE_LEXER=lexer.out

$(OUTFILE_LEXER): $(DEPENDENCIES_LEXER)
	@$(COMPILER) $(DEPENDENCIES_LEXER) $(CFLAGS) -o $(OUTFILE_LEXER)

lexer: $(OUTFILE_LEXER)
	@./$(OUTFILE_LEXER) $(file)

# PARSER (Allen, Ido) #############################################################################
OUTFILE_PARSER=parser.out

$(OUTFILE_PARSER): $(DEPENDENCIES_PARSER)
	$(COMPILER) $(DEPENDENCIES_PARSER) $(CFLAGS) -o $(OUTFILE_PARSER)

parser: $(OUTFILE_PARSER)
	./$(OUTFILE_PARSER) $(file)

# MAIN (Ido) ######################################################################################
OUTFILE_MAIN=main.out

$(OUTFILE_MAIN):$(DEPENDENCIES_MAIN)
	$(COMPILER) $(DEPENDENCIES_MAIN) $(CFLAGS) -o $(OUTFILE_MAIN)

main: $(OUTFILE_MAIN)
	./$(OUTFILE_MAIN) $(file)
# MAIN TARGETS ####################################################################################
TARGETS:= main lexer parser
$(TARGETS):
# Final target ####################################################################################
run: $(OUTFILE_MAIN)
	make main & make run_simulator

# SERVER CONSTS ###################################################################################
IN_PORT=5400
OUT_PORT=5402
SERVER_IP=127.0.0.1

# FLIGHTGEAR ######################################################################################
FG_PATH=/usr/share/games/flightgear#Edit if necessary!!!
PROTOCOL_FILENAME_NOEX=$(PROJECT_DATA_DIR)/generic_small
FG:=$(shell which fgfs)
FG_ARG_SOCKET_IN=--generic=socket,out,10,$(SERVER_IP),$(IN_PORT),tcp,generic_small
FG_ARG_SOCKET_OUT=--telnet=socket,in,10,$(SERVER_IP),$(OUT_PORT),tcp
FG_ARGS=$(FG_ARG_SOCKET_IN) $(FG_ARG_SOCKET_OUT)
FG_ARGS_MINI=$(shell /bin/cat $(PROJECT_DATA_DIR)/flag_mini.txt)

copy_protocol:
	@sudo cp $(PROTOCOL_FILENAME_NOEX).xml $(FG_PATH)/Protocol/
	@echo 'Copied.'

run_simulator:
	@$(FG) $(FG_ARGS) $(FG_EXTRA_ARGS)

run_simulator_mini:
	@$(FG) $(FG_ARGS) $(FG_ARGS_MINI)

