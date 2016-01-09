#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

typedef unsigned int uint;

string char_to_string(char x) {
	return string() + x;
}

const char empty_char = '~';

string get_parenthesis(const string &A) {
	return '(' + A + ')';
}

int get_state(char x) {
	return x - 'A';
}

char state_expr(uint i) {
	return char(i + 'A');
}

int get_trans(char x) {
	return x - '0';
}

char trans_expr(uint i) {
	return char(i + '0');
}

class regular_expression {
private:
	string expression;
	bool null_expression, empty_expression;
	uint order;	//0 for atoms, 1 for star, 2 for concatenate, 3 for plus

public:
	regular_expression() : expression(""), null_expression(true), empty_expression(false), order(0) {
	}

	regular_expression(char atom) : expression(char_to_string(atom)), null_expression(false), empty_expression(atom == empty_char), order(0) {
	}

	regular_expression(string str, uint _order) : expression(str), null_expression(str == ""), empty_expression(str == char_to_string(empty_char)), order(_order) {
	}

	bool is_null() const {
		return null_expression;
	}

	bool is_empty() const {
		return empty_expression;
	}

	string suit(int _order) const {
		if (_order < order) {
			return '(' + expression + ')';
		} else {
			return expression;
		}
	}

	string LaTeX() const {
		string ret;
		for (uint i = 0; i < expression.length(); ++i) {
			if (expression[i] == empty_char) {
				ret += "\\epsilon";
			} else if (expression[i] == '*') {
				ret += "^*";
			} else {
				ret += expression[i];
			}
		}
		return ret;
	}

	string plain_text() const {
		return expression;
	}

	friend regular_expression operator~(const regular_expression &);
	friend regular_expression operator*(const regular_expression &, const regular_expression &);
	friend regular_expression operator+(const regular_expression &, const regular_expression &);
};

regular_expression operator~(const regular_expression &A) {
	if (A.is_null() || A.is_empty()) {
		return A;
	} else {
		if (A.order == 1) {
			return A;
		} else {
			return regular_expression(A.suit(1) + '*', 1);
		}
	}
}

regular_expression operator*(const regular_expression &A, const regular_expression &B) {
	if (A.is_null() || B.is_null()) {
		return regular_expression();
	} else if (A.is_empty()) {
		return B;
	} else if (B.is_empty()) {
		return A;
	} else {
		return regular_expression(A.suit(2) + B.suit(2), 2);
	}
}

regular_expression operator+(const regular_expression &A, const regular_expression &B) {
	if (A.is_null()) {
		return B;
	} else if (B.is_null()) {
		return A;
	} else {
		if (A.expression == B.expression) {
			return A;
		} else {
			return regular_expression(A.suit(3) + '+' + B.suit(3), 3);
		}
	}
}

vector<vector<regular_expression> > graph;
vector<bool> eliminated;
uint n, m;
uint start, final;

void input_dfa() {
	cin >> n >> m;
	graph.resize(n);
	for (uint index = 0; index < n; ++index) {
		graph[index].resize(n);
		graph[index][index] = regular_expression(empty_char);
	}
	eliminated.resize(n);
	string instr;
	for (uint source = 0; source < n; ++source) {
		for (uint path = 0; path < m; ++path) {
			cin >> instr;
			uint target = get_state(instr[0]);
			graph[source][target] = graph[source][target] + regular_expression(trans_expr(path));
		}
	}
	cin >> instr;
	start = get_state(instr[0]);
	cin >> instr;
	final = get_state(instr[0]);
}

void jump(uint source, uint middle) {
	for (uint target = 0; target < n; ++target) {
		if (!eliminated[target]) {
			graph[source][target] = graph[source][target] + graph[source][middle] * ~graph[middle][middle] * graph[middle][target];
		}
	}
	graph[source][middle] = regular_expression();
}

void eliminate(uint middle) {
	eliminated[middle] = true;
	for (uint source = 0; source < n; ++source) {
		if (!eliminated[source]) {
			jump(source, middle);
		}
	}
	for (uint target = 0; target < n; ++target) {
		if (!eliminated[target]) {
			graph[middle][target] = regular_expression();
		}
	}
}

regular_expression get_expression() {
	cerr << graph[start][final].LaTeX() << endl;
	for (uint middle = 0; middle < n; ++middle) {
		if (middle != start && middle != final) {
			eliminate(middle);
		}
	}
	cerr << graph[start][start].plain_text() << endl;
	cerr << graph[start][final].plain_text() << endl;
	cerr << graph[final][final].plain_text() << endl;
	cerr << graph[final][start].plain_text() << endl;
	return ~(graph[start][start] + graph[start][final] * ~graph[final][final] * graph[final][start]) * graph[start][final] * ~graph[final][final];
}

int main() {
	input_dfa();
	cout << get_expression().LaTeX() << endl;
	//cout << (~(regular_expression(empty_char) + regular_expression("10", 2))).LaTeX() << endl;
	return 0;
}
