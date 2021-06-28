#include "pch.h"
#include <iostream>
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Bluetooth.Advertisement.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <Windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
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

void scanForDevice();

int main() 
{
    scanForDevice();
}

void OnAdverReceived(BluetoothLEAdvertisementWatcher watcher, BluetoothLEAdvertisementReceivedEventArgs eventArgs)
{
    if ((uint64_t)0xd58d10fc1f39 == eventArgs.BluetoothAddress())
    {
        auto awaitBluetooth = BluetoothLEDevice::FromBluetoothAddressAsync((uint64_t)0xd58d10fc1f39);
        BluetoothLEDevice nRF = awaitBluetooth.get();
        auto waiting = nRF.GetGattServicesAsync(BluetoothCacheMode::Uncached);
        auto result = waiting.get();

        std::cout << result.Services().Size() << std::endl;

        std::array<uint8_t, 8> ar = { 17,17,17,17,17,17,17,17 };
        std::array<uint8_t, 8> ar2 = { 34,34,34,34,34,34,34,34 };

        winrt::guid Guid((uint32_t)0x111111111, (uint16_t)0x1111, (uint16_t)0x1111, ar);
        winrt::guid charGuid((uint32_t)0x22222222, (uint16_t)0x2222, (uint16_t)0x2222, ar2);

        auto bruh = nRF.GetGattServicesForUuidAsync(Guid);
        auto d = bruh.get();
        auto services = d.Services();
        std::cout << "Service Size: " << services.Size() << std::endl;
        std::cout << "Char Size: " << services.GetAt(0).GetCharacteristicsForUuidAsync(charGuid).get().Characteristics().Size() << std::endl;
        // DataWriter f;
        // f.WriteInt16(102);
        // auto b = services.GetAt(0).GetCharacteristicsForUuidAsync(charGuid).get().Characteristics().GetAt(0).WriteValueAsync(f.DetachBuffer());

        // auto re = services.GetAt(0).GetCharacteristicsForUuidAsync(charGuid).get().Characteristics().GetAt(0).CharacteristicProperties();
        // std::cout << (int)re << std::endl;
    }

    return;
}

void scanForDevice()
{
    std::cout << "Lets Find some BLE Devices: Press Enter to Quit" << std::endl;

    BluetoothLEAdvertisementWatcher watch;
    watch.Received(&OnAdverReceived);
    watch.Start();
    while (getchar() != '\n');
    watch.Stop();
}