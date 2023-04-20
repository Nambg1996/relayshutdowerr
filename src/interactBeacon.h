#define BUTTON_PIN 39
#define LED_BEACON 33
#define LED_INFOR 27

#define MAX_STORE_SIZE 4
void registerBeacon(int rssi, const char *address)
{

  if (rssi > -50 && rssi < -15)
  {
    // Serial.print("Register with new beacon address" + String(address));
    addDataToFile(address);
    digitalWrite(LED_BEACON, HIGH);
    delay(1000);
    // digitalWrite(LED_BEACON, LOW);
  }
}

void unregisterBeacon(int rssi, const char *address)
{

  if (rssi > -40 && rssi < -15)
  {
    // Serial.print("UnRegister with new beacon address" + String(address));
    removeData(address);
    digitalWrite(LED_BEACON, LOW);
    delay(1000);
  }
}

void registerBeaconWithButton(void (*buttonPressed)())
{
  unsigned long start_time = 0;
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    start_time = millis();
    while (digitalRead(BUTTON_PIN) == LOW)
    {
      if (millis() - start_time >= 1000)
      {
        buttonPressed();
        break;
      }
    }
  }
}

void interractBeaconWithButton()
{

  int start_time = 0;
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    start_time = millis();
    while (digitalRead(BUTTON_PIN) == LOW)
    {

      if (millis() - start_time >= 5000)
      {
        // Serial.println("UnRegister with new beacon address");
        getParameterBLE(unregisterBeacon);
        break;
      }
      else
      {

        if (millis() - start_time >= 1000)
        {
          // Serial.println("Register with new beacon address");
          getParameterBLE(registerBeacon);
        }
      }
    }
  }
}

/* const int ARRAY_SIZE = 20;
// Function to update array and calculate sum of last 10 elements
std::array<int, ARRAY_SIZE> arr = {};
void updateArray(std::array<int, ARRAY_SIZE>& arr, int n) {
    // Shift elements to the right by 1 position
    for (int i = arr.size() - 2; i >= 0; i--) {
        arr[i + 1] = arr[i];
    }
    
    // Add new element to the front of the array
    arr[0] = n;
    
    // Calculate sum of last 10 elements
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    
    Serial.print("Array after update: ");
    for (int i = 0; i < arr.size(); i++) {
        Serial.print(arr[i]);
        Serial.print(" ");
    }
    Serial.println();
    
    Serial.print("Sum of last 10 elements: ");
    Serial.println(sum);
}

 */

const int ARRAY_SIZE = 10;
int arr[ARRAY_SIZE];

// Function to add element to array
void addElement(int n) {
    // Shift elements to the right by 1 position
    for (int i = ARRAY_SIZE - 2; i >= 0; i--) {
        arr[i + 1] = arr[i];
    }
    
    // Add new element to the front of the array
    arr[0] = n;
}

// Function to calculate average of array
int calcAvg() {
    int sum = 0;
    int count = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (arr[i] != 0) {
            sum += arr[i];
            count++;
        }
    }
    if (count > 0) {
        return sum / count;
    } else {
        return 0;
    }
}



int checks = 0;
void toTurnOnLed(int rssi, const char *address)
{
  String data = getDataJson();
  // Serial.println(address);
  bool haveRegister = checkAddressRegister(data, address);
 

 

  if (haveRegister)
  {


    addElement(rssi);
    

    
    int rssiAvg=calcAvg();

    Serial.println(rssiAvg);

    

    if (rssiAvg >= -85 && rssiAvg <= -15)
    {
      
      // Serial.println(address);
      digitalWrite(LED_BEACON, HIGH);
      checks = 0;
      // delay(1000);
    }
    else
    {
      digitalWrite(LED_BEACON, LOW);
    }
  }
  else
  {
    checks = checks - 1;
    // Serial.println("print number go to turn off led " + String(checks));
    if (checks < -500000)
    {
      digitalWrite(LED_BEACON, LOW);
      checks = 0;
    }
  }
}








#define MAX_STORE_SIZE 4  // Maximum size of store array

String store[MAX_STORE_SIZE];  // Array to store latest 4 elements
int store_index = 0;  // Index of the next element to be added to the store array

void addTextToStore(String text) {
    // Add the text variable to the store array
    store[store_index] = text;
    // Increment the store index, wrapping around if necessary
    store_index = (store_index + 1) % MAX_STORE_SIZE;
}

String addressAndValueRegister() {
    // Concatenate the contents of the store array into a single string
    String result;
    for (int i = 0; i < MAX_STORE_SIZE; i++) {
        result += store[i];
        if (i < MAX_STORE_SIZE - 1) {
            result += ", ";
        }
    }
    return result;
}

void getRssiAndAdressOfBeaconRegisted(int rssi, const char *address)
{
  
  String data = getDataJson();
  // Serial.println(address);
  bool haveRegister = checkAddressRegister(data, address);
 // Serial.println(haveRegister);
  if (haveRegister)
  {

    String inforRegister = String(address) + '_' + String(rssi);
   // Serial.println(inforRegister);
     //Serial.println("-----------------------------------");
    addTextToStore(inforRegister);

    // saveLatestValueRegistered(rssi, address);
    
  }
  

}








