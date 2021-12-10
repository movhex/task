#include <cstdint>
#include <cstddef>
#include <string>
#include <algorithm>
#include <sstream>
#include <gtest/gtest.h>

#include "object.h"
#include "shared_buffer.h"
#include "generator.h"
#include "sorter.h"


TEST(SorterTest, SorterTest1)
{
    std::string order = "rgb";
    std::string test_data = "rbbrbbrbgr";

    std::ostringstream outstr;
    size_t bufsize = 10;
    SharedBuffer<Object> buf(bufsize);
    Sorter sorter(order);
    sorter.run(&buf, &outstr);

    std::transform(test_data.begin(), test_data.end(), buf.begin(),
        [] (const Object &obj) { return obj.getMarker(); });

    buf.notifyDataReady();
    buf.waitDataDone();

    buf.reset();
    sorter.stop();

    // ASSERT_TRUE(outstr.str() == "rrrrgbbbbb\n");
    ASSERT_STREQ(outstr.str().c_str(), "rrrrgbbbbb\n");
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
