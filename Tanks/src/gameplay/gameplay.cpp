#include "gameplay.h"

Gameplay::Gameplay() 
{
    windowWidth = 1200;
    windowHeigth = 800;    

    window.create(VideoMode(windowWidth, windowHeigth), title);       
}
Gameplay::~Gameplay() 
{

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