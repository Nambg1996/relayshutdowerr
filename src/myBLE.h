#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
//#include <BLEEddystoneURL.h>
//#include <BLEEddystoneTLM.h>
//#include <BLEBeacon.h>
#include <array>
#include <deque>
int scanTime = 1; // scan for 10 seconds
BLEScan *pBLEScan;
bool flagRegister=false;
// rssi_and_address is value store scan for 20 device one time scan
std::deque<std::pair<int, std::string>> rssi_and_address;   

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
  public:
    static const int MAX_ELEMENTS = 20;
    void saveLatestValue(int rssi, std::string address)
    {
        rssi_and_address.emplace_back(rssi, address);    
        if (rssi_and_address.size() > MAX_ELEMENTS)
        {
            rssi_and_address.pop_front();
        }
    }

    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        int rssi = advertisedDevice.getRSSI();
        std::string address = advertisedDevice.getAddress().toString().c_str();
        saveLatestValue(rssi, address);
    }
};


void getParameterBLE(void (*callbackFunction)(int rssi, const char* address))
{
    for (const auto &[rssi, address] : rssi_and_address)
    {
        callbackFunction(rssi, address.c_str());
    }
}


void beginMyble()
{
    BLEDevice::init("M5ATOM");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); // Active scan uses more power, but get results faster
}

const char* allAdressRssi(const std::deque<std::pair<int, std::string>>& rssi_and_address) {
  std::string output;
  for (const auto& elem : rssi_and_address) {
    output += std::to_string(elem.first) + ": " + elem.second + "\n";
  }
  return output.c_str();
}