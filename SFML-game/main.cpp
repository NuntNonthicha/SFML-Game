#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include"Animation.h"
#include"Player.h"
#include"Platform.h"
#include"Collider.h"
#include"bullet.h"
#include "enemy.h"
#include "Coin.h"
#include "Key.h"
#include<vector>
#include"Menu.h"
#include<algorithm>
#include <fstream>
#include<sstream>
#include<time.h>


static const float VIEW_HEIGHT = 720.0f;
int blockupdown;
int enemyX[20] = {};
int ranenemyX[20] = {};
bool showHitBox = true; // show hitbox ให้มีหรือไม่มี

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

//int rand_x = (rand() % int(window.getSize().x))
int main()
{
	srand(time(NULL));
	int score = 0;
	unsigned int life = 3;
	int key = 0;
	int keyx[20] = { 0 }, keyy[20] = { 0 };
	int x = 0; //x คือ เลขตัวเข้าเมนู
	
	bool checkState = false;
	
	sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);

	/*Menu menu(window.getSize().x, window.getSize().y);*/
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT , VIEW_HEIGHT));
	sf::Vector2f checkpoint;
	
	sf::Texture playerTexture; //knight player
	playerTexture.loadFromFile("robot.png"); 

	
	sf::Texture enemyTexture; //enemy alien ในฉากที่ 3
	enemyTexture.loadFromFile("frog.png");
	sf::Texture enemyTexture2; //enemy pumpkin ในฉากที่ 5
	enemyTexture2.loadFromFile("enemy.png");
	sf::Texture enemyTexture3; //enemy bear ในฉากที่ 1
	enemyTexture3.loadFromFile("bear.png");
	sf::Texture enemyTexture4; //enemy dinosour ในฉากที่ 2 + 4
	enemyTexture4.loadFromFile("dinosour.png");

	////////////////////////////////////////////////// Background////////////////////////////////////////////////////////////

	sf::Texture backgroundmenu; // bg menu
	backgroundmenu.loadFromFile("bgmenu2.png");
	sf::RectangleShape bgmenu(sf::Vector2f(1080, 720));
	bgmenu.setTexture(&backgroundmenu);

	sf::Texture backgroundhowtoplay; // bg menu how to play
	backgroundhowtoplay.loadFromFile("menuhowtoplay.png");
	sf::RectangleShape bghowtoplay(sf::Vector2f(1080, 720));
	bghowtoplay.setTexture(&backgroundhowtoplay);

	sf::Texture backgroundhighscore; // bg menu high score
	backgroundhighscore.loadFromFile("menuhighscore.png");
	sf::RectangleShape bghighscore(sf::Vector2f(1080, 720));
	bghighscore.setTexture(&backgroundhighscore);


	sf::Texture background; // bg ฉากที่ 1 
	background.loadFromFile("bg01.png");
	sf::RectangleShape bg(sf::Vector2f(4000, 1000));
	bg.setPosition(sf::Vector2f(-800, -800)); //-500 -360
	bg.setTexture(&background);

	sf::Texture floorwater; // ใส่พื้นน้ำ
	floorwater.loadFromFile("water.png");
	sf::RectangleShape bgwater(sf::Vector2f(2500, 3800));
	bgwater.setPosition(sf::Vector2f(2500, 200));
	bgwater.setTexture(&floorwater);

	sf::Texture background2; // bg ฉากที่ 2
	background2.loadFromFile("bg02.png");
	sf::RectangleShape bg2(sf::Vector2f(4000, 1000));
	bg2.setPosition(sf::Vector2f(-800, -2200)); 
	bg2.setTexture(&background2);

	sf::Texture background3; // bg ฉากที่ 3
	background3.loadFromFile("bg03.png");
	sf::RectangleShape bg3(sf::Vector2f(4000, 1000));
	bg3.setPosition(sf::Vector2f(-800, -3600));
	bg3.setTexture(&background3);

	sf::Texture background4; // bg ฉากที่ 4
	background4.loadFromFile("bg04.png");
	sf::RectangleShape bg4(sf::Vector2f(4000, 1000));
	bg4.setPosition(sf::Vector2f(-800, -5150));
	bg4.setTexture(&background4);

	sf::Texture background5; // bg ฉากที่ 5
	background5.loadFromFile("bg5.png");
	sf::RectangleShape bg5(sf::Vector2f(4000, 1000));
	bg5.setPosition(sf::Vector2f(-800, -6600));
	bg5.setTexture(&background5);

	/// bg1+2 floor+block
	sf::Texture floor;
	floor.loadFromFile("floor01.png");
	sf::Texture floor2;
	floor2.loadFromFile("floor02.png");
	sf::Texture floor3;
	floor3.loadFromFile("floor03.png");
	sf::Texture floor4;
	floor4.loadFromFile("floor04.png");
	sf::Texture floor5;
	floor5.loadFromFile("floor05.png");
	sf::Texture block;
	block.loadFromFile("block.png");
	sf::Texture block01;
	block01.loadFromFile("block01.png");
	sf::Texture block02;
	block02.loadFromFile("block02.png");
	sf::Texture block03;
	block03.loadFromFile("block03.png");
	sf::Texture block04;
	block04.loadFromFile("block04.png");
	sf::Texture blockcoin;
	blockcoin.loadFromFile("blockcoin.png");
	sf::Texture brick; //อิฐขั้นบันได
	brick.loadFromFile("brick.png");
	sf::Texture channel; //ท่อเขียว
	channel.loadFromFile("channel.png");
	sf::Texture channel02; //ท่อเหลือง
	channel02.loadFromFile("channel02.png");
	sf::Texture windowwarp; //หน้าต่างวาร์ป
	windowwarp.loadFromFile("window.png");
	sf::Texture heart; //หัวใจ
	heart.loadFromFile("heart.png");
	sf::Texture doorwarp; //ประตูวาร์ป
	doorwarp.loadFromFile("door.png");
	sf::Texture doorwarp2; //ประตูวาร์ป2
	doorwarp2.loadFromFile("door2.png");
	sf::Texture doorwarp3; //ประตูวาร์ป3
	doorwarp3.loadFromFile("door3.png");
	sf::Texture doorwarp4; //ประตูวาร์ป4
	doorwarp4.loadFromFile("door4.png");
	sf::Texture cactus; //กระบองเพชร
	cactus.loadFromFile("cactus.png");
	sf::Texture iceblock; //ice block เลื่อน
	iceblock.loadFromFile("iceblock.png");
	sf::Texture ice; //ice block
	ice.loadFromFile("ice.png");
	sf::Texture stalagmite; //ice block
	stalagmite.loadFromFile("stalagmite.png");
	sf::Texture ball; //กระสุน
	ball.loadFromFile("ball.png");
	sf::Texture coinTexture; //coin
	coinTexture.loadFromFile("coin.png");
	sf::Texture keyTexture; //key 
	keyTexture.loadFromFile("key.png");
	

	/// Menu button
	sf::Texture buttonplay; //button menu play
	buttonplay.loadFromFile("play.png");
	sf::Texture buttonhowtoplay; //button menu howtoplay
	buttonhowtoplay.loadFromFile("howtoplay.png");
	sf::Texture buttonhighscore; //button menu highscore
	buttonhighscore.loadFromFile("highscore.png");
	sf::Texture buttonexit; //button exit
	buttonexit.loadFromFile("exit.png");
	sf::Texture buttonreturnmenu; //button return menu highscore to main menu
	buttonreturnmenu.loadFromFile("returnmenu.png");
	
	sf::Music music1, mainMusic, map2Music, map5Music, mapmainMusic, map4Music;

	music1.openFromFile("Sound/map1.mp3");
	
	music1.setVolume(100);
	music1.setLoop(true);
	
	Player player(&playerTexture, sf::Vector2u(8, 3), 0.1f, 100, 100, showHitBox);

	//////////////////////////////////////////////////////////////////////// Platform ////////////////////////////////////////////////////////////////////////
	
	/// vector //
	std::vector<Platform> platforms;
	std::vector<bullet> vbullet;
	std::vector<enemy> enemys;
	std::vector<Coin> coins;
	std::vector<Key> keys;


	keys.push_back(Key(&keyTexture, sf::Vector2u(6, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(0.0f, 0.0f)));
	keys.push_back(Key(&keyTexture, sf::Vector2u(6, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(200.0f, 0.0f)));

	/////////////////////////////////////////////////// Platform 1  ////////////////////////////////////////////////////////
	//for (int i = 0; i < 5; i++) อิหยังงงงงงงง??
	//{
	//	srand(time(NULL));
	//	enemyX[i] = rand();

	//	if (ranenemyX[i] >= 0 && ranenemyX[i] <= 1000)
	//		enemyX[i] = ranenemyX[i];

	//	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(enemyX[i], 160.0f)));
	//	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(enemyX[i], 160.0f)));
	//	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(enemyX[i], 160.0f)));
	//	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(enemyX[i], 160.0f)));
	//}
	if (player.GetPosition().y <= 2360.0f && player.GetPosition().y > 900.0f)    //1
	{
		music1.play();
		
	}
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
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(900.0f, -1690.0f), 1, showHitBox)); //heart
	platforms.push_back(Platform(&cactus, sf::Vector2f(400.0f, 100.0f), sf::Vector2f(1420.0f, -1240.0f), 0, showHitBox)); //cactus
	platforms.push_back(Platform(&channel02, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(2000.0f, -1540.0f), 0, showHitBox)); //block ท่อเหลือง1
	platforms.push_back(Platform(&channel02, sf::Vector2f(100.0f, 318.0f), sf::Vector2f(2000.0f, -1360.0f), 0, showHitBox)); ////block ท่อเหลือง1
	platforms.push_back(Platform(&block02, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(2200.0f, -1260.0f), 0, showHitBox)); ////block เลื่อนขึ้นลง
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

	platforms.push_back(Platform(&heart, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(650.0f, -2800.0f), 1, showHitBox));

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

	/////////////////////////////////////////////////// Platform 4  ////////////////////////////////////////////////////////

	Platform Partition4(&block01, sf::Vector2f(40.0f, 500.0f), sf::Vector2f(-750.0f, -4500.0f), 0, showHitBox); //ฉากกั้นของฉากที่ 4

	Platform Bmap4(&floor2, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(1050.0f , -4300.0f), 0, showHitBox); // block เลื่อนขึ้นเเละลง
	Platform Bmap5(&floor2, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(1650.0f , -4300.0f), 0, showHitBox); // block เลื่อนขึ้นเเละลง
	
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
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 700, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 800, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 1285, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 1365, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 1430, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 1850, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 2000, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 2050, -4240, 100.0f, 200));
	enemys.push_back(enemy(&enemyTexture4, sf::Vector2u(8, 1), 0.1f, 2550, -4240, 100.0f, 200));

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

	/////////////////////////////////////////////////// Platform 5  ////////////////////////////////////////////////////////
	
	Platform Partition5(&block, sf::Vector2f(40.0f, 1000.0f), sf::Vector2f(-750.0f, -5600.0f), 0, showHitBox); //ฉากกั้นของฉากที่ 5

	//// Enemy ฉากที่ 5 /////
	enemys.push_back(enemy(&enemyTexture, sf::Vector2u(10, 1), 0.1f, 700, -5640, 100.0f, 600));
	
	
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 0.0f, -5640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 300.0f, -5640.0f)));
	coins.push_back(Coin(&coinTexture, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(rand() % 100 + 500.0f, -5640.0f)));


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
	
	sf::RectangleShape warpPoint2(sf::Vector2f(60, 50)); // ประตูวาร์ป test 1 go 2
	warpPoint2.setPosition(sf::Vector2f(-600, 100));
	warpPoint2.setFillColor(sf::Color::Red);
	
	sf::RectangleShape warpPoint3(sf::Vector2f(150, 300)); // ประตูวาร์ปจากฉากที่ 2 ไป 3
	warpPoint3.setPosition(sf::Vector2f(2950, -1500));
	warpPoint3.setTexture(&doorwarp2);

	sf::RectangleShape warpPoint4(sf::Vector2f(50, 50)); // ประตูวาร์ป test 2 go 3
	warpPoint4.setPosition(sf::Vector2f(200, -1500));
	warpPoint4.setFillColor(sf::Color::Black);

	sf::RectangleShape warpPoint5(sf::Vector2f(180, 400)); // ประตูวาร์ปจากฉากที่ 3 ไป 4
	warpPoint5.setPosition(sf::Vector2f(2950, -3000));
	warpPoint5.setTexture(&doorwarp3);

	sf::RectangleShape warpPoint6(sf::Vector2f(180, 400)); // // ประตูวาร์ป test 3 go 4
	warpPoint6.setPosition(sf::Vector2f(200, -3200));
	warpPoint6.setTexture(&doorwarp3);

	sf::RectangleShape warpPoint7(sf::Vector2f(200, 400)); // ประตูวาร์ปจากฉากที่ 4 ไป 5
	warpPoint7.setPosition(sf::Vector2f(2900, -4600));
	warpPoint7.setTexture(&doorwarp4);

	float deltaTime = 0.0f;
	sf::Clock clock;
	
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
		button4.setPosition(sf::Vector2f(980, 650));
		button4.setTexture(&buttonreturnmenu);
		sf::RectangleShape button5(sf::Vector2f(295, 150)); //button exit
		button5.setPosition(sf::Vector2f(750, 520));
		button5.setTexture(&buttonexit);
		if(x == 0)
		{

			
			window.clear();
			if (button1.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				button1.setFillColor(sf::Color::Green);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					button1.setFillColor(sf::Color::Yellow);
					x = 3;
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
			window.draw(bgmenu);
			window.draw(button1);
			window.draw(button2);
			window.draw(button3);
			window.draw(button5);
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
			if (button4.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				button4.setFillColor(sf::Color::Yellow);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					button4.setFillColor(sf::Color::Blue);
					x = 0;
				}
			}
			window.draw(bghighscore);
			window.draw(button4);
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า Exit /////////////////////////////////////////////////////////////////////////////////////////////////////
		if (x == 4)
		{
			window.close();
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////// หน้า Start เข้า Game /////////////////////////////////////////////////////////////////////////////////////////////////////////
			
		if (x == 3)
		{
			printf("x = %.f  y = %.f\n", player.GetPosition().x, player.GetPosition().y);

			player.Update(deltaTime);


			sf::Vector2f direction;

			/////////////////////////////////////////////////////// check bullet /////////////////////////////////////////

			if (player.isShoot()) { // ยิงกระสนุ
				vbullet.push_back(bullet(&ball, sf::Vector2f(32.0f, 32.0f), 0, 50.0f, player.GetPosition().x, player.GetPosition().y - 35, player.faceRight));
			}

			for (int i = 0; i < vbullet.size(); i++) {
				vbullet[i].Update(deltaTime);

			}


			/// check player เดินชน enemy เเล้วพลังชีวิตลด///
			if (life <= 0) {
				printf(" Game over ");
			}
			for (size_t i = 0; i < enemys.size(); i++)
			{
				if (player.GetCollider().CheckCollision(enemys[i].GetCollider(), direction, 0.0f))
				{
					
						//enemys.erase(enemys.begin() + i);
						life--;
						if (life <= 0)
						{
							printf("Dead!!");
							x = 4;
						}

				}
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
						printf(" hit");
						if (enemys[i].hp <= 0)
						{
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
					score += 10;
					coins.erase(coins.begin() + i);
				}
					
			}


			// check player ชน key ///
			for (size_t i = 0; i < keys.size(); i++)
			{
				if (player.GetCollider().CheckCollision(keys[i].GetCollider(), direction, 0.0f))
				{
					key++;
					keys.erase(keys.begin() + i);
				}
				if (key == 2) {  // goto map boss
					player.body.setPosition(750.0f, -5600.0f);
				}
			}

			/////////////////////////////////////////////////////////check ชน //////////////////////////////////////////////////////////////////////
			int coin = 0;
			for (Platform& platform : platforms) { //check collision platform
				if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) {
					player.OnCollision(direction);
					if (platform.getBlockType() == 1) { // 1 = ชน
						printf("\n\coin");
						platforms.erase(platforms.begin() + coin);
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

			/////////////////////////////////////////////////////////// ฉากกั้น ///////////////////////////////////////////////////////////////////////////
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

			/////////////////////////////////////////////////////////// Check ชน Key ///////////////////////////////////////////////////////////////////////////
		

			//if (player.body.getGlobalBounds().intersects(map3WARP5.body.getGlobalBounds()) && key == 4)   //map 3  : goto map boss
			//	player.body.setPosition(-1380.0f, -14250.0f);
		
			

		

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
			
			for (Platform& platform : platforms)
			{
				platform.Draw(window);
			}
			
			for(Coin& coin : coins)
			{
				coin.Draw(window);
				coin.Update(deltaTime);
			}

			for (Key& key : keys)
			{
				key.Draw(window);
				key.Update(deltaTime);
			}

			for (enemy& enemy : enemys)
			{
				for (Platform& platform : platforms)
				{
					if (platform.GetCollider().CheckCollision(enemy.GetCollider(), direction, 1.0f)) //check platform collision enemy
						enemy.OnCollision(direction);
				}
				enemy.Draw(window);
				enemy.Update(deltaTime);
			}

			
			//////////////////////////////////////////////////////////check ชน WarpPoint ///////////////////////////////////////////////////////////////////////

			if (player.GetCollider().CheckCollision(Collider(door))) { // หน้าต่างวาร์ปในฉากที่ 1
				player.setPosition(sf::Vector2f(-600, -75));
			}
			if (player.GetCollider().CheckCollision(Collider(door2))) { // หน้าต่างวาร์ปในฉากที่ 3
				player.setPosition(sf::Vector2f(-800, -1600));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint))) { //ประตูวาร์ปฉากที่ 1 ไปฉากที่ 2
				player.setPosition(sf::Vector2f(-800, -1600));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint2))) { //test 1 ไป 2 สี่เหลี่ยมสีเเดง
				player.setPosition(sf::Vector2f(-500, -1500));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint3))) { //ประตูวาร์ปฉากที่ 2 ไปฉากที่ 3
				player.setPosition(sf::Vector2f(-700, -2650));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint4))) { //test 2 go 3 black 
				player.setPosition(sf::Vector2f(-300, -3500));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint5))) { //ประตูวาร์ปฉากที่ 3 ไปฉากที่ 4
				player.setPosition(sf::Vector2f(-700, -4200));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint6))) { //ประตูวาร์ปฉากที่ 3 ไปฉากที่ 4
				player.setPosition(sf::Vector2f(-700, -5150));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint7))) { //ประตูวาร์ปฉากที่ 4 ไปฉากที่ 5
				player.setPosition(sf::Vector2f(-700, -6100));
			}
			if (player.GetPosition().y > 250) { // water ในฉากที่ 1
				player.setPosition(sf::Vector2f(-340, -160));
				life--;
			}
			if (player.GetPosition().y > -1380 && player.GetPosition().y < -1000 && player.GetPosition().x > 1195 && player.GetPosition().x < 1625 ) { // cactus ในฉากที่ 2
				player.setPosition(sf::Vector2f(-260, -1260));
				life--;
			}
			
			/////////////////////////////////////  ใส่ Score /////////////////////////////////////////////////////
			sf::Text scoreText;
			sf::Font font;
			if (!font.loadFromFile("Font/ROGFonts-Regular.otf"))
			{
				std::cout << "ERROR TO LOAD FONT" << "\n";
			}
			scoreText.setFont(font);
			scoreText.setCharacterSize(25);
			scoreText.setFillColor(sf::Color::Red);
			scoreText.setOutlineColor(sf::Color::Black);
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
			lifeText.setOutlineColor(sf::Color::Black);
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
			keyText.setOutlineColor(sf::Color::Black);
			keyText.setOutlineThickness(1.0f);
			keyText.setCharacterSize(25);
			keyText.setPosition(player.GetPosition().x -300 , player.GetPosition().y -290 );
			keyString = " KEY : " + std::to_string(key);
			keyText.setString(keyString);

			

			window.draw(door); //หน้าต่างวาปฉากที่ 1
			window.draw(warpPoint);
			window.draw(warpPoint2); //test1
			window.draw(warpPoint3);
			window.draw(door2); //หน้าต่างวาปฉากที่ 3
			window.draw(warpPoint4); //test2
			window.draw(warpPoint5);
			window.draw(warpPoint6); //test3
			window.draw(warpPoint7);
			window.draw(scoreText);
			window.draw(lifeText);
			window.draw(keyText);
			/// 
			
			
			player.Draw(window);

			for (bullet& b : vbullet)
			{
				b.Draw(window);
			}


		}
		window.display();
		
		
	
	}
	return 0;
}