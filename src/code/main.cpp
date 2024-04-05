//  ___   _____  ___  __  __  ___   _  _   
// / _ \ | ___ |/ _ \|  \/  |/ _ \ | || |  
//| | | || ___ | | | | |\/| | | | || || |_ 
//| |_| || |   | |_| | |  | | |_| ||__   _|
//\___/ |_|    \___/|_|  |_|\___/    |_|  




// Include necessary headers
#include "class.h"

// Define game states as an enumeration for readability and easier state management
enum GameState {
    MENU,
    GAME,
    PLAYER,
    GAME_OVER
};

// Global variables for player sprite, movement, and game physics
sf::Sprite PlayerSprite;
sf::Vector2f velocity(0.f, 0.f);
bool isOnGround = false;
bool collision = false;
int gravity = 10;
bool isJumping = false;
int Jumping = 10;
bool isRunning = false;
bool lastDirectionLeft = false;
int currentFrame = 0;
int x = 0;
int y = 1080 - 300; // Initial player position, assuming a 1080p resolution and starting 300 pixels from the bottom
namespace fs = std::filesystem; // Namespace alias for filesystem
#define SPEED 10 // Define a constant for player and background speed

// Function to move shapes (like platforms), improving modularity
void move(sf::RectangleShape* shape, int speed) {
    shape->setPosition(shape->getPosition().x + speed, shape->getPosition().y);
}

