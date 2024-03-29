#include <SFML/Graphics.hpp>
#include <vector>

// Assure-toi que "Player.hpp" est bien configuré pour ton joueur
#include "player.hpp"

class Platform {
public:
    sf::RectangleShape shape;
    Platform(float x, float y, float width, float height) {
        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color::Red);
    }
};

enum GameState {
    MENU,
    GAME,
    FALLING
};

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Platformer", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    GameState state = MENU;
    int selectedOption = 0;

    Player player(window.getSize().x / 2 - 50, window.getSize().y - 100);

    std::vector<Platform> platforms;
    platforms.push_back(Platform(200, window.getSize().y - 200, 300, 30));
    platforms.push_back(Platform(600, window.getSize().y - 400, 300, 30));
    // Ajoute d'autres plateformes selon tes besoins

    sf::Texture backgroundTextures[4];
    backgroundTextures[0].loadFromFile("../images/level1/background1.png");
    backgroundTextures[1].loadFromFile("../images/level1/background2.png");
    backgroundTextures[2].loadFromFile("../images/level1/background3.png");
    backgroundTextures[3].loadFromFile("../images/level1/background4.png");

    sf::Sprite backgrounds[4];
    for (int i = 0; i < 4; i++) {
        backgrounds[i].setTexture(backgroundTextures[i]);
        backgrounds[i].setScale(window.getSize().x / static_cast<float>(backgroundTextures[i].getSize().x), window.getSize().y / static_cast<float>(backgroundTextures[i].getSize().y));
        backgrounds[i].setPosition(window.getSize().x * i, 0);
    }

    float backgroundSpeed = 2.0f;

    sf::Font font;
    if (!font.loadFromFile("../font/menu.ttf")) {
        return -1;
    }

    sf::Text playText("Play", font, 100);
    playText.setPosition(window.getSize().x / 2 - playText.getGlobalBounds().width / 2, window.getSize().y / 3);

    sf::Text exitText("Exit", font, 100);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 3 + 150);

    float gravity = 0.0f;
    bool isFalling = false;
    sf::Clock fallClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            if (state == MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedOption = (selectedOption + 2) % 3;
                    } else if (event.key.code == sf::Keyboard::Down) {
                        selectedOption = (selectedOption + 1) % 3;
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        state = FALLING;
                        fallClock.restart();
                    }
                }
            }
        }

               window.clear();

        if (state == MENU || state == FALLING) {
            if (state == FALLING && fallClock.getElapsedTime().asSeconds() < 1.0f) {
                gravity += 0.5f;
                if (selectedOption != 0) playText.move(0, gravity);
                if (selectedOption != 1) exitText.move(0, gravity);
            } else if (state == FALLING) {
                gravity = 0.0f;
                if (selectedOption == 0) state = GAME;
                if (selectedOption == 1) state = MENU; // Adjust this for actual settings logic
                if (selectedOption == 2) window.close();
                playText.setPosition(window.getSize().x / 2 - playText.getGlobalBounds().width / 2, window.getSize().y / 3);
                exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 3 + 150);
                isFalling = false;
            }
            playText.setFillColor(selectedOption == 0 ? sf::Color::Red : sf::Color::White);
            exitText.setFillColor(selectedOption == 1 ? sf::Color::Red : sf::Color::White);

            window.draw(playText);
            window.draw(exitText);
        } else if (state == GAME) {
            // Logique de déplacement du fond
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                for (int i = 0; i < 4; i++) {
                    backgrounds[i].move(-backgroundSpeed, 0);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                for (int i = 0; i < 4; i++) {
                    backgrounds[i].move(backgroundSpeed, 0);
                }
            }

            // Dessin du fond
            for (auto &background : backgrounds) {
                window.draw(background);
            }

            // Dessin des plateformes
            for (auto &platform : platforms) {
                window.draw(platform.shape);
            }

            // Dessin du joueur
            player.draw(window);
        }

        window.display();
    }

    return 0;
}
