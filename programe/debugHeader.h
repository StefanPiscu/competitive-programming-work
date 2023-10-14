#include <string>
#include <utility>
#include <vector>

template<typename T>
auto i_format(T var) -> decltype(std::string(var));
template<typename T>
auto i_format(T var) -> decltype(std::to_string(var));
template<typename T1, typename T2>
std::string i_format(std::pair<T1, T2> var);
template<typename T>
std::string i_format(std::vector<T> v);
std::string i_format(...);

template<typename T>
auto i_format(T var) -> decltype(std::string(var)){
	return std::string(var);
}

template<typename T>
auto i_format(T var) -> decltype(std::to_string(var)){
	return std::to_string(var);
}

template<typename T1, typename T2>
std::string i_format(std::pair<T1, T2> var){
	auto a=i_format(var.first);
	auto b=i_format(var.second);
	std::string ret="<"+a+", "+b+">";
	return ret;
}

template<typename T>
std::string i_format(std::vector<T> v){
	std::string ret;
	ret="[";
	for(int i=0;i<v.size();++i){
		ret+=i_format(v[i]);
		if((i+1)!=v.size()) ret+=", ";
	}
	ret+="]";
	return ret;
}

std::string i_format(...){
	return "N/A";
}

#define format(var) i_format(var)

namespace{
std::string i_trim(const std::string &str){
	auto l=str.begin(), r=str.end();
	while(l!=r && std::isspace(*l)) l++;
	do{r--;}while(r!=l && std::isspace(*r));
	return std::string(l, r+1);
}

std::string i_extractName(std::string &varNames){
	auto loc=varNames.find(",");
	std::string ret=varNames.substr(0, loc);
	varNames=varNames.substr(loc+1, varNames.size());
	return i_trim(ret);
}
}

void i_blog(std::string varNames){};
template<typename T, typename ...Tpack>
void i_blog(std::string varNames, T var, Tpack... varPack){
	std::cerr<<" "<<i_extractName(varNames)<<": "<<format(var)<<std::endl;
	i_blog(varNames, varPack...);	
}
template<typename ...Tpack>
void i_blog(const int line, const std::string file, std::string varNames, Tpack... varPack){
	std::cerr<<"Logging at line "<<line<<" in file "<<file<<": \n"<<std::endl;
	i_blog(varNames, varPack...);
	std::cerr<<"\nEnd of log"<<std::endl;
}

#define blog(...) i_blog(#__VA_ARGS__, ##__VA_ARGS__) 
#define blogv(...) i_blog(__LINE__, __FILE__, #__VA_ARGS__, ##__VA_ARGS__) 

/*
#ifdef DEBUG
	#include "../../debugHeader.h"
#else
	#define blog
	#define blogv
#endif
*/