#ifndef _BUCKET_
#define _BUCKET_

#include <string>
#include <stack>
#include <unordered_map>
#include "type.h"

class Bucket{
	public:
		std::string key;
		Type binding;

		Bucket(std::string key_, Type binding_) : key{key_}, binding{binding_}{}

};

typedef std::unordered_map<std::string,std::stack<Bucket>> bucketmap;

class HashT{
	public:
		static bucketmap table;
		static void insert(std::string key, Type binding){
			if(table.find(key) == HashT::table.end()){
				Bucket bucket(key, binding);
				std::stack<Bucket> bucketStack; 
				bucketStack.push(bucket);
				table[key] = bucketStack;
			}else{
				Bucket bucket(key, binding);
				table.find(key).push(bucket);
			}
			
		}
};

#endif