#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <functional>
#include <glm.hpp>
#include "SpriteRenderer.h"
#include "TextRenderer.h"

// Definicja elementu menu
struct MenuItem {
    glm::vec2 Position;
    glm::vec2 Size;
    std::string Text;
    std::function<void()> Action;
    bool Selected; // Czy przycisk jest wybrany (dla klawiatury)
};

class Menu
{
public:
    Menu(); // Konstruktor

    void AddItem(const glm::vec2& pos,
        const glm::vec2& size,
        const std::string& text,
        std::function<void()> action);

    // -- Obs³uga Klawiatury --
    void SelectNext();
    void SelectPrev();
    void ExecuteSelected();
    int GetSelected() const;

    // -- Obs³uga Myszy --
    void ProcessMouse(double mouseX, double mouseY, bool pressed);

    // -- Renderowanie --
    // Dodano glm::mat4 projection, aby renderer wiedzia³ jak rysowaæ w oknie
    void Draw(SpriteRenderer& renderer, TextRenderer& text, glm::mat4 projection);

private:
    std::vector<MenuItem> Items;
    int SelectedIndex; // Indeks aktualnie wybranego elementu
};

#endif