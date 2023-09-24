#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct FiniteAutomaton {
    int alphabet_size;
    char *alphabet;
    int states_size;
    int start_state;
    int *final_states;
    int final_states_size;
    int **transitions;
} FiniteAutomaton;

FiniteAutomaton* read_automaton_from_file(const char* file_path);
bool accepts_word(FiniteAutomaton* fa, const char* word);
bool accepts_all_words_of_length(FiniteAutomaton* fa, int length);
void generate_all_words(FiniteAutomaton* fa, int length, char* word, int index, bool* accepts_all);

int main() {
    const char* file_path = "length-1-automaton.txt";
    FiniteAutomaton* automaton = read_automaton_from_file(file_path);

    int k;
    printf("Enter the length of the words to check: ");
    scanf("%d", &k);

    if (accepts_all_words_of_length(automaton, k))
        printf("Does the automaton accept all words of length %d? Yes\n", k);
    else
        printf("Does the automaton accept all words of length %d? No\n", k);

    free(automaton->alphabet);
    free(automaton->final_states);
    for (int i = 0; i < automaton->states_size; i++)
        free(automaton->transitions[i]);
    free(automaton->transitions);
    free(automaton);

    return 0;
}

FiniteAutomaton* read_automaton_from_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    FiniteAutomaton* fa = malloc(sizeof(FiniteAutomaton));
    if (!fa) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d\n", &fa->alphabet_size);

    fa->alphabet = malloc((fa->alphabet_size + 1) * sizeof(char));
    if (!fa->alphabet) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d\n", &fa->states_size);

    fa->transitions = malloc(fa->states_size * sizeof(int*));
    for (int i = 0; i < fa->states_size; i++) {
        fa->transitions[i] = malloc(256 * sizeof(int));
        if (!fa->transitions[i]) {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < 256; j++) fa->transitions[i][j] = -1;
    }

    fscanf(file, "%d\n", &fa->start_state);

    fscanf(file, "%d", &fa->final_states_size);
    fa->final_states = malloc(fa->final_states_size * sizeof(int));
    for (int i = 0; i < fa->final_states_size; i++) fscanf(file, "%d", &fa->final_states[i]);

    int i = 0;
    char symbol;
    int state, next_state;
    while (fscanf(file, "%d %c %d\n", &state, &symbol, &next_state) == 3) {
        fa->transitions[state][(int)symbol] = next_state;
        if (strchr(fa->alphabet, symbol) == NULL) fa->alphabet[i++] = symbol;
    }
    fa->alphabet[i] = '\0';

    fclose(file);

    return fa;
}

bool accepts_word(FiniteAutomaton* fa, const char* word) {
    int current_state = fa->start_state;
    for (int i = 0; i < strlen(word); i++) {
        char symbol = word[i];
        if (fa->transitions[current_state][(int)symbol] != -1)
            current_state = fa->transitions[current_state][(int)symbol];
        else
            return false;
    }
    for (int i = 0; i < fa->final_states_size; i++)
        if (fa->final_states[i] == current_state) return true;

    return false;
}

bool accepts_all_words_of_length(FiniteAutomaton* fa, int length) {
    bool accepts_all = true;
    char* word = malloc((length + 1) * sizeof(char));
    word[length] = '\0';

    generate_all_words(fa, length, word, 0, &accepts_all);

    free(word);
    return accepts_all;
}

void generate_all_words(FiniteAutomaton* fa, int length, char* word, int index, bool* accepts_all) {
    if (!(*accepts_all)) return;
    if (index == length) {
        if (!accepts_word(fa, word)) *accepts_all = false;
        return;
    }

    for (int i = 0; i < strlen(fa->alphabet); i++) {
        word[index] = fa->alphabet[i];
        generate_all_words(fa, length, word, index + 1, accepts_all);
    }
}
