#pragma once
// Windows BLE Interface
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
    void didDiscoverPeripheral();
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

};

