from itertools import product
from typing import Set, List, Dict, Tuple


class FiniteAutomaton:
    def __init__(self, alphabet_size: int, alphabet: Set[str], states: Set[int], start_state: int,
                 final_states: Set[int],
                 transitions: Dict[Tuple[int, str], int]):
        self.alphabet_size = alphabet_size
        self.alphabet = alphabet
        self.states = states
        self.start_state = start_state
        self.final_states = final_states
        self.transitions = transitions

    def accepts_word(self, word: str) -> bool:
        current_state = self.start_state
        for symbol in word:
            if (current_state, symbol) in self.transitions:
                current_state = self.transitions[(current_state, symbol)]
                if current_state in self.final_states:
                    return True
            else:
                return False
        return current_state in self.final_states

    def accepts_all_words_of_length(self, k: int) -> bool:
        all_words = generate_all_words(self.alphabet, k)
        return all(self.accepts_word(word) for word in all_words)


def generate_all_words(alphabet: Set[str], length: int) -> List[str]:
    """Generate all possible words of given length from the given alphabet."""
    return [''.join(word) for word in product(alphabet, repeat=length)]


def read_automaton_from_file(file_path: str) -> FiniteAutomaton:
    with open(file_path, 'r') as file:
        # Read the alphabet size (actual alphabet characters are not provided in the input)
        alphabet_size = int(file.readline().strip())

        # Read the states
        states_size = int(file.readline().strip())
        states = set(range(states_size))

        # Read the start state (always 0 as per given structure)
        start_state = int(file.readline().strip())

        # Read the final states
        final_states_line = file.readline().strip().split()
        final_states = set(map(int, final_states_line[1:]))

        # Read the transitions and infer the alphabet from the transitions
        transitions = {}
        alphabet = set()
        for line in file:
            state, symbol, next_state = line.strip().split()
            transitions[(int(state), symbol)] = int(next_state)
            alphabet.add(symbol)

    return FiniteAutomaton(alphabet_size, alphabet, states, start_state, final_states, transitions)


if __name__ == "__main__":
    file_path = "length-2-automaton.txt"
    automaton = read_automaton_from_file(file_path)

    k = int(input("Enter the length of the words to check: "))
    print(
        f"Does the automaton accept all words of length {k}? {'Yes' if automaton.accepts_all_words_of_length(k) else 'No'}")
