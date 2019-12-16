ifndef file #sets default for 'file' variable.
override file=fly.txt
endif

compile_command:
	@g++ -std=c++14 command.h command.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o command.out -pthread

run_command:
	@./command.out $(file)
	@rm -f command.out

run: compile_command run_command
