// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#include "CTurtle/util/io.hpp"
namespace cturtle {
KeyboardKey keyFromName(const std::string& name) { return NAMED_KEYS.at(name); }
}  // namespace cturtle
