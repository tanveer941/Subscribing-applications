#ifndef BSIG_H
#define BSIG_H

#endif // BSIG_H

#include <ecal/ecal.h>
#include <ecal/msg/proto.h>

#include "Radar.pb.h"

eCAL::CProtoPublisher<class Radar::BsigDataRequest> *PubObj = nullptr;
eCAL::CProtoSubscriber<class Radar::BsigDataResponse> *SubscriberObj = nullptr;
