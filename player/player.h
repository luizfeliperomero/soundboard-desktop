#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player {
    private:
        std::string audio_name; 
        std::string audio_file_path;
        sf::Text center_text;
        bool loop;
        sf::RectangleShape loop_shape;
        sf::SoundBuffer buffer;
        sf::Sound sound;
    public:
        bool sound_loaded;
        void on_click();
        void play();
        void pause();
        bool is_playing;
        bool first_time_playing;
        void set_is_playing();
        sf::RectangleShape shape;
        sf::Font font;
        bool load_audio_from_file();
        Player(std::string audio_name, std::string audio_file_path);
        Player();
        std::string get_audio_name() const;
        std::string get_audio_file_path() const;
        sf::Text get_center_text();
        void set_shape_position(int top, int left);
        void set_audio_name(std::string name);
        void set_audio_file_path(std::string path);
        sf::RectangleShape& get_loop_shape();
        void set_loop();
        bool is_looping();
        sf::RectangleShape& get_shape();
};
