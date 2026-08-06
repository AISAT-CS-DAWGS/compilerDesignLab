#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 10
#define MAX_TRANSITIONS 100

typedef struct {
	int state;
	int *epsilonTransitions;
	int epsilonCount;
} NFAState;

NFAState nfa[MAX_STATES];
int numStates;

void addEpsilonTransition(int fromState, int toState) {
	nfa[fromState].epsilonTransitions[nfa[fromState].epsilonCount++] = toState;
}

void computeEpsilonClosure(int state, int *closure, int *closureCount) {
	for (int i=0; i<*closureCount; i++) {
		if (closure[i] == state) {
			return;
		}
	}

	closure[(*closureCount)++] = state;

	for (int i=0; i<nfa[state].epsilonCount; i++) {
		computeEpsilonClosure(nfa[state].epsilonTransitions[i], closure, closureCount);
	}
}

void printEpsilonClosure() {
	for (int i=0; i<numStates; i++) {
		int closure[MAX_STATES];
		int closureCount = 0;

		computeEpsilonClosure(i, closure, &closureCount);
		printf("Epsilon closure of state %d: { ", i);

		for (int j=0; j<closureCount; j++) {
			printf("%d ", closure[j]);
		}
		printf("}\n");
	}
}

int main() {
	printf("Enter number of states in the NFA: ");
	scanf("%d", &numStates);

	for (int i=0; i<numStates; i++) {
		nfa[i].state = i;
		nfa[i].epsilonTransitions = (int *)malloc(MAX_STATES * sizeof(int));
		nfa[i].epsilonCount = 0;
	}

	int numTransitions;

	printf("Enter number of epsilon transitions: ");
	scanf("%d", &numTransitions);

	printf("Enter transitions in format 'from to':\n");

	for (int i=0; i<numTransitions; i++) {
		int fromState, toState;
		scanf("%d %d", &fromState, &toState);
		addEpsilonTransition(fromState, toState);
	}

	printEpsilonClosure();

	for (int i=0; i<numStates; i++) {
		free(nfa[i].epsilonTransitions);
	}

	return 0;
}
