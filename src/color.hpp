#pragma once
#include <chrono>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <thread>
#include <unordered_map>
namespace cturtle::detail {
typedef uint32_t color_int_t; // Alpha value is extra, serves as padding
typedef uint64_t time_t;
/**
 * Pack three bytes into an integer to represent a color at compile time.
 * @param r
 * @param g
 * @param b
 * @return
 */
inline constexpr color_int_t resolveColorInt(uint8_t r, uint8_t g,
                                             uint8_t b) noexcept {
  return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}

/**
 * Unpacks R, G, and B bytes to the specified pointer (assumes sequential
 * components).
 * @param pack
 * @param colorPtr
 */
inline void resolveColorComp(color_int_t pack, uint8_t &r, uint8_t &g,
                             uint8_t &b) {
  r = (pack & 0x00FF0000) >> 16; // Red
  g = (pack & 0x0000FF00) >> 8;  // Green
  b = (pack & 0x000000FF);       // >> 0;  //Blue
}

/**
 * Returns the total number of milliseconds elapsed since the UNIX epoch.
 * @return
 */
inline time_t epochTime() {
  return std::chrono::system_clock::now().time_since_epoch() /
         std::chrono::milliseconds(1);
}

/**\brief Sleeps the calling thread the specified amount of milliseconds.
 *\param ms The total number of milliseconds to sleep.*/
inline void sleep(long ms) {
  if (ms <= 0)
    return;
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

namespace col {
const detail::color_int_t alice_blue = detail::resolveColorInt(240, 248, 255);
const detail::color_int_t AliceBlue = detail::resolveColorInt(240, 248, 255);
const detail::color_int_t antique_white =
    detail::resolveColorInt(250, 235, 215);
const detail::color_int_t AntiqueWhite = detail::resolveColorInt(250, 235, 215);
const detail::color_int_t AntiqueWhite1 =
    detail::resolveColorInt(255, 239, 219);
const detail::color_int_t AntiqueWhite2 =
    detail::resolveColorInt(238, 223, 204);
const detail::color_int_t AntiqueWhite3 =
    detail::resolveColorInt(205, 192, 176);
const detail::color_int_t AntiqueWhite4 =
    detail::resolveColorInt(139, 131, 120);
const detail::color_int_t aquamarine = detail::resolveColorInt(127, 255, 212);
const detail::color_int_t aquamarine1 = detail::resolveColorInt(127, 255, 212);
const detail::color_int_t aquamarine2 = detail::resolveColorInt(118, 238, 198);
const detail::color_int_t aquamarine3 = detail::resolveColorInt(102, 205, 170);
const detail::color_int_t aquamarine4 = detail::resolveColorInt(69, 139, 116);
const detail::color_int_t azure = detail::resolveColorInt(240, 255, 255);
const detail::color_int_t azure1 = detail::resolveColorInt(240, 255, 255);
const detail::color_int_t azure2 = detail::resolveColorInt(224, 238, 238);
const detail::color_int_t azure3 = detail::resolveColorInt(193, 205, 205);
const detail::color_int_t azure4 = detail::resolveColorInt(131, 139, 139);
const detail::color_int_t beige = detail::resolveColorInt(245, 245, 220);
const detail::color_int_t bisque = detail::resolveColorInt(255, 228, 196);
const detail::color_int_t bisque1 = detail::resolveColorInt(255, 228, 196);
const detail::color_int_t bisque2 = detail::resolveColorInt(238, 213, 183);
const detail::color_int_t bisque3 = detail::resolveColorInt(205, 183, 158);
const detail::color_int_t bisque4 = detail::resolveColorInt(139, 125, 107);
const detail::color_int_t black = detail::resolveColorInt(0, 0, 0);
const detail::color_int_t blanched_almond =
    detail::resolveColorInt(255, 235, 205);
const detail::color_int_t BlanchedAlmond =
    detail::resolveColorInt(255, 235, 205);
const detail::color_int_t blue = detail::resolveColorInt(0, 0, 255);
const detail::color_int_t blue_violet = detail::resolveColorInt(138, 43, 226);
const detail::color_int_t blue1 = detail::resolveColorInt(0, 0, 255);
const detail::color_int_t blue2 = detail::resolveColorInt(0, 0, 238);
const detail::color_int_t blue3 = detail::resolveColorInt(0, 0, 205);
const detail::color_int_t blue4 = detail::resolveColorInt(0, 0, 139);
const detail::color_int_t BlueViolet = detail::resolveColorInt(138, 43, 226);
const detail::color_int_t brown = detail::resolveColorInt(165, 42, 42);
const detail::color_int_t brown1 = detail::resolveColorInt(255, 64, 64);
const detail::color_int_t brown2 = detail::resolveColorInt(238, 59, 59);
const detail::color_int_t brown3 = detail::resolveColorInt(205, 51, 51);
const detail::color_int_t brown4 = detail::resolveColorInt(139, 35, 35);
const detail::color_int_t burlywood = detail::resolveColorInt(222, 184, 135);
const detail::color_int_t burlywood1 = detail::resolveColorInt(255, 211, 155);
const detail::color_int_t burlywood2 = detail::resolveColorInt(238, 197, 145);
const detail::color_int_t burlywood3 = detail::resolveColorInt(205, 170, 125);
const detail::color_int_t burlywood4 = detail::resolveColorInt(139, 115, 85);
const detail::color_int_t cadet_blue = detail::resolveColorInt(95, 158, 160);
const detail::color_int_t CadetBlue = detail::resolveColorInt(95, 158, 160);
const detail::color_int_t CadetBlue1 = detail::resolveColorInt(152, 245, 255);
const detail::color_int_t CadetBlue2 = detail::resolveColorInt(142, 229, 238);
const detail::color_int_t CadetBlue3 = detail::resolveColorInt(122, 197, 205);
const detail::color_int_t CadetBlue4 = detail::resolveColorInt(83, 134, 139);
const detail::color_int_t chartreuse = detail::resolveColorInt(127, 255, 0);
const detail::color_int_t chartreuse1 = detail::resolveColorInt(127, 255, 0);
const detail::color_int_t chartreuse2 = detail::resolveColorInt(118, 238, 0);
const detail::color_int_t chartreuse3 = detail::resolveColorInt(102, 205, 0);
const detail::color_int_t chartreuse4 = detail::resolveColorInt(69, 139, 0);
const detail::color_int_t chocolate = detail::resolveColorInt(210, 105, 30);
const detail::color_int_t chocolate1 = detail::resolveColorInt(255, 127, 36);
const detail::color_int_t chocolate2 = detail::resolveColorInt(238, 118, 33);
const detail::color_int_t chocolate3 = detail::resolveColorInt(205, 102, 29);
const detail::color_int_t chocolate4 = detail::resolveColorInt(139, 69, 19);
const detail::color_int_t coral = detail::resolveColorInt(255, 127, 80);
const detail::color_int_t coral1 = detail::resolveColorInt(255, 114, 86);
const detail::color_int_t coral2 = detail::resolveColorInt(238, 106, 80);
const detail::color_int_t coral3 = detail::resolveColorInt(205, 91, 69);
const detail::color_int_t coral4 = detail::resolveColorInt(139, 62, 47);
const detail::color_int_t cornflower_blue =
    detail::resolveColorInt(100, 149, 237);
const detail::color_int_t CornflowerBlue =
    detail::resolveColorInt(100, 149, 237);
const detail::color_int_t cornsilk = detail::resolveColorInt(255, 248, 220);
const detail::color_int_t cornsilk1 = detail::resolveColorInt(255, 248, 220);
const detail::color_int_t cornsilk2 = detail::resolveColorInt(238, 232, 205);
const detail::color_int_t cornsilk3 = detail::resolveColorInt(205, 200, 177);
const detail::color_int_t cornsilk4 = detail::resolveColorInt(139, 136, 120);
const detail::color_int_t cyan = detail::resolveColorInt(0, 255, 255);
const detail::color_int_t cyan1 = detail::resolveColorInt(0, 255, 255);
const detail::color_int_t cyan2 = detail::resolveColorInt(0, 238, 238);
const detail::color_int_t cyan3 = detail::resolveColorInt(0, 205, 205);
const detail::color_int_t cyan4 = detail::resolveColorInt(0, 139, 139);
const detail::color_int_t dark_blue = detail::resolveColorInt(0, 0, 139);
const detail::color_int_t dark_cyan = detail::resolveColorInt(0, 139, 139);
const detail::color_int_t dark_goldenrod =
    detail::resolveColorInt(184, 134, 11);
const detail::color_int_t dark_gray = detail::resolveColorInt(169, 169, 169);
const detail::color_int_t dark_green = detail::resolveColorInt(0, 100, 0);
const detail::color_int_t dark_grey = detail::resolveColorInt(169, 169, 169);
const detail::color_int_t dark_khaki = detail::resolveColorInt(189, 183, 107);
const detail::color_int_t dark_magenta = detail::resolveColorInt(139, 0, 139);
const detail::color_int_t dark_olive_green =
    detail::resolveColorInt(85, 107, 47);
const detail::color_int_t dark_orange = detail::resolveColorInt(255, 140, 0);
const detail::color_int_t dark_orchid = detail::resolveColorInt(153, 50, 204);
const detail::color_int_t dark_red = detail::resolveColorInt(139, 0, 0);
const detail::color_int_t dark_salmon = detail::resolveColorInt(233, 150, 122);
const detail::color_int_t dark_sea_green =
    detail::resolveColorInt(143, 188, 143);
const detail::color_int_t dark_slate_blue =
    detail::resolveColorInt(72, 61, 139);
const detail::color_int_t dark_slate_gray = detail::resolveColorInt(47, 79, 79);
const detail::color_int_t dark_slate_grey = detail::resolveColorInt(47, 79, 79);
const detail::color_int_t dark_turquoise = detail::resolveColorInt(0, 206, 209);
const detail::color_int_t dark_violet = detail::resolveColorInt(148, 0, 211);
const detail::color_int_t DarkBlue = detail::resolveColorInt(0, 0, 139);
const detail::color_int_t DarkCyan = detail::resolveColorInt(0, 139, 139);
const detail::color_int_t DarkGoldenrod = detail::resolveColorInt(184, 134, 11);
const detail::color_int_t DarkGoldenrod1 =
    detail::resolveColorInt(255, 185, 15);
const detail::color_int_t DarkGoldenrod2 =
    detail::resolveColorInt(238, 173, 14);
const detail::color_int_t DarkGoldenrod3 =
    detail::resolveColorInt(205, 149, 12);
const detail::color_int_t DarkGoldenrod4 = detail::resolveColorInt(139, 101, 8);
const detail::color_int_t DarkGray = detail::resolveColorInt(169, 169, 169);
const detail::color_int_t DarkGreen = detail::resolveColorInt(0, 100, 0);
const detail::color_int_t DarkGrey = detail::resolveColorInt(169, 169, 169);
const detail::color_int_t DarkKhaki = detail::resolveColorInt(189, 183, 107);
const detail::color_int_t DarkMagenta = detail::resolveColorInt(139, 0, 139);
const detail::color_int_t DarkOliveGreen = detail::resolveColorInt(85, 107, 47);
const detail::color_int_t DarkOliveGreen1 =
    detail::resolveColorInt(202, 255, 112);
const detail::color_int_t DarkOliveGreen2 =
    detail::resolveColorInt(188, 238, 104);
const detail::color_int_t DarkOliveGreen3 =
    detail::resolveColorInt(162, 205, 90);
const detail::color_int_t DarkOliveGreen4 =
    detail::resolveColorInt(110, 139, 61);
const detail::color_int_t DarkOrange = detail::resolveColorInt(255, 140, 0);
const detail::color_int_t DarkOrange1 = detail::resolveColorInt(255, 127, 0);
const detail::color_int_t DarkOrange2 = detail::resolveColorInt(238, 118, 0);
const detail::color_int_t DarkOrange3 = detail::resolveColorInt(205, 102, 0);
const detail::color_int_t DarkOrange4 = detail::resolveColorInt(139, 69, 0);
const detail::color_int_t DarkOrchid = detail::resolveColorInt(153, 50, 204);
const detail::color_int_t DarkOrchid1 = detail::resolveColorInt(191, 62, 255);
const detail::color_int_t DarkOrchid2 = detail::resolveColorInt(178, 58, 238);
const detail::color_int_t DarkOrchid3 = detail::resolveColorInt(154, 50, 205);
const detail::color_int_t DarkOrchid4 = detail::resolveColorInt(104, 34, 139);
const detail::color_int_t DarkRed = detail::resolveColorInt(139, 0, 0);
const detail::color_int_t DarkSalmon = detail::resolveColorInt(233, 150, 122);
const detail::color_int_t DarkSeaGreen = detail::resolveColorInt(143, 188, 143);
const detail::color_int_t DarkSeaGreen1 =
    detail::resolveColorInt(193, 255, 193);
const detail::color_int_t DarkSeaGreen2 =
    detail::resolveColorInt(180, 238, 180);
const detail::color_int_t DarkSeaGreen3 =
    detail::resolveColorInt(155, 205, 155);
const detail::color_int_t DarkSeaGreen4 =
    detail::resolveColorInt(105, 139, 105);
const detail::color_int_t DarkSlateBlue = detail::resolveColorInt(72, 61, 139);
const detail::color_int_t DarkSlateGray = detail::resolveColorInt(47, 79, 79);
const detail::color_int_t DarkSlateGray1 =
    detail::resolveColorInt(151, 255, 255);
const detail::color_int_t DarkSlateGray2 =
    detail::resolveColorInt(141, 238, 238);
const detail::color_int_t DarkSlateGray3 =
    detail::resolveColorInt(121, 205, 205);
const detail::color_int_t DarkSlateGray4 =
    detail::resolveColorInt(82, 139, 139);
const detail::color_int_t DarkSlateGrey = detail::resolveColorInt(47, 79, 79);
const detail::color_int_t DarkTurquoise = detail::resolveColorInt(0, 206, 209);
const detail::color_int_t DarkViolet = detail::resolveColorInt(148, 0, 211);
const detail::color_int_t deep_pink = detail::resolveColorInt(255, 20, 147);
const detail::color_int_t deep_sky_blue = detail::resolveColorInt(0, 191, 255);
const detail::color_int_t DeepPink = detail::resolveColorInt(255, 20, 147);
const detail::color_int_t DeepPink1 = detail::resolveColorInt(255, 20, 147);
const detail::color_int_t DeepPink2 = detail::resolveColorInt(238, 18, 137);
const detail::color_int_t DeepPink3 = detail::resolveColorInt(205, 16, 118);
const detail::color_int_t DeepPink4 = detail::resolveColorInt(139, 10, 80);
const detail::color_int_t DeepSkyBlue = detail::resolveColorInt(0, 191, 255);
const detail::color_int_t DeepSkyBlue1 = detail::resolveColorInt(0, 191, 255);
const detail::color_int_t DeepSkyBlue2 = detail::resolveColorInt(0, 178, 238);
const detail::color_int_t DeepSkyBlue3 = detail::resolveColorInt(0, 154, 205);
const detail::color_int_t DeepSkyBlue4 = detail::resolveColorInt(0, 104, 139);
const detail::color_int_t dim_gray = detail::resolveColorInt(105, 105, 105);
const detail::color_int_t dim_grey = detail::resolveColorInt(105, 105, 105);
const detail::color_int_t DimGray = detail::resolveColorInt(105, 105, 105);
const detail::color_int_t DimGrey = detail::resolveColorInt(105, 105, 105);
const detail::color_int_t dodger_blue = detail::resolveColorInt(30, 144, 255);
const detail::color_int_t DodgerBlue = detail::resolveColorInt(30, 144, 255);
const detail::color_int_t DodgerBlue1 = detail::resolveColorInt(30, 144, 255);
const detail::color_int_t DodgerBlue2 = detail::resolveColorInt(28, 134, 238);
const detail::color_int_t DodgerBlue3 = detail::resolveColorInt(24, 116, 205);
const detail::color_int_t DodgerBlue4 = detail::resolveColorInt(16, 78, 139);
const detail::color_int_t firebrick = detail::resolveColorInt(178, 34, 34);
const detail::color_int_t firebrick1 = detail::resolveColorInt(255, 48, 48);
const detail::color_int_t firebrick2 = detail::resolveColorInt(238, 44, 44);
const detail::color_int_t firebrick3 = detail::resolveColorInt(205, 38, 38);
const detail::color_int_t firebrick4 = detail::resolveColorInt(139, 26, 26);
const detail::color_int_t floral_white = detail::resolveColorInt(255, 250, 240);
const detail::color_int_t FloralWhite = detail::resolveColorInt(255, 250, 240);
const detail::color_int_t forest_green = detail::resolveColorInt(34, 139, 34);
const detail::color_int_t ForestGreen = detail::resolveColorInt(34, 139, 34);
const detail::color_int_t gainsboro = detail::resolveColorInt(220, 220, 220);
const detail::color_int_t ghost_white = detail::resolveColorInt(248, 248, 255);
const detail::color_int_t GhostWhite = detail::resolveColorInt(248, 248, 255);
const detail::color_int_t gold = detail::resolveColorInt(255, 215, 0);
const detail::color_int_t gold1 = detail::resolveColorInt(255, 215, 0);
const detail::color_int_t gold2 = detail::resolveColorInt(238, 201, 0);
const detail::color_int_t gold3 = detail::resolveColorInt(205, 173, 0);
const detail::color_int_t gold4 = detail::resolveColorInt(139, 117, 0);
const detail::color_int_t goldenrod = detail::resolveColorInt(218, 165, 32);
const detail::color_int_t goldenrod1 = detail::resolveColorInt(255, 193, 37);
const detail::color_int_t goldenrod2 = detail::resolveColorInt(238, 180, 34);
const detail::color_int_t goldenrod3 = detail::resolveColorInt(205, 155, 29);
const detail::color_int_t goldenrod4 = detail::resolveColorInt(139, 105, 20);
const detail::color_int_t gray = detail::resolveColorInt(190, 190, 190);
const detail::color_int_t gray0 = detail::resolveColorInt(0, 0, 0);
const detail::color_int_t gray1 = detail::resolveColorInt(3, 3, 3);
const detail::color_int_t gray2 = detail::resolveColorInt(5, 5, 5);
const detail::color_int_t gray3 = detail::resolveColorInt(8, 8, 8);
const detail::color_int_t gray4 = detail::resolveColorInt(10, 10, 10);
const detail::color_int_t gray5 = detail::resolveColorInt(13, 13, 13);
const detail::color_int_t gray6 = detail::resolveColorInt(15, 15, 15);
const detail::color_int_t gray7 = detail::resolveColorInt(18, 18, 18);
const detail::color_int_t gray8 = detail::resolveColorInt(20, 20, 20);
const detail::color_int_t gray9 = detail::resolveColorInt(23, 23, 23);
const detail::color_int_t gray10 = detail::resolveColorInt(26, 26, 26);
const detail::color_int_t gray11 = detail::resolveColorInt(28, 28, 28);
const detail::color_int_t gray12 = detail::resolveColorInt(31, 31, 31);
const detail::color_int_t gray13 = detail::resolveColorInt(33, 33, 33);
const detail::color_int_t gray14 = detail::resolveColorInt(36, 36, 36);
const detail::color_int_t gray15 = detail::resolveColorInt(38, 38, 38);
const detail::color_int_t gray16 = detail::resolveColorInt(41, 41, 41);
const detail::color_int_t gray17 = detail::resolveColorInt(43, 43, 43);
const detail::color_int_t gray18 = detail::resolveColorInt(46, 46, 46);
const detail::color_int_t gray19 = detail::resolveColorInt(48, 48, 48);
const detail::color_int_t gray20 = detail::resolveColorInt(51, 51, 51);
const detail::color_int_t gray21 = detail::resolveColorInt(54, 54, 54);
const detail::color_int_t gray22 = detail::resolveColorInt(56, 56, 56);
const detail::color_int_t gray23 = detail::resolveColorInt(59, 59, 59);
const detail::color_int_t gray24 = detail::resolveColorInt(61, 61, 61);
const detail::color_int_t gray25 = detail::resolveColorInt(64, 64, 64);
const detail::color_int_t gray26 = detail::resolveColorInt(66, 66, 66);
const detail::color_int_t gray27 = detail::resolveColorInt(69, 69, 69);
const detail::color_int_t gray28 = detail::resolveColorInt(71, 71, 71);
const detail::color_int_t gray29 = detail::resolveColorInt(74, 74, 74);
const detail::color_int_t gray30 = detail::resolveColorInt(77, 77, 77);
const detail::color_int_t gray31 = detail::resolveColorInt(79, 79, 79);
const detail::color_int_t gray32 = detail::resolveColorInt(82, 82, 82);
const detail::color_int_t gray33 = detail::resolveColorInt(84, 84, 84);
const detail::color_int_t gray34 = detail::resolveColorInt(87, 87, 87);
const detail::color_int_t gray35 = detail::resolveColorInt(89, 89, 89);
const detail::color_int_t gray36 = detail::resolveColorInt(92, 92, 92);
const detail::color_int_t gray37 = detail::resolveColorInt(94, 94, 94);
const detail::color_int_t gray38 = detail::resolveColorInt(97, 97, 97);
const detail::color_int_t gray39 = detail::resolveColorInt(99, 99, 99);
const detail::color_int_t gray40 = detail::resolveColorInt(102, 102, 102);
const detail::color_int_t gray41 = detail::resolveColorInt(105, 105, 105);
const detail::color_int_t gray42 = detail::resolveColorInt(107, 107, 107);
const detail::color_int_t gray43 = detail::resolveColorInt(110, 110, 110);
const detail::color_int_t gray44 = detail::resolveColorInt(112, 112, 112);
const detail::color_int_t gray45 = detail::resolveColorInt(115, 115, 115);
const detail::color_int_t gray46 = detail::resolveColorInt(117, 117, 117);
const detail::color_int_t gray47 = detail::resolveColorInt(120, 120, 120);
const detail::color_int_t gray48 = detail::resolveColorInt(122, 122, 122);
const detail::color_int_t gray49 = detail::resolveColorInt(125, 125, 125);
const detail::color_int_t gray50 = detail::resolveColorInt(127, 127, 127);
const detail::color_int_t gray51 = detail::resolveColorInt(130, 130, 130);
const detail::color_int_t gray52 = detail::resolveColorInt(133, 133, 133);
const detail::color_int_t gray53 = detail::resolveColorInt(135, 135, 135);
const detail::color_int_t gray54 = detail::resolveColorInt(138, 138, 138);
const detail::color_int_t gray55 = detail::resolveColorInt(140, 140, 140);
const detail::color_int_t gray56 = detail::resolveColorInt(143, 143, 143);
const detail::color_int_t gray57 = detail::resolveColorInt(145, 145, 145);
const detail::color_int_t gray58 = detail::resolveColorInt(148, 148, 148);
const detail::color_int_t gray59 = detail::resolveColorInt(150, 150, 150);
const detail::color_int_t gray60 = detail::resolveColorInt(153, 153, 153);
const detail::color_int_t gray61 = detail::resolveColorInt(156, 156, 156);
const detail::color_int_t gray62 = detail::resolveColorInt(158, 158, 158);
const detail::color_int_t gray63 = detail::resolveColorInt(161, 161, 161);
const detail::color_int_t gray64 = detail::resolveColorInt(163, 163, 163);
const detail::color_int_t gray65 = detail::resolveColorInt(166, 166, 166);
const detail::color_int_t gray66 = detail::resolveColorInt(168, 168, 168);
const detail::color_int_t gray67 = detail::resolveColorInt(171, 171, 171);
const detail::color_int_t gray68 = detail::resolveColorInt(173, 173, 173);
const detail::color_int_t gray69 = detail::resolveColorInt(176, 176, 176);
const detail::color_int_t gray70 = detail::resolveColorInt(179, 179, 179);
const detail::color_int_t gray71 = detail::resolveColorInt(181, 181, 181);
const detail::color_int_t gray72 = detail::resolveColorInt(184, 184, 184);
const detail::color_int_t gray73 = detail::resolveColorInt(186, 186, 186);
const detail::color_int_t gray74 = detail::resolveColorInt(189, 189, 189);
const detail::color_int_t gray75 = detail::resolveColorInt(191, 191, 191);
const detail::color_int_t gray76 = detail::resolveColorInt(194, 194, 194);
const detail::color_int_t gray77 = detail::resolveColorInt(196, 196, 196);
const detail::color_int_t gray78 = detail::resolveColorInt(199, 199, 199);
const detail::color_int_t gray79 = detail::resolveColorInt(201, 201, 201);
const detail::color_int_t gray80 = detail::resolveColorInt(204, 204, 204);
const detail::color_int_t gray81 = detail::resolveColorInt(207, 207, 207);
const detail::color_int_t gray82 = detail::resolveColorInt(209, 209, 209);
const detail::color_int_t gray83 = detail::resolveColorInt(212, 212, 212);
const detail::color_int_t gray84 = detail::resolveColorInt(214, 214, 214);
const detail::color_int_t gray85 = detail::resolveColorInt(217, 217, 217);
const detail::color_int_t gray86 = detail::resolveColorInt(219, 219, 219);
const detail::color_int_t gray87 = detail::resolveColorInt(222, 222, 222);
const detail::color_int_t gray88 = detail::resolveColorInt(224, 224, 224);
const detail::color_int_t gray89 = detail::resolveColorInt(227, 227, 227);
const detail::color_int_t gray90 = detail::resolveColorInt(229, 229, 229);
const detail::color_int_t gray91 = detail::resolveColorInt(232, 232, 232);
const detail::color_int_t gray92 = detail::resolveColorInt(235, 235, 235);
const detail::color_int_t gray93 = detail::resolveColorInt(237, 237, 237);
const detail::color_int_t gray94 = detail::resolveColorInt(240, 240, 240);
const detail::color_int_t gray95 = detail::resolveColorInt(242, 242, 242);
const detail::color_int_t gray96 = detail::resolveColorInt(245, 245, 245);
const detail::color_int_t gray97 = detail::resolveColorInt(247, 247, 247);
const detail::color_int_t gray98 = detail::resolveColorInt(250, 250, 250);
const detail::color_int_t gray99 = detail::resolveColorInt(252, 252, 252);
const detail::color_int_t gray100 = detail::resolveColorInt(255, 255, 255);
const detail::color_int_t green = detail::resolveColorInt(0, 255, 0);
const detail::color_int_t green_yellow = detail::resolveColorInt(173, 255, 47);
const detail::color_int_t green1 = detail::resolveColorInt(0, 255, 0);
const detail::color_int_t green2 = detail::resolveColorInt(0, 238, 0);
const detail::color_int_t green3 = detail::resolveColorInt(0, 205, 0);
const detail::color_int_t green4 = detail::resolveColorInt(0, 139, 0);
const detail::color_int_t GreenYellow = detail::resolveColorInt(173, 255, 47);
const detail::color_int_t grey = detail::resolveColorInt(190, 190, 190);
const detail::color_int_t grey0 = detail::resolveColorInt(0, 0, 0);
const detail::color_int_t grey1 = detail::resolveColorInt(3, 3, 3);
const detail::color_int_t grey2 = detail::resolveColorInt(5, 5, 5);
const detail::color_int_t grey3 = detail::resolveColorInt(8, 8, 8);
const detail::color_int_t grey4 = detail::resolveColorInt(10, 10, 10);
const detail::color_int_t grey5 = detail::resolveColorInt(13, 13, 13);
const detail::color_int_t grey6 = detail::resolveColorInt(15, 15, 15);
const detail::color_int_t grey7 = detail::resolveColorInt(18, 18, 18);
const detail::color_int_t grey8 = detail::resolveColorInt(20, 20, 20);
const detail::color_int_t grey9 = detail::resolveColorInt(23, 23, 23);
const detail::color_int_t grey10 = detail::resolveColorInt(26, 26, 26);
const detail::color_int_t grey11 = detail::resolveColorInt(28, 28, 28);
const detail::color_int_t grey12 = detail::resolveColorInt(31, 31, 31);
const detail::color_int_t grey13 = detail::resolveColorInt(33, 33, 33);
const detail::color_int_t grey14 = detail::resolveColorInt(36, 36, 36);
const detail::color_int_t grey15 = detail::resolveColorInt(38, 38, 38);
const detail::color_int_t grey16 = detail::resolveColorInt(41, 41, 41);
const detail::color_int_t grey17 = detail::resolveColorInt(43, 43, 43);
const detail::color_int_t grey18 = detail::resolveColorInt(46, 46, 46);
const detail::color_int_t grey19 = detail::resolveColorInt(48, 48, 48);
const detail::color_int_t grey20 = detail::resolveColorInt(51, 51, 51);
const detail::color_int_t grey21 = detail::resolveColorInt(54, 54, 54);
const detail::color_int_t grey22 = detail::resolveColorInt(56, 56, 56);
const detail::color_int_t grey23 = detail::resolveColorInt(59, 59, 59);
const detail::color_int_t grey24 = detail::resolveColorInt(61, 61, 61);
const detail::color_int_t grey25 = detail::resolveColorInt(64, 64, 64);
const detail::color_int_t grey26 = detail::resolveColorInt(66, 66, 66);
const detail::color_int_t grey27 = detail::resolveColorInt(69, 69, 69);
const detail::color_int_t grey28 = detail::resolveColorInt(71, 71, 71);
const detail::color_int_t grey29 = detail::resolveColorInt(74, 74, 74);
const detail::color_int_t grey30 = detail::resolveColorInt(77, 77, 77);
const detail::color_int_t grey31 = detail::resolveColorInt(79, 79, 79);
const detail::color_int_t grey32 = detail::resolveColorInt(82, 82, 82);
const detail::color_int_t grey33 = detail::resolveColorInt(84, 84, 84);
const detail::color_int_t grey34 = detail::resolveColorInt(87, 87, 87);
const detail::color_int_t grey35 = detail::resolveColorInt(89, 89, 89);
const detail::color_int_t grey36 = detail::resolveColorInt(92, 92, 92);
const detail::color_int_t grey37 = detail::resolveColorInt(94, 94, 94);
const detail::color_int_t grey38 = detail::resolveColorInt(97, 97, 97);
const detail::color_int_t grey39 = detail::resolveColorInt(99, 99, 99);
const detail::color_int_t grey40 = detail::resolveColorInt(102, 102, 102);
const detail::color_int_t grey41 = detail::resolveColorInt(105, 105, 105);
const detail::color_int_t grey42 = detail::resolveColorInt(107, 107, 107);
const detail::color_int_t grey43 = detail::resolveColorInt(110, 110, 110);
const detail::color_int_t grey44 = detail::resolveColorInt(112, 112, 112);
const detail::color_int_t grey45 = detail::resolveColorInt(115, 115, 115);
const detail::color_int_t grey46 = detail::resolveColorInt(117, 117, 117);
const detail::color_int_t grey47 = detail::resolveColorInt(120, 120, 120);
const detail::color_int_t grey48 = detail::resolveColorInt(122, 122, 122);
const detail::color_int_t grey49 = detail::resolveColorInt(125, 125, 125);
const detail::color_int_t grey50 = detail::resolveColorInt(127, 127, 127);
const detail::color_int_t grey51 = detail::resolveColorInt(130, 130, 130);
const detail::color_int_t grey52 = detail::resolveColorInt(133, 133, 133);
const detail::color_int_t grey53 = detail::resolveColorInt(135, 135, 135);
const detail::color_int_t grey54 = detail::resolveColorInt(138, 138, 138);
const detail::color_int_t grey55 = detail::resolveColorInt(140, 140, 140);
const detail::color_int_t grey56 = detail::resolveColorInt(143, 143, 143);
const detail::color_int_t grey57 = detail::resolveColorInt(145, 145, 145);
const detail::color_int_t grey58 = detail::resolveColorInt(148, 148, 148);
const detail::color_int_t grey59 = detail::resolveColorInt(150, 150, 150);
const detail::color_int_t grey60 = detail::resolveColorInt(153, 153, 153);
const detail::color_int_t grey61 = detail::resolveColorInt(156, 156, 156);
const detail::color_int_t grey62 = detail::resolveColorInt(158, 158, 158);
const detail::color_int_t grey63 = detail::resolveColorInt(161, 161, 161);
const detail::color_int_t grey64 = detail::resolveColorInt(163, 163, 163);
const detail::color_int_t grey65 = detail::resolveColorInt(166, 166, 166);
const detail::color_int_t grey66 = detail::resolveColorInt(168, 168, 168);
const detail::color_int_t grey67 = detail::resolveColorInt(171, 171, 171);
const detail::color_int_t grey68 = detail::resolveColorInt(173, 173, 173);
const detail::color_int_t grey69 = detail::resolveColorInt(176, 176, 176);
const detail::color_int_t grey70 = detail::resolveColorInt(179, 179, 179);
const detail::color_int_t grey71 = detail::resolveColorInt(181, 181, 181);
const detail::color_int_t grey72 = detail::resolveColorInt(184, 184, 184);
const detail::color_int_t grey73 = detail::resolveColorInt(186, 186, 186);
const detail::color_int_t grey74 = detail::resolveColorInt(189, 189, 189);
const detail::color_int_t grey75 = detail::resolveColorInt(191, 191, 191);
const detail::color_int_t grey76 = detail::resolveColorInt(194, 194, 194);
const detail::color_int_t grey77 = detail::resolveColorInt(196, 196, 196);
const detail::color_int_t grey78 = detail::resolveColorInt(199, 199, 199);
const detail::color_int_t grey79 = detail::resolveColorInt(201, 201, 201);
const detail::color_int_t grey80 = detail::resolveColorInt(204, 204, 204);
const detail::color_int_t grey81 = detail::resolveColorInt(207, 207, 207);
const detail::color_int_t grey82 = detail::resolveColorInt(209, 209, 209);
const detail::color_int_t grey83 = detail::resolveColorInt(212, 212, 212);
const detail::color_int_t grey84 = detail::resolveColorInt(214, 214, 214);
const detail::color_int_t grey85 = detail::resolveColorInt(217, 217, 217);
const detail::color_int_t grey86 = detail::resolveColorInt(219, 219, 219);
const detail::color_int_t grey87 = detail::resolveColorInt(222, 222, 222);
const detail::color_int_t grey88 = detail::resolveColorInt(224, 224, 224);
const detail::color_int_t grey89 = detail::resolveColorInt(227, 227, 227);
const detail::color_int_t grey90 = detail::resolveColorInt(229, 229, 229);
const detail::color_int_t grey91 = detail::resolveColorInt(232, 232, 232);
const detail::color_int_t grey92 = detail::resolveColorInt(235, 235, 235);
const detail::color_int_t grey93 = detail::resolveColorInt(237, 237, 237);
const detail::color_int_t grey94 = detail::resolveColorInt(240, 240, 240);
const detail::color_int_t grey95 = detail::resolveColorInt(242, 242, 242);
const detail::color_int_t grey96 = detail::resolveColorInt(245, 245, 245);
const detail::color_int_t grey97 = detail::resolveColorInt(247, 247, 247);
const detail::color_int_t grey98 = detail::resolveColorInt(250, 250, 250);
const detail::color_int_t grey99 = detail::resolveColorInt(252, 252, 252);
const detail::color_int_t grey100 = detail::resolveColorInt(255, 255, 255);
const detail::color_int_t honeydew = detail::resolveColorInt(240, 255, 240);
const detail::color_int_t honeydew1 = detail::resolveColorInt(240, 255, 240);
const detail::color_int_t honeydew2 = detail::resolveColorInt(224, 238, 224);
const detail::color_int_t honeydew3 = detail::resolveColorInt(193, 205, 193);
const detail::color_int_t honeydew4 = detail::resolveColorInt(131, 139, 131);
const detail::color_int_t hot_pink = detail::resolveColorInt(255, 105, 180);
const detail::color_int_t HotPink = detail::resolveColorInt(255, 105, 180);
const detail::color_int_t HotPink1 = detail::resolveColorInt(255, 110, 180);
const detail::color_int_t HotPink2 = detail::resolveColorInt(238, 106, 167);
const detail::color_int_t HotPink3 = detail::resolveColorInt(205, 96, 144);
const detail::color_int_t HotPink4 = detail::resolveColorInt(139, 58, 98);
const detail::color_int_t indian_red = detail::resolveColorInt(205, 92, 92);
const detail::color_int_t IndianRed = detail::resolveColorInt(205, 92, 92);
const detail::color_int_t IndianRed1 = detail::resolveColorInt(255, 106, 106);
const detail::color_int_t IndianRed2 = detail::resolveColorInt(238, 99, 99);
const detail::color_int_t IndianRed3 = detail::resolveColorInt(205, 85, 85);
const detail::color_int_t IndianRed4 = detail::resolveColorInt(139, 58, 58);
const detail::color_int_t ivory = detail::resolveColorInt(255, 255, 240);
const detail::color_int_t ivory1 = detail::resolveColorInt(255, 255, 240);
const detail::color_int_t ivory2 = detail::resolveColorInt(238, 238, 224);
const detail::color_int_t ivory3 = detail::resolveColorInt(205, 205, 193);
const detail::color_int_t ivory4 = detail::resolveColorInt(139, 139, 131);
const detail::color_int_t khaki = detail::resolveColorInt(240, 230, 140);
const detail::color_int_t khaki1 = detail::resolveColorInt(255, 246, 143);
const detail::color_int_t khaki2 = detail::resolveColorInt(238, 230, 133);
const detail::color_int_t khaki3 = detail::resolveColorInt(205, 198, 115);
const detail::color_int_t khaki4 = detail::resolveColorInt(139, 134, 78);
const detail::color_int_t lavender = detail::resolveColorInt(230, 230, 250);
const detail::color_int_t lavender_blush =
    detail::resolveColorInt(255, 240, 245);
const detail::color_int_t LavenderBlush =
    detail::resolveColorInt(255, 240, 245);
const detail::color_int_t LavenderBlush1 =
    detail::resolveColorInt(255, 240, 245);
const detail::color_int_t LavenderBlush2 =
    detail::resolveColorInt(238, 224, 229);
const detail::color_int_t LavenderBlush3 =
    detail::resolveColorInt(205, 193, 197);
const detail::color_int_t LavenderBlush4 =
    detail::resolveColorInt(139, 131, 134);
const detail::color_int_t lawn_green = detail::resolveColorInt(124, 252, 0);
const detail::color_int_t LawnGreen = detail::resolveColorInt(124, 252, 0);
const detail::color_int_t lemon_chiffon =
    detail::resolveColorInt(255, 250, 205);
const detail::color_int_t LemonChiffon = detail::resolveColorInt(255, 250, 205);
const detail::color_int_t LemonChiffon1 =
    detail::resolveColorInt(255, 250, 205);
const detail::color_int_t LemonChiffon2 =
    detail::resolveColorInt(238, 233, 191);
const detail::color_int_t LemonChiffon3 =
    detail::resolveColorInt(205, 201, 165);
const detail::color_int_t LemonChiffon4 =
    detail::resolveColorInt(139, 137, 112);
const detail::color_int_t light_blue = detail::resolveColorInt(173, 216, 230);
const detail::color_int_t light_coral = detail::resolveColorInt(240, 128, 128);
const detail::color_int_t light_cyan = detail::resolveColorInt(224, 255, 255);
const detail::color_int_t light_goldenrod =
    detail::resolveColorInt(238, 221, 130);
const detail::color_int_t light_goldenrod_yellow =
    detail::resolveColorInt(250, 250, 210);
const detail::color_int_t light_gray = detail::resolveColorInt(211, 211, 211);
const detail::color_int_t light_green = detail::resolveColorInt(144, 238, 144);
const detail::color_int_t light_grey = detail::resolveColorInt(211, 211, 211);
const detail::color_int_t light_pink = detail::resolveColorInt(255, 182, 193);
const detail::color_int_t light_salmon = detail::resolveColorInt(255, 160, 122);
const detail::color_int_t light_sea_green =
    detail::resolveColorInt(32, 178, 170);
const detail::color_int_t light_sky_blue =
    detail::resolveColorInt(135, 206, 250);
const detail::color_int_t light_slate_blue =
    detail::resolveColorInt(132, 112, 255);
const detail::color_int_t light_slate_gray =
    detail::resolveColorInt(119, 136, 153);
const detail::color_int_t light_slate_grey =
    detail::resolveColorInt(119, 136, 153);
const detail::color_int_t light_steel_blue =
    detail::resolveColorInt(176, 196, 222);
const detail::color_int_t light_yellow = detail::resolveColorInt(255, 255, 224);
const detail::color_int_t LightBlue = detail::resolveColorInt(173, 216, 230);
const detail::color_int_t LightBlue1 = detail::resolveColorInt(191, 239, 255);
const detail::color_int_t LightBlue2 = detail::resolveColorInt(178, 223, 238);
const detail::color_int_t LightBlue3 = detail::resolveColorInt(154, 192, 205);
const detail::color_int_t LightBlue4 = detail::resolveColorInt(104, 131, 139);
const detail::color_int_t LightCoral = detail::resolveColorInt(240, 128, 128);
const detail::color_int_t LightCyan = detail::resolveColorInt(224, 255, 255);
const detail::color_int_t LightCyan1 = detail::resolveColorInt(224, 255, 255);
const detail::color_int_t LightCyan2 = detail::resolveColorInt(209, 238, 238);
const detail::color_int_t LightCyan3 = detail::resolveColorInt(180, 205, 205);
const detail::color_int_t LightCyan4 = detail::resolveColorInt(122, 139, 139);
const detail::color_int_t LightGoldenrod =
    detail::resolveColorInt(238, 221, 130);
const detail::color_int_t LightGoldenrod1 =
    detail::resolveColorInt(255, 236, 139);
const detail::color_int_t LightGoldenrod2 =
    detail::resolveColorInt(238, 220, 130);
const detail::color_int_t LightGoldenrod3 =
    detail::resolveColorInt(205, 190, 112);
const detail::color_int_t LightGoldenrod4 =
    detail::resolveColorInt(139, 129, 76);
const detail::color_int_t LightGoldenrodYellow =
    detail::resolveColorInt(250, 250, 210);
const detail::color_int_t LightGray = detail::resolveColorInt(211, 211, 211);
const detail::color_int_t LightGreen = detail::resolveColorInt(144, 238, 144);
const detail::color_int_t LightGrey = detail::resolveColorInt(211, 211, 211);
const detail::color_int_t LightPink = detail::resolveColorInt(255, 182, 193);
const detail::color_int_t LightPink1 = detail::resolveColorInt(255, 174, 185);
const detail::color_int_t LightPink2 = detail::resolveColorInt(238, 162, 173);
const detail::color_int_t LightPink3 = detail::resolveColorInt(205, 140, 149);
const detail::color_int_t LightPink4 = detail::resolveColorInt(139, 95, 101);
const detail::color_int_t LightSalmon = detail::resolveColorInt(255, 160, 122);
const detail::color_int_t LightSalmon1 = detail::resolveColorInt(255, 160, 122);
const detail::color_int_t LightSalmon2 = detail::resolveColorInt(238, 149, 114);
const detail::color_int_t LightSalmon3 = detail::resolveColorInt(205, 129, 98);
const detail::color_int_t LightSalmon4 = detail::resolveColorInt(139, 87, 66);
const detail::color_int_t LightSeaGreen = detail::resolveColorInt(32, 178, 170);
const detail::color_int_t LightSkyBlue = detail::resolveColorInt(135, 206, 250);
const detail::color_int_t LightSkyBlue1 =
    detail::resolveColorInt(176, 226, 255);
const detail::color_int_t LightSkyBlue2 =
    detail::resolveColorInt(164, 211, 238);
const detail::color_int_t LightSkyBlue3 =
    detail::resolveColorInt(141, 182, 205);
const detail::color_int_t LightSkyBlue4 = detail::resolveColorInt(96, 123, 139);
const detail::color_int_t LightSlateBlue =
    detail::resolveColorInt(132, 112, 255);
const detail::color_int_t LightSlateGray =
    detail::resolveColorInt(119, 136, 153);
const detail::color_int_t LightSlateGrey =
    detail::resolveColorInt(119, 136, 153);
const detail::color_int_t LightSteelBlue =
    detail::resolveColorInt(176, 196, 222);
const detail::color_int_t LightSteelBlue1 =
    detail::resolveColorInt(202, 225, 255);
const detail::color_int_t LightSteelBlue2 =
    detail::resolveColorInt(188, 210, 238);
const detail::color_int_t LightSteelBlue3 =
    detail::resolveColorInt(162, 181, 205);
const detail::color_int_t LightSteelBlue4 =
    detail::resolveColorInt(110, 123, 139);
const detail::color_int_t LightYellow = detail::resolveColorInt(255, 255, 224);
const detail::color_int_t LightYellow1 = detail::resolveColorInt(255, 255, 224);
const detail::color_int_t LightYellow2 = detail::resolveColorInt(238, 238, 209);
const detail::color_int_t LightYellow3 = detail::resolveColorInt(205, 205, 180);
const detail::color_int_t LightYellow4 = detail::resolveColorInt(139, 139, 122);
const detail::color_int_t lime_green = detail::resolveColorInt(50, 205, 50);
const detail::color_int_t LimeGreen = detail::resolveColorInt(50, 205, 50);
const detail::color_int_t linen = detail::resolveColorInt(250, 240, 230);
const detail::color_int_t magenta = detail::resolveColorInt(255, 0, 255);
const detail::color_int_t magenta1 = detail::resolveColorInt(255, 0, 255);
const detail::color_int_t magenta2 = detail::resolveColorInt(238, 0, 238);
const detail::color_int_t magenta3 = detail::resolveColorInt(205, 0, 205);
const detail::color_int_t magenta4 = detail::resolveColorInt(139, 0, 139);
const detail::color_int_t maroon = detail::resolveColorInt(176, 48, 96);
const detail::color_int_t maroon1 = detail::resolveColorInt(255, 52, 179);
const detail::color_int_t maroon2 = detail::resolveColorInt(238, 48, 167);
const detail::color_int_t maroon3 = detail::resolveColorInt(205, 41, 144);
const detail::color_int_t maroon4 = detail::resolveColorInt(139, 28, 98);
const detail::color_int_t medium_aquamarine =
    detail::resolveColorInt(102, 205, 170);
const detail::color_int_t medium_blue = detail::resolveColorInt(0, 0, 205);
const detail::color_int_t medium_orchid = detail::resolveColorInt(186, 85, 211);
const detail::color_int_t medium_purple =
    detail::resolveColorInt(147, 112, 219);
const detail::color_int_t medium_sea_green =
    detail::resolveColorInt(60, 179, 113);
const detail::color_int_t medium_slate_blue =
    detail::resolveColorInt(123, 104, 238);
const detail::color_int_t medium_spring_green =
    detail::resolveColorInt(0, 250, 154);
const detail::color_int_t medium_turquoise =
    detail::resolveColorInt(72, 209, 204);
const detail::color_int_t medium_violet_red =
    detail::resolveColorInt(199, 21, 133);
const detail::color_int_t MediumAquamarine =
    detail::resolveColorInt(102, 205, 170);
const detail::color_int_t MediumBlue = detail::resolveColorInt(0, 0, 205);
const detail::color_int_t MediumOrchid = detail::resolveColorInt(186, 85, 211);
const detail::color_int_t MediumOrchid1 =
    detail::resolveColorInt(224, 102, 255);
const detail::color_int_t MediumOrchid2 = detail::resolveColorInt(209, 95, 238);
const detail::color_int_t MediumOrchid3 = detail::resolveColorInt(180, 82, 205);
const detail::color_int_t MediumOrchid4 = detail::resolveColorInt(122, 55, 139);
const detail::color_int_t MediumPurple = detail::resolveColorInt(147, 112, 219);
const detail::color_int_t MediumPurple1 =
    detail::resolveColorInt(171, 130, 255);
const detail::color_int_t MediumPurple2 =
    detail::resolveColorInt(159, 121, 238);
const detail::color_int_t MediumPurple3 =
    detail::resolveColorInt(137, 104, 205);
const detail::color_int_t MediumPurple4 = detail::resolveColorInt(93, 71, 139);
const detail::color_int_t MediumSeaGreen =
    detail::resolveColorInt(60, 179, 113);
const detail::color_int_t MediumSlateBlue =
    detail::resolveColorInt(123, 104, 238);
const detail::color_int_t MediumSpringGreen =
    detail::resolveColorInt(0, 250, 154);
const detail::color_int_t MediumTurquoise =
    detail::resolveColorInt(72, 209, 204);
const detail::color_int_t MediumVioletRed =
    detail::resolveColorInt(199, 21, 133);
const detail::color_int_t midnight_blue = detail::resolveColorInt(25, 25, 112);
const detail::color_int_t MidnightBlue = detail::resolveColorInt(25, 25, 112);
const detail::color_int_t mint_cream = detail::resolveColorInt(245, 255, 250);
const detail::color_int_t MintCream = detail::resolveColorInt(245, 255, 250);
const detail::color_int_t misty_rose = detail::resolveColorInt(255, 228, 225);
const detail::color_int_t MistyRose = detail::resolveColorInt(255, 228, 225);
const detail::color_int_t MistyRose1 = detail::resolveColorInt(255, 228, 225);
const detail::color_int_t MistyRose2 = detail::resolveColorInt(238, 213, 210);
const detail::color_int_t MistyRose3 = detail::resolveColorInt(205, 183, 181);
const detail::color_int_t MistyRose4 = detail::resolveColorInt(139, 125, 123);
const detail::color_int_t moccasin = detail::resolveColorInt(255, 228, 181);
const detail::color_int_t navajo_white = detail::resolveColorInt(255, 222, 173);
const detail::color_int_t NavajoWhite = detail::resolveColorInt(255, 222, 173);
const detail::color_int_t NavajoWhite1 = detail::resolveColorInt(255, 222, 173);
const detail::color_int_t NavajoWhite2 = detail::resolveColorInt(238, 207, 161);
const detail::color_int_t NavajoWhite3 = detail::resolveColorInt(205, 179, 139);
const detail::color_int_t NavajoWhite4 = detail::resolveColorInt(139, 121, 94);
const detail::color_int_t navy = detail::resolveColorInt(0, 0, 128);
const detail::color_int_t navy_blue = detail::resolveColorInt(0, 0, 128);
const detail::color_int_t NavyBlue = detail::resolveColorInt(0, 0, 128);
const detail::color_int_t old_lace = detail::resolveColorInt(253, 245, 230);
const detail::color_int_t OldLace = detail::resolveColorInt(253, 245, 230);
const detail::color_int_t olive_drab = detail::resolveColorInt(107, 142, 35);
const detail::color_int_t OliveDrab = detail::resolveColorInt(107, 142, 35);
const detail::color_int_t OliveDrab1 = detail::resolveColorInt(192, 255, 62);
const detail::color_int_t OliveDrab2 = detail::resolveColorInt(179, 238, 58);
const detail::color_int_t OliveDrab3 = detail::resolveColorInt(154, 205, 50);
const detail::color_int_t OliveDrab4 = detail::resolveColorInt(105, 139, 34);
const detail::color_int_t orange = detail::resolveColorInt(255, 165, 0);
const detail::color_int_t orange_red = detail::resolveColorInt(255, 69, 0);
const detail::color_int_t orange1 = detail::resolveColorInt(255, 165, 0);
const detail::color_int_t orange2 = detail::resolveColorInt(238, 154, 0);
const detail::color_int_t orange3 = detail::resolveColorInt(205, 133, 0);
const detail::color_int_t orange4 = detail::resolveColorInt(139, 90, 0);
const detail::color_int_t OrangeRed = detail::resolveColorInt(255, 69, 0);
const detail::color_int_t OrangeRed1 = detail::resolveColorInt(255, 69, 0);
const detail::color_int_t OrangeRed2 = detail::resolveColorInt(238, 64, 0);
const detail::color_int_t OrangeRed3 = detail::resolveColorInt(205, 55, 0);
const detail::color_int_t OrangeRed4 = detail::resolveColorInt(139, 37, 0);
const detail::color_int_t orchid = detail::resolveColorInt(218, 112, 214);
const detail::color_int_t orchid1 = detail::resolveColorInt(255, 131, 250);
const detail::color_int_t orchid2 = detail::resolveColorInt(238, 122, 233);
const detail::color_int_t orchid3 = detail::resolveColorInt(205, 105, 201);
const detail::color_int_t orchid4 = detail::resolveColorInt(139, 71, 137);
const detail::color_int_t pale_goldenrod =
    detail::resolveColorInt(238, 232, 170);
const detail::color_int_t pale_green = detail::resolveColorInt(152, 251, 152);
const detail::color_int_t pale_turquoise =
    detail::resolveColorInt(175, 238, 238);
const detail::color_int_t pale_violet_red =
    detail::resolveColorInt(219, 112, 147);
const detail::color_int_t PaleGoldenrod =
    detail::resolveColorInt(238, 232, 170);
const detail::color_int_t PaleGreen = detail::resolveColorInt(152, 251, 152);
const detail::color_int_t PaleGreen1 = detail::resolveColorInt(154, 255, 154);
const detail::color_int_t PaleGreen2 = detail::resolveColorInt(144, 238, 144);
const detail::color_int_t PaleGreen3 = detail::resolveColorInt(124, 205, 124);
const detail::color_int_t PaleGreen4 = detail::resolveColorInt(84, 139, 84);
const detail::color_int_t PaleTurquoise =
    detail::resolveColorInt(175, 238, 238);
const detail::color_int_t PaleTurquoise1 =
    detail::resolveColorInt(187, 255, 255);
const detail::color_int_t PaleTurquoise2 =
    detail::resolveColorInt(174, 238, 238);
const detail::color_int_t PaleTurquoise3 =
    detail::resolveColorInt(150, 205, 205);
const detail::color_int_t PaleTurquoise4 =
    detail::resolveColorInt(102, 139, 139);
const detail::color_int_t PaleVioletRed =
    detail::resolveColorInt(219, 112, 147);
const detail::color_int_t PaleVioletRed1 =
    detail::resolveColorInt(255, 130, 171);
const detail::color_int_t PaleVioletRed2 =
    detail::resolveColorInt(238, 121, 159);
const detail::color_int_t PaleVioletRed3 =
    detail::resolveColorInt(205, 104, 127);
const detail::color_int_t PaleVioletRed4 = detail::resolveColorInt(139, 71, 93);
const detail::color_int_t papaya_whip = detail::resolveColorInt(255, 239, 213);
const detail::color_int_t PapayaWhip = detail::resolveColorInt(255, 239, 213);
const detail::color_int_t peach_puff = detail::resolveColorInt(255, 218, 185);
const detail::color_int_t PeachPuff = detail::resolveColorInt(255, 218, 185);
const detail::color_int_t PeachPuff1 = detail::resolveColorInt(255, 218, 185);
const detail::color_int_t PeachPuff2 = detail::resolveColorInt(238, 203, 173);
const detail::color_int_t PeachPuff3 = detail::resolveColorInt(205, 175, 149);
const detail::color_int_t PeachPuff4 = detail::resolveColorInt(139, 119, 101);
const detail::color_int_t peru = detail::resolveColorInt(205, 133, 63);
const detail::color_int_t pink = detail::resolveColorInt(255, 192, 203);
const detail::color_int_t pink1 = detail::resolveColorInt(255, 181, 197);
const detail::color_int_t pink2 = detail::resolveColorInt(238, 169, 184);
const detail::color_int_t pink3 = detail::resolveColorInt(205, 145, 158);
const detail::color_int_t pink4 = detail::resolveColorInt(139, 99, 108);
const detail::color_int_t plum = detail::resolveColorInt(221, 160, 221);
const detail::color_int_t plum1 = detail::resolveColorInt(255, 187, 255);
const detail::color_int_t plum2 = detail::resolveColorInt(238, 174, 238);
const detail::color_int_t plum3 = detail::resolveColorInt(205, 150, 205);
const detail::color_int_t plum4 = detail::resolveColorInt(139, 102, 139);
const detail::color_int_t powder_blue = detail::resolveColorInt(176, 224, 230);
const detail::color_int_t PowderBlue = detail::resolveColorInt(176, 224, 230);
const detail::color_int_t purple = detail::resolveColorInt(160, 32, 240);
const detail::color_int_t purple1 = detail::resolveColorInt(155, 48, 255);
const detail::color_int_t purple2 = detail::resolveColorInt(145, 44, 238);
const detail::color_int_t purple3 = detail::resolveColorInt(125, 38, 205);
const detail::color_int_t purple4 = detail::resolveColorInt(85, 26, 139);
const detail::color_int_t red = detail::resolveColorInt(255, 0, 0);
const detail::color_int_t red1 = detail::resolveColorInt(255, 0, 0);
const detail::color_int_t red2 = detail::resolveColorInt(238, 0, 0);
const detail::color_int_t red3 = detail::resolveColorInt(205, 0, 0);
const detail::color_int_t red4 = detail::resolveColorInt(139, 0, 0);
const detail::color_int_t rosy_brown = detail::resolveColorInt(188, 143, 143);
const detail::color_int_t RosyBrown = detail::resolveColorInt(188, 143, 143);
const detail::color_int_t RosyBrown1 = detail::resolveColorInt(255, 193, 193);
const detail::color_int_t RosyBrown2 = detail::resolveColorInt(238, 180, 180);
const detail::color_int_t RosyBrown3 = detail::resolveColorInt(205, 155, 155);
const detail::color_int_t RosyBrown4 = detail::resolveColorInt(139, 105, 105);
const detail::color_int_t royal_blue = detail::resolveColorInt(65, 105, 225);
const detail::color_int_t RoyalBlue = detail::resolveColorInt(65, 105, 225);
const detail::color_int_t RoyalBlue1 = detail::resolveColorInt(72, 118, 255);
const detail::color_int_t RoyalBlue2 = detail::resolveColorInt(67, 110, 238);
const detail::color_int_t RoyalBlue3 = detail::resolveColorInt(58, 95, 205);
const detail::color_int_t RoyalBlue4 = detail::resolveColorInt(39, 64, 139);
const detail::color_int_t saddle_brown = detail::resolveColorInt(139, 69, 19);
const detail::color_int_t SaddleBrown = detail::resolveColorInt(139, 69, 19);
const detail::color_int_t salmon = detail::resolveColorInt(250, 128, 114);
const detail::color_int_t salmon1 = detail::resolveColorInt(255, 140, 105);
const detail::color_int_t salmon2 = detail::resolveColorInt(238, 130, 98);
const detail::color_int_t salmon3 = detail::resolveColorInt(205, 112, 84);
const detail::color_int_t salmon4 = detail::resolveColorInt(139, 76, 57);
const detail::color_int_t sandy_brown = detail::resolveColorInt(244, 164, 96);
const detail::color_int_t SandyBrown = detail::resolveColorInt(244, 164, 96);
const detail::color_int_t sea_green = detail::resolveColorInt(46, 139, 87);
const detail::color_int_t SeaGreen = detail::resolveColorInt(46, 139, 87);
const detail::color_int_t SeaGreen1 = detail::resolveColorInt(84, 255, 159);
const detail::color_int_t SeaGreen2 = detail::resolveColorInt(78, 238, 148);
const detail::color_int_t SeaGreen3 = detail::resolveColorInt(67, 205, 128);
const detail::color_int_t SeaGreen4 = detail::resolveColorInt(46, 139, 87);
const detail::color_int_t seashell = detail::resolveColorInt(255, 245, 238);
const detail::color_int_t seashell1 = detail::resolveColorInt(255, 245, 238);
const detail::color_int_t seashell2 = detail::resolveColorInt(238, 229, 222);
const detail::color_int_t seashell3 = detail::resolveColorInt(205, 197, 191);
const detail::color_int_t seashell4 = detail::resolveColorInt(139, 134, 130);
const detail::color_int_t sienna = detail::resolveColorInt(160, 82, 45);
const detail::color_int_t sienna1 = detail::resolveColorInt(255, 130, 71);
const detail::color_int_t sienna2 = detail::resolveColorInt(238, 121, 66);
const detail::color_int_t sienna3 = detail::resolveColorInt(205, 104, 57);
const detail::color_int_t sienna4 = detail::resolveColorInt(139, 71, 38);
const detail::color_int_t sky_blue = detail::resolveColorInt(135, 206, 235);
const detail::color_int_t SkyBlue = detail::resolveColorInt(135, 206, 235);
const detail::color_int_t SkyBlue1 = detail::resolveColorInt(135, 206, 255);
const detail::color_int_t SkyBlue2 = detail::resolveColorInt(126, 192, 238);
const detail::color_int_t SkyBlue3 = detail::resolveColorInt(108, 166, 205);
const detail::color_int_t SkyBlue4 = detail::resolveColorInt(74, 112, 139);
const detail::color_int_t slate_blue = detail::resolveColorInt(106, 90, 205);
const detail::color_int_t slate_gray = detail::resolveColorInt(112, 128, 144);
const detail::color_int_t slate_grey = detail::resolveColorInt(112, 128, 144);
const detail::color_int_t SlateBlue = detail::resolveColorInt(106, 90, 205);
const detail::color_int_t SlateBlue1 = detail::resolveColorInt(131, 111, 255);
const detail::color_int_t SlateBlue2 = detail::resolveColorInt(122, 103, 238);
const detail::color_int_t SlateBlue3 = detail::resolveColorInt(105, 89, 205);
const detail::color_int_t SlateBlue4 = detail::resolveColorInt(71, 60, 139);
const detail::color_int_t SlateGray = detail::resolveColorInt(112, 128, 144);
const detail::color_int_t SlateGray1 = detail::resolveColorInt(198, 226, 255);
const detail::color_int_t SlateGray2 = detail::resolveColorInt(185, 211, 238);
const detail::color_int_t SlateGray3 = detail::resolveColorInt(159, 182, 205);
const detail::color_int_t SlateGray4 = detail::resolveColorInt(108, 123, 139);
const detail::color_int_t SlateGrey = detail::resolveColorInt(112, 128, 144);
const detail::color_int_t snow = detail::resolveColorInt(255, 250, 250);
const detail::color_int_t snow1 = detail::resolveColorInt(255, 250, 250);
const detail::color_int_t snow2 = detail::resolveColorInt(238, 233, 233);
const detail::color_int_t snow3 = detail::resolveColorInt(205, 201, 201);
const detail::color_int_t snow4 = detail::resolveColorInt(139, 137, 137);
const detail::color_int_t spring_green = detail::resolveColorInt(0, 255, 127);
const detail::color_int_t SpringGreen = detail::resolveColorInt(0, 255, 127);
const detail::color_int_t SpringGreen1 = detail::resolveColorInt(0, 255, 127);
const detail::color_int_t SpringGreen2 = detail::resolveColorInt(0, 238, 118);
const detail::color_int_t SpringGreen3 = detail::resolveColorInt(0, 205, 102);
const detail::color_int_t SpringGreen4 = detail::resolveColorInt(0, 139, 69);
const detail::color_int_t steel_blue = detail::resolveColorInt(70, 130, 180);
const detail::color_int_t SteelBlue = detail::resolveColorInt(70, 130, 180);
const detail::color_int_t SteelBlue1 = detail::resolveColorInt(99, 184, 255);
const detail::color_int_t SteelBlue2 = detail::resolveColorInt(92, 172, 238);
const detail::color_int_t SteelBlue3 = detail::resolveColorInt(79, 148, 205);
const detail::color_int_t SteelBlue4 = detail::resolveColorInt(54, 100, 139);
const detail::color_int_t tan = detail::resolveColorInt(210, 180, 140);
const detail::color_int_t tan1 = detail::resolveColorInt(255, 165, 79);
const detail::color_int_t tan2 = detail::resolveColorInt(238, 154, 73);
const detail::color_int_t tan3 = detail::resolveColorInt(205, 133, 63);
const detail::color_int_t tan4 = detail::resolveColorInt(139, 90, 43);
const detail::color_int_t thistle = detail::resolveColorInt(216, 191, 216);
const detail::color_int_t thistle1 = detail::resolveColorInt(255, 225, 255);
const detail::color_int_t thistle2 = detail::resolveColorInt(238, 210, 238);
const detail::color_int_t thistle3 = detail::resolveColorInt(205, 181, 205);
const detail::color_int_t thistle4 = detail::resolveColorInt(139, 123, 139);
const detail::color_int_t tomato = detail::resolveColorInt(255, 99, 71);
const detail::color_int_t tomato1 = detail::resolveColorInt(255, 99, 71);
const detail::color_int_t tomato2 = detail::resolveColorInt(238, 92, 66);
const detail::color_int_t tomato3 = detail::resolveColorInt(205, 79, 57);
const detail::color_int_t tomato4 = detail::resolveColorInt(139, 54, 38);
const detail::color_int_t turquoise = detail::resolveColorInt(64, 224, 208);
const detail::color_int_t turquoise1 = detail::resolveColorInt(0, 245, 255);
const detail::color_int_t turquoise2 = detail::resolveColorInt(0, 229, 238);
const detail::color_int_t turquoise3 = detail::resolveColorInt(0, 197, 205);
const detail::color_int_t turquoise4 = detail::resolveColorInt(0, 134, 139);
const detail::color_int_t violet = detail::resolveColorInt(238, 130, 238);
const detail::color_int_t violet_red = detail::resolveColorInt(208, 32, 144);
const detail::color_int_t VioletRed = detail::resolveColorInt(208, 32, 144);
const detail::color_int_t VioletRed1 = detail::resolveColorInt(255, 62, 150);
const detail::color_int_t VioletRed2 = detail::resolveColorInt(238, 58, 140);
const detail::color_int_t VioletRed3 = detail::resolveColorInt(205, 50, 120);
const detail::color_int_t VioletRed4 = detail::resolveColorInt(139, 34, 82);
const detail::color_int_t wheat = detail::resolveColorInt(245, 222, 179);
const detail::color_int_t wheat1 = detail::resolveColorInt(255, 231, 186);
const detail::color_int_t wheat2 = detail::resolveColorInt(238, 216, 174);
const detail::color_int_t wheat3 = detail::resolveColorInt(205, 186, 150);
const detail::color_int_t wheat4 = detail::resolveColorInt(139, 126, 102);
const detail::color_int_t white = detail::resolveColorInt(255, 255, 255);
const detail::color_int_t white_smoke = detail::resolveColorInt(245, 245, 245);
const detail::color_int_t WhiteSmoke = detail::resolveColorInt(245, 245, 245);
const detail::color_int_t yellow = detail::resolveColorInt(255, 255, 0);
const detail::color_int_t yellow_green = detail::resolveColorInt(154, 205, 50);
const detail::color_int_t yellow1 = detail::resolveColorInt(255, 255, 0);
const detail::color_int_t yellow2 = detail::resolveColorInt(238, 238, 0);
const detail::color_int_t yellow3 = detail::resolveColorInt(205, 205, 0);
const detail::color_int_t yellow4 = detail::resolveColorInt(139, 139, 0);
const detail::color_int_t YellowGreen = detail::resolveColorInt(154, 205, 50);
} // namespace col
} // namespace cturtle::detail

/**
 * \brief The primary representation of Color for this library.
 * Represented as a simple RGB color composed of unsigned bytes,
 * Color objects can be referenced by string and by packed integer.
 * \sa detail::resolveColorComp()
 * \sa detail::resolveColorInt()
 * \sa fromName()
 */
namespace detail = cturtle::detail;
const std::unordered_map<std::string, detail::color_int_t> NAMED_COLORS = {
    {"alice blue", detail::col::alice_blue},
    {"AliceBlue", detail::col::AliceBlue},
    {"antique white", detail::col::antique_white},
    {"AntiqueWhite", detail::col::AntiqueWhite},
    {"AntiqueWhite1", detail::col::AntiqueWhite1},
    {"AntiqueWhite2", detail::col::AntiqueWhite2},
    {"AntiqueWhite3", detail::col::AntiqueWhite3},
    {"AntiqueWhite4", detail::col::AntiqueWhite4},
    {"aquamarine", detail::col::aquamarine},
    {"aquamarine1", detail::col::aquamarine1},
    {"aquamarine2", detail::col::aquamarine2},
    {"aquamarine3", detail::col::aquamarine3},
    {"aquamarine4", detail::col::aquamarine4},
    {"azure", detail::col::azure},
    {"azure1", detail::col::azure1},
    {"azure2", detail::col::azure2},
    {"azure3", detail::col::azure3},
    {"azure4", detail::col::azure4},
    {"beige", detail::col::beige},
    {"bisque", detail::col::bisque},
    {"bisque1", detail::col::bisque1},
    {"bisque2", detail::col::bisque2},
    {"bisque3", detail::col::bisque3},
    {"bisque4", detail::col::bisque4},
    {"black", detail::col::black},
    {"blanched almond", detail::col::blanched_almond},
    {"BlanchedAlmond", detail::col::BlanchedAlmond},
    {"blue", detail::col::blue},
    {"blue violet", detail::col::blue_violet},
    {"blue1", detail::col::blue1},
    {"blue2", detail::col::blue2},
    {"blue3", detail::col::blue3},
    {"blue4", detail::col::blue4},
    {"BlueViolet", detail::col::BlueViolet},
    {"brown", detail::col::brown},
    {"brown1", detail::col::brown1},
    {"brown2", detail::col::brown2},
    {"brown3", detail::col::brown3},
    {"brown4", detail::col::brown4},
    {"burlywood", detail::col::burlywood},
    {"burlywood1", detail::col::burlywood1},
    {"burlywood2", detail::col::burlywood2},
    {"burlywood3", detail::col::burlywood3},
    {"burlywood4", detail::col::burlywood4},
    {"cadet blue", detail::col::cadet_blue},
    {"CadetBlue", detail::col::CadetBlue},
    {"CadetBlue1", detail::col::CadetBlue1},
    {"CadetBlue2", detail::col::CadetBlue2},
    {"CadetBlue3", detail::col::CadetBlue3},
    {"CadetBlue4", detail::col::CadetBlue4},
    {"chartreuse", detail::col::chartreuse},
    {"chartreuse1", detail::col::chartreuse1},
    {"chartreuse2", detail::col::chartreuse2},
    {"chartreuse3", detail::col::chartreuse3},
    {"chartreuse4", detail::col::chartreuse4},
    {"chocolate", detail::col::chocolate},
    {"chocolate1", detail::col::chocolate1},
    {"chocolate2", detail::col::chocolate2},
    {"chocolate3", detail::col::chocolate3},
    {"chocolate4", detail::col::chocolate4},
    {"coral", detail::col::coral},
    {"coral1", detail::col::coral1},
    {"coral2", detail::col::coral2},
    {"coral3", detail::col::coral3},
    {"coral4", detail::col::coral4},
    {"cornflower blue", detail::col::cornflower_blue},
    {"CornflowerBlue", detail::col::CornflowerBlue},
    {"cornsilk", detail::col::cornsilk},
    {"cornsilk1", detail::col::cornsilk1},
    {"cornsilk2", detail::col::cornsilk2},
    {"cornsilk3", detail::col::cornsilk3},
    {"cornsilk4", detail::col::cornsilk4},
    {"cyan", detail::col::cyan},
    {"cyan1", detail::col::cyan1},
    {"cyan2", detail::col::cyan2},
    {"cyan3", detail::col::cyan3},
    {"cyan4", detail::col::cyan4},
    {"dark blue", detail::col::dark_blue},
    {"dark cyan", detail::col::dark_cyan},
    {"dark goldenrod", detail::col::dark_goldenrod},
    {"dark gray", detail::col::dark_gray},
    {"dark green", detail::col::dark_green},
    {"dark grey", detail::col::dark_grey},
    {"dark khaki", detail::col::dark_khaki},
    {"dark magenta", detail::col::dark_magenta},
    {"dark olive green", detail::col::dark_olive_green},
    {"dark orange", detail::col::dark_orange},
    {"dark orchid", detail::col::dark_orchid},
    {"dark red", detail::col::dark_red},
    {"dark salmon", detail::col::dark_salmon},
    {"dark sea green", detail::col::dark_sea_green},
    {"dark slate blue", detail::col::dark_slate_blue},
    {"dark slate gray", detail::col::dark_slate_gray},
    {"dark slate grey", detail::col::dark_slate_grey},
    {"dark turquoise", detail::col::dark_turquoise},
    {"dark violet", detail::col::dark_violet},
    {"DarkBlue", detail::col::DarkBlue},
    {"DarkCyan", detail::col::DarkCyan},
    {"DarkGoldenrod", detail::col::DarkGoldenrod},
    {"DarkGoldenrod1", detail::col::DarkGoldenrod1},
    {"DarkGoldenrod2", detail::col::DarkGoldenrod2},
    {"DarkGoldenrod3", detail::col::DarkGoldenrod3},
    {"DarkGoldenrod4", detail::col::DarkGoldenrod4},
    {"DarkGray", detail::col::DarkGray},
    {"DarkGreen", detail::col::DarkGreen},
    {"DarkGrey", detail::col::DarkGrey},
    {"DarkKhaki", detail::col::DarkKhaki},
    {"DarkMagenta", detail::col::DarkMagenta},
    {"DarkOliveGreen", detail::col::DarkOliveGreen},
    {"DarkOliveGreen1", detail::col::DarkOliveGreen1},
    {"DarkOliveGreen2", detail::col::DarkOliveGreen2},
    {"DarkOliveGreen3", detail::col::DarkOliveGreen3},
    {"DarkOliveGreen4", detail::col::DarkOliveGreen4},
    {"DarkOrange", detail::col::DarkOrange},
    {"DarkOrange1", detail::col::DarkOrange1},
    {"DarkOrange2", detail::col::DarkOrange2},
    {"DarkOrange3", detail::col::DarkOrange3},
    {"DarkOrange4", detail::col::DarkOrange4},
    {"DarkOrchid", detail::col::DarkOrchid},
    {"DarkOrchid1", detail::col::DarkOrchid1},
    {"DarkOrchid2", detail::col::DarkOrchid2},
    {"DarkOrchid3", detail::col::DarkOrchid3},
    {"DarkOrchid4", detail::col::DarkOrchid4},
    {"DarkRed", detail::col::DarkRed},
    {"DarkSalmon", detail::col::DarkSalmon},
    {"DarkSeaGreen", detail::col::DarkSeaGreen},
    {"DarkSeaGreen1", detail::col::DarkSeaGreen1},
    {"DarkSeaGreen2", detail::col::DarkSeaGreen2},
    {"DarkSeaGreen3", detail::col::DarkSeaGreen3},
    {"DarkSeaGreen4", detail::col::DarkSeaGreen4},
    {"DarkSlateBlue", detail::col::DarkSlateBlue},
    {"DarkSlateGray", detail::col::DarkSlateGray},
    {"DarkSlateGray1", detail::col::DarkSlateGray1},
    {"DarkSlateGray2", detail::col::DarkSlateGray2},
    {"DarkSlateGray3", detail::col::DarkSlateGray3},
    {"DarkSlateGray4", detail::col::DarkSlateGray4},
    {"DarkSlateGrey", detail::col::DarkSlateGrey},
    {"DarkTurquoise", detail::col::DarkTurquoise},
    {"DarkViolet", detail::col::DarkViolet},
    {"deep pink", detail::col::deep_pink},
    {"deep sky blue", detail::col::deep_sky_blue},
    {"DeepPink", detail::col::DeepPink},
    {"DeepPink1", detail::col::DeepPink1},
    {"DeepPink2", detail::col::DeepPink2},
    {"DeepPink3", detail::col::DeepPink3},
    {"DeepPink4", detail::col::DeepPink4},
    {"DeepSkyBlue", detail::col::DeepSkyBlue},
    {"DeepSkyBlue1", detail::col::DeepSkyBlue1},
    {"DeepSkyBlue2", detail::col::DeepSkyBlue2},
    {"DeepSkyBlue3", detail::col::DeepSkyBlue3},
    {"DeepSkyBlue4", detail::col::DeepSkyBlue4},
    {"dim gray", detail::col::dim_gray},
    {"dim grey", detail::col::dim_grey},
    {"DimGray", detail::col::DimGray},
    {"DimGrey", detail::col::DimGrey},
    {"dodger blue", detail::col::dodger_blue},
    {"DodgerBlue", detail::col::DodgerBlue},
    {"DodgerBlue1", detail::col::DodgerBlue1},
    {"DodgerBlue2", detail::col::DodgerBlue2},
    {"DodgerBlue3", detail::col::DodgerBlue3},
    {"DodgerBlue4", detail::col::DodgerBlue4},
    {"firebrick", detail::col::firebrick},
    {"firebrick1", detail::col::firebrick1},
    {"firebrick2", detail::col::firebrick2},
    {"firebrick3", detail::col::firebrick3},
    {"firebrick4", detail::col::firebrick4},
    {"floral white", detail::col::floral_white},
    {"FloralWhite", detail::col::FloralWhite},
    {"forest green", detail::col::forest_green},
    {"ForestGreen", detail::col::ForestGreen},
    {"gainsboro", detail::col::gainsboro},
    {"ghost white", detail::col::ghost_white},
    {"GhostWhite", detail::col::GhostWhite},
    {"gold", detail::col::gold},
    {"gold1", detail::col::gold1},
    {"gold2", detail::col::gold2},
    {"gold3", detail::col::gold3},
    {"gold4", detail::col::gold4},
    {"goldenrod", detail::col::goldenrod},
    {"goldenrod1", detail::col::goldenrod1},
    {"goldenrod2", detail::col::goldenrod2},
    {"goldenrod3", detail::col::goldenrod3},
    {"goldenrod4", detail::col::goldenrod4},
    {"gray", detail::col::gray},
    {"gray0", detail::col::gray0},
    {"gray1", detail::col::gray1},
    {"gray2", detail::col::gray2},
    {"gray3", detail::col::gray3},
    {"gray4", detail::col::gray4},
    {"gray5", detail::col::gray5},
    {"gray6", detail::col::gray6},
    {"gray7", detail::col::gray7},
    {"gray8", detail::col::gray8},
    {"gray9", detail::col::gray9},
    {"gray10", detail::col::gray10},
    {"gray11", detail::col::gray11},
    {"gray12", detail::col::gray12},
    {"gray13", detail::col::gray13},
    {"gray14", detail::col::gray14},
    {"gray15", detail::col::gray15},
    {"gray16", detail::col::gray16},
    {"gray17", detail::col::gray17},
    {"gray18", detail::col::gray18},
    {"gray19", detail::col::gray19},
    {"gray20", detail::col::gray20},
    {"gray21", detail::col::gray21},
    {"gray22", detail::col::gray22},
    {"gray23", detail::col::gray23},
    {"gray24", detail::col::gray24},
    {"gray25", detail::col::gray25},
    {"gray26", detail::col::gray26},
    {"gray27", detail::col::gray27},
    {"gray28", detail::col::gray28},
    {"gray29", detail::col::gray29},
    {"gray30", detail::col::gray30},
    {"gray31", detail::col::gray31},
    {"gray32", detail::col::gray32},
    {"gray33", detail::col::gray33},
    {"gray34", detail::col::gray34},
    {"gray35", detail::col::gray35},
    {"gray36", detail::col::gray36},
    {"gray37", detail::col::gray37},
    {"gray38", detail::col::gray38},
    {"gray39", detail::col::gray39},
    {"gray40", detail::col::gray40},
    {"gray41", detail::col::gray41},
    {"gray42", detail::col::gray42},
    {"gray43", detail::col::gray43},
    {"gray44", detail::col::gray44},
    {"gray45", detail::col::gray45},
    {"gray46", detail::col::gray46},
    {"gray47", detail::col::gray47},
    {"gray48", detail::col::gray48},
    {"gray49", detail::col::gray49},
    {"gray50", detail::col::gray50},
    {"gray51", detail::col::gray51},
    {"gray52", detail::col::gray52},
    {"gray53", detail::col::gray53},
    {"gray54", detail::col::gray54},
    {"gray55", detail::col::gray55},
    {"gray56", detail::col::gray56},
    {"gray57", detail::col::gray57},
    {"gray58", detail::col::gray58},
    {"gray59", detail::col::gray59},
    {"gray60", detail::col::gray60},
    {"gray61", detail::col::gray61},
    {"gray62", detail::col::gray62},
    {"gray63", detail::col::gray63},
    {"gray64", detail::col::gray64},
    {"gray65", detail::col::gray65},
    {"gray66", detail::col::gray66},
    {"gray67", detail::col::gray67},
    {"gray68", detail::col::gray68},
    {"gray69", detail::col::gray69},
    {"gray70", detail::col::gray70},
    {"gray71", detail::col::gray71},
    {"gray72", detail::col::gray72},
    {"gray73", detail::col::gray73},
    {"gray74", detail::col::gray74},
    {"gray75", detail::col::gray75},
    {"gray76", detail::col::gray76},
    {"gray77", detail::col::gray77},
    {"gray78", detail::col::gray78},
    {"gray79", detail::col::gray79},
    {"gray80", detail::col::gray80},
    {"gray81", detail::col::gray81},
    {"gray82", detail::col::gray82},
    {"gray83", detail::col::gray83},
    {"gray84", detail::col::gray84},
    {"gray85", detail::col::gray85},
    {"gray86", detail::col::gray86},
    {"gray87", detail::col::gray87},
    {"gray88", detail::col::gray88},
    {"gray89", detail::col::gray89},
    {"gray90", detail::col::gray90},
    {"gray91", detail::col::gray91},
    {"gray92", detail::col::gray92},
    {"gray93", detail::col::gray93},
    {"gray94", detail::col::gray94},
    {"gray95", detail::col::gray95},
    {"gray96", detail::col::gray96},
    {"gray97", detail::col::gray97},
    {"gray98", detail::col::gray98},
    {"gray99", detail::col::gray99},
    {"gray100", detail::col::gray100},
    {"green", detail::col::green},
    {"green yellow", detail::col::green_yellow},
    {"green1", detail::col::green1},
    {"green2", detail::col::green2},
    {"green3", detail::col::green3},
    {"green4", detail::col::green4},
    {"GreenYellow", detail::col::GreenYellow},
    {"grey", detail::col::grey},
    {"grey0", detail::col::grey0},
    {"grey1", detail::col::grey1},
    {"grey2", detail::col::grey2},
    {"grey3", detail::col::grey3},
    {"grey4", detail::col::grey4},
    {"grey5", detail::col::grey5},
    {"grey6", detail::col::grey6},
    {"grey7", detail::col::grey7},
    {"grey8", detail::col::grey8},
    {"grey9", detail::col::grey9},
    {"grey10", detail::col::grey10},
    {"grey11", detail::col::grey11},
    {"grey12", detail::col::grey12},
    {"grey13", detail::col::grey13},
    {"grey14", detail::col::grey14},
    {"grey15", detail::col::grey15},
    {"grey16", detail::col::grey16},
    {"grey17", detail::col::grey17},
    {"grey18", detail::col::grey18},
    {"grey19", detail::col::grey19},
    {"grey20", detail::col::grey20},
    {"grey21", detail::col::grey21},
    {"grey22", detail::col::grey22},
    {"grey23", detail::col::grey23},
    {"grey24", detail::col::grey24},
    {"grey25", detail::col::grey25},
    {"grey26", detail::col::grey26},
    {"grey27", detail::col::grey27},
    {"grey28", detail::col::grey28},
    {"grey29", detail::col::grey29},
    {"grey30", detail::col::grey30},
    {"grey31", detail::col::grey31},
    {"grey32", detail::col::grey32},
    {"grey33", detail::col::grey33},
    {"grey34", detail::col::grey34},
    {"grey35", detail::col::grey35},
    {"grey36", detail::col::grey36},
    {"grey37", detail::col::grey37},
    {"grey38", detail::col::grey38},
    {"grey39", detail::col::grey39},
    {"grey40", detail::col::grey40},
    {"grey41", detail::col::grey41},
    {"grey42", detail::col::grey42},
    {"grey43", detail::col::grey43},
    {"grey44", detail::col::grey44},
    {"grey45", detail::col::grey45},
    {"grey46", detail::col::grey46},
    {"grey47", detail::col::grey47},
    {"grey48", detail::col::grey48},
    {"grey49", detail::col::grey49},
    {"grey50", detail::col::grey50},
    {"grey51", detail::col::grey51},
    {"grey52", detail::col::grey52},
    {"grey53", detail::col::grey53},
    {"grey54", detail::col::grey54},
    {"grey55", detail::col::grey55},
    {"grey56", detail::col::grey56},
    {"grey57", detail::col::grey57},
    {"grey58", detail::col::grey58},
    {"grey59", detail::col::grey59},
    {"grey60", detail::col::grey60},
    {"grey61", detail::col::grey61},
    {"grey62", detail::col::grey62},
    {"grey63", detail::col::grey63},
    {"grey64", detail::col::grey64},
    {"grey65", detail::col::grey65},
    {"grey66", detail::col::grey66},
    {"grey67", detail::col::grey67},
    {"grey68", detail::col::grey68},
    {"grey69", detail::col::grey69},
    {"grey70", detail::col::grey70},
    {"grey71", detail::col::grey71},
    {"grey72", detail::col::grey72},
    {"grey73", detail::col::grey73},
    {"grey74", detail::col::grey74},
    {"grey75", detail::col::grey75},
    {"grey76", detail::col::grey76},
    {"grey77", detail::col::grey77},
    {"grey78", detail::col::grey78},
    {"grey79", detail::col::grey79},
    {"grey80", detail::col::grey80},
    {"grey81", detail::col::grey81},
    {"grey82", detail::col::grey82},
    {"grey83", detail::col::grey83},
    {"grey84", detail::col::grey84},
    {"grey85", detail::col::grey85},
    {"grey86", detail::col::grey86},
    {"grey87", detail::col::grey87},
    {"grey88", detail::col::grey88},
    {"grey89", detail::col::grey89},
    {"grey90", detail::col::grey90},
    {"grey91", detail::col::grey91},
    {"grey92", detail::col::grey92},
    {"grey93", detail::col::grey93},
    {"grey94", detail::col::grey94},
    {"grey95", detail::col::grey95},
    {"grey96", detail::col::grey96},
    {"grey97", detail::col::grey97},
    {"grey98", detail::col::grey98},
    {"grey99", detail::col::grey99},
    {"grey100", detail::col::grey100},
    {"honeydew", detail::col::honeydew},
    {"honeydew1", detail::col::honeydew1},
    {"honeydew2", detail::col::honeydew2},
    {"honeydew3", detail::col::honeydew3},
    {"honeydew4", detail::col::honeydew4},
    {"hot pink", detail::col::hot_pink},
    {"HotPink", detail::col::HotPink},
    {"HotPink1", detail::col::HotPink1},
    {"HotPink2", detail::col::HotPink2},
    {"HotPink3", detail::col::HotPink3},
    {"HotPink4", detail::col::HotPink4},
    {"indian red", detail::col::indian_red},
    {"IndianRed", detail::col::IndianRed},
    {"IndianRed1", detail::col::IndianRed1},
    {"IndianRed2", detail::col::IndianRed2},
    {"IndianRed3", detail::col::IndianRed3},
    {"IndianRed4", detail::col::IndianRed4},
    {"ivory", detail::col::ivory},
    {"ivory1", detail::col::ivory1},
    {"ivory2", detail::col::ivory2},
    {"ivory3", detail::col::ivory3},
    {"ivory4", detail::col::ivory4},
    {"khaki", detail::col::khaki},
    {"khaki1", detail::col::khaki1},
    {"khaki2", detail::col::khaki2},
    {"khaki3", detail::col::khaki3},
    {"khaki4", detail::col::khaki4},
    {"lavender", detail::col::lavender},
    {"lavender blush", detail::col::lavender_blush},
    {"LavenderBlush", detail::col::LavenderBlush},
    {"LavenderBlush1", detail::col::LavenderBlush1},
    {"LavenderBlush2", detail::col::LavenderBlush2},
    {"LavenderBlush3", detail::col::LavenderBlush3},
    {"LavenderBlush4", detail::col::LavenderBlush4},
    {"lawn green", detail::col::lawn_green},
    {"LawnGreen", detail::col::LawnGreen},
    {"lemon chiffon", detail::col::lemon_chiffon},
    {"LemonChiffon", detail::col::LemonChiffon},
    {"LemonChiffon1", detail::col::LemonChiffon1},
    {"LemonChiffon2", detail::col::LemonChiffon2},
    {"LemonChiffon3", detail::col::LemonChiffon3},
    {"LemonChiffon4", detail::col::LemonChiffon4},
    {"light blue", detail::col::light_blue},
    {"light coral", detail::col::light_coral},
    {"light cyan", detail::col::light_cyan},
    {"light goldenrod", detail::col::light_goldenrod},
    {"light goldenrod yellow", detail::col::light_goldenrod_yellow},
    {"light gray", detail::col::light_gray},
    {"light green", detail::col::light_green},
    {"light grey", detail::col::light_grey},
    {"light pink", detail::col::light_pink},
    {"light salmon", detail::col::light_salmon},
    {"light sea green", detail::col::light_sea_green},
    {"light sky blue", detail::col::light_sky_blue},
    {"light slate blue", detail::col::light_slate_blue},
    {"light slate gray", detail::col::light_slate_gray},
    {"light slate grey", detail::col::light_slate_grey},
    {"light steel blue", detail::col::light_steel_blue},
    {"light yellow", detail::col::light_yellow},
    {"LightBlue", detail::col::LightBlue},
    {"LightBlue1", detail::col::LightBlue1},
    {"LightBlue2", detail::col::LightBlue2},
    {"LightBlue3", detail::col::LightBlue3},
    {"LightBlue4", detail::col::LightBlue4},
    {"LightCoral", detail::col::LightCoral},
    {"LightCyan", detail::col::LightCyan},
    {"LightCyan1", detail::col::LightCyan1},
    {"LightCyan2", detail::col::LightCyan2},
    {"LightCyan3", detail::col::LightCyan3},
    {"LightCyan4", detail::col::LightCyan4},
    {"LightGoldenrod", detail::col::LightGoldenrod},
    {"LightGoldenrod1", detail::col::LightGoldenrod1},
    {"LightGoldenrod2", detail::col::LightGoldenrod2},
    {"LightGoldenrod3", detail::col::LightGoldenrod3},
    {"LightGoldenrod4", detail::col::LightGoldenrod4},
    {"LightGoldenrodYellow", detail::col::LightGoldenrodYellow},
    {"LightGray", detail::col::LightGray},
    {"LightGreen", detail::col::LightGreen},
    {"LightGrey", detail::col::LightGrey},
    {"LightPink", detail::col::LightPink},
    {"LightPink1", detail::col::LightPink1},
    {"LightPink2", detail::col::LightPink2},
    {"LightPink3", detail::col::LightPink3},
    {"LightPink4", detail::col::LightPink4},
    {"LightSalmon", detail::col::LightSalmon},
    {"LightSalmon1", detail::col::LightSalmon1},
    {"LightSalmon2", detail::col::LightSalmon2},
    {"LightSalmon3", detail::col::LightSalmon3},
    {"LightSalmon4", detail::col::LightSalmon4},
    {"LightSeaGreen", detail::col::LightSeaGreen},
    {"LightSkyBlue", detail::col::LightSkyBlue},
    {"LightSkyBlue1", detail::col::LightSkyBlue1},
    {"LightSkyBlue2", detail::col::LightSkyBlue2},
    {"LightSkyBlue3", detail::col::LightSkyBlue3},
    {"LightSkyBlue4", detail::col::LightSkyBlue4},
    {"LightSlateBlue", detail::col::LightSlateBlue},
    {"LightSlateGray", detail::col::LightSlateGray},
    {"LightSlateGrey", detail::col::LightSlateGrey},
    {"LightSteelBlue", detail::col::LightSteelBlue},
    {"LightSteelBlue1", detail::col::LightSteelBlue1},
    {"LightSteelBlue2", detail::col::LightSteelBlue2},
    {"LightSteelBlue3", detail::col::LightSteelBlue3},
    {"LightSteelBlue4", detail::col::LightSteelBlue4},
    {"LightYellow", detail::col::LightYellow},
    {"LightYellow1", detail::col::LightYellow1},
    {"LightYellow2", detail::col::LightYellow2},
    {"LightYellow3", detail::col::LightYellow3},
    {"LightYellow4", detail::col::LightYellow4},
    {"lime green", detail::col::lime_green},
    {"LimeGreen", detail::col::LimeGreen},
    {"linen", detail::col::linen},
    {"magenta", detail::col::magenta},
    {"magenta1", detail::col::magenta1},
    {"magenta2", detail::col::magenta2},
    {"magenta3", detail::col::magenta3},
    {"magenta4", detail::col::magenta4},
    {"maroon", detail::col::maroon},
    {"maroon1", detail::col::maroon1},
    {"maroon2", detail::col::maroon2},
    {"maroon3", detail::col::maroon3},
    {"maroon4", detail::col::maroon4},
    {"medium aquamarine", detail::col::medium_aquamarine},
    {"medium blue", detail::col::medium_blue},
    {"medium orchid", detail::col::medium_orchid},
    {"medium purple", detail::col::medium_purple},
    {"medium sea green", detail::col::medium_sea_green},
    {"medium slate blue", detail::col::medium_slate_blue},
    {"medium spring green", detail::col::medium_spring_green},
    {"medium turquoise", detail::col::medium_turquoise},
    {"medium violet red", detail::col::medium_violet_red},
    {"MediumAquamarine", detail::col::MediumAquamarine},
    {"MediumBlue", detail::col::MediumBlue},
    {"MediumOrchid", detail::col::MediumOrchid},
    {"MediumOrchid1", detail::col::MediumOrchid1},
    {"MediumOrchid2", detail::col::MediumOrchid2},
    {"MediumOrchid3", detail::col::MediumOrchid3},
    {"MediumOrchid4", detail::col::MediumOrchid4},
    {"MediumPurple", detail::col::MediumPurple},
    {"MediumPurple1", detail::col::MediumPurple1},
    {"MediumPurple2", detail::col::MediumPurple2},
    {"MediumPurple3", detail::col::MediumPurple3},
    {"MediumPurple4", detail::col::MediumPurple4},
    {"MediumSeaGreen", detail::col::MediumSeaGreen},
    {"MediumSlateBlue", detail::col::MediumSlateBlue},
    {"MediumSpringGreen", detail::col::MediumSpringGreen},
    {"MediumTurquoise", detail::col::MediumTurquoise},
    {"MediumVioletRed", detail::col::MediumVioletRed},
    {"midnight blue", detail::col::midnight_blue},
    {"MidnightBlue", detail::col::MidnightBlue},
    {"mint cream", detail::col::mint_cream},
    {"MintCream", detail::col::MintCream},
    {"misty rose", detail::col::misty_rose},
    {"MistyRose", detail::col::MistyRose},
    {"MistyRose1", detail::col::MistyRose1},
    {"MistyRose2", detail::col::MistyRose2},
    {"MistyRose3", detail::col::MistyRose3},
    {"MistyRose4", detail::col::MistyRose4},
    {"moccasin", detail::col::moccasin},
    {"navajo white", detail::col::navajo_white},
    {"NavajoWhite", detail::col::NavajoWhite},
    {"NavajoWhite1", detail::col::NavajoWhite1},
    {"NavajoWhite2", detail::col::NavajoWhite2},
    {"NavajoWhite3", detail::col::NavajoWhite3},
    {"NavajoWhite4", detail::col::NavajoWhite4},
    {"navy", detail::col::navy},
    {"navy blue", detail::col::navy_blue},
    {"NavyBlue", detail::col::NavyBlue},
    {"old lace", detail::col::old_lace},
    {"OldLace", detail::col::OldLace},
    {"olive drab", detail::col::olive_drab},
    {"OliveDrab", detail::col::OliveDrab},
    {"OliveDrab1", detail::col::OliveDrab1},
    {"OliveDrab2", detail::col::OliveDrab2},
    {"OliveDrab3", detail::col::OliveDrab3},
    {"OliveDrab4", detail::col::OliveDrab4},
    {"orange", detail::col::orange},
    {"orange red", detail::col::orange_red},
    {"orange1", detail::col::orange1},
    {"orange2", detail::col::orange2},
    {"orange3", detail::col::orange3},
    {"orange4", detail::col::orange4},
    {"OrangeRed", detail::col::OrangeRed},
    {"OrangeRed1", detail::col::OrangeRed1},
    {"OrangeRed2", detail::col::OrangeRed2},
    {"OrangeRed3", detail::col::OrangeRed3},
    {"OrangeRed4", detail::col::OrangeRed4},
    {"orchid", detail::col::orchid},
    {"orchid1", detail::col::orchid1},
    {"orchid2", detail::col::orchid2},
    {"orchid3", detail::col::orchid3},
    {"orchid4", detail::col::orchid4},
    {"pale goldenrod", detail::col::pale_goldenrod},
    {"pale green", detail::col::pale_green},
    {"pale turquoise", detail::col::pale_turquoise},
    {"pale violet red", detail::col::pale_violet_red},
    {"PaleGoldenrod", detail::col::PaleGoldenrod},
    {"PaleGreen", detail::col::PaleGreen},
    {"PaleGreen1", detail::col::PaleGreen1},
    {"PaleGreen2", detail::col::PaleGreen2},
    {"PaleGreen3", detail::col::PaleGreen3},
    {"PaleGreen4", detail::col::PaleGreen4},
    {"PaleTurquoise", detail::col::PaleTurquoise},
    {"PaleTurquoise1", detail::col::PaleTurquoise1},
    {"PaleTurquoise2", detail::col::PaleTurquoise2},
    {"PaleTurquoise3", detail::col::PaleTurquoise3},
    {"PaleTurquoise4", detail::col::PaleTurquoise4},
    {"PaleVioletRed", detail::col::PaleVioletRed},
    {"PaleVioletRed1", detail::col::PaleVioletRed1},
    {"PaleVioletRed2", detail::col::PaleVioletRed2},
    {"PaleVioletRed3", detail::col::PaleVioletRed3},
    {"PaleVioletRed4", detail::col::PaleVioletRed4},
    {"papaya whip", detail::col::papaya_whip},
    {"PapayaWhip", detail::col::PapayaWhip},
    {"peach puff", detail::col::peach_puff},
    {"PeachPuff", detail::col::PeachPuff},
    {"PeachPuff1", detail::col::PeachPuff1},
    {"PeachPuff2", detail::col::PeachPuff2},
    {"PeachPuff3", detail::col::PeachPuff3},
    {"PeachPuff4", detail::col::PeachPuff4},
    {"peru", detail::col::peru},
    {"pink", detail::col::pink},
    {"pink1", detail::col::pink1},
    {"pink2", detail::col::pink2},
    {"pink3", detail::col::pink3},
    {"pink4", detail::col::pink4},
    {"plum", detail::col::plum},
    {"plum1", detail::col::plum1},
    {"plum2", detail::col::plum2},
    {"plum3", detail::col::plum3},
    {"plum4", detail::col::plum4},
    {"powder blue", detail::col::powder_blue},
    {"PowderBlue", detail::col::PowderBlue},
    {"purple", detail::col::purple},
    {"purple1", detail::col::purple1},
    {"purple2", detail::col::purple2},
    {"purple3", detail::col::purple3},
    {"purple4", detail::col::purple4},
    {"red", detail::col::red},
    {"red1", detail::col::red1},
    {"red2", detail::col::red2},
    {"red3", detail::col::red3},
    {"red4", detail::col::red4},
    {"rosy brown", detail::col::rosy_brown},
    {"RosyBrown", detail::col::RosyBrown},
    {"RosyBrown1", detail::col::RosyBrown1},
    {"RosyBrown2", detail::col::RosyBrown2},
    {"RosyBrown3", detail::col::RosyBrown3},
    {"RosyBrown4", detail::col::RosyBrown4},
    {"royal blue", detail::col::royal_blue},
    {"RoyalBlue", detail::col::RoyalBlue},
    {"RoyalBlue1", detail::col::RoyalBlue1},
    {"RoyalBlue2", detail::col::RoyalBlue2},
    {"RoyalBlue3", detail::col::RoyalBlue3},
    {"RoyalBlue4", detail::col::RoyalBlue4},
    {"saddle brown", detail::col::saddle_brown},
    {"SaddleBrown", detail::col::SaddleBrown},
    {"salmon", detail::col::salmon},
    {"salmon1", detail::col::salmon1},
    {"salmon2", detail::col::salmon2},
    {"salmon3", detail::col::salmon3},
    {"salmon4", detail::col::salmon4},
    {"sandy brown", detail::col::sandy_brown},
    {"SandyBrown", detail::col::SandyBrown},
    {"sea green", detail::col::sea_green},
    {"SeaGreen", detail::col::SeaGreen},
    {"SeaGreen1", detail::col::SeaGreen1},
    {"SeaGreen2", detail::col::SeaGreen2},
    {"SeaGreen3", detail::col::SeaGreen3},
    {"SeaGreen4", detail::col::SeaGreen4},
    {"seashell", detail::col::seashell},
    {"seashell1", detail::col::seashell1},
    {"seashell2", detail::col::seashell2},
    {"seashell3", detail::col::seashell3},
    {"seashell4", detail::col::seashell4},
    {"sienna", detail::col::sienna},
    {"sienna1", detail::col::sienna1},
    {"sienna2", detail::col::sienna2},
    {"sienna3", detail::col::sienna3},
    {"sienna4", detail::col::sienna4},
    {"sky blue", detail::col::sky_blue},
    {"SkyBlue", detail::col::SkyBlue},
    {"SkyBlue1", detail::col::SkyBlue1},
    {"SkyBlue2", detail::col::SkyBlue2},
    {"SkyBlue3", detail::col::SkyBlue3},
    {"SkyBlue4", detail::col::SkyBlue4},
    {"slate blue", detail::col::slate_blue},
    {"slate gray", detail::col::slate_gray},
    {"slate grey", detail::col::slate_grey},
    {"SlateBlue", detail::col::SlateBlue},
    {"SlateBlue1", detail::col::SlateBlue1},
    {"SlateBlue2", detail::col::SlateBlue2},
    {"SlateBlue3", detail::col::SlateBlue3},
    {"SlateBlue4", detail::col::SlateBlue4},
    {"SlateGray", detail::col::SlateGray},
    {"SlateGray1", detail::col::SlateGray1},
    {"SlateGray2", detail::col::SlateGray2},
    {"SlateGray3", detail::col::SlateGray3},
    {"SlateGray4", detail::col::SlateGray4},
    {"SlateGrey", detail::col::SlateGrey},
    {"snow", detail::col::snow},
    {"snow1", detail::col::snow1},
    {"snow2", detail::col::snow2},
    {"snow3", detail::col::snow3},
    {"snow4", detail::col::snow4},
    {"spring green", detail::col::spring_green},
    {"SpringGreen", detail::col::SpringGreen},
    {"SpringGreen1", detail::col::SpringGreen1},
    {"SpringGreen2", detail::col::SpringGreen2},
    {"SpringGreen3", detail::col::SpringGreen3},
    {"SpringGreen4", detail::col::SpringGreen4},
    {"steel blue", detail::col::steel_blue},
    {"SteelBlue", detail::col::SteelBlue},
    {"SteelBlue1", detail::col::SteelBlue1},
    {"SteelBlue2", detail::col::SteelBlue2},
    {"SteelBlue3", detail::col::SteelBlue3},
    {"SteelBlue4", detail::col::SteelBlue4},
    {"tan", detail::col::tan},
    {"tan1", detail::col::tan1},
    {"tan2", detail::col::tan2},
    {"tan3", detail::col::tan3},
    {"tan4", detail::col::tan4},
    {"thistle", detail::col::thistle},
    {"thistle1", detail::col::thistle1},
    {"thistle2", detail::col::thistle2},
    {"thistle3", detail::col::thistle3},
    {"thistle4", detail::col::thistle4},
    {"tomato", detail::col::tomato},
    {"tomato1", detail::col::tomato1},
    {"tomato2", detail::col::tomato2},
    {"tomato3", detail::col::tomato3},
    {"tomato4", detail::col::tomato4},
    {"turquoise", detail::col::turquoise},
    {"turquoise1", detail::col::turquoise1},
    {"turquoise2", detail::col::turquoise2},
    {"turquoise3", detail::col::turquoise3},
    {"turquoise4", detail::col::turquoise4},
    {"violet", detail::col::violet},
    {"violet red", detail::col::violet_red},
    {"VioletRed", detail::col::VioletRed},
    {"VioletRed1", detail::col::VioletRed1},
    {"VioletRed2", detail::col::VioletRed2},
    {"VioletRed3", detail::col::VioletRed3},
    {"VioletRed4", detail::col::VioletRed4},
    {"wheat", detail::col::wheat},
    {"wheat1", detail::col::wheat1},
    {"wheat2", detail::col::wheat2},
    {"wheat3", detail::col::wheat3},
    {"wheat4", detail::col::wheat4},
    {"white", detail::col::white},
    {"white smoke", detail::col::white_smoke},
    {"WhiteSmoke", detail::col::WhiteSmoke},
    {"yellow", detail::col::yellow},
    {"yellow green", detail::col::yellow_green},
    {"yellow1", detail::col::yellow1},
    {"yellow2", detail::col::yellow2},
    {"yellow3", detail::col::yellow3},
    {"yellow4", detail::col::yellow4},
    {"YellowGreen", detail::col::YellowGreen}};

namespace cturtle {
class Color {
public:
  typedef uint8_t component_t;

