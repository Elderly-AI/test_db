#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "DBManager.h"
#include "KDTree.h"

mongocxx::instance inst{};
mongocxx::client conn{mongocxx::uri{}};

class TestKDTree: public::testing::Test{
protected:
	void SetUp();
	void TearDown();

	KDTree *kd_tree;
	std::vector<std::vector<double>> test_keys;
	std::vector<std::vector<double>> neighbour_search_tests;
	std::vector<std::string> neighbour_search_answers;


private:
	void load_test_keys();
	void neighbour_search_search_test_data();

	DBManager *db_manager;
	mongocxx::v_noabi::collection collection;
};

void TestKDTree::SetUp(){

	load_test_keys();
	neighbour_search_search_test_data();

	collection = conn["testdb"]["testcollection"];
	db_manager = new DBManager(collection);
	kd_tree = new KDTree("...", db_manager);
}

void TestKDTree::TearDown(){
	delete db_manager;
	delete kd_tree;
}

void TestKDTree::load_test_keys(){
	std::ifstream inFile;
    inFile.open("Tests/GeneratedTests/test_data.txt");

    if(inFile.fail()){
    	ADD_FAILURE();
    }

    size_t vector_size;
    inFile >> vector_size;

    while(!inFile.eof()){
    	std::vector<double> key;
    	for(int i = 0; i < vector_size; ++i){
			std::string x;
			inFile >> x;
			key.push_back(::atof(x.c_str()));
		}

		if(!inFile.eof()){
			test_keys.push_back(key);
		}
    }
    inFile.close();
}

void TestKDTree::neighbour_search_search_test_data(){
	std::ifstream inFile;
	inFile.open("Tests/GeneratedTests/nearest_neighbour_data.txt");
	
	if(inFile.fail()){
    	ADD_FAILURE();
    }

	size_t vector_size;
	inFile >> vector_size;

	while(!inFile.eof()){
		std::string answer;
		std::vector<double> neighbour_vector;
		double buffer;

		for(int i = 0; i < vector_size; ++i){
			inFile >> buffer;
			neighbour_vector.push_back(buffer);
		}
		inFile >> answer;

		if(!inFile.eof()){
			neighbour_search_tests.push_back(neighbour_vector);
			neighbour_search_answers.push_back(answer);
		}
	}
	inFile.close();	
}



TEST(KDTreeTest, InitTest){
	auto collection = conn["testdb"]["testcollection"];
	DBManager *db_manager;
	
	EXPECT_NO_THROW(db_manager = new DBManager(collection));
	EXPECT_NO_THROW(KDTree kd_tree("...", db_manager));

	delete db_manager;
}


TEST_F(TestKDTree, AddTest){
	for(auto &key : test_keys){
		EXPECT_NO_THROW(kd_tree->add(key, std::to_string(key[0])));
	}
}
/*
TEST_F(TestKDTree, RangeSearchTest){

	for(auto &key : test_keys){
		EXPECT_NO_THROW(kd_tree->add(key, std::to_string(key[0])));
	}

	//kd_tree->add(std::vector<double>{0, 0, 0, 0}, "0");
	//kd_tree->add(std::vector<double>{0.5, 0.8, 0.3, 0.4}, "0.5");
	//kd_tree->add(std::vector<double>{0.2, 0.1, 0.2, 0.3}, "0.2");

	std::vector<std::string> kd_tree_range_search_answers;
	EXPECT_NO_THROW(kd_tree_range_search_answers = kd_tree->range_search(test_keys[0], test_keys[1]));

	for(auto &e : kd_tree_range_search_answers){
		std::cout << e << " ";
	}
	std::cout << "\n\n";

	for(auto &e : range_search_test_data){
		std::cout << e << " ";
	}
	std::cout << "\n";
	/*
	while(std::next_permutation(kd_tree_range_search_answers.begin(), kd_tree_range_search_answers.end())){
    	if(range_search_test_data == kd_tree_range_search_answers){
    		SUCCEED();
    	}
    }

    ADD_FAILURE();*/

    //EXPECT_NO_THROW(kd_tree->add(key, std::to_string(key[0])));

    /*std::vector<std::string> range_search_answers;
    inFile.open("/home/awerkiler/progs/Mail/old1/AdvancedC ++/Project/8/Tests/range_search_data.txt"); //TODO

	while(!inFile.eof()){
		std::string x;
		inFile >> x;
		range_search_answers.push_back(x);
	}

	
    std::vector<std::string> kd_tree_range_search_answers;
    EXPECT_NO_THROW(kd_tree_range_search_answers = kd_tree->range_search);

    while(std::next_permutation(range_search_answers.begin(), range_search_answers.end())){
    	if(range_search_answers == )
    }

	for(auto &e : range_search_answers){
    	for(int i = 0; i < 45; ++i){
    		std::cout << e[i] << " ";
    	}
    	std::cout << "\n";
    }

	inFile.close();
}*/

TEST_F(TestKDTree, NeighborSearch){
	for(auto &key : test_keys){
		EXPECT_NO_THROW(kd_tree->add(key, std::to_string(key[0])));
	}

	for(size_t c = 0; c < neighbour_search_tests.size(); ++c){
		std::string kd_tree_answer;
		EXPECT_NO_THROW(kd_tree_answer = kd_tree->neighbor_search(neighbour_search_tests[c])[0]);
		EXPECT_EQ(kd_tree_answer, neighbour_search_answers[c]);
	}
}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}