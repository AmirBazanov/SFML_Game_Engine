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
    void drawGrid(RenderWindow &wn){
        Vector2i wn_size =  Vector2i(wn.getSize().x, wn.getSize().y);
        int line_count = (wn_size.x+wn_size.y)/50+1;
        auto* grid = new RectangleShape[line_count];
        for(int i =0; i<line_count; i++){
            if(i>wn_size.x/50){
                int y_pos = i-wn_size.x/50;
                grid[i] = RectangleShape(Vector2f(wn_size.x, 1));
                grid[i].setPosition(0, y_pos*50);
                grid[i].setFillColor(Color(80, 80, 80));
            }
            else {
                grid[i] = RectangleShape(Vector2f(1, wn_size.y));
                grid[i].setPosition(i*50, 0);
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
    RectangleShape dir;
    float angelView;
    Vector2f position;

public:
    explicit Player(float anl){
        position = Vector2f(100, 100);
        dir = RectangleShape({10, 2});
        dir.setPosition(position);
        dir.setFillColor(Color(200,0,0));
        angelView = anl;
    }
    void moving(float speed){
        if(isKeyPressed(W)){
            dir.move(speed* cos((dir.getRotation()*3.24)/180), speed* sin((dir.getRotation()*3.24)/180));
        }
        if(isKeyPressed(A)){
            dir.rotate(-0.4);
        }if(isKeyPressed(D)){
            dir.rotate(0.4);
        }
        }
    void setPlayer(RenderWindow &wn){
        wn.draw(dir);
    }
    };

int main()
{
    RenderWindow window(VideoMode(1360, 720), "Vertex");
    Map mp;
    Player pl(10);
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