#include <ESP8266WiFi.h>//esp8266 wifi-support, builtin library enables us to create a web server and listen to incoming requests to it.
#include <Servo.h>//this library allows arduino to control servo motors
#include <DHT.h>//temp & hum sensor library for dht11 sensor
#include <DHTesp.h> //temp & hum sensor library for dht11 & ESP 


int pinDHT11 = 0;//d3
SimpleDHT11 dht22; // Creats a DHT object
const char* ssid = "Nomore"; //ssid of router
const char* password = "muhammad123"; //password of router

int LED = 16; // led connected to D0
int FAN = 13; // led connected to D7
//we configured our web server to listen to port 8080, which is the standard for HTTP communication. 
//For now, just think of port as a gateway through which the requests to access our application comes from.
WiFiServer server(8080);//Creates a server that listens for incoming connections on the specified port
Servo myServo;//define servo name

void setup()
{
  Serial.begin(115200); //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(LED, OUTPUT); //declaring I/O pins
  digitalWrite(LED, LOW);
  pinMode(FAN, OUTPUT);
  digitalWrite(FAN, LOW);
  myServo.attach(2); //d4 servo pin
 myServo.write(0); //servo start position
 // Connect to WiFi network
  Serial.print("Connecting to the Newtork");
  //initiating the connection to WiFi
  WiFi.begin(ssid, password); //Initializes the WiFi library's network settings and provides the current status
  //This process can take some time, which we are checking in a loop. The loop keeps on running as long as the WiFi.status() does not become WL_CONNECTED
  while (WiFi.status() != WL_CONNECTED)//wait until successful connection is established with the access point
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  server.begin();  // Starts the Server
  Serial.println("Server started");
 // Print the IP address
  Serial.print("IP Address of network: "); // Prints IP address on Serial Monitor
  Serial.println(WiFi.localIP()); //Gets the WiFi shield's IP address
  Serial.print("Copy and paste the following URL: https://");
  //printing out the ip address of our web server
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
// Check if a client has connected
// Inside the loop function, we are checking if the client is connected to the server. In other words if someone has searched for the ip address in the browser
 WiFiClient client = server.available();//Gets a client that is connected to the server and has data available for reading. 
 //The connection persists when the returned client object goes out of scope; you can close it by calling client.stop(). 
 //Returns a Client object; if no Client has data available for reading, this object will evaluate to false in an if-statement
  if (!client)//if client is not connected then return. Instructions below are skipped
  {
    return;
  }
   // Wait until the client sends some data
  Serial.println("Waiting for new client");
  while(!client.available())//client.availablereturns the number of bytes that a client (remote client) may have written.
  {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');//readStringUntil() reads characters from the serial buffer into a string. 
  //The function terminates if the terminator character is detected or it times out. () have terminator characyer within them
  Serial.println(request);
  client.flush(); //Waits until all outgoing characters in buffer have been sent
  
 // Match the request
 //Notice that whenever you click the On Off buttons, some new parameters got added to the url (LED=ON  and LED=Off). 
 //whenever we receive the request with LED=ON parameter, we set the led pin to HIGH and assign the same to the variable value. 
 //We followed the same pattern when we receive LED=Off respectively
  int value = LOW;
  if(request.indexOf("/LED=ON") != -1)
  {
    digitalWrite(LED, HIGH); // Turn ON LED
    value = HIGH;
  }
  if(request.indexOf("/LED=OFF") != -1)
  {
    digitalWrite(LED, LOW); // Turn OFF LED
    value = LOW;
  }
  
  //for fan
    int value1 = LOW;
  if(request.indexOf("/FAN=ON") != -1)
  {
    digitalWrite(FAN, HIGH); // Turn ON FAN
    value1 = HIGH;
  }
  if(request.indexOf("/FAN=OFF") != -1)
  {
    digitalWrite(FAN, LOW); // Turn OFF FAN
    value1 = LOW;
  }
  
//FOR DOOR

   int value2 = 0;
  if(request.indexOf("/DOOR=OPEN") != -1)
  {
  myServo.write(180); //servo start position;
   value2=180;
  }
  if(request.indexOf("/DOOR=CLOSE") != -1)
  {
    myServo.write(0); //servo start position
    value2=0;
  }

   // read without samples.
  byte temperature = 0;//initializing tem & hum with value=0
  byte humidity = 0;
  //if dht11 reading is null then printing dht reading failed
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }
  
  
  // DHT11 sampling rate is 1HZ.
  delay(1000);
/*------------------HTML Page Creation---------------------*/
// Return the response
//server is sending the response, in the form of HTML
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");//html in cpp
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 client.println("<head>\n");
client.println("<style>\n");
client.println("body  {\n");
client.println("  \n");
client.println("}\n");
client.println("</style>\n");
client.println("</head>\n");
client.println("<center><body>\n");
client.println("\n");
client.println("<h1 style=\"color:gray;font-family:candara;font-size:300%\"><strong>WIFI BASED SMART HOME SYSTEM</strong></h1>");

  client.print("<h2 style=\"color:gray;font-family:candara;font-size:250%\">TEMPERATURE: ");
 client.print( temperature);//prints temperature measured by sensor
  client.print(" oC");
    client.println("</h2>"); 
  client.println("<h2 style=\"color:gray;font-family:candara;font-size:250%\">HUMIDITY:   ");
    client.print( humidity);//prints humidity measured by sensor
  client.print("%");
  client.print("</h2>");
  client.println("<div class=\"w3-container\">\n");
client.print("<h2 style=\"color:gray;font-family:candara;font-size:250%\">LIGHT:   </h2>");
 
 
  client.println("<a href=\"/LED=ON\"\"><button style=\" color:gray ; height:25px; width:100px\">ON</button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button style=\" color:gray ;height:25px; width:100px\">OFF</button></a><br />");
  
  client.print("<h2 style=\"color:gray;font-family:candara;font-size:250%\">FAN:   </h2>");

  client.println("<a href=\"/FAN=ON\"\"><button style=\"  color:gray ;height:25px; width:100px\">ON</button></a>");
  client.println("<a href=\"/FAN=OFF\"\"><button style=\" color:gray ; height:25px; width:100px\">OFF</button></a><br />");


  client.print("<h2 style=\"color:gray;font-family:candara;font-size:250%\">DOOR LOCK:</h2>");
 ;
  client.println("<a href=\"/DOOR=OPEN\"\"><button style=\" color:gray ; height:25px; width:100px\">OPEN</button></a>");
  client.println("<a href=\"/DOOR=CLOSE\"\"><button style=\" color:gray ; height:25px; width:100px\">CLOSE</button></a><br />");
  client.println("</div>\n");
  client.println("</body>\n");
   client.println("</html>");
  delay(100);
  Serial.println("Client disconnected");
}
