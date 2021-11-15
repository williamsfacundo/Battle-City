#include "gameplay.h"

#include <SFML/Window/Event.hpp>

#include "player.h"
 
namespace Battle_City 
{
    Gameplay::Gameplay()
    {
        windowWidth = 1200;
        windowHeigth = 800;

        window.create(VideoMode(windowWidth, windowHeigth), title);

        playerTank = new Player(window.getSize().x / 2.0f, window.getSize().y / 2.0f, { 50.0f, 50.0f }, tankColor);
    }

    Gameplay::~Gameplay()
    {
        delete playerTank;
    }

    void Gameplay::Input()
    {
        ((Player*)playerTank)->Input();
    }

    void Gameplay::Update(Time dt)
    {
        ((Player*)playerTank)->Update(dt, windowWidth, windowHeigth);
    }

    void Gameplay::Draw()
    {
        window.clear(Color::Black);

        playerTank->Draw(window);

        window.display();
    }

    void Gameplay::Run()
    {
        while (window.isOpen())
        {
            dt = clock.restart();

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            Input();
            Update(dt);
            Draw();
        }
    }
}