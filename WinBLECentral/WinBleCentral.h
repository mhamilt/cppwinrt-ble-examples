#pragma once
// Windows BLE Interface
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using winrt::Windows::Devices::Bluetooth::BluetoothConnectionStatus;
using winrt::Windows::Devices::Bluetooth::BluetoothLEDevice;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisement;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementReceivedEventArgs;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcher;
using winrt::Windows::Devices::Bluetooth::Advertisement::BluetoothLEAdvertisementWatcherStoppedEventArgs;
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
    void setIgnoreiPhone(bool shouldIgnore);
    //void setMaxObjectRef(MaxExternalObject* extMaxObjectRef);
    void setReporting(bool reportingMode);
    void subscribeToCharacteristic(const char* cuuid,
        const char* suuid,
        int deviceIndex);
    std::string winrtGuidToString(winrt::guid);
private:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="watcher"></param>
    /// <param name="eventArgs"></param>
    void didDiscoverPeripheral(BluetoothLEAdvertisementWatcher watcher, BluetoothLEAdvertisementReceivedEventArgs eventArgs);
    void didCancelScanning();
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
    void printDeviceDescription(BluetoothLEAdvertisementReceivedEventArgs device);
    bool isPeripheralNew(BluetoothLEAdvertisementReceivedEventArgs);

private:
    std::vector<uint64_t> discoveredPeripheralUUIDs;
    std::vector<BluetoothLEAdvertisementReceivedEventArgs> discoveredPeripherals;
    bool shouldReport = true;
    uint32_t connectDeviceIndex;
    int rssiSensitivity;
    BluetoothLEAdvertisementWatcher bleWatcher;
};

