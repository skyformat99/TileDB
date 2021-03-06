/**
 * @file   unit-cppapi-schema.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017 TileDB Inc.
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
 * Tests the C++ API for schema related functions.
 */

#include "catch.hpp"
#include "tiledb/sm/cpp_api/tiledb"

TEST_CASE("C++ API: Schema", "[cppapi]") {
  using namespace tiledb;
  Context ctx;

  Domain domain(ctx);
  auto d1 = Dimension::create<int>(ctx, "d1", {{-100, 100}}, 10);
  auto d2 = Dimension::create<int>(ctx, "d2", {{0, 100}}, 5);
  domain.add_dimension(d1).add_dimension(d2);

  auto a1 = Attribute::create<int>(ctx, "a1");
  auto a2 = Attribute::create<std::string>(ctx, "a2");
  auto a3 = Attribute::create<std::array<double, 2>>(ctx, "a3");
  auto a4 = Attribute::create<std::vector<uint32_t>>(ctx, "a4");
  a1.set_compressor({TILEDB_BLOSC_LZ, -1});

  SECTION("Array Schema") {
    ArraySchema schema(ctx, TILEDB_DENSE);
    schema.set_domain(domain);
    schema.add_attribute(a1);
    schema.add_attribute(a2);
    schema.add_attribute(a3);
    schema.add_attribute(a4);
    schema.set_cell_order(TILEDB_ROW_MAJOR);
    schema.set_tile_order(TILEDB_COL_MAJOR);
    schema.set_offsets_compressor({TILEDB_DOUBLE_DELTA, -1});
    schema.set_coords_compressor({TILEDB_ZSTD, -1});

    auto attrs = schema.attributes();
    CHECK(attrs.count("a1") == 1);
    CHECK(attrs.count("a2") == 1);
    CHECK(attrs.count("a3") == 1);
    REQUIRE(schema.attribute_num() == 4);
    CHECK(schema.attribute(0).name() == "a1");
    CHECK(schema.attribute(1).name() == "a2");
    CHECK(schema.attribute(2).name() == "a3");
    CHECK(schema.attribute("a1").compressor().compressor() == TILEDB_BLOSC_LZ);
    CHECK(schema.attribute("a2").cell_val_num() == TILEDB_VAR_NUM);
    CHECK(schema.attribute("a3").cell_val_num() == 16);
    CHECK(schema.attribute("a4").cell_val_num() == TILEDB_VAR_NUM);
    CHECK(schema.attribute("a4").type() == TILEDB_UINT32);

    auto dims = schema.domain().dimensions();
    REQUIRE(dims.size() == 2);
    CHECK(dims[0].name() == "d1");
    CHECK(dims[1].name() == "d2");
    CHECK_THROWS(dims[0].domain<uint32_t>());
    CHECK(dims[0].domain<int>().first == -100);
    CHECK(dims[0].domain<int>().second == 100);
    CHECK_THROWS(dims[0].tile_extent<unsigned>());
    CHECK(dims[0].tile_extent<int>() == 10);
  }

  SECTION("Map Schema") {
    MapSchema schema(ctx);
    schema.add_attribute(a1);
    schema.add_attribute(a2);
    schema.add_attribute(a3);
    schema.add_attribute(a4);

    auto attrs = schema.attributes();
    CHECK(attrs.count("a1") == 1);
    CHECK(attrs.count("a2") == 1);
    CHECK(attrs.count("a3") == 1);
    REQUIRE(schema.attribute_num() == 4);
    CHECK(schema.attribute(0).name() == "a1");
    CHECK(schema.attribute(1).name() == "a2");
    CHECK(schema.attribute(2).name() == "a3");
    CHECK(schema.attribute("a1").compressor().compressor() == TILEDB_BLOSC_LZ);
    CHECK(schema.attribute("a2").cell_val_num() == TILEDB_VAR_NUM);
    CHECK(schema.attribute("a3").cell_val_num() == 16);
    CHECK(schema.attribute("a4").cell_val_num() == TILEDB_VAR_NUM);
    CHECK(schema.attribute("a4").type() == TILEDB_UINT32);
  }
}
