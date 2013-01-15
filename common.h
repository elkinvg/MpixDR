#ifndef COMMON_H
#define COMMON_H
#include <utility>
#include <vector>
const int MaxNClust=65536;
const int NPix=256;

typedef std::pair<unsigned char,unsigned char> XYpos;
typedef std::pair<XYpos,unsigned short int> PixValue;
typedef std::vector<PixValue> ClusterType;
#endif // COMMON_H
