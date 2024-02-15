#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "player/player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG SOUNDBOARD");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    Player players[8];

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
           if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(174, 198, 207, 1));
        int i = 100;
        for(auto &p : players) {
            std::string audio_name = "Dark Fantasy";
            std::string audio_path = "/home/luizf/Projects/rpg-soundboard-desktop/sounds/darkfantasy.wav";


            p.set_audio_name(audio_name);
            p.set_audio_file_path(audio_path);

            std::unique_ptr<sf::RectangleShape> shape = std::make_unique<sf::RectangleShape>(p.get_shape());
            p.set_shape_position(i, 100);

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                sf::CircleShape dot(4.0f);
                dot.setFillColor(sf::Color::Red);
                dot.setPosition(sf::Vector2f(mouse_position));
                window.draw(dot);

                if( p.shape.getGlobalBounds().contains(sf::Vector2f(mouse_position))) {
                    p.on_click();
                }
            }

            window.draw(p.get_shape());
            window.draw(p.get_center_text());
            window.draw(p.get_loop_shape());

            i = i + 300;
        }

        /*Player player("asd", "asddas");
        std::unique_ptr<sf::RectangleShape> shape = std::make_unique<sf::RectangleShape>(player.get_shape());
        player.set_shape_position(100, 100);
        window.draw(player.get_shape());
        window.draw(player.get_center_text());*/

        window.display();
    }
    return 0;
}
