#include "Menu.h"
#include "ResourceManager.h"

Menu::Menu() : SelectedIndex(0) {
    
}

void Menu::AddItem(const glm::vec2& pos,
    const glm::vec2& size,
    const std::string& text,
    std::function<void()> action)
{
    // Jeeli to pierwszy element, ustaw go jako domyslnie wybrany
    bool isFirst = Items.empty();
    Items.push_back({ pos, size, text, action, isFirst });
}

void Menu::SelectNext() {
    if (Items.empty()) return;
    Items[SelectedIndex].Selected = false;
    SelectedIndex = (SelectedIndex + 1) % Items.size(); // Przejdz dalej i zapetl
    Items[SelectedIndex].Selected = true;
}

void Menu::SelectPrev() {
    if (Items.empty()) return;
    Items[SelectedIndex].Selected = false;
    SelectedIndex--;
    if (SelectedIndex < 0) SelectedIndex = Items.size() - 1; // Zapetl od tylu
    Items[SelectedIndex].Selected = true;
}

void Menu::ExecuteSelected() {
    if (!Items.empty() && Items[SelectedIndex].Action) {
        Items[SelectedIndex].Action();
    }
}

int Menu::GetSelected() const {
    return SelectedIndex;
}

void Menu::Draw(SpriteRenderer& renderer, TextRenderer& text, glm::mat4 projection)
{
    for (const auto& item : Items)
    {
        // 1. Rysuj t�o przycisku
        glm::vec3 buttonColor = item.Selected ? glm::vec3(0.4f, 0.4f, 0.4f) : glm::vec3(0.2f, 0.2f, 0.2f);
        renderer.DrawMenuSprite(projection, ResourceManager::GetTexture("White"), ResourceManager::GetShader("Sprite"),
            item.Position, item.Size, 0.0f, buttonColor);
        float scale = 0.7f;

        // 2. Rysuj tekst (na wierzchu)
        // Obliczamy �rodek przycisku dla tekstu (prosta matematyka)
        float textX = item.Position.x + (item.Size.x * 0.1f); // ma�y margines od lewej
        float textY = item.Position.y + (item.Size.y * 0.2f); // ma�y margines od g�ry

        glm::vec3 textColor = item.Selected ? glm::vec3(1.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 1.0f, 1.0f);

        text.RenderText(item.Text, textX, textY, 1.0f, textColor);
        text.RenderText("SomeGame", 50.0f, 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
}