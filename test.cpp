#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include "TleRecord.hpp"
#include "_deps/catch2-src/src/catch2/catch_all.hpp"


TEST_CASE("Decoding is valid", "[decoding]")
{
    std::string line0 = "NOAA 1 [-]                  ";
    std::string line1 = "1 04793U 70106A   22245.45853542 -.00000050  00000+0 -40295-4 0  9998";
    std::string line2 = "2 04793 101.5506 307.3106 0031822 171.7841 201.3026 12.54007165367245";

    auto ptr = TleRecord::parse(line0, line1, line2);

    REQUIRE(ptr->name == "NOAA 1 [-]");
    REQUIRE(ptr->catalog_number == 4793);
    REQUIRE(ptr->classification == 'U');
    REQUIRE(ptr->year == 70);
}