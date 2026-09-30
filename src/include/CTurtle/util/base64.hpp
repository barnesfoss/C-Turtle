// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#pragma once
#include <string>  // Strings...
#include <vector>  // For Polygon point storage
// See https://github.com/mvorbrodt/blog/blob/master/src/base64.hpp for original
// source. The below has been modified to use unsigned characters to avoid
// signed->unsigned->signed fiddling.
namespace base64 {
static constexpr unsigned char kEncodeLookup[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static constexpr unsigned char kPadCharacter = '=';

/**
 * Encodes a given unsigned character buffer to Base64.
 * Can be a file, for example.
 * @param input data buffer
 * @return Base64 encoded string.
 */
std::string encode(const std::vector<unsigned char>& input);

}  // namespace base64
