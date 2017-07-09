/**
 * @file   basic_array_schema.h
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
 * This file defines class BasicArraySchema.
 */

#ifndef __TILEDB_BASIC_ARRAY_SCHEMA_H__
#define __TILEDB_BASIC_ARRAY_SCHEMA_H__

#include "array_schema.h"

namespace tiledb {

/** Defines the BasicArraySchema. */
class BasicArraySchema {
 public:
  /* ********************************* */
  /*     CONSTRUCTORS & DESTRUCTORS    */
  /* ********************************* */

  /**
   * Consturctor.
   *
   * @param name The name of the basic array.
   */
  BasicArraySchema(const char* name);

  /** Destructor. */
  ~BasicArraySchema();

  /* ********************************* */
  /*                API                */
  /* ********************************* */

  /**
   * Returns the underlying array schema.
   *
   * @return The array schema.
   */
  ArraySchema* array_schema();

  /**
   * Initializes the array schema.
   *
   * @return Status
   */
  Status init();

 private:
  /* ********************************* */
  /*         PRIVATE ATTRIBUTES        */
  /* ********************************* */

  /** The array schema object that implements BasicArraySchema. */
  ArraySchema* array_schema_;
};

}  // namespace tiledb

#endif  // __TILEDB_BASIC_ARRAY_SCHEMA_H__
