#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

typedef struct {
	int transitions[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
	int num_states;
	int num_symbols;
} NFA;

typedef struct {
	int transitions[MAX_STATES][MAX_SYMBOLS];
	int num_states;
	int num_symbols;
} DFA;

void initializeNFA(NFA* nfa, int num_states, int num_symbols) {
	nfa->num_states = num_states;
	nfa->num_symbols = num_symbols;
	
	for (int i = 0; i < num_states; i++) {
		for (int j = 0; j < num_symbols; j++) {
			for (int k = 0; k < num_states; k++) {
				nfa->transitions[i][j][k] = -1;
			}
		}
	}
}

void addTransitionNFA(NFA* nfa, int from_state, int symbol, int to_state) {
	for (int i = 0; i < MAX_STATES; i++) {
		if (nfa->transitions[from_state][symbol][i] == -1) {
			nfa->transitions[from_state][symbol][i] = to_state;
			break;
		}
	}
}

int stateSetExists(int state_sets[MAX_STATES][MAX_STATES], int* set_size, int num_dfa_states, int new_set[], int new_set_size) {
	for (int i = 0; i < num_dfa_states; i++) {
		if (set_size[i] == new_set_size) {
			int match = 1;
			for (int j = 0; j < new_set_size; j++) {
				if (state_sets[i][j] != new_set[j]) {
					match = 0;
					break;
				}
			}
			if (match) {
				return i;
			}
		}
	}
	return -1;
}

void addStateSet(int state_sets[MAX_STATES][MAX_STATES], int* set_size, int num_dfa_states, int new_set[], int new_set_size) {
	for (int i = 0; i < new_set_size; i++) {
		state_sets[num_dfa_states][i] = new_set[i];
	}
	set_size[num_dfa_states] = new_set_size;
}

void convertNFAToDFA(NFA* nfa, DFA* dfa) {
	int state_sets[MAX_STATES][MAX_STATES];
	int set_size[MAX_STATES];
	int num_dfa_states = 0;

	int initial_set[] = {0};
	addStateSet(state_sets, set_size, num_dfa_states++, initial_set, 1);
	
	dfa->num_states = 0;
	dfa->num_symbols = nfa->num_symbols;

	for (int i = 0; i < num_dfa_states; i++) {
		for (int symbol = 0; symbol < nfa->num_symbols; symbol++) {
			int new_set[MAX_STATES];
			int new_set_size = 0;
			
			for (int j = 0; j < set_size[i]; j++) {
				int current_nfa_state = state_sets[i][j];
				
				for (int k = 0; k < MAX_STATES; k++) {
					int next_state = nfa->transitions[current_nfa_state][symbol][k];
					
					if (next_state != -1) {
						int already_in_set = 0;
						for (int l = 0; l < new_set_size; l++) {
							if (new_set[l] == next_state) {
								already_in_set = 1;
								break;
							}
						}
						
						if (!already_in_set) {
							new_set[new_set_size++] = next_state;
						}
					}
				}
			}
			
			for (int j = 0; j < new_set_size - 1; j++) {
				for (int k = j + 1; k < new_set_size; k++) {
					if (new_set[j] > new_set[k]) {
						int temp = new_set[j];
						new_set[j] = new_set[k];
						new_set[k] = temp;
					}
				}
			}
			
			int state_index = stateSetExists(state_sets, set_size, num_dfa_states, new_set, new_set_size);
			
			if (state_index == -1) {
				addStateSet(state_sets, set_size, num_dfa_states, new_set, new_set_size);
				state_index = num_dfa_states++;
			}
			
			dfa->transitions[i][symbol] = state_index;
		}
	}
	
	dfa->num_states = num_dfa_states;
}

void printDFA(DFA* dfa) {
	printf("\nDFA Transitions:\n");
	for (int i = 0; i < dfa->num_states; i++) {
		for (int symbol = 0; symbol < dfa->num_symbols; symbol++) {
			printf("DFA state %d on symbol %d -> DFA state %d\n", i, symbol, dfa->transitions[i][symbol]);
		}
	}
}

int main() {
	NFA nfa;
	DFA dfa;
	int num_states, num_symbols, num_transitions;
	
	printf("Enter the number of NFA states: ");
	scanf("%d", &num_states);
	printf("Enter the number of input symbols: ");
	scanf("%d", &num_symbols);
	
	initializeNFA(&nfa, num_states, num_symbols);
	
	printf("Enter the number of transitions: ");
	scanf("%d", &num_transitions);
	
	printf("Enter transitions (from_state symbol to_state):\n");
	
	for (int i = 0; i < num_transitions; i++) {
		int from_state, symbol, to_state;
		scanf("%d %d %d", &from_state, &symbol, &to_state);
		addTransitionNFA(&nfa, from_state, symbol, to_state);
	}
	
	convertNFAToDFA(&nfa, &dfa);
	printDFA(&dfa);
	
	return 0;
}
