#include "BaseDB.h"
#include "KDTree.h"
#include "SearchEngine.h"
#include "DBManager.h"
#include "DB.h"

DB::DB(mongocxx::v_noabi::collection collection){

	db_manager = new DBManager(collection);
	data_structure = new KDTree("...", db_manager);
	search_engine = new SearchEngine(data_structure, db_manager);
}

DB::~DB(){

	delete db_manager;
	delete data_structure;
	delete search_engine;	
}

void DB::add(const std::vector<double>& key, const std::string& data){
	data_structure->add(key, data);
}