#pragma once
// Windows BLE Interface
#include <iostream>

using winrt::Windows::Devices::Bluetooth::BluetoothConnectionStatus;
using winrt::Windows::Devices::Bluetooth::BluetoothLEDevice;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher;
using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristic;
using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties;
using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicsResult;
using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCommunicationStatus;
using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService;
using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceServicesResult;
using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattSession;
using winrt::Windows::Storage::Streams::DataWriter;
using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattWriteOption;
using winrt::Windows::Devices::Bluetooth::BluetoothCacheMode;




class WinBleCentral
{
public:    
    WinBleCentral();
    ~WinBleCentral();
    void scan();
    
    //void scanForService(t_atom* serviceUUID, long argc);
    void stop();
    void connectToFoundDevice(int deviceIndex);
    void connectToDeviceWithUUID(const char* uuid);
    void connectToDeviceWithName(const char* name);
    void clearDicoveredPeripherals();
    void getRssiOfFoundDevice(int deviceIndex);
    void getFoundDeviceList();
    void setRssiSensitivity(int rssiSensitivity);
    void setIgnoreiPhone(BOOL shouldIgnore);
    //void setMaxObjectRef(MaxExternalObject* extMaxObjectRef);
    void setReporting(BOOL reportingMode);
    void subscribeToCharacteristic(const char* cuuid,
        const char* suuid,
        int deviceIndex);
private:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="watcher"></param>
    /// <param name="eventArgs"></param>
    void didDiscoverPeripheral(BluetoothLEAdvertisementWatcher watcher, BluetoothLEAdvertisementReceivedEventArgs eventArgs);
    void didConnectPeripheral();
    void didDisconnectPeripheral();
    void didFailToConnectPeripheral();
    void didDiscoverIncludedServicesForService();
    void didDiscoverServices();
    void didDiscoverCharacteristicsForService();
    void didUpdateValueForDescriptor();
    void didUpdateValueForCharacteristic();
    void didDiscoverDescriptorsForCharacteristic();
    void postCharacteristicDescription();

private:
    std::vector<uint64_t> discoveredPeripherals;
    uint32_t connectDeviceIndex;
    int rssiSensitivity;
    BluetoothLEAdvertisementWatcher bleWatcher;
};

