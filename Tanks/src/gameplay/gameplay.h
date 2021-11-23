#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "tank.h"
#include "player.h"
#include "enemy.h"
#include "base.h"
#include "wall.h"

using namespace sf;
using namespace std;

namespace Battle_City 
{	
	const short maxKeys = 20;

	const String keysUIFiles[maxKeys] = {"assets/UI/letters/ALetter.png", "assets/UI/letters/DLetter.png", "assets/UI/letters/DownArrow.png", "assets/UI/letters/FLetter.png", "assets/UI/letters/GLetter.png",
	"assets/UI/letters/HLetter.png", "assets/UI/letters/I_Letter.png", "assets/UI/letters/JLetter.png", "assets/UI/letters/KLetter.png", "assets/UI/letters/L_Letter.png", 
	"assets/UI/letters/LCtrl.png", "assets/UI/letters/LeftArrow.png", "assets/UI/letters/P_Letter.png", "assets/UI/letters/RCtrl.png", "assets/UI/letters/RightArrow.png", 
	"assets/UI/letters/SLetter.png", "assets/UI/letters/Space.png", "assets/UI/letters/TLetter.png", "assets/UI/letters/UpArrow.png", "assets/UI/letters/WLetter.png" };			
	
	const String playerOneTexturesFiles[maxTextures] = {
		"assets/player/playerOneTankDownOne.png", "assets/player/playerOneTankDownTwo.png",
		"assets/player/playerOneTankLeftOne.png", "assets/player/playerOneTankLeftTwo.png",
		"assets/player/playerOneTankRightOne.png", "assets/player/playerOneTankRightTwo.png",
		"assets/player/playerOneTankUpOne.png", "assets/player/playerOneTankUpTwo.png" };

	const String playerTwoTexturesFiles[maxTextures] = {
		"assets/player/playerTwoTankDownOne.png", "assets/player/playerTwoTankDownTwo.png",
		"assets/player/playerTwoTankLeftOne.png", "assets/player/playerTwoTankLeftTwo.png",
		"assets/player/playerTwoTankRightOne.png", "assets/player/playerTwoTankRightTwo.png",
		"assets/player/playerTwoTankUpOne.png", "assets/player/playerTwoTankUpTwo.png" };

	const String playerThreeTexturesFiles[maxTextures] = {
		"assets/player/playerThreeTankDownOne.png", "assets/player/playerThreeTankDownTwo.png",
		"assets/player/playerThreeTankLeftOne.png", "assets/player/playerThreeTankLeftTwo.png",
		"assets/player/playerThreeTankRightOne.png", "assets/player/playerThreeTankRightTwo.png",
		"assets/player/playerThreeTankUpOne.png", "assets/player/playerThreeTankUpTwo.png" };

	const String playerFourTexturesFiles[maxTextures] = {
		"assets/player/playerFourTankDownOne.png", "assets/player/playerFourTankDownTwo.png",
		"assets/player/playerFourTankLeftOne.png", "assets/player/playerFourTankLeftTwo.png",
		"assets/player/playerFourTankRightOne.png", "assets/player/playerFourTankRightTwo.png",
		"assets/player/playerFourTankUpOne.png", "assets/player/playerFourTankUpTwo.png" };



	const String enemyTexturesFiles[maxTextures] = {
		"assets/enemy/enemyTankDownOne.png", "assets/enemy/enemyTankDownTwo.png",
	 	"assets/enemy/enemyTankLeftOne.png", "assets/enemy/enemyTankLeftTwo.png",
		"assets/enemy/enemyTankRightOne.png", "assets/enemy/enemyTankRightTwo.png",
		"assets/enemy/enemyTankUpOne.png", "assets/enemy/enemyTankUpTwo.png" };

	const String nonDestroyableWallTextureFile = "assets/wall/nonDestroyableWall.png";
	const String destroyableWallTextureFile = "assets/wall/destroyableWall.png";
	const String mapLimitingWallFile = "assets/wall/mapLimitingWall.png";

	const String textFontFile = "assets/fonts/PressStart2P.ttf";

	//assets https://opengameart.org/content/heart-pixel-arts
	const short maxHearts = 4;

	const String heartsFiles[maxHearts] = { "assets/UI/hearts/yellow_heart_ pixel_art.png", "assets/UI/hearts/blue_heart_ pixel_art.png" , 
		"assets/UI/hearts/green_heart_ pixel_art.png" , "assets/UI/hearts/red_heart_ pixel_art.png" };

	const Keyboard::Key playerOneInputKeys[maxInputKeys]{ Keyboard::Key::RControl, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down};
	const Keyboard::Key playerTwoInputKeys[maxInputKeys]{ Keyboard::Key::LControl, Keyboard::Key::A, Keyboard::Key::D, Keyboard::Key::W, Keyboard::Key::S };
	const Keyboard::Key playerThreeInputKeys[maxInputKeys]{ Keyboard::Key::Space, Keyboard::Key::F, Keyboard::Key::H, Keyboard::Key::T, Keyboard::Key::G };
	const Keyboard::Key playerFourInputKeys[maxInputKeys]{ Keyboard::Key::P, Keyboard::Key::J, Keyboard::Key::L, Keyboard::Key::I, Keyboard::Key::K };

	const short maxEnemyTanks = 5;
	const short maxPlayers = 4;
	const short maxDestroyableWalls = 4;
	const short maxNonDestroyableWalls = 4;	
	const short maxMapLimitingWalls = 4;

	const float limitingWallXOffset = 135.0f;
	const float limitingWallYOffset = 100.0f;
	const float limitingWallWidth = 15.0f;
	const float limitingWallHeight = 15.0f;		

	const Vector2f UISpriteSize = {55.0f, 55.0f};	
	const Vector2f heartsSpriteSize = {69.0f, 69.0f};
	const Vector2f heartsSpritesSeparation = { 5.0f, 15.0f};

	class Gameplay
	{
	private:
		bool gameOver;
		short windowWidth;
		short windowHeigth;
		short numberOfPlayers;
		const char* title = "TANKS";
		Texture inputKeysUITextures[maxKeys];
		Sprite inputKeysUISprites[maxKeys];
		Texture heartsTextures[maxHearts];
		Sprite heartsSprites[maxHearts];
		Font textFont;
		Text enemiesLeftMeassegeText;
		Text enemiesLeftText;
		RenderWindow window;		
		Player* playerTanks[maxPlayers];
		Enemy* enemyTanks[maxEnemyTanks];
		Base* militaryBase;
		Wall* destroyableWalls[maxDestroyableWalls];
		Wall* nonDestroyableWalls[maxNonDestroyableWalls];
		Wall* mapLimitingWalls[maxMapLimitingWalls];
		Clock clock;
		Time dt;		
	public:
		Gameplay(short numberOfPlayers);
		~Gameplay();

		void Input();
		void Update(Time dt);
		void Draw();
		void Run();

		void WinCondition();
		void DefeatCondition();		

		void EnemiesBulletsCollideWithPlayers();
		void DestroyEnemyTanksWhenHit();
		bool BulletsCollideWithMilitaryBase();
		void DestroyDestroyableWallsWhenHit();
		void DestroyBulletsWhenHitNonDestroyableWalls();
		void TanksCollideWithWalls();
		void TanksCollideWithMilitaryBase();
		void TanksCollideWithEachOther();
		bool AllTanksDestroyed();		
		void DestroyPlayerTankIfHasNoLifesLeft(short index);

		void DrawTanksMoveKeysUI();
		void DrawHearts();		
	};
}

#endif
