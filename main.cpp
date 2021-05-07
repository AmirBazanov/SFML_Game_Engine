#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace sf;


class Map{
private:
    int map[15][29] =  {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,2,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
public:
    void drawMap(RenderWindow& wn){
        for(int row=0; row<15;row++){
            for(int collum=0;collum<29;collum++){
                if(map[row][collum]){
                    RectangleShape rec = RectangleShape({50,50});
                    rec.setPosition(collum*50, row*50);
                    switch (map[row][collum]) {
                        case 1: rec.setFillColor(Color::White); break;
                        case 2: rec.setFillColor(Color::Blue); break;
                        case 3: rec.setFillColor(Color::Red); break;
                    }
                    wn.draw(rec);
                }
            }
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
    RenderWindow window(VideoMode(1450, 750), "Vertex");
    Player pl;
    Map map;
    while (window.isOpen())
    {
        Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

        }
        pl.moving(0.2);
        window.clear();
        pl.setPlayer(window);
        Map::drawGrid(window);
        map.drawMap(window);
        window.display();
    }

}