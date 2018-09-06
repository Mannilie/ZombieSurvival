#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>

#include "CameraManager.h"
#include "HighScoresManager.h"
#include "Player.h"
#include "Textures.h"
#include "Button.h"
#include "GameObject.h"
#include "Weapon.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ZombieBox.h"

enum eGameStates	//Enumerator for Game States
{
	MAIN_MENU,
	GAME_PLAY,
	GAME_OVER,
	PAUSE_MENU,
	HIGH_SCORES,
	NEW_GAME
}; 

const int m_iMapDimension	= 1800;
const int m_iScreenWidth	= 900;
const int m_iScreenHeight	= 900;
float m_dPI = 3.1428571428571428f;

int main( int argc, char* argv[] )
{	
	//Point2D m_oGameScreen;
	Initialise(m_iScreenWidth, m_iScreenHeight, false, "Zombie Slayer - v1.0 (BETA) © Emmanuel Vaccaro");

	bool Exit = false;
	bool m_bInGame  = false;
	bool m_bHighScoresPrinted = false;
	bool m_bSavedGame = false;
	bool m_bNewGame = false;

	//Sprite creation
	unsigned int MapTexture = CreateSprite("./images/Maps/map_city.png", m_iMapDimension, m_iMapDimension, false);
	unsigned int ScrollingMap = CreateSprite("./images/Maps/map_scroll.png", m_iMapDimension, m_iMapDimension, false);
	unsigned int ZombieSurvivalText = CreateSprite("./images/UI/Text/txt_ZombieSurvival.png", 683, 111, true);
	unsigned int GameOverText = CreateSprite("./images/UI/Text/txt_GameOver.png", 683, 111, true);
	unsigned int PausedText = CreateSprite("./images/UI/Text/txt_Paused.png", 683, 111, true);
	unsigned int HighScoresText	= CreateSprite("./images/UI/Text/txt_HighScores.png", 683, 111, true);
	unsigned int PlayerTexture = CreateSprite("./images/Player/Trucker.png", 40, 49, true);
	unsigned int DarkTransparentBackground = CreateSprite("./images/UI/Backgrounds/HighScoresBackground.png", 550, 300, true);
	unsigned int PlayerStatsBar = CreateSprite("./images/UI/Backgrounds/HighScoresBackground.png", 900, 40, true);
	unsigned int GameOverScoreBackground = CreateSprite("./images/UI/Backgrounds/HighScoresBackground.png", 550, 50, true);

	eGameStates GameState;	//Declares enum as "GameStates"
	GameState = MAIN_MENU;	//Sets first screen to "MAIN_MENU"

	//Point2D's
	Point2D m_oVelocity;
	Point2D m_oCameraPosition;
	Point2D m_oPlayerPosition;

	m_oVelocity.x = 1;
	m_oVelocity.y = 1;
	m_oCameraPosition.x = 450;
	m_oCameraPosition.y = 600;
	m_oPlayerPosition.x = m_iMapDimension / 2;
	m_oPlayerPosition.y = m_iMapDimension / 2;


	//Game Objects
	GameObject m_oGameObject;
	HighScoresManager* m_oHighScoresManager = nullptr;
	ZombieSpawner* m_oZombieSpawner = nullptr;
	Player* oPlayer = nullptr;
	CameraManager m_oCamera(m_oVelocity, m_oCameraPosition);
	Weapon m_oWeapon(11, 45, m_oPlayerPosition);

	Button m_oStartButton("./images/UI/Buttons/btn_StartGame.png", 250, 150, Point2D(m_oCameraPosition.x / 2, m_oCameraPosition.y / 2 - 100));	//Draws START GAME button texture
	Button m_oHighScoreButton("./images/UI/Buttons/btn_HighScore.png", 250, 150, Point2D(m_oCameraPosition.x / 2, m_oCameraPosition.y / 2));	//Draws HIGH SCORE button texture
	Button m_oExitGameButton("./images/UI/Buttons/btn_ExitGame.png", 250, 150, Point2D(m_oCameraPosition.x / 2, m_oCameraPosition.y / 2 + 100));//Draws HIGH SCORE button texture
	Button m_oBackButton("./images/UI/Buttons/btn_BackButton.png", 250, 150, Point2D(m_oCameraPosition.x / 2, m_oCameraPosition.y / 2 + 100));	//Draws BACK button texture
	Button m_oResumeGameButton("./images/UI/Buttons/btn_ResumeGame.png", 250, 150, Point2D(m_oCameraPosition.x / 2, m_oCameraPosition.y / 2 + 100));//Draws RESUME GAME button texture
	Button m_oMainMenu("./images/UI/Buttons/btn_MainMenu.png", 250, 150, Point2D(m_oCameraPosition.x / 2, m_oCameraPosition.y / 2 + 100));		//Draws MAIN MENU button texture
	Button m_oRestartGame("./images/UI/Buttons/btn_RestartGame.png", 250, 150, Point2D(m_oCameraPosition.x / 2, m_oCameraPosition.y / 2 + 100));//Draws RESTART GAME button texture


	m_oHighScoresManager = new HighScoresManager();
	m_oZombieSpawner = new ZombieSpawner();
	oPlayer = new Player(PlayerTexture, 38, 45, m_oPlayerPosition);

	const int m_iPushObjectsDown = 340;
	const int m_iZombieAmount = m_oGameObject.GetZombieAmount();

	float m_fCamX, m_fCamY;
	int m_iCamX, m_iCamY;
	float m_fPlayerAngle;
	Zombie** m_oZombie	= m_oZombieSpawner->ReturnZombie();
	int m_iZombiesKilled;
	char m_cZombiesKilled[64];
	do 
    {
        //Clears screen
        ClearScreen();
		switch(GameState)
		{
			case MAIN_MENU:	//Displays the Main Menu screen
				DrawSprite(ScrollingMap);

				m_oCamera.MainMenuCamera();
				GetCameraPosition(m_fCamX, m_fCamY);
				MoveSprite(ZombieSurvivalText, m_fCamX + 450, m_fCamY + 160);
				m_oStartButton.Update(m_iScreenWidth / 2, m_iScreenHeight / 2 - 100);		//Updates the START button
				m_oHighScoreButton.Update(m_iScreenWidth / 2, m_iScreenHeight / 2);			//Updates the HIGH SCORE button
				m_oExitGameButton.Update(m_iScreenWidth / 2, m_iScreenHeight / 2 + 100);	//Updates the EXIT GAME button
				DrawString("Made by: Emmanuel Vaccaro", (int)m_fCamX + 260, (int)m_fCamY + 800);		//Draws string credits to programmer
				DrawString("Artists: Ilaria Youkhana, Darren Naidu, Scott Hamilton", (int)m_fCamX + 120, (int)m_fCamY + 850);	//Draws string credits to artists
				DrawSprite(ZombieSurvivalText);

				if(m_oStartButton.ButtonClicked() == true)
				{
					m_bNewGame = true;
					m_oHighScoresManager->NewGame();
					m_oStartButton.Reset();		//Resets the START button clicked value
					GameState = NEW_GAME;
				}else if(m_oHighScoreButton.ButtonClicked() == true)
				{
					GameState = HIGH_SCORES;
					m_bInGame = false;
					m_bSavedGame = false;
					m_oHighScoreButton.Reset(); //Resets the HIGH SCORE button clicked value
				}else if(m_oExitGameButton.ButtonClicked() == true)
				{
					Exit = true;
				}
				break;
			case GAME_PLAY:
				DrawSprite(MapTexture);

				m_oZombieSpawner->UpdateZombies(oPlayer);
				
				m_fPlayerAngle = oPlayer->GetDirection(m_dPI);
				m_oPlayerPosition = oPlayer->GetPlayerPos();
				m_oCamera.AdjustCamera(m_oPlayerPosition, m_iScreenWidth, m_iScreenHeight, m_iMapDimension);
				m_oWeapon.Update(m_fPlayerAngle, m_oPlayerPosition, m_iScreenWidth, m_iScreenHeight, m_oZombie);
				oPlayer->Update(m_fPlayerAngle);
				
				GetCameraPosition(m_fCamX, m_fCamY);
				m_iCamX = (int) m_fCamX;
				m_iCamY = (int) m_fCamY;
				MoveSprite(PlayerStatsBar, m_fCamX + 450, m_fCamY + 20);
				m_iZombiesKilled = m_oZombieSpawner->CurrentZombiesKilled();
				DrawString("Zombies Killed:", m_iCamX + 640, m_iCamY + 3);
				//Draws the amount of zombies killed
				_itoa_s(m_iZombiesKilled, m_cZombiesKilled, 10);
				DrawString(m_cZombiesKilled, m_iCamX + 835, m_iCamY + 3);

				
				oPlayer->Draw();
				
				m_oZombieSpawner->DrawZombies();
				m_oWeapon.Draw();
				DrawSprite(PlayerStatsBar);
				if(IsKeyDown(KEY_ESC))
				{
					GameState = PAUSE_MENU;
					m_bSavedGame = false;
				}
				if(oPlayer->GetPlayerHealth() <= 0)
				{
					GameState = GAME_OVER;
					m_bSavedGame = false;
				}
				break;
			case PAUSE_MENU:
				DrawSprite(MapTexture);

				m_oZombieSpawner->DrawZombies();
				oPlayer->Draw();	
				m_oWeapon.Draw();
				
				GetCameraPosition(m_fCamX, m_fCamY);
				MoveSprite(PausedText, m_fCamX + 450, m_fCamY + 160);
				m_oResumeGameButton.Update(m_iScreenWidth / 2, m_iScreenHeight / 2 - 100);		//Updates the START button
				m_oHighScoreButton.Update(m_iScreenWidth / 2, m_iScreenHeight / 2);			//Updates the HIGH SCORE button
				m_oMainMenu.Update(m_iScreenWidth / 2, m_iScreenHeight / 2 + 100);	//Updates the EXIT GAME button
				
				DrawSprite(PausedText);

				if(m_oResumeGameButton.ButtonClicked() == true)
				{	
					GameState = GAME_PLAY;	
					m_oResumeGameButton.Reset();		//Resets the START button clicked value
				}
				if(m_oHighScoreButton.ButtonClicked() == true)
				{
					GameState = HIGH_SCORES;
					m_bInGame = true;
					m_oHighScoreButton.Reset(); //Resets the HIGH SCORE button clicked value
				}
				if(m_oMainMenu.ButtonClicked() == true)
				{
					GameState = MAIN_MENU;
					m_bInGame = true;
					m_oMainMenu.Reset(); //Resets the HIGH SCORE button clicked value
				}
				if(m_bSavedGame == false)
				{
						m_oHighScoresManager->WriteToFile();
						m_bSavedGame = true;
				}
				break;
			case HIGH_SCORES:
				if(m_bInGame == true)
				{
					DrawSprite(MapTexture);
					m_oZombieSpawner->DrawZombies();
					oPlayer->Draw();	
					m_oWeapon.Draw();
					GetCameraPosition(m_fCamX, m_fCamY);
					MoveSprite(HighScoresText, m_fCamX + 450, m_fCamY + 160);

					m_oBackButton.Update(m_iScreenWidth / 2, m_iScreenHeight / 2 + 130);		//Updates the BACK button
					
					DrawSprite(HighScoresText);
					DrawSprite(DarkTransparentBackground);
					MoveSprite(DarkTransparentBackground, m_fCamX + 450, m_fCamY + 383);

					m_oHighScoresManager->PrintHighScores(m_fCamX, m_fCamY, false, m_iPushObjectsDown);
					if(m_oBackButton.ButtonClicked() == true)
					{
						GameState = PAUSE_MENU;
						m_oBackButton.Reset();		//Resets the BACK button clicked value
					}
				}
				else
				{
					DrawSprite(ScrollingMap);

					m_oCamera.MainMenuCamera();
					GetCameraPosition(m_fCamX, m_fCamY);
					MoveSprite(HighScoresText, m_fCamX + 450, m_fCamY + 160);
					
					m_oBackButton.Update(m_iScreenWidth / 2, m_iScreenHeight / 2 + 130);		//Updates the BACK button
					
					DrawSprite(HighScoresText);
					DrawSprite(DarkTransparentBackground);
					MoveSprite(DarkTransparentBackground, m_fCamX + 450, m_fCamY + 383);

					m_oHighScoresManager->PrintHighScores(m_fCamX, m_fCamY, false, m_iPushObjectsDown);
					if(m_oBackButton.ButtonClicked() == true)
					{
						GameState = MAIN_MENU;
						m_bInGame = false;
						m_oBackButton.Reset();		//Resets the BACK button clicked value
					}
				}
				break;
			case GAME_OVER:
				DrawSprite(MapTexture);

				m_oMainMenu.Update(m_iScreenWidth / 2 - 150, m_iScreenHeight / 2 + 290 - m_iPushObjectsDown);		//Updates the BACK button
				m_oRestartGame.Update(m_iScreenWidth / 2 + 150, m_iScreenHeight / 2 + 290 - m_iPushObjectsDown);	

				GetCameraPosition(m_fCamX, m_fCamY);
				m_iCamX = (int) m_fCamX;
				m_iCamY = (int) m_fCamY;
				MoveSprite(GameOverText, m_fCamX + 450, m_fCamY + 160);
				MoveSprite(HighScoresText, m_fCamX + 450, m_fCamY + 160 + m_iPushObjectsDown);

				DrawSprite(GameOverText);
				DrawSprite(GameOverScoreBackground);
				DrawSprite(HighScoresText);
				DrawSprite(DarkTransparentBackground);
				MoveSprite(GameOverScoreBackground, m_fCamX + 450, m_fCamY + 300);
				MoveSprite(DarkTransparentBackground, m_fCamX + 450, m_fCamY + 383 + m_iPushObjectsDown);

				m_oZombieSpawner->CurrentZombiesKilled();
				DrawString("Zombies Killed:", m_iCamX + 200, m_iCamY + 283);
				_itoa_s(m_iZombiesKilled, m_cZombiesKilled, 10);
				DrawString(m_cZombiesKilled, m_iCamX + 515, m_iCamY + 283);


				if(m_bSavedGame == false)
				{
					m_oHighScoresManager->UpdateHighScores(m_oZombieSpawner);
					m_oHighScoresManager->WriteToFile();
					m_bSavedGame = true;
				}
				if(m_oMainMenu.ButtonClicked() == true)
				{
					GameState = MAIN_MENU;
					m_oMainMenu.Reset();		//Resets the BACK button clicked value
				}
				if(m_oRestartGame.ButtonClicked() == true)
				{
					GameState = NEW_GAME;
					m_oRestartGame.Reset();		//Resets the BACK button clicked value
				}
				m_oHighScoresManager->PrintHighScores(m_fCamX, m_fCamY, true, m_iPushObjectsDown);
				break;
			case NEW_GAME:
				m_oVelocity.x = 1;
				m_oVelocity.y = 1;
				m_oCameraPosition.x = 450;
				m_oCameraPosition.y = 600;
				m_oPlayerPosition.x = m_iMapDimension / 2;
				m_oPlayerPosition.y = m_iMapDimension / 2;
				delete m_oHighScoresManager;
				delete m_oZombieSpawner;
				delete oPlayer;
				m_oHighScoresManager = nullptr;
				m_oHighScoresManager = new HighScoresManager();
				m_oZombieSpawner = nullptr;
				m_oZombieSpawner = new ZombieSpawner();
				oPlayer = nullptr;
				oPlayer = new Player(PlayerTexture, 38, 45, m_oPlayerPosition);
				m_oStartButton.Reset();		//Resets the START button clicked value
				m_oHighScoreButton.Reset();		
				m_oExitGameButton.Reset();		
				m_oBackButton.Reset();	
				Exit = false;
				m_bInGame  = false;
				m_bHighScoresPrinted = false;
				m_bSavedGame = false;
				m_bNewGame = false;
				m_oZombie = m_oZombieSpawner->ReturnZombie();
				GameState = GAME_PLAY;
				break;
		}
    } while (FrameworkUpdate() == false && Exit == false);
	delete m_oHighScoresManager;
	delete m_oZombieSpawner;
	delete oPlayer;

	Shutdown();

    return 0;
}