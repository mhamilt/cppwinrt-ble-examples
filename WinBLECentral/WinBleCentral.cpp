#include "pch.h"
#include "WinBleCentral.h"

//--------------------------------------------------------------------------------------------
WinBleCentral::WinBleCentral()
{
    bleWatcher.Received([this](BluetoothLEAdvertisementWatcher watcher, BluetoothLEAdvertisementReceivedEventArgs eventArgs) {this->didDiscoverPeripheral(watcher, eventArgs); });
    bleWatcher.Stopped([](BluetoothLEAdvertisementWatcher w, BluetoothLEAdvertisementWatcherStoppedEventArgs b) {});
}
//--------------------------------------------------------------------------------------------
WinBleCentral::~WinBleCentral()
{
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::scan()
{
    bleWatcher.Start();
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::stop()
{
    bleWatcher.Stop();
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::connectToFoundDevice(int deviceIndex) {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::connectToDeviceWithUUID(const char* uuid) 
{
    uint64_t deviceAddress;
    BluetoothLEDevice::FromBluetoothAddressAsync(deviceAddress);
}

//--------------------------------------------------------------------------------------------
void WinBleCentral::connectToDeviceWithName(const char* name) {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::clearDicoveredPeripherals() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::getRssiOfFoundDevice(int deviceIndex) {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::getFoundDeviceList() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::setRssiSensitivity(int rssiSensitivity) {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::setIgnoreiPhone(bool shouldIgnore) {}
//--------------------------------------------------------------------------------------------
std::string WinBleCentral::winrtGuidToString(winrt::guid uuid)
{
    char uuidCStr[34];
    uint64_t d6 = *((uint64_t*)&uuid.Data4[2]);
    sprintf(uuidCStr, "%08x-%04x-%04x-%02x%02x-%06x", uuid.Data1, uuid.Data2, uuid.Data3, uuid.Data4[0], uuid.Data4[1], d6);
    std::string guid = std::string(uuidCStr);
    return guid;
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::didDiscoverPeripheral(BluetoothLEAdvertisementWatcher watcher,
    BluetoothLEAdvertisementReceivedEventArgs eventArgs)
{
    if (isPeripheralNew(eventArgs))
    {
        discoveredPeripheralUUIDs.push_back(eventArgs.BluetoothAddress());
        discoveredPeripherals.push_back(eventArgs);

        if (shouldReport)
        {
            std::cout << "Device UUID: " << eventArgs.BluetoothAddress() << std::endl;
            printDeviceDescription(eventArgs);
        }
    }
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::didConnectPeripheral() {  }

//--------------------------------------------------------------------------------------------
void WinBleCentral::didDisconnectPeripheral() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didFailToConnectPeripheral() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didDiscoverIncludedServicesForService() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didDiscoverServices() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didDiscoverCharacteristicsForService() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didUpdateValueForDescriptor() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didUpdateValueForCharacteristic() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didDiscoverDescriptorsForCharacteristic() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::postCharacteristicDescription() {}
//--------------------------------------------------------------------------------------------
void WinBleCentral::printDeviceDescription(BluetoothLEAdvertisementReceivedEventArgs device)
{
    BluetoothLEAdvertisement deviceAdvert = device.Advertisement();
    std::cout << "Name: " << deviceAdvert.LocalName().c_str() << std::endl;
    
    for (auto service: deviceAdvert.ServiceUuids())            
        std::cout << "UUID: " << winrtGuidToString(service) << std::endl;        
     
    for (auto manuData : deviceAdvert.ManufacturerData())
    {       
        std::cout << std::hex << "Manu: ";
        printf("%04x : ", manuData.CompanyId());

        for (size_t i = 0; i < manuData.Data().Length(); i++)
        {
            printf("%02x", manuData.Data().data()[i]);
        }
        std::cout << std::endl;
    }
    std::cout << "*----------------------------------------*" << std::endl;
}
//--------------------------------------------------------------------------------------------
bool WinBleCentral::isPeripheralNew(BluetoothLEAdvertisementReceivedEventArgs eventArgs)
{
    return (discoveredPeripheralUUIDs.empty() || !(std::find(discoveredPeripheralUUIDs.begin(), discoveredPeripheralUUIDs.end(), eventArgs.BluetoothAddress()) != discoveredPeripheralUUIDs.end()));
}

