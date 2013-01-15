#include <iostream>
#include "totdataread.h"

using namespace std;

int main(int argc, char** argv)
{
    TOTdataread *dr = new TOTdataread;

    dr->ReadDataCreateRootTree((string)argv[1]);

    delete dr;
    return 0;
}

