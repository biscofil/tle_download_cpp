#include <string>
#include "TleDataset.hpp"

int main(void)
{

    TleDataset aaa("http://celestrak.org/NORAD/elements/gp.php?GROUP=noaa&FORMAT=tle");
    aaa.fetch();

    return 0;
}
