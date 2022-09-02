#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "HTTPRequest.hpp"
#include "TleRecord.hpp"

class TleDataset
{
public:
    void fetch()
    {
        try
        {
            // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
            http::Request request{URL};

            // send a get request
            const auto response = request.send("GET");

            const std::string body(response.body.begin(), response.body.end());

            std::istringstream f(body);
            std::string line, line0, line1, line2;
            while (std::getline(f, line))
            {
                if (line.at(0) == '1')
                {
                    line1 = line;
                    line2 = "";
                }
                else if (line.at(0) == '2')
                {
                    line2 = line;

                    auto ptr = TleRecord::parse(line0, line1, line2);
                    records.push_back(ptr);

                    std::cout << ptr->toString() << std::endl;
                }
                else
                {
                    line0 = line;
                    line1 = "";
                    line2 = "";
                }
            }

        }
        catch (const std::exception &e)
        {
            std::cerr << "Request failed, error: " << e.what() << '\n';
        }
    }

    std::vector<std::shared_ptr<TleRecord>> records;

private:
    std::string URL = "http://celestrak.org/NORAD/elements/gp.php?GROUP=noaa&FORMAT=tle";
};