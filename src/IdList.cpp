
#if !defined(IdList_cpp)
#define IdList_cpp

#include <IdList.hpp>

IdList::IdList(/* args */) {}

void IdList::AddId(std::string id) { id_list.push_back(id); }
IdList::~IdList() {}


#endif  // IdList_cpp
