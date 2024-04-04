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
int x = 0;
int y = 1080-300;

#define SPEED 10


void move(sf::RectangleShape* shape, int speed){
    shape->setPosition(shape->getPosition().x + speed, shape->getPosition().y);
}

int main() {
    std::cout << "SetWindow" << std::endl;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Platformer", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    sf::Clock ClockAnimation;

    std::array<sf::RectangleShape, 1000> arr;
    for(int i = 0; i < 100; i++){
        arr[i].setSize(sf::Vector2f(200, 20));
        arr[i].setPosition((rand() % (1920*12))+400, (rand() % 800)+200);
        arr[i].setFillColor(sf::Color::Red);
    }

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

    sf::Sprite backgrounds;
    backgrounds.setTexture(BackgroundTexture);

    float windowRatio = float(window.getSize().x) / float(window.getSize().y);
    float backgroundRatio = float(BackgroundTexture.getSize().x) / float(BackgroundTexture.getSize().y);
    float scale = (windowRatio > backgroundRatio) ? float(window.getSize().x) / float(BackgroundTexture.getSize().x) : float(window.getSize().y) / float(BackgroundTexture.getSize().y);
    backgrounds.setScale(scale, scale);

    if (windowRatio > backgroundRatio) {
        backgrounds.setPosition(0, (window.getSize().y - BackgroundTexture.getSize().y * scale) / 2);
    } else {
        backgrounds.setPosition((window.getSize().x - BackgroundTexture.getSize().x * scale) / 2, 0);
    }
    sf::Text playText("Play", font, 100);
    playText.setPosition(window.getSize().x / 2 - playText.getGlobalBounds().width / 2, window.getSize().y / 3);

    sf::Text exitText("Exit", font, 100);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 3 + 150);

    float backgroundSpeed = 7.0f;
    float PlatformSpeed = 7.0f;

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                backgrounds.move(-backgroundSpeed, 0);
                for(int i = 0; i < 100; i++){
                    move(&arr[i], -SPEED);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                backgrounds.move(backgroundSpeed, 0);
                for(int i = 0; i < 100; i++){
                    move(&arr[i], SPEED);
                }
            }


            window.draw(backgrounds);

             for(int i = 0; i < 100; i++){
            std::cout<<"draw"<<std::endl;
            window.draw(arr[i]);
        }
        } 
        if(state == PLAYER - 1){
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
              isRunning = true;
              lastDirectionLeft = false;
               std::cout<<  "loop" <<std::endl;
              if(ClockAnimation.getElapsedTime().asSeconds() > 0.1f){
                currentFrame = (currentFrame + 1) % PRunRightSheet.size();
                PlayerSprite.setTexture(PRunRightSheet[currentFrame]);
                ClockAnimation.restart();
              }
               
            }

             if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
              isRunning = true;
              lastDirectionLeft = true;
               std::cout<< "loop" <<std::endl;
              if(ClockAnimation.getElapsedTime().asSeconds() > 0.1f){
                currentFrame = (currentFrame + 1) % PRunLeftSheet.size();
                PlayerSprite.setTexture(PRunLeftSheet[currentFrame]);
                ClockAnimation.restart();
              }
             }
        window.draw(PlayerSprite);
    }
        
        window.display();
}
    return 0;
}
