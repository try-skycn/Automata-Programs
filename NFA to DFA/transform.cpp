#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned int uint;

map<uint, map<uint, uint> > table;
map<uint, map<uint, uint> > mapping;
uint n,m;
uint startstate, finalstates;

uint string_to_set(string x) {
	if (x == "0") {
		return 0;
	}
	uint ans = 0;
	uint len = x.length();
	for (int i = 0; i < len; ++i) {
		ans |= 1 << (x[i] - 'A');
	}
	return ans;
}

string set_to_string(uint multistate, bool is_graph = false) {
	if (multistate == 0) {
		return is_graph ? "trap" : "\\varnothing";
	}
	string ans;
	for (int i = 0; i < n; ++i) {
		if (multistate & (1 << i)) {
			ans += char('A' + i);
		}
	}
	return ans;
}

void input() {
	cin >> n >> m;
	string input;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> input;
			table[i][j] = string_to_set(input);
		}
	}
	cin >> input;
	startstate = string_to_set(input);
	cin >> input;
	finalstates = string_to_set(input);
}

void transform() {
	queue<uint> Q;
	Q.push(startstate);
	while (!Q.empty()) {
		uint multistate = Q.front();
		Q.pop();
		for (int j = 0; j < m; ++j) {
			uint endstate = 0;
			for (int i = 0; i < n; ++i) {
				if (multistate & (1 << i)) {
					endstate |= table[i][j];
				}
			}
			mapping[multistate][j] = endstate;
			if (mapping.find(endstate) == mapping.end()) {
				Q.push(endstate);
			}
		}
	}
}

void output() {
	cout << "\\begin{tabular}{r|";
	for (int i = 0; i < m; ++i) {
		cout << "c";
	}
	cout << "}" << endl;

	for (int i = 0; i < m; ++i) {
		cout << "& $" << i << "$ ";
	}
	cout << "\\\\" << endl;

	cout << "\\hline" << endl;

	for (map<uint, map<uint, uint> >::iterator it = mapping.begin(); it != mapping.end(); ++it) {
		if (it->first) {
			cout << "$\\{" << set_to_string(it->first) << "\\}$ ";
			for (int j = 0; j < m; ++j) {
				cout << "& $\\{" << set_to_string(it->second[j]) << "\\}$ ";
			}
			cout << "\\\\" << endl;
		}
	}

	cout << "\\end{tabular}";
}

void graph_output_node(map<uint, map<uint, uint> >::iterator it) {
	vector<pair<uint, uint> > forward_node;
	for (map<uint, uint>::iterator nodes = it->second.begin(); nodes != it->second.end(); ++nodes) {
		forward_node.push_back(pair<uint, uint>(nodes->second, nodes->first));
	}
	sort(forward_node.begin(), forward_node.end());
	for (int i = 0, j = i; i < forward_node.size(); i = j + 1, j = i) {
		cout << "\t";
		cout << set_to_string(it->first, true);
		cout << "->" << set_to_string(forward_node[i].first, true) << "[label = \"" << forward_node[i].second;
		while (j + 1 < forward_node.size() && forward_node[j + 1].first == forward_node[j].first) {
			++j;
			cout << "," << forward_node[j].second;
		}
		cout << "\"]" << endl;
	}
}

void graph_output() {
	cout << "digraph {" << endl;
	cout << "\trankdir = LR;" << endl;

	cout << "\tnode[shape = none, label = \"\"]" << endl;
	cout << "Start;" << endl;

	cout << "\tnode[shape = circle]" << endl;
	for (map<uint, map<uint, uint> >::iterator it = mapping.begin(); it != mapping.end(); ++it) {
		cout << "\t" << set_to_string(it->first) << "[";
		if (it->first & finalstates) {
			cout << "shape = doublecircle,";
		}
		cout << "label = " << set_to_string(it->first);
		cout << "];" << endl;
	}

	cout << "\tStart->" << set_to_string(startstate) << "[label=start];" << endl;

	for (map<uint, map<uint, uint> >::iterator it = mapping.begin(); it != mapping.end(); ++it) {
		graph_output_node(it);
	}
	cout << "}";
}

int main(int argc, char *argv[]) {
	input();
	transform();
	if (argc > 0 && strcmp(argv[1], "graph") == 0) {
		graph_output();
	} else {
		output();
	}
	return 0;
}
