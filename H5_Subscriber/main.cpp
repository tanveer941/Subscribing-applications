#include <iostream>
#include <thread>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "h5sub.h"

using namespace cv;
using namespace std;

void ReadH5Channels(const char *topic_name_, const ImageService::devicesDataResponse &h5ChannelResp)
{
    int numDevices = h5ChannelResp.devicecount();
    cout << "numDevices::"<< numDevices << endl;
    for(int eachChannelindex = 0; eachChannelindex < h5ChannelResp.devicedata_size(); eachChannelindex++)
    {
        ImageService::deviceData h5DeviceData = h5ChannelResp.devicedata(eachChannelindex);
        std::string h5DeviceName = h5DeviceData.devicename();
        int channelCount = h5DeviceData.no_of_channels();
        cout << "devicename::"<< h5DeviceName << endl;
        cout << "channelCount::"<< channelCount << endl;
        std::map<std::string, std::list<float>> channelTimestampMapper;
        for(int eachChannel = 0; eachChannel < h5DeviceData.channel_info_size(); eachChannel++)
        {
            ImageService::channelInfo h5ChannelInfo = h5DeviceData.channel_info(eachChannel);
            std::string channelName = h5ChannelInfo.channel_name();
            std::list<float> timeStampList;
            cout << "channelName::"<< channelName << endl;
            for(int tmStampCounter = 0; tmStampCounter < h5ChannelInfo.timestamp_size(); tmStampCounter++)
            {
                timeStampList.push_back(h5ChannelInfo.timestamp(tmStampCounter));
//                cout << h5ChannelInfo.timestamp(tmStampCounter) << endl;
            }
            channelTimestampMapper[channelName]=timeStampList;
        }
    }
}

void ReadH5Image(const char *topic_name_, const ImageService::ImageResponse &h5ImageResp)
{
    int recvdTimestamp = h5ImageResp.recieved_timestamp();
    cout << recvdTimestamp << endl;

    std::string h5ImageString = h5ImageResp.base_image();
//    cout << h5ImageString << endl;
//    QByteArray imageData = QByteArray::fromStdString(h5ImageString);

    vector<uchar> data(h5ImageString.begin(), h5ImageString.end());
    Mat matImg = cv::imdecode(data, CV_LOAD_IMAGE_UNCHANGED);
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", matImg );

    waitKey(0);
}

void H5ChannelSubsciber()
{
    eCAL::Initialize(NULL, NULL, "H5 channel subscriber");
    SubscriberObj = new eCAL::CProtoSubscriber<class ImageService::devicesDataResponse> ("Channel_Response");
    h5ImageSubscrObj = new eCAL::CProtoSubscriber<class ImageService::ImageResponse> ("HFL_Response");

    SubscriberObj->AddReceiveCallback(std::bind(&ReadH5Channels, std::placeholders::_1,  std::placeholders::_2));
    h5ImageSubscrObj->AddReceiveCallback(std::bind(&ReadH5Image, std::placeholders::_1,  std::placeholders::_2));
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    while(eCAL::Ok())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }

}

int main(int argc, char *argv[])
{
    cout << "Start" << endl;
    H5ChannelSubsciber();
    return 0;
}
