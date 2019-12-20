#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <vector>

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>

#include "DBManager.h"
#include "Container.h"

mongocxx::instance inst{};
mongocxx::client conn{mongocxx::uri{}};

class TestDBManager: public::testing::Test{
protected:
	void SetUp();
	void TearDown();
	DBManager *db_manager;

private:
	mongocxx::v_noabi::collection collection;
};

void TestDBManager::SetUp(){
	collection = conn["testdb"]["testcollection"];
	db_manager = new DBManager(collection);
}

void TestDBManager::TearDown(){
	delete db_manager;
}


TEST(DBManagerTest, InitTest){
	auto collection = conn["testdb"]["testcollection"];
	EXPECT_NO_THROW(DBManager db_manager(collection));
}

TEST_F(TestDBManager, GetFreeContainerTest){
	Container *empty_container;
	EXPECT_NO_THROW(empty_container = db_manager->get_free_container());
	EXPECT_EQ(empty_container->get_key(), std::vector<double>{});
	EXPECT_EQ(empty_container->get_data(), "");

	delete empty_container;
}

TEST_F(TestDBManager, InvalidSaveLoadContainerTest){
	Container invalid_container("12312");

	ASSERT_ANY_THROW(db_manager->save_container(&invalid_container));
	ASSERT_ANY_THROW(db_manager->get_container("123123"));
}

TEST_F(TestDBManager, SaveLoadContainerTest){
	Container *container;
	EXPECT_NO_THROW(container = db_manager->get_free_container());
	
	std::vector<double> key{10.123013323, 1283.124235345, 4.345341236, 5.3453454234, 38.1233993};
	std::string data = "https://vk.com/id1234";

	EXPECT_NO_THROW(container->set_key(key));
	EXPECT_NO_THROW(container->set_data(data));

	EXPECT_EQ(key, container->get_key());
   	EXPECT_EQ(data, container->get_data());

   	EXPECT_NO_THROW(db_manager->save_container(container));

   	std::string container_id = container->id;

   	Container *loaded_container;
   	EXPECT_NO_THROW(loaded_container = db_manager->get_container(container_id));

   	EXPECT_EQ(key, loaded_container->get_key());
   	EXPECT_EQ(data, loaded_container->get_data());

   	delete container;
   	delete loaded_container;
}



int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}