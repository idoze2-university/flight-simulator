PROJECT_DATA_DIR=Project_Data

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

# Compilation #####################################################################################
ifndef file #sets default for 'file' variable.
override file=$(PROJECT_DATA_DIR)/fly.txt
endif

COMPILER=g++
COMPILER_ARGS= -ggdb3 -std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pthread
MAIN_DIR=.
clean:
	@rm -f *.out
# Lexer (Allen) ###################################################################################
_DEPENDENCIES_LEXER=lexer command
DEPENDENCIES_LEXER=$(foreach d,$(_DEPENDENCIES_LEXER),$(d).cpp)
OUTFILE_LEXER=lexer.out
TARGET_FILE_LEXER=lexer_main.cpp

compile_lexer:
	@echo '################## NOW COMPILING LEXER ###############'
	@$(COMPILER) $(DEPENDENCIES_LEXER) $(MAIN_DIR)/$(TARGET_FILE_LEXER) $(COMPILER_ARGS) -o $(OUTFILE_LEXER) ${COMPILER_EXTRA_ARGS}
	@echo '################## END COMPILING #####################'

run_lexer:
	@./$(OUTFILE_LEXER) $(file)

test_lexer: compile_lexer run_lexer clean

# Parser (Allen, Ido) #############################################################################
_DEPENDENCIES_PARSER=parser parse_value command lexer DB Commands/*
DEPENDENCIES_PARSER=$(foreach d,$(_DEPENDENCIES_PARSER),$(d).cpp)
OUTFILE_PARSER=parser.out
TARGET_FILE_PARSER=parser_main.cpp

compile_parser:
	@echo '################## NOW COMPILING PARSER ###############'
	@$(COMPILER) $(DEPENDENCIES_PARSER) $(MAIN_DIR)/$(TARGET_FILE_PARSER) $(COMPILER_ARGS) -o $(OUTFILE_PARSER) ${COMPILER_EXTRA_ARGS}
	@echo '################## END COMPILING ######################'
run_parser:
	@./$(OUTFILE_PARSER) $(file)

test_parser: compile_parser run_parser clean

# Main (Ido) ######################################################################################
_DEPENDENCIES_MAIN= $(_DEPENDENCIES_PARSER)
DEPENDENCIES_MAIN=$(foreach d,$(_DEPENDENCIES_MAIN),$(d).cpp)
#DEPENDENCIES_MAIN=$(SOURCE_FILES)
OUTFILE_MAIN=a.out
TARGET_FILE_MAIN=main.cpp

compile_main:
	@echo '################## NOW COMPILING MAIN ################'
	@$(COMPILER) $(DEPENDENCIES_MAIN) $(MAIN_DIR)/$(TARGET_FILE_MAIN) $(COMPILER_ARGS) -o $(OUTFILE_MAIN) ${COMPILER_EXTRA_ARGS}
	@echo '################## END COMPILING #####################'
run_main:
	@./$(OUTFILE_MAIN) $(file)

test_main: compile_main run_main clean

# Final target ####################################################################################
run: compile_main
	make run_simulator & make run_main


