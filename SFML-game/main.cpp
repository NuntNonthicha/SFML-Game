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
#include<vector>
#include"Menu.h"
#include<algorithm>
#include <fstream>
#include<sstream>

static const float VIEW_HEIGHT = 720.0f;
int blockupdown;

bool showHitBox = true; // show hitbox ��������������

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int score(int score)
{
	if (score)
	{
		printf("%d\n", score);
	}
	return score;
}

int main()
{
	int j = 0; //�� score
	int x = 0; //x ��� �Ţ����������
	bool checkState = false;
	
	sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);

	/*Menu menu(window.getSize().x, window.getSize().y);*/
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT , VIEW_HEIGHT));
	sf::Vector2f checkpoint;
	
	sf::Texture playerTexture; //knight player
	playerTexture.loadFromFile("robot.png"); 

	
	sf::Texture enemyTexture; //enemy frog 㹩ҡ��� 1
	enemyTexture.loadFromFile("frog.png");
	sf::Texture enemyTexture2; //enemy pumpkin 㹩ҡ��� 2
	enemyTexture2.loadFromFile("enemy.png");
	sf::Texture enemyTexture3; //enemy bear 㹩ҡ��� 3
	enemyTexture3.loadFromFile("bear.png");
	sf::Texture enemyTexture4; //enemy dinosour 㹩ҡ��� 4
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


	sf::Texture background; // bg �ҡ��� 1 
	background.loadFromFile("bg01.png");
	sf::RectangleShape bg(sf::Vector2f(4000, 1000));
	bg.setPosition(sf::Vector2f(-800, -800)); //-500 -360
	bg.setTexture(&background);

	sf::Texture floorwater; // ����鹹��
	floorwater.loadFromFile("water.png");
	sf::RectangleShape bgwater(sf::Vector2f(2500, 3800));
	bgwater.setPosition(sf::Vector2f(2500, 200));
	bgwater.setTexture(&floorwater);

	sf::Texture background2; // bg �ҡ��� 2
	background2.loadFromFile("bg02.png");
	sf::RectangleShape bg2(sf::Vector2f(4000, 1000));
	bg2.setPosition(sf::Vector2f(-800, -2200)); 
	bg2.setTexture(&background2);

	sf::Texture background3; // bg �ҡ��� 3
	background3.loadFromFile("bg03.png");
	sf::RectangleShape bg3(sf::Vector2f(4000, 1000));
	bg3.setPosition(sf::Vector2f(-800, -3600));
	bg3.setTexture(&background3);

	sf::Texture background4; // bg �ҡ��� 4
	background4.loadFromFile("bg04.png");
	sf::RectangleShape bg4(sf::Vector2f(4000, 1000));
	bg4.setPosition(sf::Vector2f(-800, -5150));
	bg4.setTexture(&background4);

	sf::Texture background5; // bg �ҡ��� 5
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
	sf::Texture brick; //�԰��鹺ѹ�
	brick.loadFromFile("brick.png");
	sf::Texture channel; //�������
	channel.loadFromFile("channel.png");
	sf::Texture channel02; //�������ͧ
	channel02.loadFromFile("channel02.png");
	sf::Texture windowwarp; //˹�ҵ�ҧ����
	windowwarp.loadFromFile("window.png");
	sf::Texture heart; //����
	heart.loadFromFile("heart.png");
	sf::Texture doorwarp; //��е�����
	doorwarp.loadFromFile("door.png");
	sf::Texture doorwarp2; //��е�����2
	doorwarp2.loadFromFile("door2.png");
	sf::Texture doorwarp3; //��е�����3
	doorwarp3.loadFromFile("door3.png");
	sf::Texture doorwarp4; //��е�����4
	doorwarp4.loadFromFile("door4.png");
	sf::Texture cactus; //��кͧྪ�
	cactus.loadFromFile("cactus.png");
	sf::Texture iceblock; //ice block ����͹
	iceblock.loadFromFile("iceblock.png");
	sf::Texture ice; //ice block
	ice.loadFromFile("ice.png");
	sf::Texture stalagmite; //ice block
	stalagmite.loadFromFile("stalagmite.png");
	sf::Texture ball; //����ع
	ball.loadFromFile("ball.png");


	/// Menu button
	sf::Texture buttonplay; //button menu play
	buttonplay.loadFromFile("play.png");
	sf::Texture buttonhowtoplay; //button menu howtoplay
	buttonhowtoplay.loadFromFile("howtoplay.png");
	sf::Texture buttonhighscore; //button menu highscore
	buttonhighscore.loadFromFile("highscore.png");
	sf::Texture buttonreturnmenu; //button return menu highscore to main menu
	buttonreturnmenu.loadFromFile("returnmenu.png");
	
	
	Player player(&playerTexture, sf::Vector2u(8, 3), 0.1f, 100, 100, showHitBox);

	///  Enemy 㹩ҡ��� 1
	//enemy enemy1(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 600, 115 , 100.0f); //enemy bears
	//enemy enemy2(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 700, 115, 100.0f);
	enemy enemy3(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 1300, 115, 100.0f);
	enemy enemy4(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 2160, 115, 100.0f);

	

	//////////////////////////////////////////////////////////////////////// Platform ////////////////////////////////////////////////////////////////////////
	
	/// vector //
	std::vector<Platform> platforms;
	std::vector<bullet> vbullet;
	std::vector<enemy> enemys;

	enemys.push_back(enemy(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 600, 115, 100.0f));
	enemys.push_back(enemy(&enemyTexture3, sf::Vector2u(6, 1), 0.1f, 00, 115, 100.0f));

	/////////////////////////////////////////////////// Platform 1  ////////////////////////////////////////////////////////

	Platform Partition(&block, sf::Vector2f(40.0f, 2143.0f), sf::Vector2f(-760.0f, 0.0f), 0, showHitBox); //�ҡ��鹢ͧ�ҡ��� 1

	platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-180.0f, 30.0f), 0, showHitBox)); //block1
	float tmp = 0;
	for (float i=0;i<5;i++) //loop block 
	{
	
		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(150.0f + tmp, 30.0f),0, showHitBox)); //block2��� ��
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(850.0f + tmp, 180.0f),0, showHitBox)); //��鹺ѹ䴢�鹷�� 1 : 5 �԰ 
		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2100.0f + tmp, 100.0f), 0, showHitBox)); //block5 ��ҧ blockcoin
		tmp += 40;
	}
	for (float i = 0; i < 4; i++) //loop block 
	{
		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(90.0f + tmp, -150.0f),0, showHitBox)); //block3��� ��
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(690.0f + tmp, 140.0f),0, showHitBox)); //��鹺ѹ䴢�鹷�� 2 : 4 �԰ 
		tmp += 40;
	}
	for (float i = 0; i < 3; i++) //loop block 
	{
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(570.0f + tmp, 100.0f),0, showHitBox)); //��鹺ѹ䴢�鹷�� 3 : 3 �԰ 
		tmp += 40;
	}
	for (float i = 0; i < 2; i++) //loop block 
	{
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(490.0f + tmp, 60.0f),0, showHitBox)); //��鹺ѹ䴢�鹷�� 4 : 2 �԰ s
		tmp += 40;
	}
	for (float i = 0; i <= 0; i++)
	{
		for (float j = 0; j <= 3; j++)
			platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2000.0f + 150 * j, -80.0f + 150 * i),0, showHitBox)); // block4 �ç������
	}

	platforms.push_back(Platform(&channel, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(1400.0f, -80.0f),0, showHitBox)); //block �������
	platforms.push_back(Platform(&channel, sf::Vector2f(100.0f, 700.0f), sf::Vector2f(1400.0f, 300.0f),0, showHitBox)); ////block �������
	

	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(130.0f, 30.0f),1, showHitBox)); //blockcoin1 in block2��� ��
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(250.0f, -150.0f),1, showHitBox)); //blockcoin2 in block3��� ��
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1800.0f, 20.0f),1, showHitBox)); //blockcoin2 in block4��� ��
	platforms.push_back(Platform(&heart, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2250.0f, -280.0f), 1, showHitBox)); //heart

	
	//// Platform background  ��鹩ҡ /////
	platforms.push_back(Platform(&floor, sf::Vector2f(4000.0f, 400.0f), sf::Vector2f(500.0f, 400.0f),0, showHitBox)); //��鹩ҡ��� 1
	platforms.push_back(Platform(&floor, sf::Vector2f(4000.0f, 400.0f), sf::Vector2f(4700.0f, 400.0f),0, showHitBox)); //��鹩ҡ��� 1 ��ѧ���
	platforms.push_back(Platform(&floor2, sf::Vector2f(8000.0f, 400.0f), sf::Vector2f(-500.0f, -1000.0f),0, showHitBox)); //��鹩ҡ��� 2
	platforms.push_back(Platform(&floor3, sf::Vector2f(16000.0f, 400.0f), sf::Vector2f(-1500.0f, -2400.0f), 0, showHitBox)); //��鹩ҡ��� 3
	platforms.push_back(Platform(&floor4, sf::Vector2f(16000.0f, 400.0f), sf::Vector2f(-1000.0f, -4000.0f), 0, showHitBox)); //��鹩ҡ��� 4
	platforms.push_back(Platform(&floor5, sf::Vector2f(16000.0f, 400.0f), sf::Vector2f(-1000.0f, -5400.0f), 0, showHitBox)); //��鹩ҡ��� 4

	

	/////////////////////////////////////////////////// Platform 2  ///////////////////////////////////////////////////////////////////////////////

	Platform Partition2(&block, sf::Vector2f(40.0f, 200.0f), sf::Vector2f(-760.0f, -1350.0f), 0, showHitBox); //�ҡ��鹢ͧ�ҡ��� 2 

	Platform Bmap2(&block02, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(2200.0f, -1500.0f), 0, showHitBox); // block ����͹�������ŧ

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
			platforms.push_back(Platform(&block02, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1200.0f + 120 * j, -1450.0f + 120 * i), 0, showHitBox)); // block4 �ç������
	}

	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1400.0f, -1700.0f), 1, showHitBox)); //blockcoin1 ����кͧ���

	platforms.push_back(Platform(&floor, sf::Vector2f(30.0f, 200.0f), sf::Vector2f(1160.0f, -1300.0f), 0, showHitBox)); //block ��Ǣ�ҧ��кͧྪ�1
	platforms.push_back(Platform(&floor, sf::Vector2f(30.0f, 200.0f), sf::Vector2f(1660.0f, -1300.0f), 0, showHitBox)); //block ��Ǣ�ҧ��кͧྪ�2
	platforms.push_back(Platform(&heart, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(900.0f, -1690.0f), 1, showHitBox)); //heart
	platforms.push_back(Platform(&cactus, sf::Vector2f(400.0f, 100.0f), sf::Vector2f(1420.0f, -1240.0f), 0, showHitBox)); //cactus
	platforms.push_back(Platform(&channel02, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(2000.0f, -1540.0f), 0, showHitBox)); //block �������ͧ1
	platforms.push_back(Platform(&channel02, sf::Vector2f(100.0f, 318.0f), sf::Vector2f(2000.0f, -1360.0f), 0, showHitBox)); ////block �������ͧ1
	platforms.push_back(Platform(&block, sf::Vector2f(100.0f, 150.0f), sf::Vector2f(2200.0f, -1260.0f), 0, showHitBox)); ////block ����͹���ŧ
	platforms.push_back(Platform(&channel02, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(2450.0f, -1540.0f), 0, showHitBox)); //block �������ͧ2
	platforms.push_back(Platform(&channel02, sf::Vector2f(100.0f, 318.0f), sf::Vector2f(2450.0f, -1360.0f), 0, showHitBox)); ////block �������ͧ2

	

	/////////////////////////////////////////////////// Platform 3  ///////////////////////////////////////////////////////////////////////////////

	Platform Partition3(&block, sf::Vector2f(40.0f, 500.0f), sf::Vector2f(-750.0f, -2600.0f), 0, showHitBox); //�ҡ��鹢ͧ�ҡ��� 3

	Platform BlockSlide(&iceblock, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(50.0f, -2650.0f), 0, showHitBox); //block ����͹

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
	platforms.push_back(Platform(&ice, sf::Vector2f(150.0f, 300.0f), sf::Vector2f(850.0f, -2650.0f), 0, showHitBox)); // ice block1
	platforms.push_back(Platform(&stalagmite, sf::Vector2f(180.0f, 600.0f), sf::Vector2f(900.0f, -3330.0f), 0, showHitBox));
	platforms.push_back(Platform(&stalagmite, sf::Vector2f(200.0f, 600.0f), sf::Vector2f(1300.0f, -3330.0f), 0, showHitBox));
	platforms.push_back(Platform(&ice, sf::Vector2f(150.0f, 400.0f), sf::Vector2f(1200.0f, -2650.0f), 0, showHitBox)); //ice block
	Platform BlockSlide2(&iceblock, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1400.0f, -2650.0f), 0, showHitBox); //block ����͹2
	platforms.push_back(Platform(&ice, sf::Vector2f(130.0f, 450.0f), sf::Vector2f(1800.0f, -2650.0f), 0, showHitBox)); //ice block2
	platforms.push_back(Platform(&ice, sf::Vector2f(150.0f, 200.0f), sf::Vector2f(2300.0f, -2650.0f), 0, showHitBox)); //ice block3

	platforms.push_back(Platform(&heart, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(650.0f, -2800.0f), 1, showHitBox));



	/////////////////////////////////////////////////// Platform 4  ////////////////////////////////////////////////////////

	Platform Partition4(&block01, sf::Vector2f(40.0f, 500.0f), sf::Vector2f(-750.0f, -4500.0f), 0, showHitBox); //�ҡ��鹢ͧ�ҡ��� 4

	Platform Bmap4(&floor2, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(1050.0f , -4300.0f), 0, showHitBox); // block ����͹�������ŧ
	Platform Bmap5(&floor2, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(1650.0f , -4300.0f), 0, showHitBox); // block ����͹�������ŧ
	
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


	/////////////////////////////////////////////////// Platform 5  ////////////////////////////////////////////////////////
	
	Platform Partition5(&block, sf::Vector2f(40.0f, 1000.0f), sf::Vector2f(-750.0f, -5600.0f), 0, showHitBox); //�ҡ��鹢ͧ�ҡ��� 5



	//////////////////////////////////////////////////////////////////// WarpPoint ���ҧ��е��һ ////////////////////////////////////////////////////////////
	
	sf::RectangleShape door(sf::Vector2f(100, 150)); // ˹�ҵ�ҧ㹩ҡ��� 1
	door.setPosition(sf::Vector2f(650, -290));
	door.setTexture(&windowwarp);
	
	sf::RectangleShape door2(sf::Vector2f(100, 150)); // ˹�ҵ�ҧ㹩ҡ��� 3
	door2.setPosition(sf::Vector2f(2500, -2950));
	door2.setTexture(&windowwarp);

	sf::RectangleShape warpPoint(sf::Vector2f(200, 300)); // ��е����컨ҡ�ҡ��� 1 � 2
	warpPoint.setPosition(sf::Vector2f(2900, -100));
	warpPoint.setTexture(&doorwarp);
	
	sf::RectangleShape warpPoint2(sf::Vector2f(60, 50)); // ��е����� test 1 go 2
	warpPoint2.setPosition(sf::Vector2f(-600, 100));
	warpPoint2.setFillColor(sf::Color::Red);
	
	sf::RectangleShape warpPoint3(sf::Vector2f(150, 300)); // ��е����컨ҡ�ҡ��� 2 � 3
	warpPoint3.setPosition(sf::Vector2f(2950, -1500));
	warpPoint3.setTexture(&doorwarp2);

	sf::RectangleShape warpPoint4(sf::Vector2f(50, 50)); // ��е����� test 2 go 3
	warpPoint4.setPosition(sf::Vector2f(200, -1500));
	warpPoint4.setFillColor(sf::Color::Black);

	sf::RectangleShape warpPoint5(sf::Vector2f(180, 400)); // ��е����컨ҡ�ҡ��� 3 � 4
	warpPoint5.setPosition(sf::Vector2f(2950, -3000));
	warpPoint5.setTexture(&doorwarp3);

	sf::RectangleShape warpPoint6(sf::Vector2f(180, 400)); // // ��е����� test 3 go 4
	warpPoint6.setPosition(sf::Vector2f(200, -3200));
	warpPoint6.setTexture(&doorwarp3);

	sf::RectangleShape warpPoint7(sf::Vector2f(200, 400)); // ��е����컨ҡ�ҡ��� 4 � 5
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
		

	//////////////////////////////////////////////////////////////////////////////////////////////////// ˹�� Menu /////////////////////////////////////////////////////////////////////////////////////////////////////////

		///// ���� ˹�� MENU ///////
		sf::RectangleShape button1(sf::Vector2f(300, 150)); //button play
		button1.setPosition(sf::Vector2f(380, 340));
		button1.setTexture(&buttonplay);
		sf::RectangleShape button2(sf::Vector2f(300, 150)); //button how to play
		button2.setPosition(sf::Vector2f(220, 520));
		button2.setTexture(&buttonhowtoplay);
		sf::RectangleShape button3(sf::Vector2f(300, 150)); //button high score
		button3.setPosition(sf::Vector2f(550, 520));
		button3.setTexture(&buttonhighscore);
		sf::RectangleShape button4(sf::Vector2f(100, 50)); //button how to play
		button4.setPosition(sf::Vector2f(980, 650));
		button4.setTexture(&buttonreturnmenu);

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
			window.draw(bgmenu);
			window.draw(button1);
			window.draw(button2);
			window.draw(button3);
		}

	//////////////////////////////////////////////////////////////////////////////////////////////////// ˹�� How to play /////////////////////////////////////////////////////////////////////////////////////////////////////
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

		//////////////////////////////////////////////////////////////////////////////////////////////////// ˹�� High score /////////////////////////////////////////////////////////////////////////////////////////////////////

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


		//////////////////////////////////////////////////////////////////////////////////////////////////// ˹�� Start ��� Game /////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (x == 3)
		{
			printf("x = %.f  y = %.f\n", player.GetPosition().x, player.GetPosition().y);

			player.Update(deltaTime);


			sf::Vector2f direction;

			/////////////////////////////////////////////////////// check bullet /////////////////////////////////////////

			if (player.isShoot()) { // �ԧ���ʹ�
				vbullet.push_back(bullet(&ball, sf::Vector2f(32.0f, 32.0f), 0, 50.0f, player.GetPosition().x, player.GetPosition().y - 35, player.faceRight));
			}

			for (int i = 0; i < vbullet.size(); i++) {
				vbullet[i].Update(deltaTime);

			}

			/*enemy1.Update(deltaTime);
			enemy2.Update(deltaTime);*/
			enemy3.Update(deltaTime);

			int enemy1Hp = 10;
			int enemy2Hp = 10;
			int enemy3Hp = 10;

			for (int i = 0; i < vbullet.size(); i++) //check bullet �� enemy
			{
					if (enemy3.updateBulletCollision(&vbullet[i]))
					{
						enemy3Hp = 0;
						vbullet.erase(vbullet.begin() + i);
						if (enemy3Hp == 0)
						{
							j += 100;
						}
						break;
					}
			}

			if (enemy1Hp == 0 || enemy2Hp == 0)
			{
				score(j);
			}
			
			/*for (size_t i = 0; i < enemys.size(); i++)
			{
				for (size_t j = 0; j < vbullet.size(); j++)
				{
					if (vbullet[j].getGlobalBounds().intersects(enemys[i].getGlobalBounds()))
					{
						enemys.erase(enemys.begin() + i);
						vbullet.erase(vbullet.begin() + j);
						
						j += 100;
					}
					break;
				}
			}*/
			
		
				

			/////////////////////////////////////////////////////////check �� //////////////////////////////////////////////////////////////////////
			int coin = 0;
			for (Platform& platform : platforms) { //check collision platform
				if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) {
					player.OnCollision(direction);
					if (platform.getBlockType() == 1) { // 1 = ��
						printf("\n\coin");
						platforms.erase(platforms.begin() + coin);
					}
				}
				coin += 1;
				//if (platform.GetCollider().CheckCollision(enemy1.GetCollider(), direction, 1.0f)) //check platform collision enemy1
				//	enemy1.OnCollision(direction);
				//if (platform.GetCollider().CheckCollision(enemy2.GetCollider(), direction, 1.0f)) //check platform collision enemy2
				//	enemy2.OnCollision(direction);
				if (platform.GetCollider().CheckCollision(enemy3.GetCollider(), direction, 1.0f)) //check platform collision enemy2
					enemy3.OnCollision(direction);
				
			}

			// check �� enemy //
			/*if (player.getPlayerGlobalbounds().intersects(enemy1.getEnemyGloabalbounds())) 
			{
				printf("HITTTTTTTT \n");
			}*/

			for (Platform& platform : platforms) { //check block ����͹
				if (BlockSlide.GetCollider().CheckCollision(player.GetCollider(), direction, 0.0f)) {
					player.OnCollision(direction);
				}
				if (BlockSlide2.GetCollider().CheckCollision(player.GetCollider(), direction, 0.0f)) {
					player.OnCollision(direction);
				}
			}

			///////////////////////////////////////////////////////// check block �� up and down //////////////////////////////////////////////////////////////////////
			
			// block updown �ҡ��� 2 //
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

			// block updown �ҡ��� 4 //
			if (Bmap4.body.getPosition().y == -4700) // �ѹ��á
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

			if (Bmap5.body.getPosition().y == -4700) //�ѹ��� 2
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

			/////////////////////////////////////////////////////////// �ҡ��� ///////////////////////////////////////////////////////////////////////////
			if (Partition.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //�ҡ��鹷�� 1 ��ͧ˹
				player.OnCollision(direction);
			if (Partition2.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //�ҡ��鹷�� 2 ��ͧ˹
				player.OnCollision(direction);
			if (Partition3.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //�ҡ��鹷�� 3 ��ͧ˹
				player.OnCollision(direction);
			if (Partition4.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //�ҡ��鹷�� 4 ��ͧ˹
				player.OnCollision(direction);
			if (Partition5.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //�ҡ��鹷�� 5 ��ͧ˹
				player.OnCollision(direction);

			//// Player view ////
			if (player.GetPosition().x >= -418 && player.GetPosition().x <= 2800) //��ͤ�ҡ��� 1 ����������͹�Թ ��ҹ���� && ��ҹ��� (��������ҧ��) && player.GetPosition().x <= 824
			{
				view.setCenter(player.GetPosition().x, player.GetPosition().y); //��ͤ�ҡ�������͹��鹺� ,0
			}


			window.clear(sf::Color(100, 100, 100)); //130 100 60 brown
			window.setView(view);
			window.draw(bg);
			window.draw(bgwater);
			window.draw(bg2);
			window.draw(bg3);
			window.draw(bg4);
			window.draw(bg5);

			BlockSlide.Draw(window); // block ����͹
			BlockSlide2.Draw(window); // block slide2 ����͹
			Bmap2.Draw(window); // block ����͹���ŧ
			Bmap4.Draw(window); // block2 ����͹���ŧ
			Bmap4.Draw(window); // block3 ����͹���ŧ
			Bmap5.Draw(window); // block3 ����͹���ŧ
			
			for (Platform& platform : platforms)
			{
				platform.Draw(window);
			}

			for (enemy& enemy : enemys)
			{
				for (Platform& platform : platforms)
				{
					if (platform.GetCollider().CheckCollision(enemy.GetCollider(), direction, 1.0f)) //check platform collision enemy1
						enemy.OnCollision(direction);
				}
				enemy.Draw(window);
				enemy.Update(deltaTime);
			}

			//////////////////////////////////////////////////////////check �� WarpPoint ///////////////////////////////////////////////////////////////////////

			if (player.GetCollider().CheckCollision(Collider(door))) { // ˹�ҵ�ҧ����㹩ҡ��� 1
				player.setPosition(sf::Vector2f(-600, -75));
			}
			if (player.GetCollider().CheckCollision(Collider(door2))) { // ˹�ҵ�ҧ����㹩ҡ��� 3
				player.setPosition(sf::Vector2f(-800, -1600));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint))) { //��е����컩ҡ��� 1 仩ҡ��� 2
				player.setPosition(sf::Vector2f(-800, -1600));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint2))) { //test 1 � 2 �������������ധ
				player.setPosition(sf::Vector2f(-500, -1500));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint3))) { //��е����컩ҡ��� 2 仩ҡ��� 3
				player.setPosition(sf::Vector2f(-700, -2650));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint4))) { //test 2 go 3 black 
				player.setPosition(sf::Vector2f(-300, -3500));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint5))) { //��е����컩ҡ��� 3 仩ҡ��� 4
				player.setPosition(sf::Vector2f(-700, -4200));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint6))) { //��е����컩ҡ��� 3 仩ҡ��� 4
				player.setPosition(sf::Vector2f(-700, -5150));
			}
			if (player.GetCollider().CheckCollision(Collider(warpPoint7))) { //��е����컩ҡ��� 4 仩ҡ��� 5
				player.setPosition(sf::Vector2f(-700, -6100));
			}
			/*if ( player.GetPosition().x >2800 && player.GetPosition().y < 140) { 
				player.setPosition(sf::Vector2f(-260, -1260));
			}*/
			if (player.GetPosition().y > -1380 && player.GetPosition().y < -1000 && player.GetPosition().x > 1195 && player.GetPosition().x < 1625 ) { // cactus 㹩ҡ��� 2
				player.setPosition(sf::Vector2f(-260, -1260));
			}
			
			/////////////////////////////////////  ��� Score /////////////////////////////////////////////////////
			sf::Text scoreText;
			sf::Font font;
			if (!font.loadFromFile("Font/ROGFonts-Regular.otf"))
			{
				std::cout << "ERROR TO LOAD FONT" << "\n";
			}
			scoreText.setFont(font);
			scoreText.setCharacterSize(25);
			scoreText.setFillColor(sf::Color::Red);
			std::stringstream ss;
			scoreText.setPosition(sf::Vector2f(player.GetPosition().x + 120, player.GetPosition().y - 320));
			ss << "SCORE : " << score(j);
			scoreText.setString(ss.str());

			
			window.draw(scoreText);
			window.draw(door); //˹�ҵ�ҧ�һ�ҡ��� 1
			window.draw(warpPoint);
			window.draw(warpPoint2); //test1
			window.draw(warpPoint3);
			window.draw(door2); //˹�ҵ�ҧ�һ�ҡ��� 3
			window.draw(warpPoint4); //test2
			window.draw(warpPoint5);
			window.draw(warpPoint6); //test3
			window.draw(warpPoint7);
			/// 
			
			
			//enemy1.Draw(window);
			//enemy2.Draw(window);
			enemy3.Draw(window);
			enemy4.Draw(window);

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