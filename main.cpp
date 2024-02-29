#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "src/player/player.h"
#include "src/textbox/textbox.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG SOUNDBOARD");
    window.setFramerateLimit(60);
    Player players[31];
    sf::Vector2f mouse_click_position;
    sf::Font poppins;
    poppins.loadFromFile("/home/luizf/Projects/rpg-soundboard-desktop/assets/fonts/Poppins-Regular.ttf");
    Textbox edit_player_textbox(20, sf::Color::White, true);
    edit_player_textbox.setLimit(true, 15);
    edit_player_textbox.setFont(poppins);
    edit_player_textbox.setPosition({100, 100});
    bool user_clicked{false};
    bool open_textbox{false};
    bool submit_name{false};
    int current_player_id{};

    int i = 1;
    for(auto &p : players) {
        p.set_id(i);
        i++;
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
           if (event.type == sf::Event::TextEntered) {
               edit_player_textbox.typedOn(event);
           }
           if (event.type == sf::Event::KeyPressed) {
               if(event.key.code == sf::Keyboard::Escape) {
                   current_player_id = 0;
                   open_textbox = false;
               }
               if(event.key.code == sf::Keyboard::Enter) {
                   submit_name = true;
                   open_textbox = false;
               }
           }
        }

        window.clear(sf::Color(60, 65, 66));

        int startX = 70;
        int startY = 70;
        int spacingX = 50;
        int spacingY = 30;
        int x = startX;
        int y = startY;
        int maxWidth = (window.getSize().x * 60 / 100);
        int maxHeight = window.getSize().y - startY;
        bool draw{true};
        sf::Vector2f player_pos;

        for(auto &p : players) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));                                              
            p.slider.update(mousePos);  
            p.get_shape().setPosition(x, y);
            p.slider.setPosition(p.get_shape().getPosition().x + 13, p.get_shape().getPosition().y + 150);
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


            if(user_clicked) {
                if(p.shape.getGlobalBounds().contains(mouse_click_position)) {
                    p.on_click();
                    user_clicked = false;
                } else if(p.get_loop_btn_sprite().getGlobalBounds().contains(mouse_click_position)) {
                    p.set_loop();
                    user_clicked = false;
                } else if(p.get_open_file_btn_sprite().getGlobalBounds().contains(mouse_click_position)) {
                    p.open_file();
                    user_clicked = false;
                } else if(p.get_edit_btn_sprite().getGlobalBounds().contains(mouse_click_position)) {
                    current_player_id = p.get_id();
                    int shape_x = p.get_shape().getPosition().x;
                    int shape_y = p.get_shape().getPosition().y; 
                    float shape_width = p.get_shape().getSize().x;
                    float shape_height = p.get_shape().getSize().y;
                    float center_y = shape_y + shape_height / 2 + 50;
                    float margin = 50;
                    float textbox_x = shape_x + margin;

                    edit_player_textbox.setPosition({textbox_x, center_y});
                    open_textbox = true;
                    user_clicked = false;
                }
            }

            if(submit_name && p.get_id() == current_player_id) {
                p.set_audio_name(edit_player_textbox.getText());
                submit_name = false;
                current_player_id = 0;
            }

            if(p.sound.getStatus() == sf::SoundSource::Status::Stopped) {
                p.get_shape().setOutlineThickness(0);
            }

            p.draw(window);

            if(open_textbox) {
                edit_player_textbox.drawTo(window);
            } 
        }

        window.display();
    }
    return 0;
}
