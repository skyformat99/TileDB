/**
 * @file   dimension.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017 TileDB, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * This file implements class Dimension.
 */

#include "dimension.h"
#include <cstdlib>
#include "utils.h"

namespace tiledb {

/* ********************************* */
/*     CONSTRUCTORS & DESTRUCTORS    */
/* ********************************* */

Dimension::Dimension(
    const char* name,
    Datatype type,
    const void* domain,
    const void* tile_extent) {
  // Set name
  if (name != nullptr)
    name_ = name;

  // Set type
  type_ = type;

  // Get type size
  uint64_t type_size = utils::datatype_size(type);

  // Set domain
  if (domain == nullptr) {
    domain_ = nullptr;
  } else {
    uint64_t domain_size = 2 * type_size;
    domain_ = malloc(domain_size);
    memcpy(domain_, domain, domain_size);
  }

  // Set tile extent
  if (tile_extent == nullptr) {
    tile_extent_ = nullptr;
  } else {
    tile_extent_ = malloc(type_size);
    memcpy(tile_extent_, tile_extent, type_size);
  }

  // Set default compressor and compression level
  compressor_ = Compressor::NO_COMPRESSION;
  compression_level_ = -1;
}

Dimension::~Dimension() {
  // Clean up
  if (domain_ != nullptr)
    free(domain_);
  if (tile_extent_ != nullptr)
    free(tile_extent_);
}

/* ********************************* */
/*              SETTERS              */
/* ********************************* */

void Dimension::set_compressor(Compressor compressor) {
  compressor_ = compressor;
}

void Dimension::set_compression_level(int compression_level) {
  compression_level_ = compression_level;
}

}  // namespace tiledb
