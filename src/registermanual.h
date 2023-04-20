
#include <string>
#include <vector>

/* std::vector<std::string> dataStore = {
    "ef:be:54:f8:c5:9c",
    "ec:ee:01:3a:97:86",
    "cd:09:fe:8f:7f:1a",
    "d8:97:b4:6e:bc:35",
    "52:77:e2:cd:26:2b",
    "f5:86:9e:af:bc:6c",
    "fb:3a:16:b4:31:1f",
    "ea:7f:4a:5b:ce:1f",
    "e1:c8:d1:74:98:73",
    "59:b5:b5:f2:a7:87",
    "de:7f:e9:06:76:51",
    "dd:10:bb:19:3f:88",
    "cd:61:52:c4:f7:49",
    "c6:f7:61:fa:6f:11",
    "ef:92:17:ed:6f:a2",
    "e3:ed:50:30:0f:d2",
    "f4:1d:cf:1e:67:57",
    "eb:79:19:94:e0:3b",
    "c1:cf:5d:5d:c0:e2",
    "f7:45:3d:07:25:c3",
    "c2:7d:e4:b8:5d:cc",
    "fc:06:01:13:ea:e2"

  }; */

  std::vector<std::string> dataStore = {"f7:45:3d:07:25:c3"};


void processDataStore(std::vector<std::string>& dataStore) {
    
for (auto& dataRegis : dataStore) {
    addDataToFile(String(dataRegis.c_str()));
};

}