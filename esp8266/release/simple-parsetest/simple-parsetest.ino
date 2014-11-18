/* Simple sketch to parse out commands from TCP socket 
    and send to serial
    new and improved parsing all thanks to James Armstrong
*/

const int LED_PIN = 13;  //Set up pin for LED

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial1.begin(115200); 
  Serial.begin(115200);
  Serial1.println("AT+RST");  //Reset the ESP8266
  delay(1000);                //Delay to let reset run
  Serial1.println("AT+CIPMODE=0");  //set cipmode to control rcv string
  delay(1000);
  Serial1.println("AT+CIPMUX=1");  //set cipmux to allow multiple connections
  delay(1000);
  Serial1.println("AT+CIPSERVER=1,8888");  //turn on tcp server
}
String command;  //String to hold commands sent to ESP

// copy from and to each port 
void loop() { 
 while(Serial.available()) 
 Serial1.write(Serial.read());  
 
 if(Serial1.available())
 {
   char c =Serial1.read();
   Serial.write(c);
   if(c == '\n')
   {
     parseCommand(command);
     command = "";
   }
   else if (c != '\r')command += c;
 }
}
 
 // Read command
void parseCommand(String com)
{
  String maincmd;
  //trying to parse out everything after the :  i.e. +IPD,0,3:off
  if (com.indexOf("+IPD")!=-1) {
    maincmd = com.substring(com.indexOf(":")+1); 
 if(maincmd.equalsIgnoreCase("off"))
 {
   digitalWrite(LED_PIN, LOW);
 } 
 else if (maincmd.equalsIgnoreCase("on")) 
 {
  digitalWrite(LED_PIN, HIGH);
 } 
 else {
       Serial.println(maincmd);
       Serial.println("\" (available commands: \"off\", \"on\")");
   } 
}
}
