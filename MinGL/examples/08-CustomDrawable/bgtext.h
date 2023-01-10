#ifndef BGTEXT_H
#define BGTEXT_H
#include "mingl/graphics/idrawable.h"
#include "mingl/gui/text.h"
#include "mingl/shape/rectangle.h"
class BgText: public nsGraphics::IDrawable {
public:
    // Le constructeur de la classe, prenant les paramètres lors de l'instanciation
    BgText(const nsGraphics::Vec2D& position, const std::string& content, const nsGraphics::RGBAcolor& textColor,
          const nsGraphics::RGBAcolor& backgroundColor);
    // Ne pas oublier le destructeur virtuel
    virtual ~BgText() = default;
    virtual void draw(MinGL& window) const override;
private:
    nsGui::Text m_text;
    nsShape::Rectangle m_background;
};
//-------------------------------------------------------//
// class Pacman: public nsGraphics::IDrawable {
// public:
//     Pacman(const nsGraphics::Vec2D& position, string& direction, bool& isDefaultState, const Skin defaultsSkins, const Skin madSkins);
//
// }
#endif // BGTEXT_H
