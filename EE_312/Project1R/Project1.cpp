/*
 * Project1.cpp

Name: Alan Tan
EID: AJT 2459
Unique: 16675
TA: Kamran Saleem

Project 1 





 * EE312 Fall 2014
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

#include <cstdlib>
#include <cctype>
#include <cstring>



/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent 
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * (while there are always exceptions, a good rule of thumb is about 15 lines in a function).
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */



void spellCheck(char article[], char dictionary[]);
bool isInDictionary (char *word, char *dictionary);
void convertToLower (char *dest, char *string);
bool stringsAreEqualIgnoreCase(char *str1, char *str2);



void spellCheck(char article[], char dictionary[]) {
	/* TESTING convertToLower() and stringsAreEqualIgnoreCase()
	char *test_str = "HEllo World";
	printf("Orig str: %s\n", test_str);
	char test_str_lower[100];
	convertToLower(test_str_lower, test_str);
	printf("toLower: %s\n", test_str_lower);

	char *test_str2 = "hello WORLD";
	if (stringsAreEqualIgnoreCase(test_str, test_str2)){
		printf("equals1 success\n" );
	}
	else{
		printf("equals1 fail\n");
	}
	if(stringsAreEqualIgnoreCase("123ASDF","123ASDF")){
		printf("equals2 success\n" );
	}
	else{
		printf("equals2 fail\n");
	}
	*/
	
	char *current_char = article;
	char *start_char = NULL;
	while(*current_char != 0){
		if(start_char == NULL){
			if (std::isalpha(*current_char)){
				start_char = current_char;
			}

		}
		else {
			if (!std::isalpha(*current_char)){
				//we now have a word located from addr [start_char, current_char)
				int32_t word_size = current_char - start_char;
				if(word_size > 1){
					//we have a valid word len >= 2
					char word[word_size + 1];
					std::memcpy((void *)word, (void *)start_char, word_size+1);
					word[word_size] = 0;
					//printf("Checking: %s\n", word);
					//printf("start_char = %u, current_char = %u\n", (uint32_t)start_char, (uint32_t)current_char);
					if(!isInDictionary(word, dictionary)){
						printf("%s\n", word);
					}
				}
				start_char = NULL;
			}
		}

		current_char++;
	}
	//special case: words are terminated with NULL..
	//copy/paste from loop again.
	if(start_char != NULL){
		int32_t word_size = current_char - start_char;
		if(word_size > 1){
			//we have a valid word len >= 2
			char word[word_size + 1];
			std::memcpy((void *)word, (void *)start_char, word_size+1);
			word[word_size] = 0;
			//printf("Checking: %s\n", word);
			//printf("start_char = %u, current_char = %u\n", (uint32_t)start_char, (uint32_t)current_char);
			if(!isInDictionary(word, dictionary)){
				printf("\"%s\"\n", word);
			}
		}
	}

}

void convertToLower(char *dest, char *string){
	for(int32_t i = 0; i< (int32_t)std::strlen(string) + 1; i++){
		dest[i] = std::tolower(string[i]);
	}
}

bool stringsAreEqualIgnoreCase(char *str1, char *str2){
	char temp_str1[std::strlen(str1) + 1];
	char temp_str2[std::strlen(str2) + 1];
	std::strcpy(temp_str1, str1);
	std::strcpy(temp_str2, str2);
	convertToLower(temp_str1, temp_str1);
	convertToLower(temp_str2, temp_str2);
	if (std::strcmp(temp_str1, temp_str2) == 0){
		return true;
	}
	else {
		return false;
	}
}

bool isInDictionary (char *word, char *dictionary){
	char temp_dictionary[std::strlen(dictionary) + 1];
	std::strcpy(temp_dictionary, dictionary);

	char *dictionary_entry = std::strtok(temp_dictionary, "\n");
	while (dictionary_entry != NULL){
		if (stringsAreEqualIgnoreCase(word, dictionary_entry)){
			return true;
		}
		dictionary_entry = std::strtok(NULL, "\n");
	}
	return false;

}
