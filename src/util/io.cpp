#include "CTurtle/util/io.hpp"
namespace cturtle {
KeyboardKey keyFromName(const std::string &name) { return NAMED_KEYS.at(name); }
} // namespace cturtle
