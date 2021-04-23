/*********************
* @author Jake Rhoads, Branden Thome
* @class CS 3150
* @project Dungeon Crawler Competition
* @date 10/26/2020
*******/


#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Entity.h"
#include <list>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameDriver : public olc::PixelGameEngine
{

private:

	/******************************************************************************
	*							 Private Class Variables						  *
	******************************************************************************/
	//game loop variables
	float frameRate = 1.0f / 925.0f;
	float timeLength = 0.0f;
	
	//setting tile size
	const int TILE_WIDTH = 64;
	const int TILE_HEIGHT = 64;

	//combat log variables
	std::string sUpdate = "";
	list <std::string> combatLog;
	list<std::string>::iterator it;

	//player character variables
	float speed = 200;
	float xPlayer = 0;
	float yPlayer = 0;
	float xTopLeft = 0;
	float yTopLeft = 0;
	float xTopRight = 0;
	float yTopRight = 0;
	float xBotLeft = 0;
	float yBotLeft = 0;
	float xBotRight = 0;
	float yBotRight = 0;
	int direction = 0;
	int nextImage = 0;
	float imageDuration = .15;
	float imageCurrent = 0;
	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;
	bool axeEpd = false;

	//map variables
	wstring sMap;
	wstring sMapObjects;
	int groundCounter = 0;
	int nLevelWidth = 0;
	int nLevelHeight = 0;
	float decalDuration = 1.0f;
	float currentDuration = 0.0f;
	int bleedCounter = 1;
	float bleedDuration = 5.0f;
	float bleedCurrent = 0.0f;
	bool drawBattle = false;
	bool drawTrap = false;
	bool drawHeal = false;
	bool bleeding = false;
	bool doorOpen = false;
	bool win = false;
	olc::vf2d mapPos; //position variable needed to send things to the draw method - contains x and y point
	
	//Entity objects
	Entity hero;
	Entity enemy;

public:
	GameDriver(){sAppName = "Dungie Wungie UwU";}//Constructor that gives application its name and prints it at the top of the window

	/******************************************************************************
	*							 Public Class Variables							  *
	******************************************************************************/

	olc::Sprite* dragon = nullptr;
	olc::Sprite* grass = nullptr;
	olc::Sprite* wall = nullptr;
	olc::Sprite* player = nullptr;
	olc::Sprite* dog = nullptr;
	olc::Sprite* healthPot = nullptr;
	olc::Sprite* parchment = nullptr;
	olc::Sprite* solidBlock = nullptr;
	olc::Sprite* minoDead = nullptr;
	olc::Sprite* minoAlive = nullptr;
	olc::Sprite* ghostAlive = nullptr;
	olc::Sprite* ghostDead = nullptr;
	olc::Sprite* bossAlive = nullptr;
	olc::Sprite* bossDead = nullptr;
	olc::Sprite* crossSwords = nullptr;
	olc::Sprite* trap = nullptr;
	olc::Sprite* heal = nullptr;
	olc::Sprite* youDied = nullptr;
	olc::Sprite* axe = nullptr;
	olc::Sprite* axeWpn = nullptr;
	olc::Sprite* floor1 = nullptr;
	olc::Sprite* floor2 = nullptr;
	olc::Sprite* floor3 = nullptr;
	olc::Sprite* nCap = nullptr;
	olc::Sprite* sCap = nullptr;
	olc::Sprite* eCap = nullptr;
	olc::Sprite* wCap = nullptr;
	olc::Sprite* innerHWall = nullptr;
	olc::Sprite* innerVWall = nullptr;
	olc::Sprite* topWall1 = nullptr;
	olc::Sprite* topWall2 = nullptr;
	olc::Sprite* bottomWall = nullptr;
	olc::Sprite* rockWall = nullptr;
	olc::Sprite* torchLight = nullptr;
	olc::Sprite* trc = nullptr;
	olc::Sprite* tlc = nullptr;
	olc::Sprite* blc = nullptr;
	olc::Sprite* brc = nullptr;
	olc::Sprite* lw = nullptr;
	olc::Sprite* rw = nullptr;
	olc::Sprite* exitClosed = nullptr;
	olc::Sprite* exitOpen = nullptr;
	olc::Sprite* victory = nullptr;

	olc::Decal* dragonDec = nullptr;
	olc::Decal* grassDec = nullptr;
	olc::Decal* wallDec = nullptr;
	olc::Decal* playerDec = nullptr;
	olc::Decal* dogDec = nullptr;
	olc::Decal* healthPotDec = nullptr;
	olc::Decal* updateDec = nullptr;
	olc::Decal* parchmentDec = nullptr;
	olc::Decal* solidBlockDec = nullptr;
	olc::Decal* minoDeadDec = nullptr;
	olc::Decal* minoAliveDec = nullptr;
	olc::Decal* ghostDeadDec = nullptr;
	olc::Decal* ghostAliveDec = nullptr;
	olc::Decal* bossDeadDec = nullptr;
	olc::Decal* bossAliveDec = nullptr;
	olc::Decal* crossSwordsDec = nullptr;
	olc::Decal* trapDec = nullptr;
	olc::Decal* healDec = nullptr;
	olc::Decal* youDiedDec = nullptr;
	olc::Decal* axeDec = nullptr;
	olc::Decal* axeWpnDec = nullptr;
	olc::Decal* floor1Dec = nullptr;
	olc::Decal* floor2Dec = nullptr;
	olc::Decal* floor3Dec = nullptr;
	olc::Decal* nCapDec = nullptr;
	olc::Decal* sCapDec = nullptr;
	olc::Decal* eCapDec = nullptr;
	olc::Decal* wCapDec = nullptr;
	olc::Decal* innerWDec = nullptr;
	olc::Decal* innerVDec = nullptr;
	olc::Decal* topWall1Dec = nullptr;
	olc::Decal* topWall2Dec = nullptr;
	olc::Decal* bottomWallDec = nullptr;
	olc::Decal* rockWallDec = nullptr;
	olc::Decal* torchLightDec = nullptr;
	olc::Decal* trcDecal = nullptr;
	olc::Decal* tlcDecal = nullptr;
	olc::Decal* brcDecal = nullptr;
	olc::Decal* blcDecal = nullptr;
	olc::Decal* lwDecal = nullptr;
	olc::Decal* rwDecal = nullptr;
	olc::Decal* exitOpenDec = nullptr;
	olc::Decal* exitClosedDec = nullptr;
	olc::Decal* victoryDec = nullptr;


public:
	//called only once at the very start
	bool OnUserCreate() override
	{
		//************ TEST CODE ****************************
		

		//Initialize hero and enemy
		hero = Entity( "Hobo", 120, 10);

		
		//***********************************************************



		/******************************************************************************
		*                     Load Images Into Sprites and Decals				      *
		******************************************************************************/
		//sprite section -loaded directly from resource file
		dragon = new olc::Sprite("./res/dragon.png");
		grass = new olc::Sprite("./res/grass.png");
		wall = new olc::Sprite("./res/bloodWall.png");
		player = new olc::Sprite("./res/playerSheet.png");
		dog = new olc::Sprite("./res/dog.png");
		healthPot = new olc::Sprite("./res/healthPot.png");
		parchment = new olc::Sprite("./res/gameInfo.png");
		solidBlock = new olc::Sprite("./res/solidBlock.png");
		minoDead = new olc::Sprite("./res/minotaurDead.png");
		minoAlive = new olc::Sprite("./res/minotaurAlive.png");
		ghostDead = new olc::Sprite("./res/ghostDead.png");
		ghostAlive = new olc::Sprite("./res/ghostAlive.png");
		bossDead = new olc::Sprite("./res/bossDead.png");
		bossAlive = new olc::Sprite("./res/bossAlive.png");
		crossSwords = new olc::Sprite("./res/crossSwords.png");
		trap = new olc::Sprite("./res/trap.png");
		heal = new olc::Sprite("./res/heal.png");
		youDied = new olc::Sprite("./res/youDied.png");
		axe = new olc::Sprite("./res/axe.png");
		axeWpn = new olc::Sprite("./res/axeWpn.png");
		floor1 = new olc::Sprite("./res/floor1.png");
		floor2 = new olc::Sprite("./res/floor2.png");
		floor3 = new olc::Sprite("./res/floor3.png");
		nCap = new olc::Sprite("./res/northWCap.png");
		sCap = new olc::Sprite("./res/southWCap.png");
		eCap = new olc::Sprite("./res/eastWCap.png");
		wCap = new olc::Sprite("./res/westWCap.png");
		innerHWall = new olc::Sprite("./res/innerWallHorizontal.png");
		innerVWall = new olc::Sprite("./res/innerWallVertical.png");
		topWall1 = new olc::Sprite("./res/Topwall1.png");
		topWall2 = new olc::Sprite("./res/Topwall2.png");
		bottomWall = new olc::Sprite("./res/BottomMap.png");
		rockWall = new olc::Sprite("./res/innerWallHEmpty.png");
		torchLight = new olc::Sprite("./res/torchLight.png");
		trc = new olc::Sprite("./res/topRightCorner.png");
		tlc = new olc::Sprite("./res/topLeftCorner.png");
		blc = new olc::Sprite("./res/bottomLeftCorner.png");
		brc = new olc::Sprite("./res/bottomRightCorner.png");
		lw = new olc::Sprite("./res/leftWall.png");
		rw = new olc::Sprite("./res/rightWall.png");
		exitOpen = new olc::Sprite("./res/exitOpen.png");
		exitClosed = new olc::Sprite("./res/exitClosed.png");
		victory = new olc::Sprite("./res/victory.png");

		//decal section
		dragonDec = new olc::Decal(dragon);
		grassDec = new olc::Decal(grass);
		wallDec = new olc::Decal(wall);
		playerDec = new olc::Decal(player);
		dogDec = new olc::Decal(dog);
		healthPotDec = new olc::Decal(healthPot);
		parchmentDec = new olc::Decal(parchment);
		solidBlockDec = new olc::Decal(solidBlock);
		minoDeadDec = new olc::Decal(minoDead);
		minoAliveDec = new olc::Decal(minoAlive);
		ghostDeadDec = new olc::Decal(ghostDead);
		ghostAliveDec = new olc::Decal(ghostAlive);
		bossDeadDec = new olc::Decal(bossDead);
		bossAliveDec = new olc::Decal(bossAlive);
		crossSwordsDec = new olc::Decal(crossSwords);
		trapDec = new olc::Decal(trap);
		healDec = new olc::Decal(heal);
		youDiedDec = new olc::Decal(youDied);
		axeDec = new olc::Decal(axe);
		axeWpnDec = new olc::Decal(axeWpn);
		floor1Dec = new olc::Decal(floor1);
		floor2Dec = new olc::Decal(floor2);
		floor3Dec = new olc::Decal(floor3);
		nCapDec = new olc::Decal(nCap);
		sCapDec = new olc::Decal(sCap);
		eCapDec = new olc::Decal(eCap);
		wCapDec = new olc::Decal(wCap);
		innerWDec = new olc::Decal(innerHWall);
		innerVDec = new olc::Decal(innerVWall);
		topWall1Dec = new olc::Decal(topWall1);
		topWall2Dec = new olc::Decal(topWall2);
		bottomWallDec = new olc::Decal(bottomWall);
		rockWallDec = new olc::Decal(rockWall);
		torchLightDec = new olc::Decal(torchLight);
		trcDecal = new olc::Decal(trc);
		tlcDecal = new olc::Decal(tlc);
		blcDecal = new olc::Decal(blc);
		brcDecal = new olc::Decal(brc);
		lwDecal = new olc::Decal(lw);
		rwDecal = new olc::Decal(rw);
		exitClosedDec = new olc::Decal(exitClosed);
		exitOpenDec = new olc::Decal(exitOpen);
		victoryDec = new olc::Decal(victory);


		/******************************************************************************
		*								 Map Design	and Second Layer			      *
		******************************************************************************/
		nLevelWidth = 26; //how many tiles we are including for width/height
		nLevelHeight = 22;

		//Background Map
		sMap += L"(!^^^!^^^@^^^@^^^!^^^@^^^)";
		sMap += L"(..s.....................)";
		sMap += L"(....n*^^^*^^^*^^^*n.....)";
		sMap += L"(*^^^&.............&*^...)";
		sMap += L"(....s*^..n.n*^^^*.&...n*)";
		sMap += L"(.........&.&......&...&.)";
		sMap += L"(*^^^*^n..&.s*^^^*^s...&.)";
		sMap += L"(......&..&..........nns.)";
		sMap += L"(......&..&n*w####e..&s..)";
		sMap += L"(......&..ss.&&*^^^..&...)";
		sMap += L"(*n..*^s.....&&......&...)";
		sMap += L"(.&..........&&.wn---&...)";
		sMap += L"(.s*^^^*^^n.w&&..&####e.w)";
		sMap += L"(.........&..&&..se......)";
		sMap += L"(.........s.w&&e.........)";
		sMap += L"(............&&...n......)";
		sMap += L"(w######e...w&&*^^^*n.n*^)";
		sMap += L"(*^^^*#######s&.....&.s..)";
		sMap += L"(.....*^^^*^^^s.....&....)";
		sMap += L"d.............*^^.w#s.n..)";
		sMap += L"(.....*^^^*^^.........s..)";
		sMap += L"(------------------------)";

		//Second Map with Items, Enemies, Walls
		sMapObjects += L"##########################";
		sMapObjects += L"#..#T.......M......P.....#";
		sMapObjects += L"#....###############.M..M#";
		sMapObjects += L"######P......T....P###...#";
		sMapObjects += L"#P...###..#.######.#P..###";
		sMapObjects += L"#....MM...#.#PT..T.#...#P#";
		sMapObjects += L"########..#.########G..#P#";
		sMapObjects += L"#PP.M..#..#..M.......###.#";
		sMapObjects += L"#PBM.M.#T.#########..##..#";
		sMapObjects += L"#M.M..M#..##.######..#M..#";
		sMapObjects += L"###..###.....##M.....#...#";
		sMapObjects += L"#T#..........##.######M..#";
		sMapObjects += L"#P#########.###..######.##";
		sMapObjects += L"#......P..#..##..##M.....#";
		sMapObjects += L"#........G#M####.........#";
		sMapObjects += L"#P......G....##M..#..G...#";
		sMapObjects += L"#########..A#########.####";
		sMapObjects += L"###############P...P#.#..#";
		sMapObjects += L"#.....#########.GGG.#....#";
		sMapObjects += L"#B.......T....###.###.#..#";
		sMapObjects += L"#.....#######.........#P.#";
		sMapObjects += L"##########################";
		
		
		/******************************************************************************
		*						   Player Starting Position							  *
		******************************************************************************/
		xPlayer = 1 * 64;
		yPlayer = 1 * 64;


		

		return true;
	}//close of onUserCreate

	//continuously called to update screen (game loop)
	bool OnUserUpdate(float fElapsedTime) override
	{
		// METHODS TO CHANGE MAP
		auto GetTile = [&](int x, int y, wstring map )
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				return map[y * nLevelWidth + x];
			else
				return L' ';
		};

		auto SetTile = [&](int x, int y, wchar_t c, wstring map )
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				sMapObjects[y * nLevelWidth + x] = c;
		};

		

		/******************************************************************************
		*								  Draw Map								  
		******************************************************************************/
		wchar_t hashID = L'#';
		wchar_t periodID = L'.';

		//loads map based upon the sMap wstring 
		for (int y = 0; y < nLevelHeight; y++)
		{
			for (int x = 0; x < nLevelWidth; x++)
			{
				wchar_t tile = sMap[y * nLevelWidth + x];
				mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
				switch (tile) {
				case L'#':
					DrawDecal(mapPos, rockWallDec);
					break;
				case L'*':
					DrawDecal(mapPos, innerWDec);
					break;
				case L'&':
					DrawDecal(mapPos, innerVDec);
					break;
				case L'n':
					DrawDecal(mapPos, nCapDec);
					break;
				case L's':
					DrawDecal(mapPos, sCapDec);
					break;
				case L'e':
					DrawDecal(mapPos, eCapDec);
					break;
				case L'w':
					DrawDecal(mapPos, wCapDec);
					break;
				case L'd':
					if(doorOpen)
						DrawDecal(mapPos, exitOpenDec);
					else
						DrawDecal(mapPos, exitClosedDec);
					break;
				case L'.':
					if (groundCounter == 0) { DrawDecal(mapPos, floor1Dec, { 1.0f, 1.0f }, olc::Pixel(219, 189, 142)); groundCounter++; break; }
					if (groundCounter == 1) { DrawDecal(mapPos, floor2Dec, { 1.0f, 1.0f }, olc::Pixel(219, 189, 142)); groundCounter++; break; }
					if (groundCounter == 2) { DrawDecal(mapPos, floor3Dec, { 1.0f, 1.0f }, olc::Pixel(219, 189, 142)); groundCounter = 0; break; }
					break;
				case L'^':
					break;
				case L'!':
					DrawDecal(mapPos, topWall1Dec);
					break;
				case L'@':
					DrawDecal(mapPos, topWall2Dec);
					break;
				case L'-':
					DrawDecal(mapPos, bottomWallDec);
					break;
				case L'(':
					DrawDecal(mapPos, lwDecal);
					break;
				case L')':
					DrawDecal(mapPos, rwDecal);
					break;
				default:
					break;
				}//close switch
			}
		}//End of loading map

		//draw the corners
		DrawDecal({ 0.0,0.0 }, tlcDecal);
		DrawDecal({ 1554.0,0.0 }, trcDecal);
		DrawDecal({ 0.0,1344.0 }, blcDecal);
		DrawDecal({ 1600.0,1344.0 }, brcDecal);

		/******************************************************************************
		*								  Draw Map Objects
		******************************************************************************/

		wchar_t enemyID = L'E';
		wchar_t potionID = L'P';
		wchar_t minoAliveID = L'M';
		wchar_t minoDeadID = L'W';
		wchar_t ghostAliveID = L'G';
		wchar_t ghostDeadID = L'H';
		wchar_t bossAliveID = L'B';
		wchar_t bossDeadID = L'D';
		wchar_t axeWpnID = L'A';
	

		//loads map based upon the sMap wstring 
		for (int y = 0; y < nLevelHeight; y++)
		{
			for (int x = 0; x < nLevelWidth; x++)
			{
				wchar_t tile = sMapObjects[y * nLevelWidth + x];

				if ( GetTile( x, y, sMapObjects ) == enemyID )
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, dogDec);
				}

				if ( GetTile( x , y, sMapObjects ) == potionID )
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, healthPotDec);
				}

				if (GetTile(x, y, sMapObjects) == minoAliveID)
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, minoAliveDec);
				}

				if (GetTile(x, y, sMapObjects) == minoDeadID)
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, minoDeadDec);
				}

				if (GetTile(x, y, sMapObjects) == ghostAliveID)
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, ghostAliveDec);
				}

				if (GetTile(x, y, sMapObjects) == ghostDeadID)
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, ghostDeadDec);
				}

				if (GetTile(x, y, sMapObjects) == bossAliveID)
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, bossAliveDec);
				}

				if (GetTile(x, y, sMapObjects) == bossDeadID)
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, bossDeadDec);
				}

				if (GetTile(x, y, sMapObjects) == axeWpnID)
				{
					mapPos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
					DrawDecal(mapPos, axeWpnDec);
				}
			}
		}//End of loading map

		/******************************************************************************
		*								  Clear Map									  *
		******************************************************************************/
		//Clear(olc::BLACK);
		
		


		/******************************************************************************
		*                 Getting User Input For Player Movement(WASD)				  *
		******************************************************************************/

		//Collision Detection Points for Player
		
		//Top-Left Corner
		xTopLeft = xPlayer + 10;
		yTopLeft = yPlayer + 10;

		//Top-Right Corner
		xTopRight = xPlayer + 50;
		yTopRight = yPlayer;

		//Bottom-Left Corner
		xBotLeft = xPlayer + 10;
		yBotLeft = yPlayer + 50;

		//Right-Mid Position
		xBotRight = xPlayer + 50;
		yBotRight = yPlayer + 50;



		//Moving left
		if (GetKey(olc::Key::A).bHeld)
		{
			
			if (GetTile(((xTopRight - 2) / 64), (yTopRight / 64), sMapObjects) != hashID && GetTile(((xTopLeft - 2) / 64), (yTopLeft / 64), sMapObjects) != hashID && GetTile(((xBotLeft - 2) / 64), (yBotLeft / 64), sMapObjects) != hashID && GetTile(((xBotRight - 2) / 64), (yBotRight / 64), sMapObjects) != hashID  )
			{
				if (left == true)
				{
					imageCurrent += 1 * fElapsedTime;

					if (imageCurrent > imageDuration)
					{
						nextImage += 64;
						imageCurrent = 0;
					}

					if (nextImage == 256)
						nextImage = 0;
				}
				else
				{
					nextImage = 0;
					imageCurrent = 0;
				}

				xPlayer -= speed * fElapsedTime;
				direction = 192;

				right = false;
				left = true;
				up = false;
				down = false;
			}
		}

		//Moving right
		if (GetKey(olc::Key::D).bHeld)
		{
			if ( GetTile(((xTopRight + 2) / 64), (yTopRight / 64), sMapObjects) != hashID && GetTile(((xTopLeft + 2) / 64), (yTopLeft / 64), sMapObjects) != hashID && GetTile(((xBotLeft + 2) / 64), (yBotLeft / 64), sMapObjects) != hashID && GetTile(((xBotRight + 2) / 64), (yBotRight / 64), sMapObjects) != hashID)
			{
				if (right == true)
				{
					imageCurrent += 1 * fElapsedTime;

					if (imageCurrent > imageDuration)
					{
						nextImage += 64;
						imageCurrent = 0;
					}

					if (nextImage == 256)
						nextImage = 0;
				}
				else
				{
					nextImage = 0;
					imageCurrent = 0;
				}

				xPlayer += speed * fElapsedTime;
				direction = 128;

				right = true;
				left = false;
				up = false;
				down = false;

				
				

				
			}
		}

		//Moving up
		if (GetKey(olc::Key::W).bHeld)
		{
			if (GetTile(( xTopRight / 64), ((yTopRight - 2) / 64), sMapObjects) != hashID && GetTile( ( xTopLeft / 64), ( (yTopLeft -  2 ) / 64), sMapObjects) != hashID && GetTile( (xBotLeft / 64), ( (yBotLeft - 2) / 64), sMapObjects) != hashID && GetTile( ( xBotRight / 64), ( (yBotRight - 2) / 64), sMapObjects) != hashID)
			{
				if (up == true)
				{
					imageCurrent += 1 * fElapsedTime;

					if (imageCurrent > imageDuration)
					{
						nextImage += 64;
						imageCurrent = 0;
					}

					if (nextImage == 256)
						nextImage = 0;
				}
				else
				{
					nextImage = 0;
					imageCurrent = 0;
				}

				yPlayer -= speed * fElapsedTime;
				direction = 64;

				right = false;
				left = false;
				up = true;
				down = false;
			}
		}

		//Moving down
		if (GetKey(olc::Key::S).bHeld)
		{
			if (GetTile((xTopRight / 64), ((yTopRight + 2) / 64), sMapObjects) != hashID && GetTile((xTopLeft / 64), ((yTopLeft + 2) / 64), sMapObjects) != hashID && GetTile((xBotLeft / 64), ((yBotLeft + 2) / 64), sMapObjects) != hashID && GetTile((xBotRight / 64), ((yBotRight + 2) / 64), sMapObjects) != hashID)
			{
				if (down == true)
				{
					imageCurrent += 1 * fElapsedTime;

					if (imageCurrent > imageDuration)
					{
						nextImage += 64;
						imageCurrent = 0;
					}

					if (nextImage == 256)
						nextImage = 0;
				}
				else
				{
					nextImage = 0;
					imageCurrent = 0;
				}

				yPlayer += speed * fElapsedTime;
				direction = 0;

				right = false;
				left = false;
				up = false;
				down = true;
			}
		}

		/******************************************************************************
		*						Battle Enemies / Pickup Potions
		******************************************************************************/

		//ENEMIES
		if (GetTile(xPlayer / 64, yPlayer / 64, sMapObjects) == L'E')
		{
			drawBattle = true;
			enemy = Entity( "Goblin", 30, 10 );
			sUpdate = hero.battle(enemy);
			combatLog.push_back(sUpdate);
			hero.setXp(hero.getXp() + 50);
			SetTile(xPlayer / 64, yPlayer / 64, L'.', sMapObjects);
		}

		if (GetTile(xPlayer / 64, yPlayer / 64, sMapObjects) == L'M')
		{
			drawBattle = true;
			srand(time(NULL));
			enemy = Entity("Minotaur", 30 + ((rand() %10) - 4), 10 + ((rand() % 5) - 2));
			sUpdate = hero.battle(enemy);
			combatLog.push_back(sUpdate);
			hero.setXp(hero.getXp() + 25);

			SetTile(xPlayer / 64, yPlayer / 64, L'W', sMapObjects);
		}

		if (GetTile(xPlayer / 64, yPlayer / 64, sMapObjects) == L'G')
		{
			drawBattle = true;
			enemy = Entity("Ghost", 50 + ((rand() % 10) - 4), 15 + ((rand() % 5) - 2));
			sUpdate = hero.battle(enemy);
			combatLog.push_back(sUpdate);
			hero.setXp(hero.getXp() + 50);
			SetTile(xPlayer / 64, yPlayer / 64, L'H', sMapObjects);
		}

		if (GetTile(xPlayer / 64, yPlayer / 64, sMapObjects) == L'B')
		{
			
			drawBattle = true;
			enemy = Entity("Gary", 100, 30);
			sUpdate = hero.battle(enemy);
			combatLog.push_back(sUpdate);
			hero.setXp(hero.getXp() + 150);
			SetTile(xPlayer / 64, yPlayer / 64, L'D', sMapObjects);
			if( hero.getHealth() > 0 )
			{
				doorOpen = true;
				sUpdate = "A door has opened somewhere!";
				combatLog.push_back(sUpdate);
				SetTile(0, 19, L'.', sMapObjects);

			}
			
		}

		//TRAP
		if (GetTile(xPlayer / 64, yPlayer / 64, sMapObjects) == L'T' )
		{
			drawTrap = true;
			bleeding = true;
			SetTile(xPlayer / 64, yPlayer / 64, L'.', sMapObjects);
			sUpdate = "You hit a trap! Bleed for 5 seconds.";
			combatLog.push_back(sUpdate);
		}

		//POTIONS
		if (GetTile(xPlayer / 64, yPlayer / 64, sMapObjects) == L'P' && hero.getHealth() < hero.getMaxHealth() )
		{
			drawHeal = true;
			hero.setHealth(hero.getHealth() + 20);
			SetTile(xPlayer / 64, yPlayer / 64, L'.', sMapObjects);
			sUpdate = "You found a potion! Healed for 20 hp.";
			combatLog.push_back(sUpdate);
		}

		//AXE WEAPON
		if (GetTile(xPlayer / 64, yPlayer / 64, sMapObjects) == L'A' )
		{
			SetTile(xPlayer / 64, yPlayer / 64, L'.', sMapObjects);
			sUpdate = "You found an Axe! Strength +10";
			axeEpd = true;
			hero.setStrength(hero.getStrength() + 20);
			combatLog.push_back(sUpdate);
		}

		//CHECK FOR PLAYER LEVELUP
		if (hero.getXp() >= hero.getXpToLevel() && hero.getHealth() > 0 )
		{
			sUpdate = hero.levelUp();
			combatLog.push_back(sUpdate);
		}
		
		
		/******************************************************************************
		*						Draw Player On Map w/ FoV									  
		******************************************************************************/
		olc::vf2d playerPoint = { float( xPlayer ), float( yPlayer ) };

		if (!bleeding)
		{
			if( axeEpd )
				DrawPartialDecal(playerPoint, axeDec, { float(0) + nextImage, float(0) + direction }, { float(64), float(64) }, { float(1.10), float(1.10) });
			else
				DrawPartialDecal(playerPoint, playerDec, { float(0) + nextImage, float(0) + direction }, { float(64), float(64) }, { float(1.10), float(1.10) } );
		}
		else
		{
			if( axeEpd )
				DrawPartialDecal(playerPoint, axeDec, { float(0) + nextImage, float(0) + direction }, { float(64), float(64) }, { float(1.25), float(1.25) }, olc::RED);
			else
				DrawPartialDecal(playerPoint, playerDec, { float(0) + nextImage, float(0) + direction }, { float(64), float(64) }, { float(1.25), float(1.25) }, olc::RED);
		}

		olc::vf2d torchPos = { float( xPlayer - (1935) ), float(yPlayer - (1870))};
		DrawDecal(torchPos, torchLightDec);
		if (win)
		{
			mapPos = { float(0), float(0) };
			DrawDecal(mapPos, victoryDec);
		}
		//TRIGGERS
		
		//if player fights enemy
		if (drawBattle)
		{
			if (currentDuration < decalDuration)
			{
				mapPos = { float(0), float(0) };
				DrawDecal(mapPos, crossSwordsDec);
				currentDuration += (1 * fElapsedTime);

				if (currentDuration > decalDuration)
				{
					drawBattle = false;
					currentDuration = 0;
				}
			}
		}

		//Show player hit a trap
		if (drawTrap)
		{
			if (currentDuration < decalDuration)
			{
				mapPos = { float(0), float(0) };
				DrawDecal(mapPos, trapDec);
				currentDuration += (1 * fElapsedTime);

				if (currentDuration > decalDuration)
				{
					drawTrap = false;
					currentDuration = 0;
				}
			}
		}

		//Show player healing
		if (drawHeal)
		{
			if (currentDuration < decalDuration)
			{
				mapPos = { float(0), float(0) };
				DrawDecal(mapPos, healDec);
				currentDuration += (1 * fElapsedTime);

				if (currentDuration > decalDuration)
				{
					drawHeal = false;
					currentDuration = 0;
				}
			}
		}

		//if player is bleeding from trap
		if (bleeding)
		{
			if (bleedCurrent < bleedDuration)
			{
				bleedCurrent += (1 * fElapsedTime);

				if ( bleedCurrent > bleedCounter )
				{
					hero.setHealth(hero.getHealth() - 5);
					bleedCounter++;
				}

				if ( bleedCurrent > bleedDuration)
				{
					bleeding = false;
					bleedCounter = 1;
					bleedCurrent = 0;
				}
			}
		}

		//UI BACKGROUND
		mapPos = { float(0), float(1408) };
		DrawDecal(mapPos, solidBlockDec);


		//GAME INFO PANEL
		mapPos = { float(300), float(1408) };
		DrawDecal(mapPos, parchmentDec);

		int counter = 0;

		//PLAYER HEALTH
		mapPos = { float(495), float(1440 ) };
		DrawStringDecal(mapPos, std::to_string( hero.getHealth() ) + " / " + std::to_string(hero.getMaxHealth()), olc::BLACK, { (3.0f), (3.0f) });

		//PLAYER LEVEL
		mapPos = { float(470), float(1510) };
		DrawStringDecal(mapPos, std::to_string(hero.getLevel()) , olc::BLACK, { (3.0f), (3.0f) });

		//XP NEEDED
		mapPos = { float(510), float(1565) };
		DrawStringDecal(mapPos, std::to_string(hero.getXp()) + " / " + std::to_string(hero.getXpToLevel()), olc::BLACK, { (3.0f), (3.0f) });

		//COMBAT LOG STRINGS
		if (combatLog.size() > 5)
		{
			combatLog.pop_front();
		}

		for (it = combatLog.begin(); it != combatLog.end(); ++it )
		{
			counter++;
			mapPos = { float(815), float(1460 + (counter * 20 ) ) };
			DrawStringDecal(mapPos, *it, olc::BLACK, { (1.5f), (1.5f) } );
		}

		/******************************************************************************
		*						But did you die??
		******************************************************************************/
		if (hero.getHealth() <= 0)
		{
			mapPos = { float(0), float(0) };
			DrawDecal(mapPos, youDiedDec);

			//loads map based upon the sMap wstring 
			for (int y = 0; y < nLevelHeight; y++)
			{
				for (int x = 0; x < nLevelWidth; x++)
				{
					SetTile(x, y, L'.', sMapObjects);
				}
			}
		}


		/******************************************************************************
		*						But did you win??
		******************************************************************************/
		if (GetTile( (xPlayer + 55) / 64, yPlayer / 64, sMap) == L'd')
		{
			win = true;
		}

		if (win == true)
		{

		}

		return true;
	}//close of onUserUpdate
};


int main()
{
	GameDriver game;
	if (game.Construct(1664, 1600, 1, 1, true, false, false) )
		game.Start();

	return 0;
}
