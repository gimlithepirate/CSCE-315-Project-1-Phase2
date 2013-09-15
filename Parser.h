#ifndef PARSER_H_
#define PARSER_H_

#include Database.h

#include <string>

class Parser{

public:
	enum Token {
		// symbols
		// <-     (        )      +     -     *      ,        ;       =
		LARROW, LPAREN, RPAREN, PLUS, MINUS, TIMES, COMMA, SEMICOLON, EQUALS,
		//== !=    <      >      <=   >=  ||   &&
		EQ, NEQ, LESS, GREATER, LEQ, GEQ, OR, AND,
		
		// keywords
		SELECT, PROJECT, RENAME, OPEN, CLOSE, WRITE, EXIT, SHOW,
		CREATE_TABLE, PRIMARY_KEY, UPDATE, SET, WHERE, INSERT_INTO,
		VALUES_FROM, VALUES_FROM_RELATION, DELETE_FROM, VARCHAR, INTEGER_SYM,

		// others
		// INTEGER - any amount of digits
		// IDENTIFIER - starts with alpha, then any amount of alpha, digit, or "_"
		// LITERAL - " (any amount of characters) "
		INTEGER, IDENTIFIER, LITERAL
	};
	void execute(string input);
	string get_error();

private:
	void lex(string input);
	void parse();

	int accept(Token);
	int expect(Token);

	void query();
	void command();
	void expression();
	void atomic_expr();

	void selection();
	void projection();
	void renaming();
	void unions();
	void difference();
	void product();

	void condition();
	void conjunction();
	void comparison();
	void op();
	void operand();

	void attribute_list();
	void typed_attribute_list();
	void type();

	vector<string> tokens;
	vector<string> raw_data;

	int current_index;
}

#endif