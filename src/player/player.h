#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "slider.h"

class Player {
    private:
        std::string audio_name; 
        std::string audio_file_path;
        sf::Text center_text;
        sf::Text loop_text;
        std::string loading_msg;
        bool loop;
        sf::RectangleShape loop_shape;
        sf::RectangleShape options_shape;
        sf::SoundBuffer buffer;
        std::unique_ptr<sf::Texture> loop_toggle_btn;
        std::unique_ptr<sf::Texture> open_file_btn;
        std::unique_ptr<sf::Texture> edit_btn;
        int id;
    public:
        Slider slider;
        int get_id();
        void set_id(int id);
        void draw(sf::RenderWindow& window);
        bool is_loading;
        sf::Sound sound;
        bool sound_loaded;
        void on_click();
        void play();
        void pause();
        bool is_playing;
        bool first_time_playing;
        void open_file();
        void set_is_playing();
        void set_loop_shape_design();
        void set_shapes_design();
        void set_shape_design();
        void set_options_shape_design();
        void load_loop_textures();
        void load_textures();
        sf::Sprite get_loop_btn_sprite();
        sf::Sprite get_open_file_btn_sprite();
        sf::Sprite get_edit_btn_sprite();
        sf::RectangleShape shape;
        sf::RectangleShape& get_options_shape();
        sf::Font font;
        bool load_audio_from_file();
        Player(std::string audio_name, std::string audio_file_path);
        Player();
        std::string get_audio_name() const;
        std::string get_audio_file_path() const;
        sf::Text get_center_text();
        sf::Text get_loop_text();
        void set_shape_position(int top, int left);
        void set_audio_name(std::string name);
        void set_audio_file_path(std::string path);
        sf::RectangleShape& get_loop_shape();
        void set_loop();
        bool is_looping();
        sf::RectangleShape& get_shape();
};
#endif
