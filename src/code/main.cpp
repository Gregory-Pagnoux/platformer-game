#include "class.h"

enum GameState {
    MENU,
    GAME,
    PLAYER

};

sf::Sprite PlayerSprite;
sf::Vector2f velocity(0.f, 0.f);
bool isOnGround = false;
bool collision = false;
int gravity= 10;
bool isJumping = false;
int Jumping = 5;
 bool isRunning = false;
    bool lastDirectionLeft = false;
    int currentFrame = 0;
    int x = 375;
    int y = 275;

int main() {
    std::cout << "SetWindow" << std::endl;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Platformer", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    sf::Clock ClockAnimation;

    GameState state = MENU;
    int selectedOption = 0;
   
    PlayerSprite.setTexture(PRunRightSheet[0]);
    PlayerSprite.setScale(sf::Vector2f(0.5f, 0.5)); 
    PlayerSprite.setPosition(x, y);

    std::cout << "loadFont" << std::endl;
    sf::Font font;
    if (!font.loadFromFile("../font/menu.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return -1;
    }

    sf::Texture BackgroundTexture;
    std::cout << "loadImages" << std::endl;
    if (!BackgroundTexture.loadFromFile("../images/level1/lvl1.png")) {
        std::cerr << "Failed to load images." << std::endl;
        return -1;
    }

    sf::Texture BackgroundTexture2;
    std::cout<< "loadImages" <<std::endl;
    if(!BackgroundTexture2.loadFromFile("../images/platform/platform.png")){
        std::cerr << "Failed to load images." << std::endl;
        return -1;
    }

    sf::Texture BackgroundTexture3;
    std::cout<< "loadImages" <<std::endl;
    if(!BackgroundTexture3.loadFromFile("../images/obstacle/obstacle.png")){
        std::cerr << "Failed to load images." << std::endl;
        return -1;
    }

    sf::Sprite backgrounds;
    backgrounds.setTexture(BackgroundTexture);

    float windowRatio = float(window.getSize().x) / float(window.getSize().y);
    float backgroundRatio = float(BackgroundTexture.getSize().x) / float(BackgroundTexture.getSize().y);
    float scale = (windowRatio > backgroundRatio) ? float(window.getSize().x) / float(BackgroundTexture.getSize().x) :
                                                    float(window.getSize().y) / float(BackgroundTexture.getSize().y);
    backgrounds.setScale(scale, scale);

    if (windowRatio > backgroundRatio) {
        backgrounds.setPosition(0, (window.getSize().y - BackgroundTexture.getSize().y * scale) / 2);
    } else {
        backgrounds.setPosition((window.getSize().x - BackgroundTexture.getSize().x * scale) / 2, 0);
    }

    sf::Sprite backgrounds2;
    backgrounds2.setTexture(BackgroundTexture2);

    float windowRatio2 = float(window.getSize().x) / float(window.getSize().y);
    float background2Ratio = float(BackgroundTexture2.getSize().x) / float(BackgroundTexture2.getSize().y);
    float scale2 = (windowRatio > backgroundRatio) ? float(window.getSize().x) / float(BackgroundTexture2.getSize().x) :
                                                    float(window.getSize().y) / float(BackgroundTexture2.getSize().y);
    backgrounds2.setScale(scale, scale);

    if (windowRatio > background2Ratio) {
        backgrounds2.setPosition(0, (window.getSize().y - BackgroundTexture2.getSize().y * scale) / 2);
    } else {
        backgrounds2.setPosition((window.getSize().x - BackgroundTexture2.getSize().x * scale) / 2, 0);
    }

    sf::Sprite backgrounds3;
    backgrounds3.setTexture(BackgroundTexture3);

    float windowRatio3 = float(window.getSize().x) / float(window.getSize().y);
    float background3Ratio = float(BackgroundTexture3.getSize().x) / float(BackgroundTexture3.getSize().y);
    float scale3 = (windowRatio > backgroundRatio) ? float(window.getSize().x) / float(BackgroundTexture3.getSize().x) :
                                                    float(window.getSize().y) / float(BackgroundTexture3.getSize().y);
    backgrounds3.setScale(scale, scale);

    if (windowRatio > background2Ratio) {
        backgrounds3.setPosition(0, (window.getSize().y - BackgroundTexture3.getSize().y * scale) / 2);
    } else {
        backgrounds3.setPosition((window.getSize().x - BackgroundTexture3.getSize().x * scale) / 2, 0);
    }

    sf::Text playText("Play", font, 100);
    playText.setPosition(window.getSize().x / 2 - playText.getGlobalBounds().width / 2, window.getSize().y / 3);

    sf::Text exitText("Exit", font, 100);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 3 + 150);

    float backgroundSpeed = 7.0f;
    float backgroundSpeed2 = 7.0f;
    float backgroundSpeed3 = 7.0f;

    sf::Music menu;
    if (!menu.openFromFile("../sounds/Menu.wav")) {
        std::cerr << "Failed to load music." << std::endl;
        return -1;
    }

    sf::Music level;
    if (!level.openFromFile("../sounds/LevelBackground.wav")) {
        std::cerr << "Failed to load music." << std::endl;
        return -1;
    }

    sf::Music boss1;
    if (!boss1.openFromFile("../sounds/BossBackground1.wav")) {
        std::cerr << "Failed to load music." << std::endl;
        return -1;
    }

    sf::Music boss2;
    if (!boss2.openFromFile("../sounds/BossBackground2.wav")) {
        std::cerr << "Failed to load music." << std::endl;
        return -1;
    }

    sf::Music finalBoss;
    if (!finalBoss.openFromFile("../sounds/FinalBoss.wav")) {
        std::cerr << "Failed to load music." << std::endl;
        return -1;
    }

    sf::Music enemiesDeath;
    if (!enemiesDeath.openFromFile("../sounds/EnemiesDeath.wav")) {
        std::cerr << "Failed to load music." << std::endl;
        return -1;
    }

    sf::Music mainDeath;
    if (!mainDeath.openFromFile("../sounds/MainDeath.wav")) {
        std::cerr << "Failed to load music." << std::endl;
        return -1;
    }

    menu.play();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Escape)) {
                window.close();
            }

            if (state == MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Z) {
                        selectedOption = (selectedOption + 1) % 2;
                    } else if (event.key.code == sf::Keyboard::S) {
                        selectedOption = (selectedOption + 1) % 2;
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        if (selectedOption == 0) {
                            state = GAME;
                            menu.stop();
                            level.play();
                        } else if (selectedOption == 1) {
                            window.close();
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
        } else if (state == GAME) {

            if (event.key.code == sf::Keyboard::Escape) {
                state = MENU;
                level.stop();
                menu.play();
            }

            if (event.key.code == sf::Keyboard::D) {
                sf::FloatRect playerBounds = PlayerSprite.getGlobalBounds();
                sf::FloatRect background2Bounds = backgrounds2.getGlobalBounds();

                if (!playerBounds.intersects(background2Bounds)) {
                    backgrounds.move(-backgroundSpeed, 0);
                }
            } else if (event.key.code == sf::Keyboard::Q) {
                sf::FloatRect playerBounds = PlayerSprite.getGlobalBounds();
                sf::FloatRect background2Bounds = backgrounds2.getGlobalBounds();

                if (!playerBounds.intersects(background2Bounds)) {
                    backgrounds.move(backgroundSpeed, 0);
                }
            }

            if (event.key.code == sf::Keyboard::D) {
                sf::FloatRect playerBounds = PlayerSprite.getGlobalBounds();
                sf::FloatRect background2Bounds = backgrounds2.getGlobalBounds();

                if (!playerBounds.intersects(background2Bounds)) {
                    backgrounds2.move(-backgroundSpeed2, 0);
                }
            } else if (event.key.code == sf::Keyboard::Q) {
                sf::FloatRect playerBounds = PlayerSprite.getGlobalBounds();
                sf::FloatRect background2Bounds = backgrounds2.getGlobalBounds();

                if (!playerBounds.intersects(background2Bounds)) {
                    backgrounds2.move(backgroundSpeed2, 0);
                }
            }

            if (event.key.code == sf::Keyboard::D) {
                sf::FloatRect playerBounds = PlayerSprite.getGlobalBounds();
                sf::FloatRect background2Bounds = backgrounds2.getGlobalBounds();

                if (!playerBounds.intersects(background2Bounds)) {
                    backgrounds3.move(-backgroundSpeed3, 0);
                }
            } else if (event.key.code == sf::Keyboard::Q) {
                sf::FloatRect playerBounds = PlayerSprite.getGlobalBounds();
                sf::FloatRect background2Bounds = backgrounds2.getGlobalBounds();

                if (!playerBounds.intersects(background2Bounds)) {
                    backgrounds3.move(backgroundSpeed3, 0);
                }
            }

            window.draw(backgrounds);
            window.draw(backgrounds3);
            window.draw(backgrounds2);
        } if(state == PLAYER - 1){

            
            
            std::cout<< "state="<<state<<std::endl;
            std::cout<< "player="<<PLAYER<<std::endl;
            std::cout<< "loop" <<std::endl;

            if (event.key.code == sf::Keyboard::D) {
                isRunning = true;
                lastDirectionLeft = false;
                std::cout<< "loop" <<std::endl;
                if(ClockAnimation.getElapsedTime().asSeconds() > 0.1f){
                    currentFrame = (currentFrame + 1) % PRunRightSheet.size();
                    PlayerSprite.setTexture(PRunRightSheet[currentFrame]);
                    ClockAnimation.restart();
                }
            }
            if (event.key.code == sf::Keyboard::Q) {
                isRunning = true;
                lastDirectionLeft = true;
                std::cout<< "loop" <<std::endl;
                if (ClockAnimation.getElapsedTime().asSeconds() > 0.1f){
                    currentFrame = (currentFrame + 1) % PRunLeftSheet.size();
                    PlayerSprite.setTexture(PRunLeftSheet[currentFrame]);
                    ClockAnimation.restart();
                }
            }

            if(collision == false){
                y += gravity;
                PlayerSprite.setPosition(x, y);
            }

            if (event.key.code == sf::Keyboard::Space) {
                isJumping = true;
            }
            window.draw(PlayerSprite);
        }
>>>>>>> ef843bc0feac975f6de393805fa62826be1d8396
        window.display();
    }
    return 0;
}