  union {
    struct {
      component_t r;
      component_t g;
      component_t b;
    };
    component_t components[3];
  };

  Color(cturtle::detail::color_int_t packedColor) {
    cturtle::detail::resolveColorComp(packedColor, r, g, b);
  }

  /*\brief Color constructor for unsigned 8-bit RGB values.
    \param r Red component.
    \param g Green component.
    \param b Blue component.*/
  Color(component_t r, component_t g, component_t b) : r(r), g(g), b(b) {};

  /*\brief Copy constructor.
    \param other Constant reference to other instance of a color object.*/
  Color(const Color &other) : r(other.r), g(other.g), b(other.b) {}

  /*\brief Name constructor. Takes a literal color name as an input.
    \param name The name of the color from which to derive value.
    \sa fromName()*/
  Color(const std::string &name);

  /*\brief Default constructor.
                   Initializes this color to white. (all components 255)*/
  Color() { r = g = b = 255; }

  Color &operator=(cturtle::detail::color_int_t pack) {
    cturtle::detail::resolveColorComp(pack, r, g, b);
    return *this;
  }

  /**\brief Returns a pointer to the first component of this color.
                   This is useful for functions which require color as an input
    array. Returns a read-only pointer to the elements, in sequential order.*/
  const component_t *rgbPtr() const { return &components[0]; }
};

/**
 * Generates and returns a random color.
 * @return
 */
inline Color randomColor() {
  static std::default_random_engine rng(detail::epochTime());
  static std::uniform_int_distribution<int> rng_dist(0, 255);
  return Color((uint8_t)rng_dist(rng), (uint8_t)rng_dist(rng),
               (uint8_t)rng_dist(rng));
}

/**\brief Retrieves a read-only reference to a color
 *         associated with the specified input name string.
 * Default colors have an associated name string you can use to retrieve
 * their values. All of the names can be found here:
 * https://www.tcl.tk/man/tcl8.4/TkCmd/colors.htm */
inline Color fromName(const std::string &name) {
  if (name == "random")
    return randomColor();

  if (NAMED_COLORS.count(name))
    return NAMED_COLORS.at(name);

  throw std::runtime_error("No color by the name \"" + name + "\" exists.");
}

// Define named color constructor after the definition of the named color map.

/*\brief Name constructor.
                 Takes a literal color name as an input.
  \param name The name of the color from which to derive value.
  \sa fromName()*/
inline Color::Color(const std::string &name) {
  const Color c = fromName(name);
  r = c.r;
  g = c.g;
  b = c.b;
}

} // namespace cturtle
