#ifndef H5SUB_H
#define H5SUB_H

#endif // H5SUB_H

#include <ecal/ecal.h>
#include <ecal/msg/proto.h>

#include "imageservice.pb.h"

eCAL::CProtoSubscriber<class ImageService::devicesDataResponse> *SubscriberObj = nullptr;
eCAL::CProtoSubscriber<class ImageService::ImageResponse> *h5ImageSubscrObj = nullptr;
