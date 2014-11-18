/* Simple TCP server setup
you can use this for sending
AT commands and viewing how 
commands are recvd by the 
ESP8266
*/

void setup() {
  Serial1.begin(115200); 
  Serial.begin(115200);
  Serial1.println("AT+RST");
  //delay(1000);
  //Serial1.println("AT+CIPMODE=0");
  //delay(1000);
  //Serial1.println("AT+CIPMUX=1");
  //delay(1000);
  //Serial1.println("AT+CIPSERVER=1,8888");
}


/*Need to send to get set up as tcp server
AT+CIPMODE=0
AT+CIPMUX=1
AT+CIPSERVER=1,8888 OR WHATEVER PORT YOU WANT
*/

// copy from and to each port 
void loop() { 
 while(Serial1.available()) 
 Serial.write(Serial1.read()); 
 while(Serial.available()) 
 Serial1.write(Serial.read()); 
}

