#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
using namespace sf;


class Map{
private:
    std::vector<RectangleShape> objects;
public:
    Map(){
        for(int i=0; i<=50; i++){
            objects.emplace_back(Vector2f(std::rand()%100, std::rand()%100));
        }
    }

    void generatePos(){
        for(RectangleShape& object : objects){
            object.setPosition(std::rand() % 1500 + 1, std::rand() % 1000 + 1);
        }
    }



    void setObjects(RenderWindow &wn){
        for (const RectangleShape& object: objects){
            wn.draw(object);
        }
    }
    static void drawGrid(RenderWindow &wn){
        Vector2i wn_size =  Vector2i(wn.getSize().x, wn.getSize().y);
        int line_count = (wn_size.x+wn_size.y)/50+1;
        auto* grid = new RectangleShape[line_count];
        for(int i =0; i<line_count; i++){
            if(i>wn_size.x/50){
                int y_pos = i-wn_size.x/50;
                grid[i] = RectangleShape(Vector2f((float)wn_size.x, 1));
                grid[i].setPosition(0, (float)y_pos*50);
                grid[i].setFillColor(Color(80, 80, 80));
            }
            else {
                grid[i] = RectangleShape(Vector2f(1, (float)wn_size.y));
                grid[i].setPosition((float)i*50, 0);
                grid[i].setFillColor(Color(80, 80, 80));
            }
        }
        for(int i =0; i<line_count;i++){
            wn.draw(grid[i]);
        }
    }
};

class Player : public Keyboard{
private:
    CircleShape player;

    Vector2f position;

public:
    Player(){
        position = Vector2f(100, 100);
        player = CircleShape(5, 50);
        player.setPosition(position);
        player.setFillColor(Color::Green);

    }
    void moving(float speed){
        if(isKeyPressed(W)){
            player.move(speed* cos((player.getRotation()*3.24)/180), speed* sin((player.getRotation()*3.24)/180));
        }
        if(isKeyPressed(A)){
            player.rotate(-0.4);
        }if(isKeyPressed(D)){
            player.rotate(0.4);
        }
        }
    void setPlayer(RenderWindow &wn){
        wn.draw(player);
    }
    };

int main()
{
    RenderWindow window(VideoMode(1450, 745), "Vertex");
    Map mp;
    Player pl;
    mp.generatePos();
    while (window.isOpen())
    {
        Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if(Keyboard::isKeyPressed(sf::Keyboard::R)){
                mp.generatePos();
            }

        }
        pl.moving(0.2);
        window.clear();
        mp.setObjects(window);
        pl.setPlayer(window);
        mp.drawGrid(window);
        window.display();
    }

}