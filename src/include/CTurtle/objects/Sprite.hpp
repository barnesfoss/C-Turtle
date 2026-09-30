#pragma once
#include "AbstractDrawableObject.hpp"
namespace cturtle {
/**\brief The Sprite class represents a selection of a larger image.
 * This class ignores color in favor of color provided by the image the sprite
 * corresponds to.
 */
class Sprite : public AbstractDrawableObject {
public:
  int srcX, srcY, srcW, srcH;
  int drawWidth = 0;
  int drawHeight = 0;

  explicit Sprite(Image &img, int outlineWidth = 0,
                  const Color &outlineColor = Color());

  Sprite(Image &img, int srcX, int srcY, int srcW, int srcH,
         int outlineWidth = 0, const Color &outlineColor = Color());

  Sprite(const Sprite &copy) = default;

  ~Sprite() override = default;

  AbstractDrawableObject *copy() const override;

  /**Draws this Sprite.
   * Disregards the Color attribute in favor of sprites colors.*/
  void draw(const Transform &t, Image &imgRef) const override;

protected:
  Image &spriteImg;
};
} // namespace cturtle
