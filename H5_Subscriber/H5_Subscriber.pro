QT += core
QT -= gui

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += main.cpp \
    imageservice.pb.cc

DISTFILES += \
    imageservice.proto

HEADERS += \
    imageservice.pb.h \
    h5sub.h

INCLUDEPATH+= "C:/Program Files/eCAL/lang/c++/protobuf3/include"
INCLUDEPATH+= "C:/Program Files/eCAL/lang/c++/protobuf3/compiler"
INCLUDEPATH+= "C:/Program Files/eCAL/lang/c++/ecal/include"
INCLUDEPATH+= "C:/OpenCV3.2/opencv/build/include"

win32{
CONFIG(debug, debug|release) {
LIBS += "C:/Program Files/eCAL/lang/c++/protobuf3/lib/v140/x64/Debug Dll/libprotobuf.lib"
LIBS += "C:/Program Files/eCAL/lang/c++/ecal/lib/v140/x64/Debug Dll/ecal64d.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/ucrtd.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/Ws2_32.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/WSock32.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/Kernel32.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/Psapi.lib"
LIBS += "C:/Program Files/eCAL/lang/c++/ecalhdf5/lib/v140/x64/Debug Dll/ecal_hdf5.lib"
LIBS += "C:/Program Files/eCAL/lang/c++/ecalhdf5/lib/v140/x64/Debug Dll/libhdf5.lib"

LIBS +=  -LC:/OpenCV3.2/opencv/build/x64/vc14/lib/ -lopencv_world320d
}

CONFIG(release, debug|release) {
LIBS += "C:/Program Files/eCAL/lang/c++/protobuf3/lib/v140/x64/Release Dll/libprotobuf.lib"
LIBS += "C:/Program Files/eCAL/lang/c++/ecal/lib/v140/x64/Release Dll/ecal64.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/ucrt.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/Ws2_32.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/WSock32.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/Kernel32.lib"
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/Psapi.lib"
LIBS += "C:/Program Files/eCAL/lang/c++/ecalhdf5/lib/v140/x64/Release Dll/ecal_hdf5.lib"
LIBS += "C:/Program Files/eCAL/lang/c++/ecalhdf5/lib/v140/x64/Release Dll/libhdf5.lib"


LIBS +=  -LC:/OpenCV3.2/opencv/build/x64/vc14/lib/ -lopencv_world320
}
}
