#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <ctime>
#include <cstdlib>
#include "Hero.h"
#include "Mage.h"
#include "Hunter.h"
#include "Card.h"
#include "Fire.h"
#include "Ice.h"
#include "Aether.h"
#include "Hand.h"
#include "Monster.h"
namespace Textures
{
    enum ID
    {
        Background,
        Fire,
        Ice,
        Aether,
        Monster,
        GameOver,
        Menu,
        Rules,
    };
}

int main()
{
    srand(time(NULL));
    std::fstream file;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Error loading the font" << std::endl;
    }
    bool myTurn = true;
    int myTurns = 1;
    int enemyTurns = 1;
    int myTokens = 1;
    bool gameStarted = false;
    int count = 0;
    Mage mage;
    Hunter hunter;
    mage.HP = 30;
    hunter.HP = 30;
    sf::Text text1, text2, text3;
    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);
    text1.setPosition(sf::Vector2f(760,65));
    text2.setPosition(sf::Vector2f(760,960));
    text3.setPosition(sf::Vector2f(1765,640));
    text1.setCharacterSize(50);
    text2.setCharacterSize(50);
    text3.setCharacterSize(70);
    text1.setStyle(sf::Text::Bold);
    text2.setStyle(sf::Text::Bold);
    text3.setStyle(sf::Text::Bold);

    sf::RectangleShape rect1, rect2, rect3, rect4, rect5, rect6, rect7, rect8, opponent;
    rect1.setFillColor(sf::Color::Black);
    rect1.setSize(sf::Vector2f(180, 192));
    rect1.setPosition(sf::Vector2f(340, 600));
    rect1.setOutlineThickness(10);
    rect1.setOutlineColor(sf::Color::White);

    rect2.setFillColor(sf::Color::Black);
    rect2.setSize(sf::Vector2f(180, 192));
    rect2.setPosition(sf::Vector2f(670, 600));
    rect2.setOutlineThickness(10);
    rect2.setOutlineColor(sf::Color::White);

    rect3.setFillColor(sf::Color::Black);
    rect3.setSize(sf::Vector2f(180, 192));
    rect3.setPosition(sf::Vector2f(1000, 600));
    rect3.setOutlineThickness(10);
    rect3.setOutlineColor(sf::Color::White);

    rect4.setFillColor(sf::Color::Black);
    rect4.setSize(sf::Vector2f(180, 192));
    rect4.setPosition(sf::Vector2f(1330, 600));
    rect4.setOutlineThickness(10);
    rect4.setOutlineColor(sf::Color::White);

    rect5.setFillColor(sf::Color::Black);
    rect5.setSize(sf::Vector2f(180, 192));
    rect5.setPosition(sf::Vector2f(340, 280));
    rect5.setOutlineThickness(10);
    rect5.setOutlineColor(sf::Color::White);

    rect6.setFillColor(sf::Color::Black);
    rect6.setSize(sf::Vector2f(180, 192));
    rect6.setPosition(sf::Vector2f(670, 280));
    rect6.setOutlineThickness(10);
    rect6.setOutlineColor(sf::Color::White);

    rect7.setFillColor(sf::Color::Black);
    rect7.setSize(sf::Vector2f(180, 192));
    rect7.setPosition(sf::Vector2f(1000, 280));
    rect7.setOutlineThickness(10);
    rect7.setOutlineColor(sf::Color::White);

    rect8.setFillColor(sf::Color::Black);
    rect8.setSize(sf::Vector2f(180, 192));
    rect8.setPosition(sf::Vector2f(1330, 280));
    rect8.setOutlineThickness(10);
    rect8.setOutlineColor(sf::Color::White);

    opponent.setPosition(sf::Vector2f(850, 10));
    opponent.setSize(sf::Vector2f(185, 180));

    Hand hand1, hand2, hand3, hand4;
    hand1.shape.setPosition(sf::Vector2f(235, 900));
    hand1.shape.setSize(sf::Vector2f(180, 192));
    hand1.empty = true;

    hand2.shape.setPosition(sf::Vector2f(480, 900));
    hand2.shape.setSize(sf::Vector2f(180, 192));
    hand2.empty = true;

    hand3.shape.setPosition(sf::Vector2f(1230, 900));
    hand3.shape.setSize(sf::Vector2f(180, 192));
    hand3.empty = true;

    hand4.shape.setPosition(sf::Vector2f(1460, 900));
    hand4.shape.setSize(sf::Vector2f(180, 192));
    hand4.empty = true;

    sf::CircleShape circle;
    circle.setPosition(sf::Vector2f(1065,950));
    circle.setRadius(35);
    circle.setFillColor(sf::Color::Blue);

    sf::RectangleShape drawCard;
    drawCard.setPosition(sf::Vector2f(1820, 910));
    drawCard.setSize(sf::Vector2f(100, 100));
    drawCard.setFillColor(sf::Color::White);
    drawCard.setRotation(45);

    ResourceHolder<sf::Texture, Textures::ID>textures;
    try
    {
        textures.load(Textures::Background, "Media/Textures/Board.png");
        textures.load(Textures::Fire, "Media/Textures/Fire.png");
        textures.load(Textures::Ice, "Media/Textures/Ice.png");
        textures.load(Textures::Aether, "Media/Textures/Aether.png");
        textures.load(Textures::Monster, "Media/Textures/Monster3.png");
        textures.load(Textures::GameOver, "Media/Textures/GameOver.png");
        textures.load(Textures::Menu, "Media/Textures/MainMenu.png");
        textures.load(Textures::Rules, "Media/Textures/Rules.png");
    }
    catch (std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }
    sf::Sprite fire(textures.get(Textures::Fire)), ice(textures.get(Textures::Ice)), aether(textures.get(Textures::Aether)), background(textures.get(Textures::Background)), monster(textures.get(Textures::Monster)), menu(textures.get(Textures::Menu)), rulessprite(textures.get(Textures::Rules));
    std::deque<Card*>deq;
    std::deque<Card*>hand(4);

    for (int i = 0; i < 24; i++)
    {
        switch (rand() % 12)
        {
        case 0:
        {
            deq.push_back(new Fire(1, 1, 1, fire));
            break;
        }      
        case 1: 
        {
            deq.push_back(new Fire(2, 2, 2, fire));
            break;
        }
        case 2:
        {
            deq.push_back(new Fire(3, 3, 3, fire));
            break;
        }
        case 3:
        {
            deq.push_back(new Fire(4, 4, 4, fire));
            break;
        }
        case 4:
        {
            deq.push_back(new Ice(1, 1, 1, ice));
            break;
        }
        case 5:
        {
            deq.push_back(new Ice(2, 2, 2, ice));
            break;
        }
        case 6: 
        {
            deq.push_back(new Ice(3, 3, 3, ice));
            break;
        }
        case 7: 
        {
            deq.push_back(new Ice(4, 4, 4, ice));
            break;
        }
        case 8:
        {
            deq.push_back(new Aether(1, 1, 1, aether));
            break;
        }
        case 9:
        {
            deq.push_back(new Aether(2, 2, 2, aether));
            break;
        }
        case 10:
        {
            deq.push_back(new Aether(3, 3, 3, aether));
            break;
        }
        case 11:
        {
            deq.push_back(new Aether(4, 4, 4, aether));
            break;
        }
      }
    }
    for (int i = 0; i < 4; i++)
    {
        hand.at(i) = deq.at(i);
    }
    hand.at(0)->sprite.setPosition(hand1.shape.getPosition());
    hand.at(1)->sprite.setPosition(hand2.shape.getPosition());
    hand.at(2)->sprite.setPosition(hand3.shape.getPosition());
    hand.at(3)->sprite.setPosition(hand4.shape.getPosition());

    sf::RectangleShape button;
    button.setPosition(sf::Vector2f(1727, 482));
    button.setSize(sf::Vector2f(117, 112));
    button.setFillColor(sf::Color::Green);

    sf::RectangleShape start;
    start.setPosition(sf::Vector2f(450, 155));
    start.setSize(sf::Vector2f(980, 140));

    sf::RectangleShape rules;
    rules.setPosition((sf::Vector2f(450,380)));
    rules.setSize(sf::Vector2f(980,140));

    sf::RectangleShape load;
    load.setPosition(sf::Vector2f(445, 580));
    load.setSize(sf::Vector2f(980, 140));

    sf::RectangleShape exit;
    exit.setPosition((sf::Vector2f(450, 785)));
    exit.setSize(sf::Vector2f(980, 140));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game");
    window.setFramerateLimit(200);

    Monster monster1(2, 2, 1, monster);
    Monster monster2(2, 2, 2, monster);
    Monster monster3(2, 2, 3, monster);
    Monster monster4(2, 2, 4, monster);

    monster1.sprite.setPosition(rect5.getPosition());
    monster2.sprite.setPosition(rect6.getPosition());
    monster3.sprite.setPosition(rect7.getPosition());
    monster4.sprite.setPosition(rect8.getPosition());

    auto el = deq.begin() + 5;

    while (window.isOpen())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        sf::Vector2f Middle;
        Middle.x = mousePosF.x - 50;
        Middle.y = mousePosF.y - 50;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (!gameStarted)
            {
                if (event.type == sf::Event::EventType::Closed)
                    window.close();
                if (event.type == sf::Event::EventType::MouseButtonPressed && event.key.code == sf::Mouse::Left)
                    if (start.getGlobalBounds().contains(mousePosF))
                        gameStarted = true;
                    else if (exit.getGlobalBounds().contains(mousePosF))
                        window.close();
                    else if (rules.getGlobalBounds().contains(mousePosF))
                    {
                        sf::RenderWindow ruleswindow(sf::VideoMode(800, 600), "Rules");
                        while (ruleswindow.isOpen())
                        {
                            sf::Event event2;
                            while (ruleswindow.pollEvent(event2))
                            {
                                if (event2.type == sf::Event::EventType::Closed)
                                    ruleswindow.close();

                                ruleswindow.clear();
                                ruleswindow.draw(rulessprite);
                                ruleswindow.display();
                            }
                        }
                    }  
                    else if(load.getGlobalBounds().contains(mousePosF))
                    {
                        file.open("Data.txt");
                        if (file.good())
                        {
                            std::string line;
                            getline(file, line);
                            hunter.HP = stoi(line);
                            getline(file, line);
                            mage.HP = stoi(line);
                            getline(file, line);
                            myTokens = stoi(line);
                            getline(file, line);
                            myTurns = stoi(line);
                            getline(file, line);
                            monster1.ad = stoi(line);
                            getline(file, line);
                            monster1.hp = stoi(line);
                            getline(file, line);
                            monster2.ad = stoi(line);
                            getline(file, line);
                            monster2.hp = stoi(line);
                            getline(file, line);
                            monster3.ad = stoi(line);
                            getline(file, line);
                            monster3.hp = stoi(line);
                            getline(file, line);
                            monster4.ad = stoi(line);
                            getline(file, line);
                            monster4.hp = stoi(line);
                            for (auto element = hand.begin(); element != hand.begin() + 4; element++)
                            {
                                getline(file, line);
                                (*element)->ad = stoi(line);
                                getline(file, line);
                                (*element)->hp = stoi(line);
                                getline(file, line);
                                (*element)->tokens = stoi(line);
                                getline(file, line);
                                if (stoi(line) == 1)
                                    (*element)->sprite = fire;
                                else if (stoi(line) == 2)
                                    (*element)->sprite = ice;
                                else if (stoi(line) == 3)
                                    (*element)->sprite = aether;

                                sf::Vector2f Pos;
                                getline(file, line);
                                Pos.x = stoi(line);
                                getline(file, line);
                                Pos.y = stoi(line);
                                (*element)->sprite.setPosition(Pos);
                                if (rect1.getGlobalBounds().contains(Pos) || rect2.getGlobalBounds().contains(Pos) || rect3.getGlobalBounds().contains(Pos) || rect4.getGlobalBounds().contains(Pos))
                                {
                                    (*element)->movable = false;
                                    (*element)->attackable = true;
                                }
                            }
                        }
                        else
                            std::cout << "Error opening the file" << std::endl;

                        gameStarted = true;
                        file.close();
                    }
                window.clear();
                window.draw(menu);
                window.display();
            }
            else
            {
                switch (event.type)
                {
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
                case sf::Event::EventType::MouseMoved:
                {
                    for (auto element = hand.begin(); element != hand.end(); element++)
                    {
                        if ((*element)->sprite.getGlobalBounds().contains(mousePosF))
                        {
                            (*element)->hovered = true;
                            (*element)->sprite.setScale(sf::Vector2f(1.2f, 1.2f));
                        }
                        else
                        {
                            (*element)->hovered = false;
                            (*element)->sprite.setScale(sf::Vector2f(1, 1));
                        }
                    }
                    if (circle.getGlobalBounds().contains(mousePosF))
                    {
                        circle.setOutlineThickness(5);
                        circle.setOutlineColor(sf::Color::Yellow);
                    }
                    else
                        circle.setOutlineThickness(0);
                    break;
                }
                case sf::Event::EventType::MouseButtonPressed:
                {
                    if (event.key.code == sf::Mouse::Left)
                    {
                        for (auto element = hand.begin(); element != hand.end(); element++)
                        {
                            if ((*element)->hovered)
                                (*element)->clicked = true;
                        }
                        if (button.getGlobalBounds().contains(mousePosF))
                        {
                            if (myTurn)
                            {
                                button.setFillColor(sf::Color::Red);
                                myTurn = false;

                                hunter.HP -= (monster1.ad + monster2.ad + monster3.ad + monster4.ad);
                                mage.HeroAbility(hunter);
                            }
                            else
                            {
                                if (monster1.ad == monster1.hp)
                                    monster1.ad += 1;
                                else
                                    monster1.hp += 1;
                                if (monster2.ad == monster2.hp)
                                    monster2.ad += 1;
                                else
                                    monster2.hp += 1;
                                if (monster3.ad == monster3.hp)
                                    monster3.ad += 1;
                                else
                                    monster3.hp += 1;
                                if (monster4.ad == monster4.hp)
                                    monster4.ad += 1;
                                else
                                    monster4.hp += 1;

                                button.setFillColor(sf::Color::Green);
                                myTurn = true;
                                if (myTurns < 10)
                                    myTurns++;

                                myTokens = myTurns;
                                for (auto element = hand.begin(); element != hand.end(); element++)
                                {
                                    (*element)->attackable = true;
                                    (*element)->clicked = false;
                                }
                            }
                        }
                        else if (circle.getGlobalBounds().contains(mousePosF) && myTokens >= 2 && myTurn)
                        {
                            hunter.HeroAbility(mage);
                            myTokens -= 2;
                        }
                        else if(drawCard.getGlobalBounds().contains(mousePosF) && myTurn)
                        {
                            hand.push_back(*el);
                            (*el)->sprite.setPosition(hand1.shape.getPosition());
                            el++;
                        }
                    }
                    else if (event.key.code == sf::Mouse::Right)
                    {
                        for (auto element = hand.begin(); element != hand.end(); element++)
                        {
                            if ((*element)->hovered && !((*element)->movable) && (*element)->attackable)
                            {
                                mage.HP -= (*element)->ad;
                                (*element)->attackable = false;
                            }
                        }
                    }
                    break;
                }
                case sf::Event::EventType::MouseButtonReleased:
                {
                    if (event.key.code == sf::Mouse::Left)
                    {
                        for (auto element = hand.begin(); element != hand.end(); element++)
                        {
                            if ((*element)->clicked && (*element)->movable && (*element)->tokens <= myTokens)
                            {
                                (*element)->clicked = false;

                                if (rect1.getGlobalBounds().contains((*element)->sprite.getPosition()))
                                {
                                    (*element)->movable = false;
                                    (*element)->sprite.setPosition(sf::Vector2f(340, 600));
                                    myTokens -= (*element)->tokens;
                                }
                                else if (rect2.getGlobalBounds().contains((*element)->sprite.getPosition()))
                                {
                                    (*element)->movable = false;
                                    (*element)->sprite.setPosition(sf::Vector2f(670, 600));
                                    myTokens -= (*element)->tokens;
                                }
                                else if (rect3.getGlobalBounds().contains((*element)->sprite.getPosition()))
                                {
                                    (*element)->movable = false;
                                    (*element)->sprite.setPosition(sf::Vector2f(1000, 600));
                                    myTokens -= (*element)->tokens;
                                }
                                else if (rect4.getGlobalBounds().contains((*element)->sprite.getPosition()))
                                {
                                    (*element)->movable = false;
                                    (*element)->sprite.setPosition(sf::Vector2f(1330, 600));
                                    myTokens -= (*element)->tokens;
                                }
                            }
                        }
                    }
                    break;
                }
                case sf::Event::EventType::KeyPressed:
                {
                    for (auto element = hand.begin(); element != hand.end(); element++)
                    {
                        if (!((*element)->movable) && (*element)->hovered && (*element)->attackable)
                        {
                            if (event.key.code == sf::Keyboard::Num1)
                            {
                                monster1.hp -= (*element)->ad;
                                (*element)->hp -= monster1.ad;
                                (*element)->attackable = false;
                            }

                            else if (event.key.code == sf::Keyboard::Num2)
                            {
                                monster2.hp -= (*element)->ad;
                                (*element)->hp -= monster2.ad;
                                (*element)->attackable = false;
                            }
                            else if (event.key.code == sf::Keyboard::Num3)
                            {
                                monster3.hp -= (*element)->ad;
                                (*element)->hp -= monster3.ad;
                                (*element)->attackable = false;
                            }
                            else if (event.key.code == sf::Keyboard::Num4)
                            {
                                monster4.hp -= (*element)->ad;
                                (*element)->hp -= monster4.ad;
                                (*element)->attackable = false;
                            }
                        }
                    }
                    if (event.key.code == sf::Keyboard::Escape)
                            {
                            file.open("Data.txt");
                            if (file.good())
                            {
                                file << hunter.HP << std::endl;
                                file << mage.HP << std::endl;
                                file << myTokens << std::endl;
                                file << myTurns << std::endl;
                                file << monster1.ad << std::endl;
                                file << monster1.hp << std::endl;
                                file << monster2.ad << std::endl;
                                file << monster2.hp << std::endl;
                                file << monster3.ad << std::endl;
                                file << monster3.hp << std::endl;
                                file << monster4.ad << std::endl;
                                file << monster4.hp << std::endl;
                                for (auto element = hand.begin(); element != hand.begin() + 4; element++)
                                {
                                    file << (*element)->ad << std::endl;
                                    file << (*element)->hp << std::endl;
                                    file << (*element)->tokens << std::endl;
                                    file << (*element)->id << std::endl;
                                    file << (*element)->sprite.getPosition().x << std::endl;
                                    file << (*element)->sprite.getPosition().y << std::endl;
                                }

                            }
                            else
                                std::cout << "Error opening the file" << std::endl;

                            file.close();
                            }
                }
                }
                for (auto element = hand.begin(); element != hand.end(); element++)
                {
                    if ((*element)->clicked && (*element)->movable && (*element)->tokens <= myTokens)
                    {
                        (*element)->sprite.setPosition(Middle);
                    }
                }
                std::string str1 = std::to_string(mage.HP);
                std::string str2 = std::to_string(hunter.HP);
                std::string str3 = std::to_string(myTokens);
                text1.setString(str1);
                text2.setString(str2);
                text3.setString(str3);
                text3.setFillColor(sf::Color::Yellow);
                window.clear();
                window.draw(background);
                window.draw(rect1);
                window.draw(rect2);
                window.draw(rect3);
                window.draw(rect4);
                window.draw(rect5);
                window.draw(rect6);
                window.draw(rect7);
                window.draw(rect8);
                window.draw(button);
                window.draw(circle);
                window.draw(drawCard);
                window.draw(text1);
                window.draw(text2);
                window.draw(text3);
                if (monster1.hp > 0)
                {
                    window.draw(monster1.sprite);
                    monster1.Display(window);
                }
                else
                    monster1.ad = 0;
                if (monster2.hp > 0)
                {
                    window.draw(monster2.sprite);
                    monster2.Display(window);
                }
                else
                    monster2.ad = 0;
                if (monster3.hp > 0)
                {
                    window.draw(monster3.sprite);
                    monster3.Display(window);
                }
                else
                    monster3.ad = 0;
                if (monster4.hp > 0)
                {
                    window.draw(monster4.sprite);
                    monster4.Display(window);
                }
                else
                    monster4.ad = 0;

                for (auto element = hand.begin(); element != hand.end(); element++)
                {
                    if ((*element)->hp > 0)
                    {
                        window.draw((*element)->sprite);
                        (*element)->DisplayStats(window);
                    }
                    else
                    {
                        (*element)->ad = 0;
                    }
                }
                window.display();
            if (mage.HP <= 0 || hunter.HP <= 0)
            {
                sf::RenderWindow gameover(sf::VideoMode(800, 600), "Game Over");
                gameover.setFramerateLimit(60);
                sf::Sprite go(textures.get(Textures::GameOver));
                while (gameover.isOpen())
                {
                    sf::Event event1;
                    while (gameover.pollEvent(event1))
                    {
                        if (event1.type == sf::Event::EventType::Closed)
                        {
                            gameover.close();
                            window.close();
                        }

                        gameover.clear();
                        gameover.draw(go);
                        gameover.display();
                    }
                }
            }
          }
        }
    }
    for (auto el : deq)
    {
        delete(el);
    }
    deq.clear();   
    hand.clear();

    return 0;
}