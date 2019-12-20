#include <gtest/gtest.h>
#include <string>

#include "DB.h"

TEST(DBTest, InitTest){
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	mongocxx::v_noabi::collection collection;

	EXPECT_NO_THROW(collection = conn["testdb"]["testcollection"]);
	EXPECT_NO_THROW(DB db(collection));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}