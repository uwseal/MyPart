/*
The sketch demonstrates how to increase or decrease the Bluetooth Low Energy 4
Advertisement transmission interval.

Faster iterval = higher power consumption = lower connection latency
*/

/*
 Copyright (c) 2014 OpenSourceRF.com.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <RFduinoBLE.h>


// pin 3 on the RGB shield is the green led
int led = 3;

// interval between advertisement transmissions ms (range is 20ms to 10.24s) - default 20ms
int interval = 500;  // 675 ms between advertisement transmissions

void setup() {
  // led used to indicate that the RFduino is advertising
  pinMode(led, OUTPUT);

  // this is the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.deviceName = "myPart";
  
  
  // change the advertisement interval
  RFduinoBLE.advertisementInterval = interval;

  
}

void loop() {
  // start the BLE stack
  
  int i = 0;
  
  while (true) {
    
    i ++ ; // send some new data every time
    RFduinoBLE.advertisementData = (char*) (i);
    
    RFduinoBLE.begin();
    delay(10000); // stop advertising
    RFduinoBLE.end();
  }
  
}

void RFduinoBLE_onAdvertisement(bool start)
{
  // turn the green led on if we start advertisement, and turn it
  // off if we stop advertisement
  
  if (start)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
}