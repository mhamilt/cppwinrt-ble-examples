#include "pch.h"
#include "WinBleCentral.h"


WinBleCentral::WinBleCentral()
{
    bleWatcher.Received([this](BluetoothLEAdvertisementWatcher watcher, BluetoothLEAdvertisementReceivedEventArgs eventArgs) {this->didDiscoverPeripheral(watcher, eventArgs); });
}

WinBleCentral::~WinBleCentral()
{
}

void WinBleCentral::scan()
{    
    bleWatcher.Start();
}

void WinBleCentral::stop()
{
    bleWatcher.Stop();
}

void WinBleCentral::didDiscoverPeripheral(BluetoothLEAdvertisementWatcher watcher,
    BluetoothLEAdvertisementReceivedEventArgs eventArgs)
{
    if (discoveredPeripherals.empty() || !(std::find(discoveredPeripherals.begin(), discoveredPeripherals.end(), eventArgs.BluetoothAddress()) != discoveredPeripherals.end()))
    {
        discoveredPeripherals.push_back(eventArgs.BluetoothAddress());
        std::cout << "Device UUID: " << eventArgs.BluetoothAddress() << std::endl;
    }
}