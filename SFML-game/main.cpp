#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"Animation.h"
#include"Player.h"
#include"Platform.h"
#include"Collider.h"
#include"bullet.h"
#include "enemy.h"
#include "Coin.h"
#include "Key.h"
#include "Boss.h"
#include "Princess.h"
#include "Item.h"
#include"Menu.h"
#include<iostream>
#include<algorithm>
#include <fstream>
#include<sstream>
#include<time.h>

using namespace sf;
using namespace std;

static const float VIEW_HEIGHT = 720.0f;
int blockupdown;
int BossBlood = 6;
int enemyX[20] = {};
int ranenemyX[20] = {};
bool showHitBox = true; // show hitbox ให้มีหรือไม่มี

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main()
{
	float debounce = 0;
	
	srand(time(NULL));
	int items = 0;
	int rowItem = 0;
	bool checkItem = false;
	bool checkchon[100];
	bool row0 = false;
	bool row1 = false;
	bool row2 = false;

	sf::Clock clock2; 
	sf::Clock Clockrow0;
	sf::Clock Clockrow1;
	sf::Clock Clockrow2;
	float row0Clock = 0.0f;
	float row1Clock = 0.0f;
	float row2Clock = 0.0f;

	int score = 0;
	unsigned int life = 3;
	int key = 0;
	int x = 0; //x คือ เลขตัวเข้าเมนู
	
	
	bool checkState = false;
	std::memset(checkchon, true, sizeof checkchon);

	sf::RenderWindow window(sf::VideoMode(1080, 720), "The Lost Princess | 63010484 | Programming Fundamental | KMITL", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT , VIEW_HEIGHT));
	sf::Vector2f checkpoint;
	
	
	////////////////////////////////////////////////// Background////////////////////////////////////////////////////////////

	// Menu
	sf::Texture backgroundmenu; // bg menu
	backgroundmenu.loadFromFile("Pic/bgmenu2.png");
	sf::RectangleShape bgmenu(sf::Vector2f(1080, 720));
	bgmenu.setTexture(&backgroundmenu);
	sf::Texture backgroundhowtoplay; // bg menu how to play
	backgroundhowtoplay.loadFromFile("Pic/menuhowtoplay.png");
	sf::RectangleShape bghowtoplay(sf::Vector2f(1080, 720));
	bghowtoplay.setTexture(&backgroundhowtoplay);
	sf::Texture backgroundhighscore; // bg menu high score
	backgroundhighscore.loadFromFile("Pic/menuhighscore.png");
	sf::RectangleShape bghighscore(sf::Vector2f(1080, 720));
	bghighscore.setTexture(&backgroundhighscore);

		/// Menu button
	sf::Texture buttonplay; //button menu play
	buttonplay.loadFromFile("Pic/play.png");
	sf::Texture buttonhowtoplay; //button menu howtoplay
	buttonhowtoplay.loadFromFile("Pic/howtoplay.png");
	sf::Texture buttonhighscore; //button menu highscore
	buttonhighscore.loadFromFile("Pic/highscore.png");
	sf::Texture buttonexit; //button exit
	buttonexit.loadFromFile("Pic/exit.png");
	sf::Texture buttonreturnmenu; //button return menu highscore to main menu
	buttonreturnmenu.loadFromFile("Pic/returnmenu.png");
	sf::Texture backgroundvictory; // bg victory
	backgroundvictory.loadFromFile("Pic/victory.png");
	sf::RectangleShape bgvictory(sf::Vector2f(1080, 720));
	bgvictory.setTexture(&backgroundvictory);
	bgvictory.setScale(sf::Vector2f(0.0f, 0.0f));
	bgvictory.setPosition(sf::Vector2f(2255.0f, -5640.0f));

	//Input your name
	sf::Texture backgroundname; // bg name
	backgroundname.loadFromFile("Pic/bgname.png");
	sf::RectangleShape bgname(sf::Vector2f(1080, 720));
	bgname.setTexture(&backgroundname);
	sf::Text name;
	sf::Font font;
	font.loadFromFile("Font/ROGFonts-Regular.otf");
	name.setFont(font);
	name.setFillColor(sf::Color::Red);
	name.setCharacterSize(30);
	name.setPosition(415, 320);
	sf::String nameplayer;

	//gameover
	Texture gameoverTexture;
	gameoverTexture.loadFromFile("Pic/gameover.png");
	RectangleShape gameo;
	gameo.setTexture(&gameoverTexture);
	gameo.setSize(Vector2f(window.getSize()));
	gameo.setOrigin(gameo.getSize() / 2.f);
	Text hname, hscore;
	hscore.setFont(font);
	hscore.setCharacterSize(35);
	hscore.setFillColor(Color::Black);
	hname.setFont(font);
	hname.setCharacterSize(35);
	hname.setFillColor(Color::Black);

	//victory
	Texture victoryTexture;
	victoryTexture.loadFromFile("Pic/victory.png");
	RectangleShape win;
	win.setTexture(&victoryTexture);
	win.setSize(Vector2f(window.getSize()));
	win.setOrigin(win.getSize() / 2.f);
	Text hname2, hscore2;
	hscore2.setFont(font);
	hscore2.setCharacterSize(35);
	hscore2.setFillColor(Color::Black);
	hname2.setFont(font);
	hname2.setCharacterSize(35);
	hname2.setFillColor(Color::Black);

	// Player+Enemy
	sf::Texture playerTexture; //knight player
	playerTexture.loadFromFile("Pic/robot.png");
	sf::Texture enemyTexture; //enemy alien ในฉากที่ 3
	enemyTexture.loadFromFile("Pic/frog.png");
	sf::Texture enemyTexture2; //enemy pumpkin ในฉากที่ 5
	enemyTexture2.loadFromFile("Pic/enemy.png");
	sf::Texture enemyTexture3; //enemy bear ในฉากที่ 1
	enemyTexture3.loadFromFile("Pic/bear.png");
	sf::Texture enemyTexture4; //enemy dinosour ในฉากที่ 2 + 4
	enemyTexture4.loadFromFile("Pic/dinosour.png");
	sf::Texture BossTexture; //boss dinosour
	BossTexture.loadFromFile("Pic/boss.png");
	sf::Texture PrincessTexture; //Princess
	PrincessTexture.loadFromFile("Pic/Princess.png");

	sf::Texture background; // bg ฉากที่ 1 
	background.loadFromFile("Pic/bg01.png");
	sf::RectangleShape bg(sf::Vector2f(4000, 1000));
	bg.setPosition(sf::Vector2f(-800, -800)); //-500 -360
	bg.setTexture(&background);

	sf::Texture floorwater; // ใส่พื้นน้ำ
	floorwater.loadFromFile("Pic/water.png");
	sf::RectangleShape bgwater(sf::Vector2f(2500, 3800));
	bgwater.setPosition(sf::Vector2f(2500, 200));
	bgwater.setTexture(&floorwater);
	sf::Texture background2; // bg ฉากที่ 2
	background2.loadFromFile("Pic/bg02.png");
	sf::RectangleShape bg2(sf::Vector2f(4000, 1000));
	bg2.setPosition(sf::Vector2f(-800, -2200)); 
	bg2.setTexture(&background2);
	sf::Texture background3; // bg ฉากที่ 3
	background3.loadFromFile("Pic/bg03.png");
	sf::RectangleShape bg3(sf::Vector2f(4000, 1000));
	bg3.setPosition(sf::Vector2f(-800, -3600));
	bg3.setTexture(&background3);
	sf::Texture background4; // bg ฉากที่ 4
	background4.loadFromFile("Pic/bg04.png");
	sf::RectangleShape bg4(sf::Vector2f(4000, 1000));
	bg4.setPosition(sf::Vector2f(-800, -5150));
	bg4.setTexture(&background4);
	sf::Texture background5; // bg ฉากที่ 5
	background5.loadFromFile("Pic/bg5.png");
	sf::RectangleShape bg5(sf::Vector2f(4000, 1000));
	bg5.setPosition(sf::Vector2f(-800, -6600));
	bg5.setTexture(&background5);

	/// bg1+2 floor+block
	sf::Texture floor;
	floor.loadFromFile("Pic/floor01.png");
	sf::Texture floor2;
	floor2.loadFromFile("Pic/floor02.png");
	sf::Texture floor3;
	floor3.loadFromFile("Pic/floor03.png");
	sf::Texture floor4;
	floor4.loadFromFile("Pic/floor04.png");
	sf::Texture floor5;
	floor5.loadFromFile("Pic/floor05.png");
	sf::Texture block;
	block.loadFromFile("Pic/block.png");
	sf::Texture block01;
	block01.loadFromFile("Pic/block01.png");
	sf::Texture block02;
	block02.loadFromFile("Pic/block02.png");
	sf::Texture block03;
	block03.loadFromFile("Pic/block03.png");
	sf::Texture block04;
	block04.loadFromFile("Pic/block04.png");
	sf::Texture blockcoin;
	blockcoin.loadFromFile("Pic/blockcoin.png");
	sf::Texture brick; //อิฐขั้นบันได
	brick.loadFromFile("Pic/brick.png");
	sf::Texture channel; //ท่อเขียว
	channel.loadFromFile("Pic/channel.png");
	sf::Texture channel02; //ท่อเหลือง
	channel02.loadFromFile("Pic/channel02.png");
	sf::Texture windowwarp; //หน้าต่างวาร์ป
	windowwarp.loadFromFile("Pic/window.png");
	sf::Texture heart; //หัวใจ
	heart.loadFromFile("Pic/heart.png");
	sf::Texture doorwarp; //ประตูวาร์ป
	doorwarp.loadFromFile("Pic/door.png");
	sf::Texture doorwarp2; //ประตูวาร์ป2
	doorwarp2.loadFromFile("Pic/door2.png");
	sf::Texture doorwarp3; //ประตูวาร์ป3
	doorwarp3.loadFromFile("Pic/door3.png");
	sf::Texture doorwarp4; //ประตูวาร์ป4
	doorwarp4.loadFromFile("Pic/door4.png");
	sf::Texture cactus; //กระบองเพชร
	cactus.loadFromFile("Pic/cactus.png");
	sf::Texture iceblock; //ice block เลื่อน
	iceblock.loadFromFile("Pic/iceblock.png");
	sf::Texture ice; //ice block
	ice.loadFromFile("Pic/ice.png");
	sf::Texture stalagmite; //stalagmite block
	stalagmite.loadFromFile("Pic/stalagmite.png");
	sf::Texture ball; //กระสุน
	ball.loadFromFile("Pic/ball.png");
	sf::Texture coinTexture; //coin
	coinTexture.loadFromFile("Pic/coin.png");
	sf::Texture keyTexture; //key 
	keyTexture.loadFromFile("Pic/key.png");
	sf::Texture itemTexture; //item
	itemTexture.loadFromFile("Pic/power.png");
	sf::Texture blockwhatTexture; //blockwhat
	blockwhatTexture.loadFromFile("Pic/blockwhat.png");
	
	////////////////////////////////////////////////////////// Sound Effect ///////////////////////////////////
	sf::Music music1;
	music1.openFromFile("Sound/map1.wav");
	music1.setVolume(50);
	music1.play();
	
	/// sound effect ///
	sf::SoundBuffer jump, shoot, coineff, enemyhurt,worldclear,powerup,gameover;
	jump.loadFromFile("Sound/jump.wav");
	shoot.loadFromFile("Sound/shoot.wav");
	coineff.loadFromFile("Sound/coin.wav");
	enemyhurt.loadFromFile("Sound/death.wav");
	powerup.loadFromFile("Sound/powerup.wav");
	worldclear.loadFromFile("Sound/worldclear.wav");
	gameover.loadFromFile("Sound/gameover.wav");

	sf::Sound jumpSound, shootSound, coineffSound, enemyhurtSound, worldclearSound,powerupSound, gameoverSound;
	jumpSound.setBuffer(jump);
	jumpSound.setVolume(70.0f);
	shootSound.setBuffer(shoot);
	shootSound.setVolume(120.0f);
	coineffSound.setBuffer(coineff);
	coineffSound.setVolume(100.0f);
	enemyhurtSound.setBuffer(enemyhurt);
	enemyhurtSound.setVolume(120.0f);
	powerupSound.setBuffer(powerup);
	powerupSound.setVolume(100.0f);
	worldclearSound.setBuffer(worldclear);
	worldclearSound.setVolume(100.0f);
	gameoverSound.setBuffer(gameover);
	gameoverSound.setVolume(120.0f);
	
	//////////////////////////////////////////////////////////////////////// Platform ////////////////////////////////////////////////////////////////////////
	
	Player player(&playerTexture, sf::Vector2u(8, 3), 0.1f, 100, 100, showHitBox);
	Boss boss(&BossTexture, sf::Vector2u(8, 3), 0.15f, 200.0f, sf::Vector2f(2200.0f, -5640.0f));

	/// vector //
	std::vector<Platform> platforms;
	std::vector<Platform> Blockwhat;
	std::vector<Platform> chonBlockwhat;
	std::vector<bullet> vbullet;
	std::vector<enemy> enemys;
	std::vector<Coin> coins;
	std::vector<Key> keys;
	std::vector<Boss> bosss;
	std::vector<Princess> myprincess;
	std::vector<Item>item;

	/////////////////////////////////////////////////// Platform 1  ////////////////////////////////////////////////////////

	Platform Partition(&block, sf::Vector2f(40.0f, 2143.0f), sf::Vector2f(-760.0f, 0.0f), 0, showHitBox); //ฉากกั้นของฉากที่ 1

	platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-180.0f, 30.0f), 0, showHitBox)); //block1
	float tmp = 0;
	for (float i=0;i<5;i++) //loop block 
	{
	
		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(150.0f + tmp, 30.0f),0, showHitBox)); //block2ลอย บน
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(850.0f + tmp, 180.0f),0, showHitBox)); //ขั้นบันไดขั้นที่ 1 : 5 อิฐ 
		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2100.0f + tmp, 100.0f), 0, showHitBox)); //block5 ข้าง blockcoin
		tmp += 40;
	}
	for (float i = 0; i < 4; i++) //loop block 
	{
		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(90.0f + tmp, -150.0f),0, showHitBox)); //block3ลอย บน
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(690.0f + tmp, 140.0f),0, showHitBox)); //ขั้นบันไดขั้นที่ 2 : 4 อิฐ 
		tmp += 40;
	}
	for (float i = 0; i < 3; i++) //loop block 
	{
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(570.0f + tmp, 100.0f),0, showHitBox)); //ขั้นบันไดขั้นที่ 3 : 3 อิฐ 
		tmp += 40;
	}
	for (float i = 0; i < 2; i++) //loop block 
	{
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(490.0f + tmp, 60.0f),0, showHitBox)); //ขั้นบันไดขั้นที่ 4 : 2 อิฐ s
		tmp += 40;
	}
	for (float i = 0; i <= 0; i++)
	{
		for (float j = 0; j <= 3; j++)
			platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2000.0f + 150 * j, -80.0f + 150 * i),0, showHitBox)); // block4 ตรงเเม่น้ำ
	}

	platforms.push_back(Platform(&channel, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(1350.0f, -80.0f),0, showHitBox)); //block ท่อเขียว
	platforms.push_back(Platform(&channel, sf::Vector2f(100.0f, 700.0f), sf::Vector2f(1350.0f, 300.0f),0, showHitBox)); ////block ท่อเขียว
	

	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(130.0f, 30.0f),1, showHitBox)); //blockcoin1 in block2ลอย บน

	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(250.0f, -150.0f),1, showHitBox)); //blockcoin2 in block3ลอย บน
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1800.0f, 20.0f),1, showHitBox)); //blockcoin2 in block4ลอย บน
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2250.0f, -280.0f), 1, showHitBox)); //heart

	//// Enemy ฉากที่ 1 /////
	enemys.push_back(enemy(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 500, 115, 100.0f, 0));
	enemys.push_back(enemy(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 200, 115, 100.0f, 0));
	enemys.push_back(enemy(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 0, 160, 100.0f, 0));
	enemys.push_back(enemy(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 1200, 160, 100.0f, 0));

	//// Coin ฉากที่ 1 /////
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(170.0f, 160.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(210.0f, 160.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(250.0f, 160.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(360.0f, -210.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2050.0f, -260.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2450.0f, -260.0f)));

	//// Key ฉากที่ 1 /////
	keys.push_back(Key(&keyTexture, sf::Vector2u(6, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2670.0f, -230.0f)));  ///2670 -230

	//// Blockwhat ฉากที่ 1 /////
	Blockwhat.push_back(Platform(&blockwhatTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(0.0f, -20.0f), 0, showHitBox));
	chonBlockwhat.push_back(Platform(&itemTexture, sf::Vector2f(30.0f, 20.0f), sf::Vector2f(0.0f, -5.0f), 0, showHitBox));

	//// Platform background  พื้นฉาก /////
	platforms.push_back(Platform(&floor, sf::Vector2f(4000.0f, 400.0f), sf::Vector2f(500.0f, 400.0f),0, showHitBox)); //พื้นฉากที่ 1
	platforms.push_back(Platform(&floor, sf::Vector2f(4000.0f, 400.0f), sf::Vector2f(4700.0f, 400.0f),0, showHitBox)); //พื้นฉากที่ 1 หลังน้ำ
	platforms.push_back(Platform(&floor2, sf::Vector2f(8000.0f, 400.0f), sf::Vector2f(-500.0f, -1000.0f),0, showHitBox)); //พื้นฉากที่ 2
	platforms.push_back(Platform(&floor3, sf::Vector2f(16000.0f, 400.0f), sf::Vector2f(-1500.0f, -2400.0f), 0, showHitBox)); //พื้นฉากที่ 3
	platforms.push_back(Platform(&floor4, sf::Vector2f(16000.0f, 400.0f), sf::Vector2f(-1000.0f, -4000.0f), 0, showHitBox)); //พื้นฉากที่ 4
	platforms.push_back(Platform(&floor5, sf::Vector2f(16000.0f, 400.0f), sf::Vector2f(-1000.0f, -5400.0f), 0, showHitBox)); //พื้นฉากที่ 4

	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(170.0f, 160.0f)));

	/////////////////////////////////////////////////// Platform 2  ///////////////////////////////////////////////////////////////////////////////

	Platform Partition2(&block, sf::Vector2f(40.0f, 200.0f), sf::Vector2f(-760.0f, -1350.0f), 0, showHitBox); //ฉากกั้นของฉากที่ 2 
	Platform Bmap2(&block02, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(2200.0f, -1500.0f), 0, showHitBox); // block เลื่อนขึ้นเเละลง

	for (float i = 0; i < 5; i++) //loop block 
	{

		platforms.push_back(Platform(&block02, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-30.0f + tmp, -1350.0f), 0, showHitBox)); //block1 
		platforms.push_back(Platform(&block02, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(50.0f + tmp, -1450.0f), 0, showHitBox)); //block2
		platforms.push_back(Platform(&block02, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(150.0f + tmp, -1550.0f), 0, showHitBox)); //block3
		tmp += 40;
	}
	for (float i = 0; i <= 0; i++)
	{
		for (float j = 0; j <= 3; j++)
			platforms.push_back(Platform(&block02, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1200.0f + 120 * j, -1450.0f + 120 * i), 0, showHitBox)); // block4 ตรงเเม่น้ำ
	}

	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1400.0f, -1700.0f), 1, showHitBox)); //blockcoin1 บนกระบองพชร
	platforms.push_back(Platform(&floor, sf::Vector2f(30.0f, 200.0f), sf::Vector2f(1160.0f, -1300.0f), 0, showHitBox)); //block ยาวข้างกระบองเพชร1
	platforms.push_back(Platform(&floor, sf::Vector2f(30.0f, 200.0f), sf::Vector2f(1660.0f, -1300.0f), 0, showHitBox)); //block ยาวข้างกระบองเพชร2
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(900.0f, -1690.0f), 1, showHitBox)); //blockcoin
	platforms.push_back(Platform(&cactus, sf::Vector2f(400.0f, 100.0f), sf::Vector2f(1420.0f, -1240.0f), 0, showHitBox)); //cactus
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1815.0f, -1550.0f), 1, showHitBox)); //heart
	platforms.push_back(Platform(&channel02, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(2000.0f, -1540.0f), 0, showHitBox)); //block ท่อเหลือง1
	platforms.push_back(Platform(&channel02, sf::Vector2f(100.0f, 318.0f), sf::Vector2f(2000.0f, -1360.0f), 0, showHitBox)); ////block ท่อเหลือง1
	platforms.push_back(Platform(&block02, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(2200.0f, -1260.0f), 0, showHitBox)); ////block เลื่อนขึ้นลง
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2325.0f, -1350.0f), 1, showHitBox)); //blockcoin
	platforms.push_back(Platform(&channel02, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(2450.0f, -1540.0f), 0, showHitBox)); //block ท่อเหลือง2
	platforms.push_back(Platform(&channel02, sf::Vector2f(100.0f, 318.0f), sf::Vector2f(2450.0f, -1360.0f), 0, showHitBox)); ////block ท่อเหลือง2

	//// Enemy ฉากที่ 2 /////
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 1000, -1240, 100.0f, 100));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 900, -1240, 100.0f, 100));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 800, -1240, 100.0f, 100));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 1700, -1240, 100.0f, 100));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 1850, -1240, 100.0f, 100));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 2000, -1240, 100.0f, 100));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 2050, -1240, 100.0f, 100));

	//// Coin ฉากที่ 2 /////
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(790.0f, -1610.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(950.0f, -1240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2105.0f, 1240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2320.0f, -1240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2190.0f, -1325.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(0.0f, -1300.0f)));

	//// Key ฉากที่ 2 /////
	keys.push_back(Key(&keyTexture, sf::Vector2u(6, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2540.0f, -1325.0f)));

	//// Blockwhat ฉากที่ 2 /////
	Blockwhat.push_back(Platform(&blockwhatTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(860.0f, -1690.0f), 0, showHitBox));
	chonBlockwhat.push_back(Platform(&itemTexture, sf::Vector2f(30.0f, 20.0f), sf::Vector2f(860.0f, -1675.0f), 0, showHitBox));
	Blockwhat.push_back(Platform(&blockwhatTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1360.0f, -1700.0f), 0, showHitBox));
	chonBlockwhat.push_back(Platform(&itemTexture, sf::Vector2f(30.0f, 20.0f), sf::Vector2f(1360.0f, -1685.0f), 0, showHitBox));

	/////////////////////////////////////////////////// Platform 3  ///////////////////////////////////////////////////////////////////////////////

	Platform Partition3(&block, sf::Vector2f(40.0f, 500.0f), sf::Vector2f(-750.0f, -2600.0f), 0, showHitBox); //ฉากกั้นของฉากที่ 3

	Platform BlockSlide(&iceblock, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(50.0f, -2650.0f), 0, showHitBox); //block เลื่อน

	for (float i = 0; i < 4; i++) //loop block 
	{

		platforms.push_back(Platform(&block03, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-600.0f + tmp, -2800.0f), 0, showHitBox)); //block1 
		platforms.push_back(Platform(&block03, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-450.0f + tmp, -2900.0f), 0, showHitBox)); //block2
		platforms.push_back(Platform(&block03, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-280.0f + tmp, -2950.0f), 0, showHitBox)); //block3
		tmp += 20;
	}

	platforms.push_back(Platform(&stalagmite, sf::Vector2f(150.0f, 350.0f), sf::Vector2f(-500.0f , -3425.0f), 0, showHitBox));
	platforms.push_back(Platform(&stalagmite, sf::Vector2f(150.0f, 450.0f), sf::Vector2f(-200.0f , -3430.0f), 0, showHitBox));
	platforms.push_back(Platform(&stalagmite, sf::Vector2f(250.0f, 600.0f), sf::Vector2f(200.0f, -3330.0f), 0, showHitBox));
	platforms.push_back(Platform(&stalagmite, sf::Vector2f(100.0f, 450.0f), sf::Vector2f(500.0f, -3430.0f), 0, showHitBox));
	platforms.push_back(Platform(&ice, sf::Vector2f(150.0f, 300.0f), sf::Vector2f(850.0f, -2650.0f), 0, showHitBox)); // ice block
	platforms.push_back(Platform(&stalagmite, sf::Vector2f(180.0f, 600.0f), sf::Vector2f(900.0f, -3330.0f), 0, showHitBox));
	platforms.push_back(Platform(&stalagmite, sf::Vector2f(200.0f, 600.0f), sf::Vector2f(1300.0f, -3330.0f), 0, showHitBox));
	platforms.push_back(Platform(&ice, sf::Vector2f(150.0f, 350.0f), sf::Vector2f(1200.0f, -2650.0f), 0, showHitBox)); //ice block
	Platform BlockSlide2(&iceblock, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1400.0f, -2650.0f), 0, showHitBox); //block เลื่อน2
	platforms.push_back(Platform(&ice, sf::Vector2f(130.0f, 300.0f), sf::Vector2f(1800.0f, -2650.0f), 0, showHitBox)); //ice block2
	platforms.push_back(Platform(&ice, sf::Vector2f(150.0f, 200.0f), sf::Vector2f(2300.0f, -2650.0f), 0, showHitBox)); //ice block3

	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(650.0f, -2800.0f), 1, showHitBox));

	//// Enemy ฉากที่ 3 /////
	enemys.push_back(enemy(&enemyTexture, sf::Vector2u(8, 1), 0.1f, 1100, -2640, 100.0f, 150));
	enemys.push_back(enemy(&enemyTexture, sf::Vector2u(8, 1), 0.1f, 1000, -2640, 100.0f, 150));
	enemys.push_back(enemy(&enemyTexture, sf::Vector2u(8, 1), 0.1f, 900, -2640, 100.0f, 150));
	enemys.push_back(enemy(&enemyTexture, sf::Vector2u(8, 1), 0.1f, 2150, -2640, 100.0f, 150));
	enemys.push_back(enemy(&enemyTexture, sf::Vector2u(8, 1), 0.1f, 2000, -2640, 100.0f, 150));

	//// Coin ฉากที่ 3 /////
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(430.0f, -2640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(500.0f, -2640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(600.0f, -2640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1500.0f, -2640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2000.0f, -2640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2100.0f, -2640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2200.0f, -2640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2400.0f, -2640.0f)));

	//// Key ฉากที่ 3 /////
	keys.push_back(Key(&keyTexture, sf::Vector2u(6, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2540.0f, -2700.0f)));

	//// Blockwhat ฉากที่ 3 /////
	Blockwhat.push_back(Platform(&blockwhatTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(690.0f, -2800.0f), 0, showHitBox));
	chonBlockwhat.push_back(Platform(&itemTexture, sf::Vector2f(30.0f, 20.0f), sf::Vector2f(690.0f, -2785.0f), 0, showHitBox));
	Blockwhat.push_back(Platform(&blockwhatTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1550.0f, -2800.0f), 0, showHitBox));
	chonBlockwhat.push_back(Platform(&itemTexture, sf::Vector2f(30.0f, 20.0f), sf::Vector2f(1550.0f, -2785.0f), 0, showHitBox));

	/////////////////////////////////////////////////// Platform 4  ////////////////////////////////////////////////////////

	Platform Partition4(&block01, sf::Vector2f(40.0f, 500.0f), sf::Vector2f(-750.0f, -4500.0f), 0, showHitBox); //ฉากกั้นของฉากที่ 4
	Platform Bmap4(&floor2, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(1050.0f , -4300.0f), 0, showHitBox); // block เลื่อนขึ้นเเละลง
	Platform Bmap5(&floor2, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(1650.0f , -4300.0f), 0, showHitBox); // block เลื่อนขึ้นเเละลง
	

	platforms.push_back(Platform(&block04, sf::Vector2f(100.0f, 150.0f), sf::Vector2f(-200.0f, -4300.0f), 0, showHitBox));
	for (float i = 0; i < 4; i++) //loop block 
	{

		platforms.push_back(Platform(&block04, sf::Vector2f(120.0f, 40.0f), sf::Vector2f( -700.0f + tmp , -4300.0f ), 0, showHitBox)); //block1 
		platforms.push_back(Platform(&block04, sf::Vector2f(120.0f, 40.0f), sf::Vector2f( -600.0f + tmp , -4350.0f ), 0, showHitBox)); //block2
		platforms.push_back(Platform(&block04, sf::Vector2f(120.0f, 40.0f), sf::Vector2f( -500.0f + tmp , -4400.0f ), 0, showHitBox)); //block3
		platforms.push_back(Platform(&block04, sf::Vector2f(120.0f, 40.0f), sf::Vector2f(-400.0f + tmp, -4450.0f), 0, showHitBox)); //block4
		platforms.push_back(Platform(&block04, sf::Vector2f(120.0f, 40.0f), sf::Vector2f(-300.0f + tmp, -4500.0f), 0, showHitBox)); //block4
		tmp += 0;
	}

	platforms.push_back(Platform(&block04, sf::Vector2f(100.0f, 320.0f), sf::Vector2f(900.0f, -4360.0f), 0, showHitBox));
	platforms.push_back(Platform(&block04, sf::Vector2f(100.0f, 320.0f), sf::Vector2f(1200.0f, -4360.0f), 0, showHitBox));
	platforms.push_back(Platform(&block04, sf::Vector2f(100.0f, 320.0f), sf::Vector2f(1500.0f, -4360.0f), 0, showHitBox));
	platforms.push_back(Platform(&block04, sf::Vector2f(100.0f, 320.0f), sf::Vector2f(1800.0f, -4360.0f), 0, showHitBox));
	platforms.push_back(Platform(&block04, sf::Vector2f(100.0f, 320.0f), sf::Vector2f(2100.0f, -4360.0f), 0, showHitBox));

	//// Enemy ฉากที่ 4 /////
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 700, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 800, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 1285, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 1365, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 1430, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 1850, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 2000, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 2050, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture2, sf::Vector2u(10, 1), 0.1f, 2550, -4240, 100.0f, 200));

	//// Coin ฉากที่ 4 /////
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(655.0f, -4660.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(700.0f, -4660.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(600.0f, -4660.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(985.0f, -4240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1055.0f, -4240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1130.0f, -4240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1370.0f, -4640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1645.0f, -4240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1570.0f, -4240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1730.0f, -4240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2000.0f, -4640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2350.0f, -4240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2550.0f, -4240.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2750.0f, -4240.0f)));

	//// Key ฉากที่ 4 /////
	keys.push_back(Key(&keyTexture, sf::Vector2u(6, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(200.0f, -4240.0f)));

	//// Blockwhat ฉากที่ 4 /////
	Blockwhat.push_back(Platform(&blockwhatTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(850.0f, -4600.0f), 0, showHitBox));
	chonBlockwhat.push_back(Platform(&itemTexture, sf::Vector2f(30.0f, 20.0f), sf::Vector2f(850.0f, -4585.0f), 0, showHitBox));


	/////////////////////////////////////////////////// Platform 5  ////////////////////////////////////////////////////////
	
	Platform Partition5(&block, sf::Vector2f(40.0f, 1000.0f), sf::Vector2f(-750.0f, -5600.0f), 0, showHitBox); //ฉากกั้นของฉากที่ 5

	
	platforms.push_back(Platform(&channel02, sf::Vector2f(50.0f, 1100.0f), sf::Vector2f(2200.0f, -6170.0f), 0, showHitBox));

	/// coin ในฉากที่ 5 ///
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 0.0f, -5640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 300.0f, -5640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 500.0f, -5640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 1000.0f, -5640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 1500.0f, -5640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 1800.0f, -5640.0f)));

	/// Princess ในฉากที่ 5 ///
	myprincess.push_back(Princess(&PrincessTexture, sf::Vector2u(4, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2700.0f, -5640.0f)));

	//// Key ฉากที่ 5 /////
	keys.push_back(Key(&keyTexture, sf::Vector2u(6, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1750.0f, -5640.0f)));



	//////////////////////////////////////////////////////////////////// WarpPoint สร้างประตูวาป ////////////////////////////////////////////////////////////
	
	sf::RectangleShape door(sf::Vector2f(100, 150)); // หน้าต่างในฉากที่ 1
	door.setPosition(sf::Vector2f(650, -290));
	door.setTexture(&windowwarp);
	
	sf::RectangleShape door2(sf::Vector2f(100, 150)); // หน้าต่างในฉากที่ 3
	door2.setPosition(sf::Vector2f(2500, -2950));
	door2.setTexture(&windowwarp);

	sf::RectangleShape warpPoint(sf::Vector2f(200, 300)); // ประตูวาร์ปจากฉากที่ 1 ไป 2
	warpPoint.setPosition(sf::Vector2f(2900, -100));
	warpPoint.setTexture(&doorwarp);
	
	//sf::RectangleShape warpPoint2(sf::Vector2f(60, 50)); // ประตูวาร์ป test 1 go 2
	//warpPoint2.setPosition(sf::Vector2f(-600, 100));
	//warpPoint2.setFillColor(sf::Color::Red);
	
	sf::RectangleShape warpPoint3(sf::Vector2f(150, 300)); // ประตูวาร์ปจากฉากที่ 2 ไป 3
	warpPoint3.setPosition(sf::Vector2f(2950, -1500));
	warpPoint3.setTexture(&doorwarp2);

	//sf::RectangleShape warpPoint4(sf::Vector2f(50, 50)); // ประตูวาร์ป test 2 go 3
	//warpPoint4.setPosition(sf::Vector2f(200, -1500));
	//warpPoint4.setFillColor(sf::Color::Black);

	sf::RectangleShape warpPoint5(sf::Vector2f(180, 400)); // ประตูวาร์ปจากฉากที่ 3 ไป 4
	warpPoint5.setPosition(sf::Vector2f(2950, -3000));
	warpPoint5.setTexture(&doorwarp3);

	//sf::RectangleShape warpPoint6(sf::Vector2f(180, 400)); // // ประตูวาร์ป test 3 go 4
	//warpPoint6.setPosition(sf::Vector2f(200, -3200));
	//warpPoint6.setTexture(&doorwarp3);

	sf::RectangleShape warpPoint7(sf::Vector2f(200, 400)); // ประตูวาร์ปจากฉากที่ 4 ไป 5
	warpPoint7.setPosition(sf::Vector2f(2900, -4600));
	warpPoint7.setTexture(&doorwarp4);


	vector<pair<int, string>> ScoreBoard;
	int cnt = 0; //highscore


	float deltaTime = 0.0f;
	sf::Clock clock;
	bool menustate = true;

	while(window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
		

	//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า Menu /////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if (menustate == true) {
			///// ปุ่ม หน้า MENU ///////
			sf::RectangleShape button1(sf::Vector2f(300, 150)); //button play
			button1.setPosition(sf::Vector2f(380, 340));
			button1.setTexture(&buttonplay);
			sf::RectangleShape button2(sf::Vector2f(300, 150)); //button how to play
			button2.setPosition(sf::Vector2f(390, 520));
			button2.setTexture(&buttonhowtoplay);
			sf::RectangleShape button3(sf::Vector2f(300, 150)); //button high score
			button3.setPosition(sf::Vector2f(40, 520));
			button3.setTexture(&buttonhighscore);
			sf::RectangleShape button4(sf::Vector2f(100, 50)); //button returnmenu 
			button4.setPosition(sf::Vector2f(20, 20));
			button4.setTexture(&buttonreturnmenu);
			sf::RectangleShape button5(sf::Vector2f(295, 150)); //button exit
			button5.setPosition(sf::Vector2f(750, 520));
			button5.setTexture(&buttonexit);

			if (x == 0)
			{

				window.clear();
				if (button1.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					button1.setFillColor(sf::Color::Green);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						button1.setFillColor(sf::Color::Yellow);
						x = 7;
					}

				}
				else if (button2.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					button2.setFillColor(sf::Color::Green);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						button2.setFillColor(sf::Color::Yellow);
						x = 1;
					}

				}
				else if (button3.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					button3.setFillColor(sf::Color::Green);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						button3.setFillColor(sf::Color::Yellow);
						//read files
						int i = 0;
						ifstream loadFile;
						loadFile.open("highScore.txt");
						while (!loadFile.eof())
						{
							string tempName;
							int tempScore;
							loadFile >> tempName >> tempScore;
							ScoreBoard.push_back({ tempScore, tempName });
							i++;
						}
						loadFile.close();

						sort(ScoreBoard.begin(), ScoreBoard.end(), greater<pair<int, string>>());
						x = 2;
					}
				}
				else if (button5.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					button5.setFillColor(sf::Color::Green);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						button5.setFillColor(sf::Color::Yellow);
						x = 4;
					}
				}

				sf::Text nameText;
				sf::Font font;
				font.loadFromFile("Font/ROGFonts-Regular.otf");
				sf::RectangleShape nameRec;
				std::string nameString;
				nameText.setFont(font);
				nameText.setFillColor(sf::Color::White);
				nameText.setCharacterSize(14);
				nameText.setPosition(view.getCenter().x + 50, 680);
				nameString = " 63010484 : Nonthicha  Sukcharoen ";
				nameText.setString(nameString);


				window.draw(bgmenu);
				window.draw(button1);
				window.draw(button2);
				window.draw(button3);
				window.draw(button5);
				window.draw(nameText);

			}

			//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า How to play /////////////////////////////////////////////////////////////////////////////////////////////////////
			if (x == 1)
			{
				window.clear();
				if (button4.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					button4.setFillColor(sf::Color::Yellow);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						button4.setFillColor(sf::Color::Blue);
						x = 0;
					}
				}
				window.draw(bghowtoplay);
				window.draw(button4);

			}

			//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า High score /////////////////////////////////////////////////////////////////////////////////////////////////////

			if (x == 2)
			{
				window.clear();
				window.draw(bghighscore);
				window.draw(button4);
				cnt = 0;
				for (vector<pair<int, string>>::iterator k = ScoreBoard.begin(); k != ScoreBoard.end(); k = k + 1)
				{
					++cnt;
					if (cnt > 5)
						break;
					cout << cnt << endl;
					hname.setPosition(250, 140 + (70 * cnt));
					hscore.setPosition(620, 140 + (70 * cnt));
					hname.setString(k->second);
					hscore.setString(to_string(k->first));
					window.draw(hname);
					window.draw(hscore);
				}
				if (button4.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					button4.setFillColor(sf::Color::Yellow);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						button4.setFillColor(sf::Color::Blue);
						x = 0;
					}
				}

			}
			//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า Exit /////////////////////////////////////////////////////////////////////////////////////////////////////

			if (x == 4)
			{
				window.close();
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า Game over /////////////////////////////////////////////////////////////////////////////////////////////////////

			if (x == 5)
			{
				window.clear();
				gameo.setPosition(player.GetPosition());
				window.draw(gameo);
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					//write score
					string name;
					name = nameplayer;
					ofstream highscore;
					highscore.open("highScore.txt", ios::out | ios::app);
					highscore << "\n" << name << " " << score;
					highscore.close();
					window.close();
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า victory /////////////////////////////////////////////////////////////////////////////////////////////////////

			if (x == 6)
			{
				window.clear();
				win.setPosition(player.GetPosition());
				window.draw(win);
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					//write score
					string name;
					name = nameplayer;
					ofstream highscore;
					highscore.open("highScore.txt", ios::out | ios::app);
					highscore << "\n" << name << " " << score;
					highscore.close();
					window.close();
				}

			}
			/////////////////////////////////////////////////////////////////////////////////////////// หน้า Input your name /////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (x == 7)
			{
				window.clear();
				if (evnt.type == sf::Event::TextEntered and debounce < clock2.getElapsedTime().asSeconds())
				{

					debounce = clock2.getElapsedTime().asSeconds() + 0.2;
					if (evnt.text.unicode >= 33 && evnt.text.unicode <= 126 && nameplayer.getSize() <= 13 && evnt.text.unicode != 44)
					{
						nameplayer += evnt.text.unicode;
					}
					else if (evnt.text.unicode == 8)//backspace
					{
						nameplayer = nameplayer.substring(0, nameplayer.getSize() - 1);
					}
					else if (evnt.text.unicode == 13 && nameplayer.getSize() > 0)//enter
					{
						x = 3;
						menustate = false;
					}

				}
				name.setString("Name : " + nameplayer);
				window.draw(bgname);
				window.draw(name);
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า Start เข้า Game /////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if (menustate == false) {
			if (x == 3)
			{

				//printf("x = %.f  y = %.f\n", player.GetPosition().x, player.GetPosition().y); //ตำเเหน่ง Position

				player.Update(deltaTime);
				sf::Vector2f direction; // direction player

				sf::Vector2f directionM; // direction boss
				if (BossBlood > 0)
					boss.Update(deltaTime);

				if (BossBlood <= 0)
					boss.Update2(deltaTime);

				/////////////////////////////////////////////////////// check bullet /////////////////////////////////////////

				if (player.isShoot()) { // ยิงกระสนุ
					vbullet.push_back(bullet(&ball, sf::Vector2f(32.0f, 32.0f), 0, 50.0f, player.GetPosition().x, player.GetPosition().y - 35, player.faceRight));
				}

				for (int i = 0; i < vbullet.size(); i++) {
					vbullet[i].Update(deltaTime);

				}


				/// check player เดินชน enemy เเล้วพลังชีวิตลด///
				for (size_t i = 0; i < enemys.size(); i++)
				{
					if (player.GetCollider().CheckCollision(enemys[i].GetCollider(), direction, 0.0f))
					{
						enemyhurtSound.play();
						enemys.erase(enemys.begin() + i);
						life--;

					}
				}
				if (life <= 0)
				{
					//printf("Dead!!");
					x = 5;
					menustate = true;
				}

				/// check กระสุน ยิงโดน enemy เเล้ว enemy ตาย + คะเเนนเพิ่มขึ้น ///
				for (size_t i = 0; i < enemys.size(); i++)
				{
					for (size_t j = 0; j < vbullet.size(); j++)
					{
						if (vbullet[j].body.getGlobalBounds().intersects(enemys[i].body.getGlobalBounds()))
						{
							enemys[i].hp -= player.dmg;
							vbullet.erase(vbullet.begin() + j);
							//printf(" hit");
							if (enemys[i].hp <= 0)
							{
								enemyhurtSound.play();
								enemys.erase(enemys.begin() + i);
								score += 100;
							}
						}
					}
				}

				// check player ชน coin ///
				for (size_t i = 0; i < coins.size(); i++)
				{
					if (player.GetCollider().CheckCollision(coins[i].GetCollider(), direction, 0.0f))
					{
						coineffSound.play();
						coins.erase(coins.begin() + i);
						score += 10;
					}

				}

				// check player ชน key ///
				for (size_t i = 0; i < keys.size(); i++)
				{
					if (player.GetCollider().CheckCollision(keys[i].GetCollider(), direction, 0.0f))
					{
						key++;
						coineffSound.play();
						keys.erase(keys.begin() + i);
					}
				}

				if (key == 5 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {  // goto map boss
					player.setPosition(sf::Vector2f(2300.0f, -5640.0f)); //2300
					key = 0;
				}

				// check player ชน Princess ///
				for (size_t i = 0; i < myprincess.size(); i++)
				{
					if (player.GetCollider().CheckCollision(myprincess[i].GetCollider(), direction, 0.0f))
					{
						score += 500;
						worldclearSound.play();
						x = 6;
						menustate = true;
					}

				}

				/// คีย์ลัด ///
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
					player.setPosition(sf::Vector2f(2500.0f, -5640.0f));
				}
				///////////////////////////////////////////////////////////check ชน //////////////////////////////////////////////////////////////////////

				///////////////////////////////////////////////////////		check ชน blockcoin	 //////////////////////////////////////////////////
				int coin = 0;
				for (Platform& platform : platforms) { //check collision platform
					if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) {
						player.OnCollision(direction);
						if (platform.getBlockType() == 1 && platform.getPosition().y + 55 <= player.GetPosition().y) { // 1 = ชน
							jumpSound.play();
							//printf("\n\coin");
							sf::Vector2f platformPos = platform.getPosition();
							platforms.erase(platforms.begin() + coin);
							coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), platformPos));
						}
					}
					coin += 1;
				}

				for (Platform& platform : platforms) { //check block เลื่อน
					if (BlockSlide.GetCollider().CheckCollision(player.GetCollider(), direction, 0.0f)) {
						player.OnCollision(direction);
					}
					if (BlockSlide2.GetCollider().CheckCollision(player.GetCollider(), direction, 0.0f)) {
						player.OnCollision(direction);
					}
				}

				////////////////////////////////////////////////////////////	check ชน item	////////////////////////////////////////////////////////////////////////
				////// Check Item เลื่อนขึ้น //////
				for (int i = 0; i < Blockwhat.size(); i++)
				{
					if (Blockwhat[i].GetCollider().CheckCollision(player.GetCollider(), direction, 1.0)) //player chon money
					{
						player.OnCollision(direction);
					}
					for (int j = 0; j < chonBlockwhat.size(); j++)
					{
						if (chonBlockwhat[j].GetCollider().CheckCollision(player.GetCollider(), direction, 1.0))
						{
							Blockwhat.push_back(Platform(&blockwhatTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(Blockwhat[j].body.getPosition().x, Blockwhat[j].body.getPosition().y), 0, showHitBox));
							player.OnCollision(direction);
							items = (rand() % 3);
							if (checkchon[j])
							{
								switch (items)
								{
								case(0):
									item.push_back(Item(&itemTexture, sf::Vector2u(2, 3), 1.0f, sf::Vector2f(chonBlockwhat[j].body.getPosition().x, chonBlockwhat[j].body.getPosition().y - 80), 0));
									break;
								case(1):
									item.push_back(Item(&itemTexture, sf::Vector2u(2, 3), 1.0f, sf::Vector2f(chonBlockwhat[j].body.getPosition().x, chonBlockwhat[j].body.getPosition().y - 80), 1));
									break;
								case(2):
									item.push_back(Item(&itemTexture, sf::Vector2u(2, 3), 1.0f, sf::Vector2f(chonBlockwhat[j].body.getPosition().x, chonBlockwhat[j].body.getPosition().y - 80), 2));
									break;
								}
								checkchon[j] = false;
							}
						}
					}

				}

				////// Get Item //////
				for (int i = 0; i < item.size(); i++)
				{
					if (item[i].GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
					{
						checkItem = true;
						rowItem = item[i].ItemRow();
						std::cout << item[i].ItemRow() << std::endl;
						switch (item[i].ItemRow()) //item[i].ItemRow()
						{
						case(0):
							Clockrow0.restart();
							//std::cout << "FFFFF";
							row0 = true;
							row1 = false;
							row2 = false;
							break;

						case(1):
							Clockrow1.restart();
							row0 = false;
							row1 = true;
							row2 = false;
							break;
						case(2):
							Clockrow2.restart();
							row0 = false;
							row1 = false;
							row2 = true;
							break;
						}
						coineffSound.play();
						item.erase(item.begin() + i);
					}
				}

				////// สมบัติของ Item //////
				// run fast
				if (Clockrow0.getElapsedTime().asMilliseconds() < 2000 && row0)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						player.speed -= 50;
						player.maxspeed = 100;
						powerupSound.play();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						player.speed += 50;
						player.maxspeed = 100;
						powerupSound.play();
					}
				}
				else
				{
					player.speed = 100;
					player.maxspeed = 100;
					row0 = false;
					checkItem = false;
				}
				// พลังชีวิตลด
				if (Clockrow1.getElapsedTime().asMilliseconds() < 2000 && row1)
				{
					life -= 1;
					gameoverSound.play();
				}
				else
				{
					row1 = false;
				}
				// คะเเนนเพิ่มอย่างรวดเร็ว
				if (Clockrow2.getElapsedTime().asMilliseconds() < 2000 && row2)
				{
					score += 10;
					powerupSound.play();
				}
				else
				{
					row2 = false;
				}

				///////////////////////////////////////////////////////// check block ชน up and down //////////////////////////////////////////////////////////////////////
				// block updown ฉากที่ 2 //
				if (Bmap2.body.getPosition().y == -1500)
					blockupdown = 0;
				else if (Bmap2.body.getPosition().y == -1100)
					blockupdown = 1;

				if (blockupdown == 0)
					Bmap2.body.move(0.0f, 1.0f);
				if (blockupdown == 1)
					Bmap2.body.move(0.0f, -1.0f);
				if (Bmap2.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) {
					player.OnCollision(direction);
				}

				// block updown ฉากที่ 4 //
				if (Bmap4.body.getPosition().y == -4700) // อันเเรก
					blockupdown = 0;
				else if (Bmap4.body.getPosition().y == -4300)
					blockupdown = 1;

				if (blockupdown == 0)
					Bmap4.body.move(0.0f, 1.0f);
				if (blockupdown == 1)
					Bmap4.body.move(0.0f, -1.0f);
				if (Bmap4.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) {
					player.OnCollision(direction);
				}

				if (Bmap5.body.getPosition().y == -4700) //อันที่ 2
					blockupdown = 0;
				else if (Bmap5.body.getPosition().y == -4300)
					blockupdown = 1;

				if (blockupdown == 0)
					Bmap5.body.move(0.0f, 1.0f);
				if (blockupdown == 1)
					Bmap5.body.move(0.0f, -1.0f);
				if (Bmap5.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) {
					player.OnCollision(direction);
				}


				///////////////////////////////////////////////////////////	 ฉากกั้น ///////////////////////////////////////////////////////////////////////////
				
				if (Partition.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //ฉากกั้นที่ 1 ล่องหน
					player.OnCollision(direction);
				if (Partition2.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //ฉากกั้นที่ 2 ล่องหน
					player.OnCollision(direction);
				if (Partition3.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //ฉากกั้นที่ 3 ล่องหน
					player.OnCollision(direction);
				if (Partition4.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //ฉากกั้นที่ 4 ล่องหน
					player.OnCollision(direction);
				if (Partition5.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //ฉากกั้นที่ 5 ล่องหน
					player.OnCollision(direction);



				//////////////////////////////////////////////////////////// Player view ///////////////////////////////////////////////////////////
				
				if (player.GetPosition().x >= -418 && player.GetPosition().x <= 2800) //ล็อคฉากที่ 1 ไม่ให้เลื่อนเกิน ด้านซ้าย && ด้านขวา (ให้อยุ่กลางจอ) && player.GetPosition().x <= 824
				{
					view.setCenter(player.GetPosition().x, player.GetPosition().y); //ล็อคฉากไม่เคลื่อนขึ้นบน ,0
				}

				window.clear(sf::Color(100, 100, 100)); //130 100 60 brown
				window.setView(view);
				window.draw(bg);
				window.draw(bgwater);
				window.draw(bg2);
				window.draw(bg3);
				window.draw(bg4);
				window.draw(bg5);


				BlockSlide.Draw(window); // block เลื่อน
				BlockSlide2.Draw(window); // block slide2 เลื่อน
				Bmap2.Draw(window); // block เลื่อนขึ้นลง
				Bmap4.Draw(window); // block2 เลื่อนขึ้นลง
				Bmap4.Draw(window); // block3 เลื่อนขึ้นลง
				Bmap5.Draw(window); // block3 เลื่อนขึ้นลง
				boss.Draw(window);

				for (Platform& platform : platforms)
				{
					platform.Draw(window);
				}

				for (Platform& platform : Blockwhat)
				{
					platform.Draw(window);
				}
				/*for (Platform& platform : chonBlockwhat) //check ชน blockwhat
				{
					platform.Draw(window);
				}*/

				for (Coin& coin : coins)
				{
					coin.Draw(window);
					coin.Update(deltaTime);
				}

				for (Key& key : keys)
				{
					key.Draw(window);
					key.Update(deltaTime);
				}

				for (Item& i : item)
				{
					i.Draw(window);
					i.Update(deltaTime);
				}

				for (Princess& princess : myprincess)
				{
					princess.Draw(window);
					princess.Update(deltaTime);
				}

				for (Platform& platform : platforms) // check boss ชน platform	
					if (platform.GetCollider().CheckCollision(boss.GetCollider(), directionM, 1.0f))
						boss.OnCollision(directionM);

				if (BossBlood > 0)
				{
					if (boss.body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						player.body.setPosition(boss.body.getPosition().x - 100.0f, boss.body.getPosition().y);

						if (life > 0)
							gameoverSound.play();
						life--;
					}
				}


				for (size_t j = 0; j < vbullet.size(); j++) //เชคกระสุนยิงศัตรู
				{
					if (vbullet[j].body.getGlobalBounds().intersects(boss.body.getGlobalBounds()))
					{
						shootSound.play();
						BossBlood--;
						vbullet.erase(vbullet.begin() + j);
						score += 1000;
					}



					if (BossBlood <= 0 && player.body.getGlobalBounds().intersects(boss.body.getGlobalBounds()))
					{
						if (BossBlood == 0)
						{
							score += 5000;
							BossBlood--;
						
						}
					}
				}


				for (enemy& enemy : enemys) //check platform collision enemy
				{
					for (Platform& platform : platforms)
					{
						if (platform.GetCollider().CheckCollision(enemy.GetCollider(), direction, 1.0f))
							enemy.OnCollision(direction);
					}
					enemy.Draw(window);
					enemy.Update(deltaTime);
				}


				//////////////////////////////////////////////////////////	check ชน WarpPoint ///////////////////////////////////////////////////////////////////////

				if (player.GetCollider().CheckCollision(Collider(door))) { // หน้าต่างวาร์ปในฉากที่ 1
					player.setPosition(sf::Vector2f(-600, -75));
				}
				if (player.GetCollider().CheckCollision(Collider(door2))) { // หน้าต่างวาร์ปในฉากที่ 3
					player.setPosition(sf::Vector2f(-800, -1600));
				}
				if (player.GetCollider().CheckCollision(Collider(warpPoint))) { //ประตูวาร์ปฉากที่ 1 ไปฉากที่ 2
					player.setPosition(sf::Vector2f(-800, -1600));
				}
				//if (player.GetCollider().CheckCollision(Collider(warpPoint2))) { //test 1 ไป 2 สี่เหลี่ยมสีเเดง
				//	player.setPosition(sf::Vector2f(-500, -1500));
				//}
				if (player.GetCollider().CheckCollision(Collider(warpPoint3))) { //ประตูวาร์ปฉากที่ 2 ไปฉากที่ 3
					player.setPosition(sf::Vector2f(-700, -2650));
				}
				//if (player.GetCollider().CheckCollision(Collider(warpPoint4))) { //test 2 go 3 black 
				//	player.setPosition(sf::Vector2f(-300, -3500));
				//}
				if (player.GetCollider().CheckCollision(Collider(warpPoint5))) { //ประตูวาร์ปฉากที่ 3 ไปฉากที่ 4
					player.setPosition(sf::Vector2f(-700, -4200));
				}
				//if (player.GetCollider().CheckCollision(Collider(warpPoint6))) { //ประตูวาร์ปฉากที่ 3 ไปฉากที่ 4
				//	player.setPosition(sf::Vector2f(-700, -5150));
				//}
				if (player.GetCollider().CheckCollision(Collider(warpPoint7))) { //ประตูวาร์ปฉากที่ 4 ไปฉากที่ 5
					player.setPosition(sf::Vector2f(-700, -6100));
				}
				if (player.GetPosition().y > 250) { // water ในฉากที่ 1
					player.setPosition(sf::Vector2f(-340, -160));
					enemyhurtSound.play();
					life--;
				}
				if (player.GetPosition().y > -1380 && player.GetPosition().y < -1000 && player.GetPosition().x > 1195 && player.GetPosition().x < 1625) { // cactus ในฉากที่ 2
					player.setPosition(sf::Vector2f(-260, -1260));
					enemyhurtSound.play();
					life--;
				}

				/////////////////////////////////////  ใส่ Score /////////////////////////////////////////////////////
				sf::Text scoreText;
				sf::Font font;
				font.loadFromFile("Font/ROGFonts-Regular.otf");

				scoreText.setFont(font);
				scoreText.setCharacterSize(25);
				scoreText.setFillColor(sf::Color::Red);
				scoreText.setOutlineColor(sf::Color::White);
				scoreText.setOutlineThickness(1.0f);
				std::stringstream ss;
				scoreText.setPosition(player.GetPosition().x + 120, player.GetPosition().y - 320); //+120 -320
				ss << "SCORE : " << score;
				scoreText.setString(ss.str());

				/////////////////////////////////////  ใส่ life /////////////////////////////////////////////////////
				sf::Text lifeText;
				sf::RectangleShape lifeRec;
				std::string lifeString;
				lifeText.setFont(font);
				lifeText.setFillColor(sf::Color::Red);
				lifeText.setOutlineColor(sf::Color::White);
				lifeText.setOutlineThickness(1.0f);
				lifeText.setCharacterSize(25);
				lifeText.setPosition(player.GetPosition().x - 300, player.GetPosition().y - 320);
				lifeString = " LIFE : " + std::to_string(life);
				lifeText.setString(lifeString);

				/////////////////////////////////////  ใส่ key /////////////////////////////////////////////////////
				sf::Text keyText;
				sf::RectangleShape keyRec;
				std::string keyString;
				keyText.setFont(font);
				keyText.setFillColor(sf::Color::Red);
				keyText.setOutlineColor(sf::Color::White);
				keyText.setOutlineThickness(1.0f);
				keyText.setCharacterSize(25);
				keyText.setPosition(player.GetPosition().x - 300, player.GetPosition().y - 290);
				keyString = " KEY : " + std::to_string(key);
				keyText.setString(keyString);



				window.draw(door); //หน้าต่างวาปฉากที่ 1
				window.draw(warpPoint);
				//window.draw(warpPoint2); //test1
				window.draw(warpPoint3);
				window.draw(door2); //หน้าต่างวาปฉากที่ 3
				//window.draw(warpPoint4); //test2
				window.draw(warpPoint5);
				//window.draw(warpPoint6); //test3
				window.draw(warpPoint7);
				window.draw(scoreText);
				window.draw(lifeText);
				window.draw(keyText);

			

				player.Draw(window);

				for (bullet& b : vbullet)
				{
					b.Draw(window);
				}

			}
		}
		window.display();
		
	
	}
	return 0;
}