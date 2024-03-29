#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float x, float y);

    void handleInput();
    void update(float groundHeight);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    sf::Vector2f getVelocity() const;
    void setVelocity(float vx, float vy);

    sf::Sprite getSprite() const;

    // Détermine si le joueur se déplace vers la gauche
    bool isMovingLeft() const;

    // Détermine si le joueur se déplace vers la droite
    bool isMovingRight() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
    bool canJump; // Indique si le joueur peut sauter (est sur le sol ou une plateforme)
    float blockSize = 50.0f; // La taille d'un "bloc" dans le jeu, ajuste selon tes besoins
};

#endif // PLAYER_HPP
