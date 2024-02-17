#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "src/player/player.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG SOUNDBOARD");
    window.setFramerateLimit(60);
    Player players[31];
    sf::Vector2f mouse_click_position;
    bool user_clicked{false};

    for(auto &p : players) {
        p.set_audio_file_path("/home/luizf/Projects/rpg-soundboard-desktop/sounds/thunder.wav");
        p.set_audio_name("Dark Fantasy");
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
           if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                sf::Vector2f world_position = window.mapPixelToCoords(mouse_position);
                mouse_click_position = world_position;
                user_clicked = true;
            }
        }

        window.clear(sf::Color(174, 198, 207, 1));

        int startX = 70; // Starting position
        int startY = 70; // Starting position
        int spacingX = 50; // Horizontal spacing between player shapes
        int spacingY = 30; // Vertical spacing between player shapes
        int x = startX;
        int y = startY;
        int maxWidth = (window.getSize().x * 60 / 100);
        int maxHeight = window.getSize().y - startY;
        bool draw{true};

        for(auto &p : players) {
            p.get_shape().setPosition(x, y);
            if(!draw) {
                break;
            }
            std::unique_ptr<sf::RectangleShape> shape = std::make_unique<sf::RectangleShape>(p.get_shape());
            x += p.get_shape().getSize().x + spacingX;

            if (x + p.get_shape().getSize().x > maxWidth) {
                x = startX;
                y += p.get_shape().getSize().y + spacingY + p.get_loop_shape().getSize().y;
                if (y + p.get_shape().getSize().y + startY + p.get_loop_shape().getSize().y > maxHeight) {
                    draw = false;
                }
            }

            if(user_clicked && p.shape.getGlobalBounds().contains(mouse_click_position)) {
                p.on_click();
                user_clicked = false;
            } else if(user_clicked && p.get_loop_btn_sprite().getGlobalBounds().contains(mouse_click_position)) {
                p.set_loop();
                user_clicked = false;
            }
            if(p.sound.getStatus() == sf::SoundSource::Status::Stopped) {
                p.get_shape().setOutlineThickness(0);
            }
            window.draw(p.get_shape());
            window.draw(p.get_center_text());
            window.draw(p.get_loop_shape());
            window.draw(p.get_loop_text());
            window.draw(p.get_loop_btn_sprite());
            window.draw(p.get_options_shape());
        }

        window.display();
    }
    return 0;
}