// Main game function
int main() {
 std::cout << "  ___   _____  ___  __  __  ___   _  _   \n"
                 " / _ \\ | ___ |/ _ \\|  \\/  |/ _ \\ | || |  \n"
                 "| | | || ___ | | | | |\\/| | | | || || |_ \n"
                 "| |_| || |   | |_| | |  | | |_| ||__   _|\n"
                 " \\___/ |_|    \\___/|_|  |_|\\___/    |_|  \n";

  std::cout << 
        "             _wr\"\"        \"-q__                             \n"
        "                 _dP                 9m_     \n"
        "               _#P                     9#_                         \n"
        "              d#@                       9#m                        \n"
        "             d##                         ###                       \n"
        "            J###                         ###L                      \n"
        "            {###K                       J###K                      \n"
        "            ]####K      ___aaa___      J####F                      \n"
        "        __gmM######_  w#P\"\"   \"\"9#m  _d#####Mmw__                  \n"
        "     _g##############mZ_         __g##############m_               \n"
        "   _d####M@PPPP@@M#######Mmp gm#########@@PPP9@M####m_             \n"
        "  a###\"\"          ,Z\"#####@' '######\"\\g          \"\"M##m            \n"
        " J#@\"             0L  \"*##     ##@\"  J#              *#K           \n"
        " #\"               `#    \"_gmwgm_~    dF               `#_          \n"
        "7F                 \"#_   ]#####F   _dK                 JE          \n"
        "]                    *m__ ##### __g@\"                   F          \n"
        "                       \"PJ#####LP\"                                 \n"
        " `                       0######_                      '           \n"
        "                       _0########_                                   \n"
        "     .               _d#####^#####m__              ,              \n"
        "      \"*w_________am#####P\"   ~9#####mw_________w*\"                  \n"
        "          \"\"9@#####@M\"\"           \"\"P@#####@M\"\"                    \n";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                     //  MAIN                                                                       /
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "SetWindow" << std::endl; //Debug message for window setup
    // Create a fullscreen window using the desktop's video mode
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Platformer", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true); // Enable vertical sync to prevent tearing
    sf::Clock ClockAnimation; // Clock to manage animations

    // Array to store platform shapes
    std::array<sf::RectangleShape, 1000> arr;
    // Initialize platforms with random positions and sizes
    for(int i = 0; i < 100; i++){
        arr[i].setSize(sf::Vector2f(200, 20));
        arr[i].setPosition((rand() % (1920*15)), (rand() % 1080));
        arr[i].setFillColor(sf::Color::Red);
    }

    // Variables to manage player movement permissions
    bool canMoveR = true;
    bool canMoveL = true;
    bool canMoveU = true;
    bool canMoveD = true;

    // Game state management
    GameState state = MENU;
    int selectedOption = 0;

    // Initialize player sprite and position
    PlayerSprite.setTexture(PRunRightSheet[0]);
    PlayerSprite.setScale(sf::Vector2f(0.3f, 0.3)); 
    PlayerSprite.setPosition(x, y);

    // Load font for menu and game-over text
    std::cout << "loadFont" << std::endl;
    sf::Font font;
    if (!font.loadFromFile("../font/menu.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return -1; // Exit if font loading fails
    }

    // Background texture and sprite setup
    sf::Texture BackgroundTexture;
    std::cout << "loadImages" << std::endl;
    if (!BackgroundTexture.loadFromFile("../images/level1/lvl1.png")) {
        std::cerr << "Failed to load images." << std::endl;
        return -1; // Exit if image loading fails
    }
    sf::Sprite backgrounds;
    backgrounds.setTexture(BackgroundTexture);

    // Adjust background scaling to fit the window
    float windowRatio = float(window.getSize().x) / float(window.getSize().y);
    float backgroundRatio = float(BackgroundTexture.getSize().x) / float(BackgroundTexture.getSize().y);
    float scale = (windowRatio > backgroundRatio) ? float(window.getSize().x) / float(BackgroundTexture.getSize().x) : float(window.getSize().y) / float(BackgroundTexture.getSize().y);
    backgrounds.setScale(scale, scale);
    if (windowRatio > backgroundRatio) {
        backgrounds.setPosition(0, (window.getSize().y - BackgroundTexture.getSize().y * scale) / 2);
    } else {
        backgrounds.setPosition((window.getSize().x - BackgroundTexture.getSize().x * scale) / 2, 0);
    }

    // Setup text for play and exit options in the menu
    sf::Text playText("Play", font, 100);
    playText.setPosition(window.getSize().x / 2 - playText.getGlobalBounds().width / 2, window.getSize().y / 3);
    sf::Text exitText("Exit", font, 100);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, window.getSize().y / 3 + 150);
    sf::Text GameOverText("GAME OVER", font, 100);
    GameOverText.setPosition(window.getSize().x / 2 - GameOverText.getGlobalBounds().width / 2, window.getSize().y / 3);

    // Variables for background and platform movement speeds
    float backgroundSpeed = 7.0f;
    float PlatformSpeed = 7.0f;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            // Menu state controls
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

        // Draw menu or game elements based on the current state
        if (state == MENU) {
            playText.setFillColor(selectedOption == 0 ? sf::Color::Red : sf::Color::White);
            exitText.setFillColor(selectedOption == 1 ? sf::Color::Red : sf::Color::White);
            window.draw(playText);
            window.draw(exitText);

          }  // GAME_OVER state controls
        if (state == GAME_OVER) { 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
              window.close();
            }
        }

        // Draw GAME_OVER text
        if (state == GAME_OVER) {
            GameOverText.setFillColor(sf::Color::Red);
            window.draw(GameOverText);
        } else if (state == GAME) {
            // Check for collisions with platforms
            for(auto &arr: arr){
                if(PlayerSprite.getGlobalBounds().intersects(arr.getGlobalBounds())){
                    collision = true;
                    state = GAME_OVER;
                }
            }

            // Player movement controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if(canMoveR){
                    backgrounds.move(-backgroundSpeed, 0);
                    for(int i = 0; i < 100; i++){
                        move(&arr[i], -SPEED);
                    }
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                if(canMoveL){
                    backgrounds.move(backgroundSpeed, 0);
                    for(int i = 0; i < 100; i++){
                        move(&arr[i], SPEED);
                    }
                }
            }

            window.draw(backgrounds);
            for(int i = 0; i < 100; i++){
                window.draw(arr[i]);
            }
        }
        
        // Draw player sprite
        if (state == PLAYER - 1) {
            // Player running animation controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                isRunning = true;
                lastDirectionLeft = false;
                if (ClockAnimation.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % PRunRightSheet.size();
                    PlayerSprite.setTexture(PRunRightSheet[currentFrame]);
                    ClockAnimation.restart();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                isRunning = true;
                lastDirectionLeft = true;
                if (ClockAnimation.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % PRunLeftSheet.size();
                    PlayerSprite.setTexture(PRunLeftSheet[currentFrame]);
                    ClockAnimation.restart();
                }
            }
            // Player jump and crouch controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (canMoveD == true) {
                    y -= gravity;
                    PlayerSprite.setPosition(x, y);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (canMoveD == true) {
                    y += gravity;
                    PlayerSprite.setPosition(x, y);
                }
            }
    
            window.draw(PlayerSprite);
        }
        window.display();

        
    } 
    return 0;
}

//  ___   _____  ___  __  __  ___   _  _   
// / _ \ | ___ |/ _ \|  \/  |/ _ \ | || |  
//| | | || ___ | | | | |\/| | | | || || |_ 
//| |_| || |   | |_| | |  | | |_| ||__   _|
//\___/ |_|    \___/|_|  |_|\___/    |_|  

