#include "totdataread.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#ifdef unix
#include <root/TFile.h>
#include <root/TSystem.h>
//#include <root/TTree.h>
#endif
//#pragma link C++ class vector<ClusterType>;
#include <root/TROOT.h>


TOTdataread::TOTdataread()
{
}

void TOTdataread::ReadDataCreateRootTree(string nameTOTfile)
{
    gROOT->ProcessLine(".L ./tmp.cxx+");
    gSystem->Load("./tmp_cxx.so");
    string S;
    cout << S << endl;

    fstream ifDataFile;
    ifDataFile.open(nameTOTfile.c_str(),ios::in);
    getline(ifDataFile,S);

    if (strcmp(S.substr(0,5).c_str(),"Frame")) {
        cerr << "No Data" << endl;
        cerr << S.substr(0,5).c_str() << endl;
        getline(ifDataFile,S);
        if (strcmp(S.substr(0,5).c_str(),"Frame"))
        {cerr << "No Data" << endl; cerr << S.substr(0,5).c_str() << endl;ifDataFile.close();
        return;}
    }
    ifDataFile.close();

    ClusterType Cluster;
    vector<ClusterType> *Frame = new vector<ClusterType>();
    Double_t TimeStamp;
    UInt_t FrameId;
    UInt_t FrameIdPrev=0;
    UShort_t NClustsInFrame;
    UShort_t NPxlsInClust[MaxNClust];

    string InFileName = nameTOTfile.substr(0,nameTOTfile.find_last_of("."));

    TFile fData((InFileName+".root").c_str(),"RECREATE");
    fData.cd();

    runData = new TTree("tot","TOTData");

    runData->Branch("TimeStamp",&TimeStamp,"TimeStamp/D");
    runData->Branch("FrameId",&FrameId,"FrameId/i");
    runData->Branch("NClustsInFrame",&NClustsInFrame,"NClustsInFrame/i");
    runData->Branch("NPxlsInClust",NPxlsInClust,"NPxlsInClust[NClustsInFrame]/s");
    runData->Branch("Frames",Frame);

    fstream InFile;
    InFile.open(nameTOTfile.c_str(),ios::in);

    int TMP=0;

    while (!InFile.eof())
    {
        getline(InFile,S);

        if (S.find("Frame")!=string::npos || S.find("[")!=string::npos)
        {
            if (S.find("Frame")!=string::npos)
            {
                //Frame->clear();
                string::size_type framepos = 0;
                framepos = S.find_first_of("(");
                FrameId = atoi(S.substr(6,framepos-7).c_str());
                TimeStamp=atof(S.substr(framepos+1,18).c_str());
                TMP++;
                NClustsInFrame=0;
//                if (FrameId<FrameIdPrev)  {cout << FrameId << " ErroR!!! " << FrameIdPrev << endl;cout << S.c_str() << endl;}
                FrameIdPrev = FrameId;
            }
            if (S.find("[")!=string::npos)
            {
                //NPxlsInClust[NClustsInFrame]=0;
                Cluster = valueoftot(S);
                NPxlsInClust[NClustsInFrame] = Cluster.size();
                Frame->push_back(Cluster);
                Cluster.clear();
                NClustsInFrame++;
            }
        }
        else
        {
//            cout << " Frame " << Frame->size() << "  ";
            runData->Fill();
            //NClustsInFrame++;
            Frame->clear();
        }
        //cout << FrameId << " " << endl;

    }
    if (Frame->size())
    {
        cout << " Frame END " << Frame->size() << "  ";
        runData->Fill();
        //NClustsInFrame++;
        Frame->clear();
    }

    cout << NClustsInFrame <<" <<< --- NClustsInFrame & Size = " << TMP <</*F << */endl;
    runData->Write();
    fData.Close();
    InFile.close();
    //delete runData;
}

ClusterType TOTdataread::valueoftot(string ToTsmatrixval)
{
    ClusterType outCluster;

    int counter = 0;
    string bufcopymatrix;

    string::size_type position = 0;
    string::size_type position2 = 0;

    while ((position = ToTsmatrixval.find("[", position)) != string::npos)
    {
        if ((position2 = ToTsmatrixval.find("]", position)) != string::npos);
        ++counter;
        bufcopymatrix = ToTsmatrixval.substr((position+1),(position2-position-1));

        ++position;++position2;
        outCluster.push_back(ToTnumb(bufcopymatrix));
     }
    return outCluster;
}

PixValue TOTdataread::ToTnumb(string ToTnumbstring)
{
    string::size_type position = 0;
    string::size_type position2 = 0;

    PixValue TOTvalue;

    position = ToTnumbstring.find_first_of(",");
    position2 = ToTnumbstring.find_last_of(",");


    TOTvalue.first = XYpos((unsigned char)atoi(ToTnumbstring.substr(0,position).c_str()),(unsigned char)atoi(ToTnumbstring.substr(position+2,(position2-position-2)).c_str()));
    TOTvalue.second = (Short_t)atoi(ToTnumbstring.substr(position2+2).c_str());
    return TOTvalue;
}
