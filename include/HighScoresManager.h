////////////////////////////////////////////////////////////
// File: HighScoresManager.h
// Author: Emmanuel Vaccaro
// Date: 14/03/2014
// Brief: Used to manage all of the high score feature's mathematics
////////////////////////////////////////////////////////////
#ifndef __HIGHSCORESMANAGER_H__
#define __HIGHSCORESMANAGER_H__

#include "ZombieSpawner.h"
#include "GameObject.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "sqlite3.h"

class HighScoresManager	: public GameObject
{
private:
	std::vector<int> m_vHighScores;		//Stores the high scores from either text file or database
	std::ifstream m_fsHighScores_Read;	//Declares an input file stream to read the High Scores text file
	std::ofstream m_fsHighScores_Write;	//Declares an output file stream to write into the High Scores text file
	char m_cHighScoresString[64];	//Used to obtain the text version from the high scores text file
	char m_cPlaces[10];				//Stores the places as a char e.g. "1st" "2nd" "3rd" etc
	int m_iZombiesKilled;			//Used to store the amount of zombies killed in the previous game
	int m_iTextFileIndex;			//used as an array index for reading the high scores text file
	int m_iPushDown;				//Used to store the amount of pixels to push the high score screen elements down at game over screen
	int m_iNewGame;					//Used to check if the player has entered a new game using an int (increments when new game is made)
	int m_iMaxFilelength;			//Used to store the maximum amount of lines in the high scores text file
	int m_cHighScores;				//Char array used to store all the high scores obtained from text file
	int Previous, Key;				//Integers used for insertion sort calculation purposes
	sqlite3 *HighScoresDatabase;
	std::string sqlStatement;
	std::string m_sHighScores;
	char* errorMsg;
public:
	HighScoresManager();	//Default constructor
	~HighScoresManager();	//Default deconstructor
	void UpdateHighScores(ZombieSpawner* a_oZombieSpawner);	//void function that Updates the high scores
	void PrintHighScores(float a_fCamX, float a_fCamY, bool a_bGameOverScreen, int a_iPushDown);	//void function that Prints the high scores
	static int Callback(void* notUsed, int numArgs, char **data, char **columnName);
	void GetDatabase();
	bool CheckFileIsEmpty(int a_iIndex);	//bool function that checks if the high scores file is empty
	void SortHighScores();	//void fun ction that sorts the high scores using insertion sort
	void WriteToFile();	//void function that writes to the high scores text file
	void NewGame();	//void function that increments the new game once the player starts a new game
};

#endif //__HIGHSCORESMANAGER_H__