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
void WinBleCentral::connectToFoundDevice(int deviceIndex)
{

    uint64_t deviceAddress = discoveredPeripherals[deviceIndex].BluetoothAddress();
    std::cout << std::hex << "Connect to: " << deviceAddress << std::endl;
    connectPeripheral(deviceAddress);
}

//--------------------------------------------------------------------------------------------
void WinBleCentral::connectToDeviceWithUUID(const char* uuid)
{
    // for items in dicovered peripherals
    // if item.uuid equals uuid
    // connectToPeripheral(item.BluetoothAddress());
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
    if(uuid.Data2 == 0)
        sprintf(uuidCStr, "%04x", uuid.Data1);
    else
        sprintf(uuidCStr, "%08x-%04x-%04x-%02x%02x-%06x", uuid.Data1, uuid.Data2, uuid.Data3, uuid.Data4[0], uuid.Data4[1], d6);
    std::string guid = std::string(uuidCStr);
    return guid;
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::connectPeripheral(uint64_t windowsDeviceAddress)
{
    /*
    * Potential Source of bother.
    https://devblogs.microsoft.com/oldnewthing/20201030-00/?p=104409

    use https://docs.microsoft.com/en-us/uwp/api/windows.foundation.metadata.apiinformation.ismethodpresent?view=winrt-20348

    to test
    */

  //  this->didConnectPeripheral(BluetoothLEDevice::FromBluetoothAddressAsync(windowsDeviceAddress).get());
    auto awaitBluetooth = BluetoothLEDevice::FromBluetoothAddressAsync(127957777215202);
    BluetoothLEDevice nRF = awaitBluetooth.get();

    auto waiting = nRF.GetGattServicesAsync();
    auto result = waiting.get();

    auto bruh = nRF.GetGattServicesAsync();
    auto d = bruh.get();
    auto services = d.Services();
    for (auto service : services)
    {
        std::cout << "Service: " << winrtGuidToString(service.Uuid()) << std::endl;
    }
    //BluetoothLEDevice::FromBluetoothAddressAsync(windowsDeviceAddress).Completed(
    //    [this](IAsyncOperation<BluetoothLEDevice> sender, AsyncStatus status)
    //    {
    //        auto device = sender.GetResults();
    //        switch (status)
    //        {
    //        case winrt::Windows::Foundation::AsyncStatus::Completed:
    //            this->didConnectPeripheral(device);
    //            break;
    //        case winrt::Windows::Foundation::AsyncStatus::Canceled:
    //        case winrt::Windows::Foundation::AsyncStatus::Error:
    //        case winrt::Windows::Foundation::AsyncStatus::Started:
    //            this->didFailToConnectPeripheral();
    //        }
    //    });
}

void WinBleCentral::discoverServices(BluetoothLEDevice device)
{
    /*auto async = device.GetGattServicesAsync();
    if (async.wait_for(5s) == AsyncStatus::Completed)
    {
        didDiscoverServices(async.GetResults().Services(), async.GetResults().Status());
    }*/


    //this->didDiscoverServices(result.Services(), result.Status());
    //worker.Completed(
    //    [this](IAsyncOperation<GattDeviceServicesResult>sender, AsyncStatus status)
    //    {
    //        //if (status == AsyncStatus::Completed)
    //        //{
    //        //    //GattDeviceServicesResult result = sender.get();
    //        //   // sender.get();
    //        //    //this->didDiscoverServices(result.Services(), result.Status());
    //        //}
    //        //else
    //        //{
    //        //    this->didFailToDiscoverServices();
    //        //}
    //    });
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::didDiscoverPeripheral(BluetoothLEAdvertisementWatcher watcher,
    BluetoothLEAdvertisementReceivedEventArgs eventArgs)
{

    if (isPeripheralNew(eventArgs) && eventArgs.RawSignalStrengthInDBm() > -60 && 127957777215202 == eventArgs.BluetoothAddress())
    {
        discoveredPeripheralUUIDs.push_back(eventArgs.BluetoothAddress());
        discoveredPeripherals.push_back(eventArgs);
        bleWatcher.Stop();
        if (shouldReport)
        {
            std::cout << "Device UUID: " << eventArgs.BluetoothAddress() << std::endl;
            printDeviceDescription(eventArgs);
        }
        
        connectToFoundDevice(discoveredPeripherals.size() - 1);
    }
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::didConnectPeripheral(BluetoothLEDevice &device)
{
    if (!connecting)
    {
        
        this->connecting = true;
        std::wcout << "didConnectPeripheral" << std::endl;
    }
}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didDisconnectPeripheral() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didFailToConnectPeripheral()
{
    std::cout << "didFailToConnectPeripheral" << std::endl;
}
void WinBleCentral::didFailToDiscoverServices()
{
    std::cout << "didFailToDiscoverServices" << std::endl;
}
//--------------------------------------------------------------------------------------------
void WinBleCentral::didDiscoverIncludedServicesForService() {}

//--------------------------------------------------------------------------------------------
void WinBleCentral::didDiscoverServices(IVectorView<GattDeviceService> services, GattCommunicationStatus status)
{
    std::cout << "didDiscoverServices" << std::endl;

    if (status == GattCommunicationStatus::Success)
    {
        for (auto service : services)
        {
            std::cout << "Service: " << winrtGuidToString(service.Uuid()) << std::endl;
        }
    }
    else
    {
        std::cout << "Error Getting Services: ";
        switch (status)
        {
        case winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus::Unreachable:
            std::cout << "Unreachable";
            break;
        case winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus::ProtocolError:
            std::cout << "ProtocolError";
            break;
        case winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus::AccessDenied:
            std::cout << "AccessDenied";
            break;
        }
        std::cout << std::endl;
    }
}

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

    for (auto service : deviceAdvert.ServiceUuids())
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
    std::cout << std::dec <<  "RSSI: " << device.RawSignalStrengthInDBm() <<  std::endl;
    std::cout << "*----------------------------------------*" << std::endl;
}
//--------------------------------------------------------------------------------------------
bool WinBleCentral::isPeripheralNew(BluetoothLEAdvertisementReceivedEventArgs eventArgs)
{
    return (discoveredPeripheralUUIDs.empty() || !(std::find(discoveredPeripheralUUIDs.begin(), discoveredPeripheralUUIDs.end(), eventArgs.BluetoothAddress()) != discoveredPeripheralUUIDs.end()));
}



void oldGetDeviceInfo()
{
    //auto gattServices = device.GetGattServicesAsync(BluetoothCacheMode::Uncached).get(); // https://docs.microsoft.com/en-us/cpp/parallel/concrt/reference/task-class?view=msvc-160#get

    //std::cout << gattServices.Services().Size() << std::endl;

    //std::array<uint8_t, 8> ar = { 17,17,17,17,17,17,17,17 };
    //std::array<uint8_t, 8> ar2 = { 34,34,34,34,34,34,34,34 };

    //winrt::guid Guid((uint32_t)0x111111111, (uint16_t)0x1111, (uint16_t)0x1111, ar);
    //winrt::guid charGuid((uint32_t)0x22222222, (uint16_t)0x2222, (uint16_t)0x2222, ar2);

    //auto bruh = device.GetGattServicesForUuidAsync(Guid);
    //auto d = bruh.get();
    //auto services = d.Services();
    //std::cout << "Service Size: " << services.Size() << std::endl;
    //std::cout << "Char Size: " << services.GetAt(0).GetCharacteristicsForUuidAsync(charGuid).get().Characteristics().Size() << std::endl;
    // DataWriter f;
    // f.WriteInt16(102);
    // auto b = services.GetAt(0).GetCharacteristicsForUuidAsync(charGuid).get().Characteristics().GetAt(0).WriteValueAsync(f.DetachBuffer());

    // auto re = services.GetAt(0).GetCharacteristicsForUuidAsync(charGuid).get().Characteristics().GetAt(0).CharacteristicProperties();
    // std::cout << (int)re << std::endl;
}