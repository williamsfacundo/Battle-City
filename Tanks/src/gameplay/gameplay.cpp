#include "gameplay.h"

#include "SFML/Window/Event.hpp"

#include "tank.h"

Gameplay::Gameplay() 
{
    windowWidth = 1200;
    windowHeigth = 800;    

    window.create(VideoMode(windowWidth, windowHeigth), title);    

    playerTank = new Tank(1, 1, {50, 50});
}

Gameplay::~Gameplay() 
{
    delete playerTank;
}

void Gameplay::Input() 
{

}

void Gameplay::Update() 
{

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
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        Input();
        Update();
        Draw();
    }
}