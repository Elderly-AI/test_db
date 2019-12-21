#include <gtest/gtest.h>
#include <string>

#include "DB.h"

TEST(DBTest, InitTest){
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	mongocxx::v_noabi::collection collection;

	EXPECT_NO_THROW(collection = conn["testdb"]["testcollection"]);

	DB *db;
	EXPECT_NO_THROW(db = new DB(collection));
	delete db;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}