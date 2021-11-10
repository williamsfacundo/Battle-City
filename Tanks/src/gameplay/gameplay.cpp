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

}
void Gameplay::Run() 
{    
    CircleShape shape(100.f);    
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}