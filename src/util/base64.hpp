#pragma once
#include <cstdint> //For well-defined integer types.
#include <cstring> //For memcpy
#include <sstream> //used for base64 encoding.
#include <string>  //Strings...
#include <vector>  //For Polygon point storage
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
inline std::string encode(const std::vector<unsigned char> &input) {
  std::stringstream encoded;
  std::uint32_t temp{};

  auto it = input.begin();

  for (std::size_t i = 0; i < input.size() / 3; ++i) {
    temp = (*it++) << 16;
    temp += (*it++) << 8;
    temp += (*it++);
    encoded << kEncodeLookup[(temp & 0x00FC0000) >> 18];
    encoded << kEncodeLookup[(temp & 0x0003F000) >> 12];
    encoded << kEncodeLookup[(temp & 0x00000FC0) >> 6];
    encoded << kEncodeLookup[(temp & 0x0000003F)];
  }

  switch (input.size() % 3) {
  case 1:
    temp = (*it++) << 16;
    encoded << kEncodeLookup[(temp & 0x00FC0000) >> 18];
    encoded << kEncodeLookup[(temp & 0x0003F000) >> 12];
    encoded << kPadCharacter << kPadCharacter;
    break;
  case 2:
    temp = (*it++) << 16;
    temp += (*it++) << 8;
    encoded << kEncodeLookup[(temp & 0x00FC0000) >> 18];
    encoded << kEncodeLookup[(temp & 0x0003F000) >> 12];
    encoded << kEncodeLookup[(temp & 0x00000FC0) >> 6];
    encoded << kPadCharacter;
    break;
  }

  return encoded.str();
}
} // namespace base64
