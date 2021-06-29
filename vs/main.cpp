/*
 * A Very Simple BLE Device Scanner
 */

#include "pch.h"
#include <iostream>
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Bluetooth.Advertisement.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <Windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
//--------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------
void scanForDevice();
//--------------------------------------------------------------------------------------------
std::vector<uint64_t> deviceUUIDs;
//--------------------------------------------------------------------------------------------

int main() 
{
    scanForDevice();
}
//--------------------------------------------------------------------------------------------
void OnAdverReceived(BluetoothLEAdvertisementWatcher watcher,
         BluetoothLEAdvertisementReceivedEventArgs eventArgs)
{        
    if (deviceUUIDs.empty() || !(std::find(deviceUUIDs.begin(), deviceUUIDs.end(), eventArgs.BluetoothAddress()) != deviceUUIDs.end()))
    {
        deviceUUIDs.push_back(eventArgs.BluetoothAddress());
        std::cout << "Device UUID: " << eventArgs.BluetoothAddress() << std::endl;
    }
    return;
}
//--------------------------------------------------------------------------------------------
void scanForDevice()
{
    std::cout << "Lets Find some BLE Devices: Press Enter to Quit" << std::endl;

    BluetoothLEAdvertisementWatcher watch;
    watch.Received(&OnAdverReceived);
    watch.Start();
    while (getchar() != '\n');
    watch.Stop();
}
//--------------------------------------------------------------------------------------------