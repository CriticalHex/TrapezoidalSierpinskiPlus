#include<SFML/Graphics.hpp>
#include<cmath>
#include<vector>

using namespace std;

float pi = 3.14159265358979;

class Trapezoid
{
public:
    Trapezoid(float x, float y, float lineLength, int trapID, sf::Color lineColor = sf::Color(0, 255, 0)) {
        id = trapID;
        scale = lineLength;
        trap = sf::VertexArray(sf::LineStrip, 4);
        color = lineColor;
        trap[0].position = sf::Vector2f(x, y);
        if (trapID == 1) {
            trap[1].position = sf::Vector2f(scale * cos((5 * pi) / 3) + trap[0].position.x,
                scale * sin((5 * pi) / 3) + trap[0].position.y);

            trap[2].position = sf::Vector2f(trap[1].position.x + scale, trap[1].position.y);

            trap[3].position = sf::Vector2f(scale * cos((5 * pi) / 3) + trap[2].position.x,
                scale * sin((pi) / 3) + trap[2].position.y);
        }
        else if (trapID == 2) {
            trap[1].position = sf::Vector2f(scale * cos((pi) / 3) + trap[0].position.x,
                scale * sin((pi) / 3) + trap[0].position.y);

            trap[2].position = sf::Vector2f(scale * cos((2 * pi) / 3) + trap[1].position.x,
                scale * sin((2 * pi) / 3) + trap[1].position.y);

            trap[3].position = sf::Vector2f(scale * cos(pi) + trap[2].position.x,
                scale * sin(pi) + trap[2].position.y);
        }
        else if (trapID == 3) {
            trap[1].position = sf::Vector2f(scale * cos((2 * pi) / 3) + trap[0].position.x,
                scale * sin((2 * pi) / 3) + trap[0].position.y);

            trap[2].position = sf::Vector2f(scale * cos((pi) / 3) + trap[1].position.x,
                scale * sin((pi) / 3) + trap[1].position.y);

            trap[3].position = sf::Vector2f(scale + trap[2].position.x,
                trap[2].position.y);
        }
        for (int i = 0; i < trap.getVertexCount(); i++) {
            trap[i].color = color;
        }
    };
    ~Trapezoid() {};

    void draw(sf::RenderWindow& window) {
        window.draw(trap);
    }

    void expand(vector<Trapezoid*>& traps) {
        sf::Color red(255, 0, 0);
        sf::Color green(0, 255, 0);
        sf::Color blue(0, 0, 255);

        if (id == 1) {
            traps.push_back(new Trapezoid(trap[1].position.x, trap[1].position.y, scale / 2, 2, blue));
            traps.push_back(new Trapezoid(trap[1].position.x, trap[1].position.y, scale / 2, 1, red));
            traps.push_back(new Trapezoid(trap[2].position.x, trap[2].position.y, scale / 2, 3, green));
        }
        if (id == 2) {
            traps.push_back(new Trapezoid(trap[3].position.x, trap[3].position.y, scale / 2, 1, red));
            traps.push_back(new Trapezoid(trap[1].position.x, trap[1].position.y, scale / 2, 2, blue));
            traps.push_back(new Trapezoid(trap[0].position.x, trap[0].position.y, scale / 2, 3, green));
        }
        if (id == 3) {
            traps.push_back(new Trapezoid(trap[0].position.x, trap[0].position.y, scale / 2, 2, blue));
            traps.push_back(new Trapezoid(trap[1].position.x, trap[1].position.y, scale / 2, 3, green));
            traps.push_back(new Trapezoid(trap[2].position.x, trap[2].position.y, scale / 2, 1, red));
        }
    }

private:
    int id;
    float scale;
    sf::Color color;
    sf::VertexArray trap;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arrowhead", sf::Style::Fullscreen);
    sf::Event event;
    sf::Color bgColor = sf::Color(8, 6, 12);
    sf::Color red(255, 0, 0);
    sf::Color green(0, 255, 0);
    sf::Color blue(0, 0, 255);
    window.clear(bgColor);

    vector<Trapezoid*> traps{new Trapezoid(600,800,400,1,red)};
    vector<Trapezoid*> traps2;

    bool open = false;

    while (window.isOpen()) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                open = true;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                traps = vector<Trapezoid*>{ new Trapezoid(600,800,400,1) };
        }

        window.clear(bgColor);

        for (auto& trap : traps) {
            trap->draw(ref(window));
            if (open) {
                trap->expand(traps2);
            }
        }
        if (open) {
            traps = traps2;
            traps2.clear();
            open = false;
        }

        window.display();

    }
}