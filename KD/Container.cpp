#include <array>
#include <string>

#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/basic/sub_document.hpp>

#include "Container.h"

Container::Container(const std::string &id_):
	BaseContainer(id_){}

void Container::save(bsoncxx::builder::basic::sub_document &document){

    auto key_array_builder = bsoncxx::builder::basic::array{};

    for (auto &e : key) {
       key_array_builder.append(e);
    }

    document.append(
        bsoncxx::builder::basic::kvp("key", key_array_builder), 
        bsoncxx::builder::basic::kvp("data", data)
    );
}

void Container::load(const bsoncxx::v_noabi::document::element& document_reader){
	size_t c = 0;
    
    for (auto&& e : document_reader["key"].get_array().value) {
        key.push_back((double)e.get_double());
        c++;
    
    }
    data = (std::string)document_reader["data"].get_utf8().value;
}

std::vector<double> Container::get_key(){
	return key;
}

std::string Container::get_data(){
	return data;
}


void Container::set_key(const std::vector<double>& key_){
	key = key_;
}


void Container::set_data(const std::string& data_){
	data = data_;
}