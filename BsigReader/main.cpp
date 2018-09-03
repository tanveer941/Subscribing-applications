#include <iostream>
#include <thread>
#include <list>
//#include <QDebug>
#include "bsig.h"

using namespace std;

std::list <std::string> samplelist = {"SIM VFB ALL.DataProcCycle.ObjSyncEgoDynamic.Longitudinal.MotVar.Velocity","MTS.Package.TimeStamp"};

void BsigNamePublisher()
{
    eCAL::Initialize(NULL, NULL, "Signal name publisher");
    PubObj = new eCAL::CProtoPublisher<class Radar::BsigDataRequest> ("BsigSignalNames");
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    //Bsig Response object
    Radar::BsigDataRequest BsigReqObj;
    Radar::BsigDataResponse BsigResponse;
    // D:/Work/2018/code/LT5G/OLT/Radar_labelling_bsig/bsig_readers/Continuous_2014.05.15_at_08.48.40.bsig
    // D:\Work\2018code\LT5G\OLT\Radar_labelling_bsig\bsig_readers\Continuous_2014.05.15_at_08.48.40.bsig
    // D://Work//2018code//LT5G//OLT//Radar_labelling_bsig//bsig_readers//Continuous_2014.05.15_at_08.48.40.bsig
    BsigReqObj.set_bsigpath("D:/Work/2018/code/LT5G/OLT/Radar_labelling_bsig/bsig_readers/Continuous_2014.05.15_at_08.48.40.bsig");
    BsigReqObj.set_objectidcount(40);
    for(int sig_count=0; sig_count<samplelist.size(); sig_count++)
    {
        std::list<std::string>::iterator it = samplelist.begin();
        std::advance(it, sig_count);
        cout << "Start" << *it << endl;
       // BsigReqObj.set_signalnames(sig_count,it->c_str());
        std::string *signame = BsigReqObj.add_signalnames();
        *signame = it->c_str();
    }

    PubObj->Send(BsigReqObj);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // finalize eCAL API
    eCAL::Finalize();

}

void ReadBsigValues(const char *topic_name_, const Radar::BsigDataResponse &bsgResp)
{
//    bsgResp.eachsigvalues_size()
//    cout << bsgResp.eachsigvalues_size() << endl;
    for(int eachSignalindex = 0; eachSignalindex < bsgResp.eachsigvalues_size(); eachSignalindex++)
    {
        Radar::BSigDataOfEachSignal SigData = bsgResp.eachsigvalues(eachSignalindex);
        std::string Signame = SigData.signalname();
        int objID = SigData.objectid();
        cout << "Signal name >> " << Signame << objID << endl;
        std::list<float> sigValList;
        std::map<std::string, std::list<float>> sigMapper;
        for(int SigValCounter = 0; SigValCounter < SigData.signalvalues_size(); SigValCounter++)
        {
            sigValList.push_back(SigData.signalvalues(SigValCounter));
            cout << SigData.signalvalues(SigValCounter) << endl;
        }
        sigMapper[Signame] = sigValList;
    }

}

void BsigValuesSubscriber()
{
    eCAL::Initialize(NULL, NULL, "CPP Signal value subscriber");
    SubscriberObj = new eCAL::CProtoSubscriber<class Radar::BsigDataResponse> ("BsigSignalValues");
//    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    Radar::BsigDataResponse BsigValResponse;

    while(eCAL::Ok())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        SubscriberObj->AddReceiveCallback(std::bind(&ReadBsigValues, std::placeholders::_1,  std::placeholders::_2));
//        for(int i = 0; i < BsigValResponse.eachsigvalues_size(); i++)
//        {
//            Radar::BSigDataOfEachSignal EachSignal = BsigValResponse.eachsigvalues(i);
//            std::string signame = EachSignal.signalname();
//            cout << signame << endl;
//        }
    }


}

int main(int argc, char *argv[])
{
    double x = 3817821904;
    cout << "Start" << endl;
//    BsigNamePublisher();
    BsigValuesSubscriber();

    return 0;
}
