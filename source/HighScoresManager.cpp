#include "HighScoresManager.h"

HighScoresManager::HighScoresManager()
{
	m_iTextFileIndex = 0;	//Sets the file index to 0
	m_iMaxFilelength = 5;	//Sets the maximum amount of high scores to 5
	int FileIncrementer = 0;
	m_fsHighScores_Read.open("HighScores.txt", std::ios_base::app);	//Opens the text file in append mode
	if(m_fsHighScores_Read.is_open())	//Checks if the text file is open
	{
		while(m_fsHighScores_Read.good())	//Executes lines of code until it has reached the EOF (End of File)
		{
			m_fsHighScores_Read >> m_cHighScores; //Reads the next line into the array
			m_vHighScores.push_back(m_cHighScores);
			m_iTextFileIndex++;	//Increments the next index
		}
		m_iTextFileIndex--;	//Removes the "null" terminator of the array
		m_fsHighScores_Read.clear();	//Clears the text file's flags
		m_fsHighScores_Read.close();	//Closes the file
		m_iNewGame = m_iTextFileIndex;	//Sets the new game value to the text file index
		m_fsHighScores_Write.open("HighScores.txt", std::ios_base::app);	//Opens the text file in append mode
		if(m_fsHighScores_Write.is_open())
		{
			while(FileIncrementer < m_iMaxFilelength)
			{
				if(m_vHighScores[FileIncrementer] < 0)
				{
					m_fsHighScores_Write << 0 << "\n"; //Initialises the high scores
				}
				FileIncrementer++;
			}
			m_fsHighScores_Write.clear();	//Clears the text file's flags
			m_fsHighScores_Write.close();	//Closes the file
		}
	}
	SortHighScores();	//Calls a function to sort the array's values
	GetDatabase();
}

HighScoresManager::~HighScoresManager(){}

void HighScoresManager::UpdateHighScores(ZombieSpawner* a_oZombieSpawner)
{
	m_iZombiesKilled = a_oZombieSpawner->CurrentZombiesKilled();	//Gets the current zombie kills
	m_iTextFileIndex = m_iNewGame;	//Sets the text file index to the new game's so it can print the new kills
	m_vHighScores[m_iNewGame] = m_iZombiesKilled;	//sets the high score array new index to the new zombie's killed
	SortHighScores();	//Sorts the modified array
	GetDatabase();
}

void HighScoresManager::PrintHighScores(float a_fCamX, float a_fCamY, bool a_bGameOverScreen, int a_iPushDown)
{
	if(a_bGameOverScreen)	//Checks if the game screen is the game over screen
	{
		m_iPushDown = a_iPushDown;	//Pushes all the elements down the page
	}else
	{
		m_iPushDown = 0;	//Keeps the high score screen elements to their original position
	}
	m_iCamX = (int) a_fCamX;	//Sets the camera location from a float to an int
	m_iCamY = (int) a_fCamY;
	DrawString("Place:",  m_iCamX + 200, m_iCamY + 240 + m_iPushDown);			//Draws "Place" on the screen
	DrawString("Zombies Killed:",  m_iCamX + 510, m_iCamY + 240 + m_iPushDown);	//Draws "Zombies Killed" on the screen
	for(int i = 0; i <= 4; i++)
	{
		if(CheckFileIsEmpty(i))	//Checks if the high scores file array is empty
		{
			DrawString("<No Score>", m_iCamX + 510, m_iCamY + 280 + (i * 50) + m_iPushDown);	//Draws "<No Score> if there is nothing to display
		}
		else
		{
			_itoa_s(m_vHighScores[i], m_cHighScoresString, 10);	//Converts the high score array values to a char
			DrawString(m_cHighScoresString, m_iCamX + 510, m_iCamY + 280 + (i * 50) + m_iPushDown);	//Draws the high score
		} 
	}	
	DrawString("1st", m_iCamX + 200, m_iCamY + 280 + (0 * 50) + m_iPushDown);
	DrawString("2nd", m_iCamX + 200, m_iCamY + 280 + (1 * 50) + m_iPushDown);
	DrawString("3rd", m_iCamX + 200, m_iCamY + 280 + (2 * 50) + m_iPushDown);	//Draws all the places e.g. "1st" "2nd" "3rd"
	DrawString("4th", m_iCamX + 200, m_iCamY + 280 + (3 * 50) + m_iPushDown);
	DrawString("5th", m_iCamX + 200, m_iCamY + 280 + (4 * 50) + m_iPushDown);

}

bool HighScoresManager::CheckFileIsEmpty(int a_iIndex)
{
	if(m_vHighScores[a_iIndex] <= 0)	//Checks if the array index is garbage
	{
		return true;	//Returns true
	}
	else
	{
		return false;	//Returns false
	}
}

void HighScoresManager::SortHighScores()
{
	Previous = 0;	//Always sets these variables to the start position
	Key = 0;
	//Insertion sort
	for (int i = 0; i <= m_iTextFileIndex; i++) //Checks through each element of the array
    {
		Key = m_vHighScores[i];	//Sets the first key element item
		Previous = i-1;			//Sets the previous element index
		while((Previous >= 0) && (m_vHighScores[Previous] < Key))	//Executes lines of code if the previous index element is less than the key element
		{
		        m_vHighScores[Previous + 1] = m_vHighScores[Previous]; //Pushes the new element up 
		        Previous -= 1;	//Index is set back one position
		}
		m_vHighScores[Previous + 1] = Key; //The new element in the previous spot is the key's element
    }
}

void HighScoresManager::WriteToFile()
{
	m_fsHighScores_Write.open("HighScores.txt", std::ios_base::out | std::ios_base::app && std::ios_base::trunc);	//Opens an output file in append and truncation mode
	if(m_fsHighScores_Write.is_open())	//Checks if the file is open
	{
		for(int i = 0; i <= m_iTextFileIndex; i++)
		{
			m_fsHighScores_Write << m_vHighScores[i] << "\n"; //Enters the new high score into the text file and shifts down a line
		}
		m_fsHighScores_Write.close();	//Closes the text file
	}
}

void HighScoresManager::NewGame()
{
	m_iNewGame++; //Increments the new game
}

void HighScoresManager::GetDatabase()
{
	HighScoresDatabase = NULL;
	errorMsg = NULL;
	sqlite3_open("HighScores.db", &HighScoresDatabase);
	
	sqlStatement =  "CREATE TABLE IF NOT EXISTS SCORES(HIGHSCORES INT);";
	sqlite3_exec(HighScoresDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);
	
	sqlStatement =  "DELETE FROM SCORES;";
	sqlite3_exec(HighScoresDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	sqlStatement =  "VACUUM;";
	sqlite3_exec(HighScoresDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);
	for(int i = 0; i < m_iTextFileIndex; i++) //INSERTING into table
	{
		if(m_vHighScores[i] > 0)
		{
			sqlStatement = "INSERT INTO SCORES(HIGHSCORES)"\
			"VALUES(" + std::to_string(m_vHighScores[i]) + ");"; 
			sqlite3_exec(HighScoresDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);
		}
	}
	sqlite3_close(HighScoresDatabase);
}

int HighScoresManager::Callback(void* notUsed, int numArgs, char **data, char **columnName)
{

    float myFloat = 4.0;

    for(int i = 0; i < numArgs; i++)
    {
        std::cout << columnName[i] << ": " << data[i] << std::endl;
    }

    return 0;
}