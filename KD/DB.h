#include <vector>
#include <string>

#include "BaseDB.h"
#include "KDTree.h"
#include "SearchEngine.h"
#include "DBManager.h"

class DB: public BaseDB{
public:
	DB(mongocxx::v_noabi::collection conection);
	~DB();

	void add(const std::vector<double>& key, const std::string& data);

	SearchEngine *search_engine;	

private:
	DBManager *db_manager;
	KDTree *data_structure;
};
