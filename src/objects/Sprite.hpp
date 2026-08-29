#pragma once
#include "../color.hpp"
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
                  const Color &outlineColor = Color())
      : spriteImg(img) {
    srcX = srcY = 0;
    srcW = img.width();
    srcH = img.height();
  }

  Sprite(Image &img, int srcX, int srcY, int srcW, int srcH,
         int outlineWidth = 0, const Color &outlineColor = Color())
      : spriteImg(img) {
    this->srcX = srcX;
    this->srcY = srcY;
    this->srcW = srcW;
    this->srcH = srcH;
    this->outlineWidth = outlineWidth;
    this->outlineColor = outlineColor;
  }

  Sprite(const Sprite &copy) = default;

  ~Sprite() override = default;

  AbstractDrawableObject *copy() const override { return new Sprite(*this); }

  /**Draws this Sprite.
   * Disregards the Color attribute in favor of sprites colors.*/
  void draw(const Transform &t, Image &imgRef) const override {
    // Vertex order is as follows for the constructed quad.
    //  0--3   3
    //  | /   /|
    //  |/   / |
    //  1   1--2

    const int halfW = drawWidth / 2;
    const int halfH = drawHeight / 2;

    Point destPoints[4] = {
        {-halfW, halfH},  // 0
        {-halfW, -halfH}, // 1
        {halfW, -halfH},  // 2
        {halfW, halfH}    // 3
    };

    Point texturePoints[4] = {{srcX, srcY},
                              {srcX, srcY + srcH},
                              {srcX + srcW, srcY},
                              {srcX + srcW, srcY + srcH}};

    /**Transforms the set of destination points.*/
    for (Point &pt : destPoints)
      pt = t(pt);

    // Yes, I know this isn't particularly readable.
    // But its purpose is described in an above commented illustration.
    imgRef.draw_triangle(destPoints[0][0], destPoints[0][1], destPoints[1][0],
                         destPoints[1][1], destPoints[3][0], destPoints[3][1],
                         spriteImg, texturePoints[0][0], texturePoints[0][1],
                         texturePoints[1][0], texturePoints[1][1],
                         texturePoints[3][0], texturePoints[3][1]);
    imgRef.draw_triangle(destPoints[1][0], destPoints[1][1], destPoints[2][0],
                         destPoints[2][1], destPoints[3][0], destPoints[3][1],
                         spriteImg, texturePoints[1][0], texturePoints[1][1],
                         texturePoints[2][0], texturePoints[2][1],
                         texturePoints[3][0], texturePoints[3][1]);

    if (outlineWidth > 0) { // draw outline using previously generated points.
      // LineLoop impl
      for (int i = 1; i < 4; i++) {
        drawLine(imgRef, destPoints[i - 1][0], destPoints[i - 1][1],
                 destPoints[i][0], destPoints[i][1], outlineColor,
                 outlineWidth);
      }
      // draw last line between first and last
      drawLine(imgRef, destPoints[3][0], destPoints[3][1], destPoints[0][0],
               destPoints[0][1], outlineColor, outlineWidth);
    }
  }

protected:
  Image &spriteImg;
};
} // namespace cturtle
