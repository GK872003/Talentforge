#ifndef UTILS_H
#define UTILS_H

#include <vector>

template<typename T>
T average(std::vector<T> v){
    T sum=0;
    for(int i=0;i<v.size();i++) sum+=v[i];
    return v.size()?sum/v.size():0;
}

#endif


