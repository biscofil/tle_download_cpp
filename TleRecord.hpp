
#pragma once

#include <memory>
#include <boost/algorithm/string.hpp>

class TleRecord
{
public:
    std::string name;
    char classification;
    int catalog_number, year, epoch_year;
    float epoch;

    std::string toString() const
    {
        std::string out = "[ NAME '" + name + "', " +                         //
                          "CLASS " + classification + ", " +                  //
                          "CATNUM " + std::to_string(catalog_number) + ", " + //
                          "EPOCH YEAR " + std::to_string(epoch_year) + ", " + //
                          "EPOCH " + std::to_string(epoch) + ", " + //
                          "YEAR " + std::to_string(year) + "]";
        return out;
    }

    static std::shared_ptr<TleRecord> parse(const std::string &line0, const std::string &line1, const std::string &line2)
    {
        auto out = std::make_shared<TleRecord>();

        out->name = line0.substr(0, 24);
        boost::trim_right(out->name);

        out->catalog_number = std::stoi(line1.substr(2, 5));
        out->classification = line1.at(7);
        out->year = std::stoi(line1.substr(9, 2));

        out->epoch_year = std::stoi(line1.substr(18, 2));
        out->epoch = std::stof(line1.substr(10, 11));

        return out;
    }

    /*
    LINE 1
    Field	Columns	Content	                                    Example
        1	01  	Line number	                                1
        2	03–07	Satellite catalog number	                25544
        3	08	    Classification (U: unclassified, C: classified, S: secret) [11]	U
        4	10–11	International Designator (last two digits of launch year)	98
        5	12–14	International Designator (launch number of the year)	067
        6	15–17	International Designator (piece of the launch)	A
        7	19–20	Epoch year (last two digits of year)	    08
        8	21–32	Epoch (day of the year and fractional portion of the day)	264.51782528
        9	34–43	First derivative of mean motion; the ballistic coefficient [12]	-.00002182
        10	45–52	Second derivative of mean motion (decimal point assumed) [12]	00000-0
        11	54–61	B*, the drag term, or radiation pressure coefficient (decimal point assumed) [12]	-11606-4
        12	63–63	Ephemeris type (always zero; only used in undistributed TLE data) [13]	0
        13	65–68	Element set number. Incremented when a new TLE is generated for this object. [12]	292
        14	69	    Checksum (modulo 10)	7

    LINE 2
    Field	Columns	Content	                                    Example
        1	01  	Line number	                                2
        2	03–07	Satellite Catalog number	                25544
        3	09–16	Inclination (degrees)	                    51.6416
        4	18–25	Right ascension of the ascending node (degrees)	247.4627
        5	27–33	Eccentricity (decimal point assumed)	    0006703
        6	35–42	Argument of perigee (degrees)	            130.5360
        7	44–51	Mean anomaly (degrees)	                    325.0288
        8	53–63	Mean motion (revolutions per day)	        15.72125391
        9	64–68	Revolution number at epoch (revolutions)	56353
        10	69	    Checksum (modulo 10)	                    7
    */
};