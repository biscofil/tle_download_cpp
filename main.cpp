#include <string>
#include "TleDataset.hpp"

int main(void)
{

    TleDataset ds("http://celestrak.org/NORAD/elements/gp.php?GROUP=noaa&FORMAT=tle");
    ds.fetch();

    return 0;
}
