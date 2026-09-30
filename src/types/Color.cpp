// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#include "CTurtle/types/Color.hpp"

#include <chrono>
#include <random>
#include <thread>
namespace cturtle {
namespace detail {

void resolveColorComp(color_int_t pack, uint8_t& r, uint8_t& g, uint8_t& b) {
    r = (pack & 0x00FF0000) >> 16;  // Red
    g = (pack & 0x0000FF00) >> 8;   // Green
    b = (pack & 0x000000FF);        // >> 0;  //Blue
}
time_t epochTime() {
    return std::chrono::system_clock::now().time_since_epoch() /
           std::chrono::milliseconds(1);
}

void sleep(long ms) {
    if (ms <= 0) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
}  // namespace detail

Color::Color(cturtle::detail::color_int_t packedColor) {
    cturtle::detail::resolveColorComp(packedColor, r, g, b);
}

Color::Color(component_t r, component_t g, component_t b) : r(r), g(g), b(b) {};

Color::Color(const Color& other) : r(other.r), g(other.g), b(other.b) {};

Color::Color() { r = g = b = 255; };

Color& Color::operator=(cturtle::detail::color_int_t pack) {
    cturtle::detail::resolveColorComp(pack, r, g, b);
    return *this;
}

const Color::component_t* Color::rgbPtr() const { return &components[0]; }

Color randomColor() {
    static std::default_random_engine rng(detail::epochTime());
    static std::uniform_int_distribution<int> rng_dist(0, 255);
    return Color((uint8_t)rng_dist(rng), (uint8_t)rng_dist(rng),
                 (uint8_t)rng_dist(rng));
}

Color fromName(const std::string& name) {
    if (name == "random") return randomColor();

    if (NAMED_COLORS.count(name)) return NAMED_COLORS.at(name);

    throw std::runtime_error("No color by the name \"" + name + "\" exists.");
}

Color::Color(const std::string& name) {
    const Color c = fromName(name);
    r = c.r;
    g = c.g;
    b = c.b;
}
}  // namespace cturtle
