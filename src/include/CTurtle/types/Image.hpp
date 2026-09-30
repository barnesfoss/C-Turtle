// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#pragma once
#include <stdint.h>

#include "CImg.h"
namespace cturtle {
/**The common Image type used by CTurtle.*/
typedef cimg_library::CImg<uint8_t> Image;
}  // namespace cturtle
