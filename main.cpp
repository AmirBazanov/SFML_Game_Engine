#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <cmath>
#define toRadians 3.14/180
using namespace sf;


class Map{
private:
    Vector2i wn_size;
    RectangleShape map_objects;
    int line_count;
    RectangleShape* grid;
public:
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
                        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,2,3,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    void drawMap(RenderWindow& wn){
        for(int row=0; row<15;row++){
            for(int collum=0;collum<29;collum++){
                if(map[row][collum]){
                    map_objects = RectangleShape({50,50});
                    map_objects.setPosition(collum*50, row*50);
                    switch (map[row][collum]) {
                        case 1: map_objects.setFillColor(Color(100,100,100)); break;
                        case 2: map_objects.setFillColor(Color::Blue); break;
                        case 3: map_objects.setFillColor(Color::Red); break;
                    }
                    wn.draw(map_objects);
                }
            }
        }
    }

     void drawGrid(RenderWindow &wn){
        wn_size =  Vector2i(wn.getSize().x, wn.getSize().y);
        line_count = (wn_size.x+wn_size.y)/50+1;
        grid = new RectangleShape[line_count];
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
    Vector2f hit_position;
    Vertex line[2];
    float distance;
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
            player.move(speed* cos(player.getRotation()*toRadians), speed* sin(player.getRotation()*toRadians));
        }
        if(isKeyPressed(S)){
            player.move(-speed* cos(player.getRotation()*toRadians), -speed* sin(player.getRotation()*toRadians));
        }
        if(isKeyPressed(A)){
            player.rotate(-0.4);
        }if(isKeyPressed(D)){
            player.rotate(0.4);
        }
        }
    void setPlayer(RenderWindow &wn){
//        wn.draw(player);      The Circle rotates from left conner, it looks awfully. Now i think to bout remove them
    }

    void findObstacle(RenderWindow &wn, int map[][29]){
        distance = 0;
        for(;distance<9000;distance+=1){
            hit_position = {static_cast<float>((float)player.getPosition().x + distance*cos(player.getRotation()*toRadians)),
                            static_cast<float>((float)player.getPosition().y + distance*sin(player.getRotation()*toRadians))};
            if(map[(int)hit_position.y/50][(int)hit_position.x/50]!=0) break;
        }
        line[0] = Vertex(player.getPosition());
        line[1] = Vertex(hit_position);
        wn.draw(line, 2, Lines);
    }

    };

int main()
{
    RenderWindow window(VideoMode(1450, 750), "SFML Engine");
    Player pl;
    Map map;
    Event event{};
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

        }
        pl.moving(0.5);
        window.clear();
        map.drawGrid(window);
        map.drawMap(window);
        pl.findObstacle(window, map.map);
        pl.setPlayer(window);
        window.display();
    }

}