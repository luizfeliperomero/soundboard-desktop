#include "player.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <regex>

void Player::set_loop_shape_design() {
    this->loop_shape.setSize(sf::Vector2f(120.0f, 30.0f));
    this->loop_shape.setFillColor(sf::Color(211, 211, 211));
}

void Player::set_options_shape_design() {
    this->options_shape.setSize(sf::Vector2f(40.0f, 140.0f));
    this->options_shape.setFillColor(sf::Color(211, 211, 211));
}

void Player::set_shape_design() {
    this->shape.setSize(sf::Vector2f(230.0f, 200.0f));
    this->shape.setFillColor(sf::Color(128,128,128));
}

void Player::set_shapes_design() {
    set_shape_design();
    set_loop_shape_design();
    set_options_shape_design();
}

Player::Player(std::string audio_name, std::string audio_file_path) {
    slider.setWidth(200);
    slider.setHeight(14);
    load_textures();
    font.loadFromFile("/home/luizf/Projects/rpg-soundboard-desktop/assets/fonts/Poppins-Regular.ttf");
    this->audio_name = audio_name;
    this->audio_file_path = audio_file_path;
    this->loading_msg = "Loading ...";
    set_shapes_design();
    this->is_playing = false;
    this->is_loading = false;
    this->first_time_playing = true;
    load_audio_from_file();
}

Player::Player() {
    slider.setWidth(200);
    slider.setHeight(15);
    load_textures();
    font.loadFromFile("/home/luizf/Projects/rpg-soundboard-desktop/assets/fonts/Poppins-Regular.ttf");
    this->loading_msg = "Loading ...";
    this->is_playing = false;
    this->is_loading = false;
    this->first_time_playing = true;
    set_shapes_design();
    load_audio_from_file();
}

std::string Player::get_audio_name() const {
    return audio_name;
}

void Player::set_is_playing() {
    is_playing = !is_playing;
}

void Player::set_audio_name(std::string name) {
    this->audio_name = name;
}


int Player::get_id() {
    return id;
}

void Player::set_id(int id) {
    this->id = id;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(get_shape());
    window.draw(get_center_text());
    window.draw(get_loop_shape());
    window.draw(get_loop_text());
    window.draw(get_loop_btn_sprite());
    window.draw(get_options_shape());
    window.draw(get_open_file_btn_sprite());
    window.draw(get_edit_btn_sprite());
    slider.draw(window);
}

std::string Player::get_audio_file_path() const {
    return audio_file_path;
}

void Player::set_audio_file_path(std::string path) {
    this->audio_file_path = path;
    load_audio_from_file();
}

void Player::set_loop() {
    loop = !loop;
    if(loop) {
        sound.setLoop(true);
    } else {
        sound.setLoop(false);
    }
}

bool Player::is_looping() {
    return loop;
}

sf::Text Player::get_center_text() {
    std::string title;
    if(is_loading) {
        title = loading_msg; 
    } else {
        title = audio_name; 
    }
    center_text = sf::Text{title, font, 20};
    center_text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2 - center_text.getLocalBounds().width / 2, this->shape.getPosition().y + this->shape.getSize().y / 2 - center_text.getLocalBounds().height / 2);
    return center_text;
}

sf::Sprite Player::get_loop_btn_sprite() {
    sf::Texture btn_texture;
    if(loop) {
        btn_texture.loadFromFile("/home/luizf/Projects/rpg-soundboard-desktop/assets/images/on-button.png");
    } else {
        btn_texture.loadFromFile("/home/luizf/Projects/rpg-soundboard-desktop/assets/images/off-button.png");
    }
    loop_toggle_btn = std::make_unique<sf::Texture>(btn_texture);
    
    float spacing = 10.0f;
    float spriteX = loop_text.getPosition().x + loop_text.getLocalBounds().width + spacing;
    float spriteY = loop_text.getPosition().y - 10;

    sf::Sprite sprite(*loop_toggle_btn);
    sprite.setPosition(spriteX, spriteY);
    sprite.setScale(0.09f, 0.07f);

    return sprite;
}

sf::Sprite Player::get_edit_btn_sprite() {
    sf::Sprite sprite(*edit_btn); 
    int spacing = 20;
    int margin = 13;
    sprite.setPosition(get_open_file_btn_sprite().getPosition().x - margin, get_open_file_btn_sprite().getPosition().y + spacing); 
    sprite.setScale(0.8f, 0.8f);
    return sprite;
}

void Player::load_textures() {
    sf::Texture edit_btn_texture; 
    edit_btn_texture.loadFromFile("/home/luizf/Projects/rpg-soundboard-desktop/assets/images/ep_edit.png");
    edit_btn = std::make_unique<sf::Texture>(edit_btn_texture);
}

sf::Text Player::get_loop_text() {
    loop_text.setPosition(this->loop_shape.getPosition().x + this->loop_shape.getSize().x / 3 - loop_text.getLocalBounds().width / 2, this->loop_shape.getPosition().y + this->loop_shape.getSize().y / 2 - loop_text.getLocalBounds().height / 2);
    return loop_text;
}

void Player::set_shape_position(int top, int left) {
    this->shape.setPosition(top, left);
}

sf::RectangleShape& Player::get_shape() {
    center_text.setFillColor(sf::Color::White);
    return shape;
}

void Player::open_file() {
    char filename[1024];
    FILE *f = popen("zenity --file-selection", "r");
    std::string file_path = fgets(filename, 1024, f);
    if (!file_path.empty() && file_path.back() == '\n') {
        file_path.pop_back();
    }
    std::string expected_path = "/home/luizf/Projects/rpg-soundboard-desktop/sounds/thunder.wav";
    set_audio_file_path(file_path);
} 

sf::RectangleShape& Player::get_loop_shape() {
    loop_text = sf::Text{"LOOP", font, 14};
    loop_text.setFillColor(sf::Color::Black);
    loop_shape.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2 - loop_shape.getLocalBounds().width / 2, this->shape.getPosition().y - loop_shape.getLocalBounds().height);
    return loop_shape;
}

sf::Sprite Player::get_open_file_btn_sprite() {
    sf::Texture texture;
    texture.loadFromFile("/home/luizf/Projects/rpg-soundboard-desktop/assets/images/foundation_sound.png");
    open_file_btn = std::make_unique<sf::Texture>(texture);
    sf::Sprite sprite(*open_file_btn);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    float x = options_shape.getPosition().x + options_shape.getSize().x / 2;
    float y = options_shape.getPosition().y + 20;
    sprite.setPosition(x, y);
    sprite.setScale(0.3f, 0.3f);
    return sprite;
}

sf::RectangleShape& Player::get_options_shape() {
    options_shape.setPosition(this->shape.getPosition().x - this->options_shape.getLocalBounds().width, this->shape.getPosition().y + this->shape.getSize().y / 2 - options_shape.getLocalBounds().height / 2);
    return options_shape;
}

void Player::on_click() {
    if(!first_time_playing) {
        set_is_playing();
    } else {
        is_playing = false;
    }
    if(is_playing) {
        pause();
        shape.setOutlineThickness(0);
    } else {
        play();
        shape.setOutlineThickness(3.0f);
        shape.setOutlineColor(sf::Color::Green);
        first_time_playing = false;
    }
}

void Player::pause() {
    sound.pause();
}

void Player::play() {
    sound.play();
}

bool Player::load_audio_from_file() {
    if(audio_file_path != "") {
        is_loading = true;
        if (!buffer.loadFromFile(audio_file_path)) {
            return 1;
        } else {
            sound.setBuffer(buffer);
            is_loading = false;
        }
    }
    return 0;
}

