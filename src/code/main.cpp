#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

enum GameState {
    MENU,
    GAME
};

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Platformer", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    GameState state = MENU;
    int selectedOption = 0;

    sf::Font font;
    if (!font.loadFromFile("../font/menu.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return -1;
    }

    sf::Text playText("Play", font, 100);
    playText.setPosition(window.getSize().x / 2 - playText.getGlobalBounds().width / 2, window.getSize().y / 3);
    sf::Text exitText("Exit", font, 100);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 3 + 150);

    float gravity = 0.0f;
    sf::Clock fallClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (state == MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Z) {
                        selectedOption = (selectedOption + 2) % 3; // Correction de la navigation
                        std::cout << "Z pressed" << std::endl;
                    } else if (event.key.code == sf::Keyboard::S) {
                        selectedOption = (selectedOption + 1) % 3; // Correction de la navigation
                        std::cout << "S pressed" << std::endl;
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        if (selectedOption == 0) {
                            state = GAME; // Commence le jeu
                        } else if (selectedOption == 1) {
                            window.close(); // Sortie du jeu
                        }
                    }
                }
            }
        }

        window.clear();

        if (state == MENU) {
            playText.setFillColor(selectedOption == 0 ? sf::Color::Red : sf::Color::White);
            exitText.setFillColor(selectedOption == 1 ? sf::Color::Red : sf::Color::White);

            window.draw(playText);
            window.draw(exitText);
        }

        window.display();
    }

    return 0;
}
