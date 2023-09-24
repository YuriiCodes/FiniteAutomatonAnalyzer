# Finite Automaton Analyzer 🤖


This repository contains the implementation of a finite automaton, a fundamental concept in computer science for recognizing regular languages 📚. The implementation is available in both Python 🐍 and C 🌐.

## 🌟 Features
- **Read Automaton from File 📁:** Parse the finite automaton configuration from a text file.
- **Word Acceptance 🧐:** Evaluate whether the automaton accepts a given word.
- **Check All Words of Given Length ✅:** Assess whether the automaton accepts all possible words of a specific length.

## 🛠️ How to Use
### 1. Define Your Automaton 🌐
Create a text file and define your finite automaton according to the structure detailed below:

```plaintext
<number_of_alphabet_symbols>
<number_of_states>
<start_state>
<number_of_final_states>    <final_state1> <final_state2> ...
<state>    <symbol>    <next_state>
...
```

### 2. Run the Scripts
#### Python 🐍
Execute the Python binding `main.py`, specifying the path to your automaton file and the word length to check.

```sh
python main.py --file_path path/to/your/automaton.txt --word_length 2
```

#### C 🌐
Compile and run the C binding `main.c`, following the instructions prompted in the terminal.

```sh
gcc main.c -o main
./main
```

### 3. Review the Results 🎉
The scripts will output whether the automaton accepts all words of the given length.

## 🗂️ Repository Structure
```
├── CMakeLists.txt
├── README.md
├── automaton.example.txt
├── cmake-build-debug
├── length-1-automaton.txt
├── length-2-automaton.txt
├── main.c
└── main.py
```

## 🌈 Example Files
- **[automaton.example.txt](path/to/automaton.example.txt):** A sample automaton configuration file.
- **[length-1-automaton.txt](path/to/length-1-automaton.txt):** An automaton that accepts all words of length 1.
- **[length-2-automaton.txt](path/to/length-2-automaton.txt):** An automaton that accepts all words of length 2.
