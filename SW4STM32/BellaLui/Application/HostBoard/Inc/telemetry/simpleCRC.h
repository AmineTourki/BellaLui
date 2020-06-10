/**

 Simplified version of CRC++ 0.2.0.6 (@copyright Daniel Bahr)

 */
#ifndef AVIONICS_TELEMETRY_SIMPLECRC_H
#define AVIONICS_TELEMETRY_SIMPLECRC_H

#include <stdint.h>

static uint16_t CRC_16_TABLE[] =
  { 0x0000, 0xa2eb, 0xe73d, 0x45d6, 0x6c91, 0xce7a, 0x8bac, 0x2947, 0xd922, 0x7bc9, 0x3e1f, 0x9cf4, 0xb5b3, 0x1758,
      0x528e, 0xf065, 0x10af, 0xb244, 0xf792, 0x5579, 0x7c3e, 0xded5, 0x9b03, 0x39e8, 0xc98d, 0x6b66, 0x2eb0, 0x8c5b,
      0xa51c, 0x07f7, 0x4221, 0xe0ca, 0x215e, 0x83b5, 0xc663, 0x6488, 0x4dcf, 0xef24, 0xaaf2, 0x0819, 0xf87c, 0x5a97,
      0x1f41, 0xbdaa, 0x94ed, 0x3606, 0x73d0, 0xd13b, 0x31f1, 0x931a, 0xd6cc, 0x7427, 0x5d60, 0xff8b, 0xba5d, 0x18b6,
      0xe8d3, 0x4a38, 0x0fee, 0xad05, 0x8442, 0x26a9, 0x637f, 0xc194, 0x42bc, 0xe057, 0xa581, 0x076a, 0x2e2d, 0x8cc6,
      0xc910, 0x6bfb, 0x9b9e, 0x3975, 0x7ca3, 0xde48, 0xf70f, 0x55e4, 0x1032, 0xb2d9, 0x5213, 0xf0f8, 0xb52e, 0x17c5,
      0x3e82, 0x9c69, 0xd9bf, 0x7b54, 0x8b31, 0x29da, 0x6c0c, 0xcee7, 0xe7a0, 0x454b, 0x009d, 0xa276, 0x63e2, 0xc109,
      0x84df, 0x2634, 0x0f73, 0xad98, 0xe84e, 0x4aa5, 0xbac0, 0x182b, 0x5dfd, 0xff16, 0xd651, 0x74ba, 0x316c, 0x9387,
      0x734d, 0xd1a6, 0x9470, 0x369b, 0x1fdc, 0xbd37, 0xf8e1, 0x5a0a, 0xaa6f, 0x0884, 0x4d52, 0xefb9, 0xc6fe, 0x6415,
      0x21c3, 0x8328, 0x8578, 0x2793, 0x6245, 0xc0ae, 0xe9e9, 0x4b02, 0x0ed4, 0xac3f, 0x5c5a, 0xfeb1, 0xbb67, 0x198c,
      0x30cb, 0x9220, 0xd7f6, 0x751d, 0x95d7, 0x373c, 0x72ea, 0xd001, 0xf946, 0x5bad, 0x1e7b, 0xbc90, 0x4cf5, 0xee1e,
      0xabc8, 0x0923, 0x2064, 0x828f, 0xc759, 0x65b2, 0xa426, 0x06cd, 0x431b, 0xe1f0, 0xc8b7, 0x6a5c, 0x2f8a, 0x8d61,
      0x7d04, 0xdfef, 0x9a39, 0x38d2, 0x1195, 0xb37e, 0xf6a8, 0x5443, 0xb489, 0x1662, 0x53b4, 0xf15f, 0xd818, 0x7af3,
      0x3f25, 0x9dce, 0x6dab, 0xcf40, 0x8a96, 0x287d, 0x013a, 0xa3d1, 0xe607, 0x44ec, 0xc7c4, 0x652f, 0x20f9, 0x8212,
      0xab55, 0x09be, 0x4c68, 0xee83, 0x1ee6, 0xbc0d, 0xf9db, 0x5b30, 0x7277, 0xd09c, 0x954a, 0x37a1, 0xd76b, 0x7580,
      0x3056, 0x92bd, 0xbbfa, 0x1911, 0x5cc7, 0xfe2c, 0x0e49, 0xaca2, 0xe974, 0x4b9f, 0x62d8, 0xc033, 0x85e5, 0x270e,
      0xe69a, 0x4471, 0x01a7, 0xa34c, 0x8a0b, 0x28e0, 0x6d36, 0xcfdd, 0x3fb8, 0x9d53, 0xd885, 0x7a6e, 0x5329, 0xf1c2,
      0xb414, 0x16ff, 0xf635, 0x54de, 0x1108, 0xb3e3, 0x9aa4, 0x384f, 0x7d99, 0xdf72, 0x2f17, 0x8dfc, 0xc82a, 0x6ac1,
      0x4386, 0xe16d, 0xa4bb, 0x0650 };

/**
 @brief CRC parameters.
 */
typedef struct
{
  uint16_t polynomial;   ///< CRC polynomial
  uint16_t initialValue;   ///< Initial CRC value
  uint16_t finalXOR;   ///< Value to XOR with the final CRC
} Parameters;

// See https://users.ece.cmu.edu/~koopman/crc/index.html for good polynomials
static Parameters CRC_16_GENERATOR_POLY =
  { 0xA2EB, 0xFFFF, 0xFFFF };

/**
 @brief Computes a 16 bit remainder on a CHAR_BIT=8 machine using a precomputed lookup table.
 @param[in] remainder Running CRC remainder. Can be an initial value or the result of a previous CRC remainder calculation.
 @return CRC remainder
 */
static uint16_t CalculateRemainderFromTable (const uint8_t byte, uint16_t remainder)
{
  remainder = (remainder << 8) ^ CRC_16_TABLE[((remainder >> 8) ^ byte)];
  return remainder;
}

/**
 @brief Finalizes the CRC computation
 @return CRC remainder XOR'ed with CRC_16_GENERATOR_POLY.finalXOR
 */
static uint16_t FinalizeCRC (uint16_t remainder)
{
  return remainder ^ CRC_16_GENERATOR_POLY.finalXOR;
}

#endif //AVIONICS_TELEMETRY_SIMPLECRC_H
