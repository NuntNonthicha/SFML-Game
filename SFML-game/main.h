#pragma once

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	sf::Texture playerTexture;
	playerTexture.loadFromFile("robot.png");

	////////////////////////////////////////////////// Background////////////////////////////////////////////////////////////
	//sf::Texture BackgroundTexture[2];
	//sf::Sprite background[2];
	//BackgroundTexture[0].loadFromFile("bg1.png");
	//background[0].setTexture(BackgroundTexture[0]);
	//BackgroundTexture[1].loadFromFile("bg1.png");
	//background[1].setTexture(BackgroundTexture[1]);
	//background[0].setPosition(0,0);

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


	/// bg1 floor+block
	sf::Texture floor;
	floor.loadFromFile("floor01.png");
	sf::Texture floor2;
	floor2.loadFromFile("floor02.png");
	sf::Texture block;
	block.loadFromFile("block.png");
	sf::Texture block02;
	block02.loadFromFile("block02.png");
	sf::Texture blockcoin;
	blockcoin.loadFromFile("blockcoin.png");
	sf::Texture brick; //�԰��鹺ѹ�
	brick.loadFromFile("brick.png");
	sf::Texture channel; //�������
	channel.loadFromFile("channel.png");
	sf::Texture windowwarp; //˹�ҵ�ҧ����
	windowwarp.loadFromFile("window.png");
	sf::Texture heart; //����
	heart.loadFromFile("heart.png");
	sf::Texture doorwarp; //��е�����
	doorwarp.loadFromFile("door.png");
	sf::Texture cactus; //��кͧྪ�
	cactus.loadFromFile("cactus.png");
	sf::Texture fire; //����ع
	fire.loadFromFile("bullet.png");





	Player player(&playerTexture, sf::Vector2u(8, 3), 0.1f, 100, 100, showHitBox);

	//////////////////////////////////////////////////////////////////////// Platform ////////////////////////////////////////////////////////////////////////

	std::vector<Platform> platforms;
	std::vector<bullet> vbullet;

	/////////////////////////////////////////////////// Platform 1  ////////////////////////////////////////////////////////

	Platform Partition(&block, sf::Vector2f(40.0f, 2143.0f), sf::Vector2f(-760.0f, 0.0f), 0, showHitBox); //�ҡ��鹢ͧ�ҡ��� 1 

	platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-180.0f, 30.0f), 0, showHitBox)); //block1
	float tmp = 0;
	for (float i = 0; i<5; i++) //loop block 
	{

		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(150.0f + tmp, 30.0f), 0, showHitBox)); //block2��� ��
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(850.0f + tmp, 180.0f), 0, showHitBox)); //��鹺ѹ䴢�鹷�� 1 : 5 �԰ 
		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2100.0f + tmp, 100.0f), 0, showHitBox)); //block5 ��ҧ blockcoin
		tmp += 40;
	}
	for (float i = 0; i < 4; i++) //loop block 
	{
		platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(90.0f + tmp, -150.0f), 0, showHitBox)); //block3��� ��
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(690.0f + tmp, 140.0f), 0, showHitBox)); //��鹺ѹ䴢�鹷�� 2 : 4 �԰ 
		tmp += 40;
	}
	for (float i = 0; i < 3; i++) //loop block 
	{
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(570.0f + tmp, 100.0f), 0, showHitBox)); //��鹺ѹ䴢�鹷�� 3 : 3 �԰ 
		tmp += 40;
	}
	for (float i = 0; i < 2; i++) //loop block 
	{
		platforms.push_back(Platform(&brick, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(490.0f + tmp, 60.0f), 0, showHitBox)); //��鹺ѹ䴢�鹷�� 4 : 2 �԰ s
		tmp += 40;
	}
	for (float i = 0; i <= 0; i++)
	{
		for (float j = 0; j <= 3; j++)
			platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2000.0f + 150 * j, -80.0f + 150 * i), 0, showHitBox)); // block4 �ç������
	}

	platforms.push_back(Platform(&channel, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(1400.0f, -80.0f), 0, showHitBox)); //block �������
	platforms.push_back(Platform(&channel, sf::Vector2f(100.0f, 700.0f), sf::Vector2f(1400.0f, 300.0f), 0, showHitBox)); ////block �������


	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(130.0f, 30.0f), 1, showHitBox)); //blockcoin1 in block2��� ��
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(250.0f, -150.0f), 1, showHitBox)); //blockcoin2 in block3��� ��
	platforms.push_back(Platform(&blockcoin, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1800.0f, 20.0f), 1, showHitBox)); //blockcoin2 in block4��� ��
	platforms.push_back(Platform(&heart, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(2250.0f, -280.0f), 1, showHitBox)); //heart


																													  //// Platform background /////
	platforms.push_back(Platform(&floor, sf::Vector2f(4000.0f, 400.0f), sf::Vector2f(500.0f, 400.0f), 0, showHitBox)); //��鹩ҡ��� 1
	platforms.push_back(Platform(&floor, sf::Vector2f(4000.0f, 400.0f), sf::Vector2f(4700.0f, 400.0f), 0, showHitBox)); //��鹩ҡ��� 1 ��ѧ���
	platforms.push_back(Platform(&floor2, sf::Vector2f(8000.0f, 400.0f), sf::Vector2f(-500.0f, -1000.0f), 0, showHitBox)); //��鹩ҡ��� 2


																														   /////////////////////////////////////////////////// Platform 2  ///////////////////////////////////////////////////////////////////////////////

	Platform Partition2(&block, sf::Vector2f(40.0f, 200.0f), sf::Vector2f(-760.0f, -1350.0f), 0, showHitBox); //�ҡ��鹢ͧ�ҡ��� 2 

	for (float i = 0; i < 5; i++) //loop block 
	{

		platforms.push_back(Platform(&block02, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-30.0f + tmp, -1350.0f), 0, showHitBox)); //block1 
		platforms.push_back(Platform(&block02, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(50.0f + tmp, -1450.0f), 0, showHitBox)); //block2
		platforms.push_back(Platform(&block02, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(150.0f + tmp, -1550.0f), 0, showHitBox)); //block3
		tmp += 40;
	}
	for (float i = 0; i <= 0; i++)
	{
		for (float j = 0; j <= 4; j++)
			platforms.push_back(Platform(&block, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(1200.0f + 120 * j, -1450.0f + 120 * i), 0, showHitBox)); // block4 �ç������
	}

	platforms.push_back(Platform(&cactus, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(1430.0f, -1240.0f), 0, showHitBox)); //cactus
	platforms.push_back(Platform(&heart, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(900.0f, -1690.0f), 1, showHitBox)); //heart





																													  //////////////////////////////////////////////////////////////////// WarpPoint ���ҧ��е��һ ////////////////////////////////////////////////////////////

	sf::RectangleShape door(sf::Vector2f(100, 150)); // ˹�ҵ�ҧ㹩ҡ��� 1
	door.setPosition(sf::Vector2f(650, -290));
	door.setTexture(&windowwarp);

	sf::RectangleShape warpPoint(sf::Vector2f(200, 300)); // ��е����컨ҡ�ҡ��� 1 � 2
	warpPoint.setPosition(sf::Vector2f(2900, -100));
	warpPoint.setTexture(&doorwarp);

	sf::RectangleShape warpPoint2(sf::Vector2f(60, 50)); // ��е����� test
	warpPoint2.setPosition(sf::Vector2f(-600, 100));
	warpPoint2.setFillColor(sf::Color::Red);

	sf::RectangleShape warpPoint3(sf::Vector2f(200, 300)); // ��е����컨ҡ�ҡ��� 2 � 3
	warpPoint3.setPosition(sf::Vector2f(2900, -1500));
	warpPoint3.setTexture(&doorwarp);
	warpPoint2.setFillColor(sf::Color::Red);



	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
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
		//printf("x = %.f  y = %.f\n", player.GetPosition().x, player.GetPosition().y);

		player.Update(deltaTime);

		/////////////////////////////////////////////////////////check �� blockcoin//////////////////////////////////////////////////////////////////////
		sf::Vector2f direction;
		int coin = 0;

		if (player.isShoot()) {
			vbullet.push_back(bullet(&fire, sf::Vector2f(30.0f, 30.0f), 50.0f, player.GetPosition().x, player.GetPosition().y - 35));
		}

		for (bullet& b : vbullet)
		{
			b.Update(deltaTime);
		}

		for (Platform& platform : platforms) { //check collision platform
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) {
				player.OnCollision(direction);
				if (platform.getBlockType() == 1) { // 1 = ��
					printf("\n\coin");
					if (platform.GetCollider().CheckCollisionEiei(player.GetCollider()))
						platforms.erase(platforms.begin() + coin);
				}
			}
			coin += 1;
		}

		/////////////////////////////////////////////////////////// �ҡ��� ///////////////////////////////////////////////////////////////////////////
		if (Partition.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //�ҡ��鹷�� 1 ��ͧ˹
			player.OnCollision(direction);
		if (Partition2.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) //�ҡ��鹷�� 2 ��ͧ˹
			player.OnCollision(direction);


		if (player.GetPosition().x >= -418 && player.GetPosition().x <= 2800) //��ͤ�ҡ��� 1 ����������͹�Թ ��ҹ���� && ��ҹ��� (��������ҧ��) && player.GetPosition().x <= 824
		{
			view.setCenter(player.GetPosition().x, player.GetPosition().y); //��ͤ�ҡ�������͹��鹺� ,0
		}
		/// 
		/*sf::Vector2f winSize = view.getSize();
		if (player.GetPosition().x <= winSize.x / 2 && player.GetPosition().y <= winSize.y / 2) {
		view.setCenter(winSize.x / 2, winSize.y / 2);
		}*/
		/// 
		/// 
		window.setView(view);
		window.draw(bg);
		window.draw(bgwater);
		window.draw(bg2);

		for (Platform& platform : platforms)
		{
			platform.Draw(window);
		}

		//////////////////////////////////////////////////////////check �� WarpPoint ///////////////////////////////////////////////////////////////////////

		if (player.GetCollider().CheckCollision(Collider(door))) { //��е�㹩ҡ��� 1
			player.setPosition(sf::Vector2f(-600, -75));
		}
		if (player.GetCollider().CheckCollision(Collider(warpPoint))) { //��е����컩ҡ��� 1 仩ҡ��� 2
			player.setPosition(sf::Vector2f(-800, -1600));
		}
		if (player.GetCollider().CheckCollision(Collider(warpPoint2))) { //test
			player.setPosition(sf::Vector2f(-500, -1500));
		}

		window.draw(door);
		window.draw(warpPoint);
		window.draw(warpPoint2); //test
								 /// 
		player.Draw(window);

		for (bullet b : vbullet)
		{
			b.Draw(window);
		}

		window.display();
		window.clear(sf::Color(100, 100, 100)); //130 100 60 brown
	}
	return 0;
}
