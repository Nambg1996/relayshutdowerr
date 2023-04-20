const char* serviceAdressValue(const char* output_cstr) {
  String lines[20];
  int numLines = 0;
  char *ptr = strtok((char *)output_cstr, "\n");
  while (ptr != NULL && numLines < 20) {
    lines[numLines++] = String(ptr);
    ptr = strtok(NULL, "\n");
  }

  // combine the last 10 lines into a new string
  String lastTenLines;
  for (int i = max(0, numLines - 5); i < numLines; i++) {
    lastTenLines += lines[i];
    if (i < numLines - 1) {
      lastTenLines += "\n";
    }
  }

  // convert to char array
  const char *lastTenLines_cstr = lastTenLines.c_str();
  return lastTenLines_cstr;
}


String pickupBeaconAdress(String data, int n) {
  // extract beacon addresses from data string
  int start = data.indexOf("[") + 1;
  int end = data.indexOf("]");
  String addresses = data.substring(start, end);

  // split the addresses string into an array
  String addrArray[20];
  int numAddr = 0;
  char *addrPtr = strtok((char *)addresses.c_str(), ",");
  while (addrPtr != NULL && numAddr < 20) {
    addrArray[numAddr++] = String(addrPtr);
    addrPtr = strtok(NULL, ",");
  }

  // pick random n addresses
  String result = "";
  for (int i = 0; i < n && i < numAddr; i++) {
    int randIndex = random(numAddr - i);
    result += addrArray[randIndex];
    if (i < n - 1 && i < numAddr - 1) {
      result += ",";
    }
    addrArray[randIndex] = addrArray[numAddr - i - 1];
  }
  return result;
}


typedef struct {
    const char* allInforScan;
    const char* addressRegister;
    const char* addressValueRegister;
} prefix;

prefix prefixs = {
    .allInforScan = "aaa",
    .addressRegister = "bbb",
    .addressValueRegister = "ccc"
};



void runfunctionEverySecond(unsigned long interval, void (*func)(void)) {
  static unsigned long lastCall = 0;
  if (millis() - lastCall > interval) {
    func();  // Call the function passed as argument
    lastCall = millis();
  }
}



void runRandomFunctionOnce() {
    // Seed the random number generator with the current time
    srand(time(0));

    // Generate a random number between 0 and 2
    int randomNum = rand() % 3;

    // Call the corresponding function based on the random number
    if (randomNum == 0) {
        //functionA();
        masterTransmit(prefixs.addressValueRegister+addressAndValueRegister());


    } else if (randomNum == 1) {
        //functionB();
              String dataRegister = getDataJson();
     String dataRegister5 = pickupBeaconAdress(dataRegister, 5);
     masterTransmit(prefixs.addressRegister+dataRegister5);


    } else {
       // functionC();
    const char *allScanResultRssiAdress = allAdressRssi(rssi_and_address);
    const char *pickup5ResultFromScan = serviceAdressValue(allScanResultRssiAdress);
     masterTransmit(prefixs.allInforScan+String(pickup5ResultFromScan));



    }
}



