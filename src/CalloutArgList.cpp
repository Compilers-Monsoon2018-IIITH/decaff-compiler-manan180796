#if !defined(CalloutArgList_cpp)
#define CalloutArgList_cpp

#include <CalloutArgList.hpp>

CalloutArgList::CalloutArgList() {}

void CalloutArgList::AddArgument(CalloutArg* argument) {
    argument_list.push_back(argument);
}

#endif  // CalloutArgList_cpp
