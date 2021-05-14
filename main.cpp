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
	RenderWindow* window;
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
    Map(RenderWindow &wn){
		window = &wn;
        wn_size =  Vector2i(wn.getSize().x, wn.getSize().y);
        line_count = (wn_size.x+wn_size.y)/50+1;
        grid = new RectangleShape[line_count];

    }
    void drawMap(){
        for(int row=0; row<15;row++){
            for(int collum=0;collum<29;collum++){
                if(map[row][collum]){
                    map_objects = RectangleShape({50,50});
                    map_objects.setPosition((float)collum*50, (float)row*50);
                    switch (map[row][collum]) {
                        case 1: map_objects.setFillColor(Color(100,100,100)); break;
                        case 2: map_objects.setFillColor(Color::Blue); break;
                        case 3: map_objects.setFillColor(Color::Red); break;
                    }
					window->draw(map_objects);
                }
            }
        }
    }

     void drawGrid(){
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
            window->draw(grid[i]);
        }
    }

};

class Player {
private:
    RectangleShape player;
    Vector2f hit_position;
    Vertex line[2];
    float fov;
    float distance;
    RenderWindow *window;
    Vector2f position;

public:
    Player(RenderWindow &wn) {
        position = Vector2f(100, 100);
        fov = 60;
        window = &wn;
        player = RectangleShape({5, 5});
        player.setPosition(position);
        player.setFillColor(Color::Green);

    }

    void moving(float speed) {
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player.move((float) (speed * cos(player.getRotation() * toRadians)),
                        (float) (speed * sin(player.getRotation() * toRadians)));
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.move((float) (-speed * cos(player.getRotation() * toRadians)),
                        (float) (-speed * sin(player.getRotation() * toRadians)));
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.rotate((float) -0.4);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.rotate((float) 0.4);
        }
    }

    void findObstacle(int map[][29]) {
        window->draw(player);
        for (int i = 0; i < window->getSize().x; i++) {
            float angle = player.getRotation() - fov / 2 + fov * i / window->getSize().x;
            distance = 0;
            for (; distance < 500; distance += 1) {
                hit_position = {(float) (player.getPosition().x + distance * cos(angle * toRadians)),
                                (float) (player.getPosition().y + distance * sin(angle * toRadians))};
                if (map[(int) (hit_position.y / 50)][(int) (hit_position.x / 50)] != 0) break;
            }
            line[0] = Vertex(player.getPosition());
            line[1] = Vertex(hit_position);
            window->draw(line, 2, Lines);
        }
    }
};

int main()
{
    RenderWindow window(VideoMode(1450, 750), "SFML Engine");
    Player pl(window);
    Map map(window);
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
        window.clear();
        map.drawGrid();
        map.drawMap();
        pl.moving(0.5);
        pl.findObstacle(map.map);
        window.display();
    }

}