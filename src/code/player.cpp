#include "player.hpp"

Player::Player(float x, float y) : canJump(true) {
    if (!texture.loadFromFile("test.png")) { // Assure-toi que ce chemin est correct
        // Gère l'erreur de chargement ici
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    velocity = sf::Vector2f(0, 0);
}

void Player::handleInput() {
    const float speed = 5.0f; // Vitesse de déplacement
    velocity.x = 0;

    // Remplace Q et D par Left et Right si tu souhaites utiliser les flèches du clavier
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        velocity.x = -speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x = speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
        velocity.y = -speed * 2; // Ajuste la force du saut
        canJump = false;
    }
}

void Player::update(float groundHeight) {
    const float gravity = 0.5f; // Ajuste la gravité si nécessaire
    velocity.y += gravity;
    sprite.move(velocity);

    sf::Vector2f pos = sprite.getPosition();
    // Gestion des collisions avec les bords de l'écran
    if (pos.x < 0) sprite.setPosition(0, pos.y);
    if (pos.x + sprite.getGlobalBounds().width > 1920) sprite.setPosition(1920 - sprite.getGlobalBounds().width, pos.y);
    if (pos.y < 0) sprite.setPosition(pos.x, 0);
    if (pos.y + sprite.getGlobalBounds().height > groundHeight) {
        sprite.setPosition(pos.x, groundHeight - sprite.getGlobalBounds().height);
        velocity.y = 0;
        canJump = true; // Réinitialise le saut
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Player::getVelocity() const {
    return velocity;
}

void Player::setVelocity(float vx, float vy) {
    velocity.x = vx;
    velocity.y = vy;
}

sf::Sprite Player::getSprite() const {
    return sprite;
}

// Implémentation des nouvelles méthodes
bool Player::isMovingLeft() const {
    return velocity.x < 0;
}

bool Player::isMovingRight() const {
    return velocity.x > 0;
}
