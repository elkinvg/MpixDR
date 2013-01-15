#ifndef TOTDATAREAD_H
#define TOTDATAREAD_H
#include "common.h"
#include <string>

#ifdef unix
#include <root/TFile.h>
#include <root/TTree.h>
#endif

using namespace std;

class TOTdataread
{
public:
    TTree *runData;

    TOTdataread();
    void ReadDataCreateRootTree(string nameTOTfile);
    ClusterType valueoftot(string ToTsmatrixval);
    PixValue ToTnumb(string ToTnumbstring);

};

#endif // TOTDATAREAD_H
