#include "player.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Player::Player(std::string audio_name, std::string audio_file_path) {
    this->audio_name = audio_name;
    this->audio_file_path = audio_file_path;
    this->shape.setSize(sf::Vector2f(230.0f, 200.0f));
    this->loop_shape.setSize(sf::Vector2f(120.0f, 30.0f));
    this->is_playing = false;
}

Player::Player() {
    this->shape.setSize(sf::Vector2f(230.0f, 200.0f));
    this->loop_shape.setSize(sf::Vector2f(120.0f, 30.0f));
    this->is_playing = false;
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

std::string Player::get_audio_file_path() const {
    return audio_file_path;
}

void Player::set_audio_file_path(std::string path) {
    this->audio_file_path = path;
    load_audio_from_file();
}

void Player::set_loop() {
    loop = !loop;
}

bool Player::is_looping() {
    return loop;
}

sf::Text Player::get_center_text() {
    center_text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2 - center_text.getLocalBounds().width / 2, this->shape.getPosition().y + this->shape.getSize().y / 2 - center_text.getLocalBounds().height / 2);
    return center_text;
}

void Player::set_shape_position(int top, int left) {
    this->shape.setPosition(top, left);
}

sf::RectangleShape& Player::get_shape() {
    font.loadFromFile("/home/luizf/Projects/rpg-soundboard-desktop/assets/fonts/Poppins-Regular.ttf");
    center_text = sf::Text{audio_name, font, 20};
    center_text.setFillColor(sf::Color::Black);
    return shape;
}

sf::RectangleShape& Player::get_loop_shape() {
    loop_shape.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2 - loop_shape.getLocalBounds().width / 2, this->shape.getPosition().y - loop_shape.getLocalBounds().height);
    return loop_shape;
}

void Player::on_click() {
    set_is_playing();
    if(is_playing) {
        pause();
        shape.setOutlineColor(sf::Color::White);
    } else {
        play();
        shape.setOutlineThickness(3.0f);
        shape.setOutlineColor(sf::Color::Green);
    }
}

void Player::pause() {
    sound.pause();
}

void Player::play() {
    sound.play();
}

bool Player::load_audio_from_file() {
    if(audio_file_path != "" && !sound_loaded) {
        if (!buffer.loadFromFile(audio_file_path)) {
            return 1;
        } else {
            sound.setBuffer(buffer);
            sound_loaded = true;
        }
    }
    return 0;
}
