#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "../_deps/requests-src/include/HTTPRequest.hpp"
#include "TleRecord.hpp"

class TleDataset
{
public:
    TleDataset(const std::string iUrl) : URL(iUrl) {}

    bool fetchFromUrl(std::string &oBody) const
    {
        try
        {
            std::cout << "Fetching from URL: " << URL << std::endl;
            http::Request request{URL};
            const auto response = request.send("GET");
            std::cout << "Response status code: " << response.status.code << std::endl;
            const std::string body(response.body.begin(), response.body.end());
            oBody = body;
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Request failed, error: " << e.what() << '\n';
            return false;
        }
    }

    void fetch()
    {
        std::string body;

        if (fetchFromUrl(body))
        {
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
    }

private:
    const std::string URL;
    std::vector<std::shared_ptr<TleRecord>> records;
};