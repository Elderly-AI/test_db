#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/sub_document.hpp>

#include "Container.h"

TEST(ContainerTest, InitTest){
	EXPECT_NO_THROW(Container container("..."));
}

TEST(ContainerTest, SetGetKeyTest){
	std::vector<double> key{1.001001, 2.12312, 3.134534, 4.932509, 5.120301203, 6.123123123};
	Container container("...");

	EXPECT_NO_THROW(container.set_key(key));
	EXPECT_EQ(container.get_key(), key);
}

TEST(ContainerTest, SetGetDataTest){
	std::string data = "https://sun1-14.userapi.com/c854424/v854424235/1825dd/0PVSKnntZqY.jpg";
	Container container("...");

	EXPECT_NO_THROW(container.set_data(data));
	EXPECT_EQ(container.get_data(), data);
}

TEST(ContainerTest, SaveLoadContainerTest){
	std::vector<double> key{10.1230123, 3.23423423, 4.345341236, 5.3453454234};
	std::string data = "https://sun1-23.userapi.com/c850732/v850732891/1d3f40/2eyhc4j7Hx4.jpg";
	Container save_container("...");

	EXPECT_NO_THROW(save_container.set_key(key));
	EXPECT_NO_THROW(save_container.set_data(data));

  bsoncxx::builder::basic::document doc;

  doc.append(bsoncxx::builder::basic::kvp("test", [&save_container](bsoncxx::builder::basic::sub_document sub_doc){
      save_container.save(sub_doc);
    }
  ));

  Container load_container("...");
  EXPECT_NO_THROW(load_container.load(doc.extract().view()["test"]));

  EXPECT_EQ(key, load_container.get_key());
  EXPECT_EQ(data, load_container.get_data());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}