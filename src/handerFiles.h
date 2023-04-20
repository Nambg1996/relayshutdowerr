#include <SPIFFS.h>

 String getDataJson() {
    String jsonString;
    if (SPIFFS.exists("/data.json")) {
        File dataFile = SPIFFS.open("/data.json", "r");
        if (dataFile) {
            jsonString = dataFile.readString();
            dataFile.close();
        } else {
            Serial.println("Failed to open data.json file");
        }
    } else {
        Serial.println("data.json file does not exist");
    }
    return jsonString;
}



bool addDataToFile(String data) {
    String jsonString = getDataJson();
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error) {
        Serial.print(F("deserializeJson() failed:"));
        Serial.println(error.c_str());
        return false;
    }
    JsonArray beaconAddress = doc["beaconAddress"];
    for (int i = 0; i < beaconAddress.size(); i++) {
        if (beaconAddress[i] == data) {
            return false;
        }
    }
    beaconAddress.add(data);
    File dataFile = SPIFFS.open("/data.json", "w");
    if (dataFile) {
        serializeJson(doc, dataFile);
        dataFile.close();
        return true;
    } else {
        Serial.println("Failed to open data.json file for writing");
        return false;
    }
}





bool createDataJsonFile(){
  
    if (!SPIFFS.exists("/data.json")) {
        File dataFile = SPIFFS.open("/data.json", "w");
        if (dataFile) {
            dataFile.println("{\"beaconAddress\":[]}");
            dataFile.close();
            return true;
        } else {
            Serial.println("Failed to create data.json file");
            return false;
        }
    }
    return true;
}
bool deleteDataJsonFile() {
    if (SPIFFS.exists("/data.json")) {
        SPIFFS.remove("/data.json");
        return true;
    }
    return false;
} 



bool removeData(String data) {
    String jsonString = getDataJson();
    DynamicJsonDocument docr(1024);
    DeserializationError error = deserializeJson(docr, jsonString);
    if (error) {
        Serial.print(F("deserializeJson() failed:"));
        Serial.println(error.c_str());
        return false;
    }
    JsonArray beaconAddress = docr["beaconAddress"];
    bool found = false;
    for (int i = 0; i < beaconAddress.size(); i++) {
        if (beaconAddress[i] == data) {
            found = true;
            beaconAddress.remove(i);
            break;
        }
    }
    if (!found) {
        return false;
    }
    File dataFile = SPIFFS.open("/data.json", "w");
    if (dataFile) {
        serializeJson(docr, dataFile);
        dataFile.close();
        return true;
    } else {
        Serial.println("Failed to open data.json file for writing");
        return false;
    }
}



bool checkAddressRegister(String data, String address) {
 /*    data.toLowerCase();
  address.toLowerCase();
   */
  // Check if the data string is found in the address string
  int index = data.indexOf(address);
  if (index != -1) {
    //Serial.println("Data string found at index " + String(index));
    return true;
  }
  else {
    //Serial.println("Data string not found");
  }
  
  // Data string not found in address string
  return false;
}



/* class MyFileHandler {
public:
    String getDataJson() {
        String jsonString;
        if (SPIFFS.exists("/data.json")) {
            File dataFile = SPIFFS.open("/data.json", "r");
            if (dataFile) {
                jsonString = dataFile.readString();
                dataFile.close();
            } else {
                Serial.println("Failed to open data.json file");
            }
        } else {
            Serial.println("data.json file does not exist");
        }
        return jsonString;
    }
  
    bool addDataToFile(String data) {
        String jsonString = getDataJson();
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, jsonString);
        if (error) {
            Serial.print(F("deserializeJson() failed:"));
            Serial.println(error.c_str());
            return false;
        }
        JsonArray beaconAddress = doc["beaconAddress"];
        for (int i = 0; i < beaconAddress.size(); i++) {
            if (beaconAddress[i] == data) {
                return false;
            }
        }
        beaconAddress.add(data);
        File dataFile = SPIFFS.open("/data.json", "w");
        if (dataFile) {
            serializeJson(doc, dataFile);
            dataFile.close();
            return true;
        } else {
            Serial.println("Failed to open data.json file for writing");
            return false;
        }
    }
  
    bool createDataJsonFile() {
        if (!SPIFFS.exists("/data.json")) {
            File dataFile = SPIFFS.open("/data.json", "w");
            if (dataFile) {
                dataFile.println("{\"beaconAddress\":[]}");
                dataFile.close();
                return true;
            } else {
                Serial.println("Failed to create data.json file");
                return false;
            }
        }
        return true;
    }
  
    bool deleteDataJsonFile() {
        if (SPIFFS.exists("/data.json")) {
            SPIFFS.remove("/data.json");
            return true;
        }
        return false;
    }
}; */