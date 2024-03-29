#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(float width, float height);
    ~Menu();

    // Fonction pour dessiner le menu
    void draw(sf::RenderWindow &window);
    
    // Fonction pour naviguer vers le haut dans le menu
    void moveUp();
    
    // Fonction pour naviguer vers le bas dans le menu
    void moveDown();
    
    // Obtenir l'index de l'item actuellement sélectionné
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex; // Index de l'option sélectionnée
    sf::Font font; // Police de caractères
    std::vector<sf::Text> menuItems; // Options du menu
};

#endif // MENU_HPP
