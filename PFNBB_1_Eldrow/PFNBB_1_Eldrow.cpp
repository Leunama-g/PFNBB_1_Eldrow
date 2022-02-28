// Written By: Amanuel Getachew
// Purpose: Figure out the best possible word for the first guess in the game wordle
// Started: Feb 22, 2022

#include <iostream>
#include <fstream>
#include <string.h>
#include <thread>

using namespace std;

struct letters {

	char letter = ' ';
	int char_occur = 0;
};

struct Words {
	string word;
	int score = 0;
};


/*
	file handler functions
*/

void progressbar(float total, float* progress, int waitfor = 500, int size = 25) {
	if (size < 1)
		size = 25;

	if (waitfor < 1)
		waitfor = 500;

	int percent = 0;
	while (total != *progress || percent != 25) {
		percent = (*progress / total) * size;
		system("cls");
		cout << endl << "Loading words from file to memory: ";
		cout << "[";
		for (int i = 0; i < size; i++) {
			if (percent > i)
				cout << "=";
			else
				cout << " ";
		}
		cout << "]";
	} 
	cout << endl << "done...";
	cin.get();
}

void readFromFile(string* wordList) {

	ifstream file("Assets/words.txt");
	float progress = 0;

	thread PB_thread(progressbar, 5757, &progress, 100, 25);

	if (!file.is_open()) {
		cout << "File did not open correctly!!(Reading From File Failed)";
	}
	else {
		
		for (int i = 0; i < 5757; i++) {
			file >> wordList[i];
			progress = i + 1;
		}	
	}
	file.close();
	PB_thread.join();	
}

void sort(letters* letter) {
	letters temp;
	for (int i = 0; i < 26; i++) {
		for (int j = i + 1; j < 26; j++) {
			if (letter[i].char_occur < letter[j].char_occur) {
				temp = letter[i];
				letter[i] = letter[j];
				letter[j] = temp;
			}

		}
	}
}

void sort(Words* words) {
	Words temp;
	for (int i = 0; i < 26; i++) {
		for (int j = i + 1; j < 26; j++) {
			if (words[i].score < words[j].score) {
				temp = words[i];
				words[i] = words[j];
				words[j] = temp;
			}

		}
	}
}

void bestword(string* wordList, letters* letter, Words* words) {
	for (int i = 0; i < 5757; i++) {
		words[i].word = wordList[i];
		for (int j = 0; j < 5; j++) {
			words[i].score += letter[wordList[i][j] - 97].char_occur;
		}
	}
}

void rankLetters(string* wordList, int size, int beg_index, letters* letters, Words* words) {

	for (int j = beg_index; j < beg_index + size; j++) {
		for (int i = 0; i < 5; i++) {
			letters[wordList[j][i] - 97].char_occur++;
		}
	}
	bestword(wordList, letters, words);
	sort(words);
	sort(letters);
}





void rankgraph(letters* letter) {
	int percentage;
	for (int i = 0; i < 26; i++) {
		cout << i + 1 << ". " << letter[i].letter << ": ";
		percentage = (float(letter[i].char_occur) / float(28785)) * 1000;
		for (int j = 0; j < percentage; j++) 
			cout << "-";
		cout << endl;
	}
	cout << "Continue...";
	cin.get();
}

void bestFive(Words* words) {
	for (int i = 0; i < 30; i++) {
		cout << i + 1 << ". " << words[i].word << " (Score = " << words[i].score << ")" << endl;
	}
	cin.get();
}


int main()
{
	string* wordList = new string[5757];

	//adds the words from words.txt file to memory
	readFromFile(wordList);

	system("cls");
	//keeps count of each letter occurrence 
	letters letter[26];
	Words* words = new Words[5757];

	for (int i = 0; i < 26; i++) {
		letter[i].letter = i + 97;
		
	}

	rankLetters(wordList, 5757, 0, letter, words);
	
	rankgraph(letter);
	system("cls");
	bestFive(words);

	//delete wordList;
	//delete words;
	cout << "done...";
	cin.get();
	return 0;
}





