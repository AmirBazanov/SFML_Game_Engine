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
        line_count = (wn_size.x+wn_size.y)/25+1;
        grid = new RectangleShape[line_count];

    }
    void drawMap(){
        for(int row=0; row<15;row++){
            for(int collum=0;collum<29;collum++){
                if(map[row][collum]){
                    map_objects = RectangleShape({25,25});
                    map_objects.setPosition((float)collum*25, (float)row*25);
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
            if(i>wn_size.x/25){
                int y_pos = i-wn_size.x/25;
                grid[i] = RectangleShape(Vector2f((float)wn_size.x, 1));
                grid[i].setPosition(0, (float)y_pos*25);
                grid[i].setFillColor(Color(80, 80, 80));
            }
            else {
                grid[i] = RectangleShape(Vector2f(1, (float)wn_size.y));
                grid[i].setPosition((float)i*25, 0);
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
    Vertex wall[2];
    float horizon;
    float max_wall_height;
    float fov;
    float distance;
    RenderWindow *mp_wn;
    RenderWindow *gm_wn;
    Vector2f position;

public:
    Player(RenderWindow &wn_m, RenderWindow &wn_g) {
        position = Vector2f(100, 100);
        fov = 60;
		distance = 0;
        mp_wn = &wn_m;
        gm_wn = &wn_g;
        horizon = mp_wn->getSize().y/2;
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
        mp_wn->draw(player);
        for (int i = 0; i < mp_wn->getSize().x; i++) {
            Color color;
            float angle = player.getRotation() - fov / 2 + fov * i / (mp_wn->getSize().x);
            distance = 0;
            for (; distance < 100; distance += 1) {
                hit_position = {(float) (player.getPosition().x + distance * cos(angle * toRadians)),
                                (float) (player.getPosition().y + distance * sin(angle * toRadians))};
                if (map[(int) (hit_position.y / 25)][(int) (hit_position.x / 25)] != 0){
                    switch (map[(int) (hit_position.y / 25)][(int) (hit_position.x / 25)]) {
                        case 1: color = Color(100,100,100); break;
                        case 2: color = Color::Blue; break;
                        case 3: color = Color::Red; break;
                    }
                    wall[0] = Vertex({(float)i,horizon}, color);
                    wall[1] = Vertex({(float)i, horizon/sqrt(distance)}, color);
                    gm_wn->draw(wall, 2, Lines);
                    break;
                }
            }
            line[0] = Vertex(player.getPosition());
            line[1] = Vertex(hit_position);
            mp_wn->draw(line, 2, Lines);


        }
    }
};


int main()
{
    RenderWindow map_window(VideoMode(725, 375), "Map");
    RenderWindow game_window(VideoMode(725, 375), "3D");
    Player pl(map_window, game_window);
    Map map(map_window);
    Event event{};
    while (map_window.isOpen())
    {
        while (map_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                map_window.close();
            }

        }
        map_window.clear();
        game_window.clear();
        map.drawGrid();
        map.drawMap();
        pl.moving(0.5);
        pl.findObstacle(map.map);
        map_window.display();
        game_window.display();
    }

}