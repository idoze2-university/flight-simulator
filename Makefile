ifndef file
override file=fly.txt
endif


compile_lexer:
	@g++ -std=c++14 lexer.h lexer.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o lexer.out -pthread

run_lexer:
	@./lexer.out $(file)
	@rm -f ./lexer.out

run: compile_lexer run_lexer