class Slider {
public:
    Slider() {
        width = 0.0f;
        height = 0.0f;
        track.setSize(sf::Vector2f(width, height));
        handle.setSize(sf::Vector2f(height, height));
        track.setFillColor(sf::Color::White);
        handle.setFillColor(sf::Color::Black);
    }

    void setWidth(float width) {
        this->width = width;
        setSize();
    }

    void setHeight(float height) {
        this->height = height;
        setSize();
    }

    void setPosition(float x, float y) {
        track.setPosition(x, y);
        handle.setPosition(x, y);
    }

    void setSize() {
        track.setSize(sf::Vector2f(width, height));
        handle.setSize(sf::Vector2f(height, height));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(track);
        window.draw(handle);
    }

    void update(sf::Vector2f mousePos) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (handle.getGlobalBounds().contains(mousePos)) {
                float newX = mousePos.x - handle.getSize().x / 2;
                float leftBound = track.getPosition().x;
                float rightBound = track.getPosition().x + track.getSize().x;

                if (newX < leftBound) {
                    newX = leftBound;
                    std::cout << "First IF" << std::endl;
                }
                else if (newX + handle.getSize().x > rightBound) {
                    newX = rightBound - handle.getSize().x;
                    std::cout << "Second IF" << std::endl;
                }

                handle.setPosition(newX, handle.getPosition().y);
            }
        }
    }

    float getValue() const {
        return (handle.getPosition().x - track.getPosition().x) / (track.getSize().x - handle.getSize().x);
    }

private:
    float width;
    float height;
    sf::RectangleShape track;
    sf::RectangleShape handle;
};
