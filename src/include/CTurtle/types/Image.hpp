// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#ifndef CTURTLE_TYPES_IMAGE_HPP
#define CTURTLE_TYPES_IMAGE_HPP
#include "CTurtle/cimg_pch.hpp"

#include <stdint.h>

namespace cturtle {
/**The common Image type used by CTurtle.*/
typedef cimg_library::CImg<uint8_t> Image;
} // namespace cturtle
#endif
