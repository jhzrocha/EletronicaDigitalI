#include <WiFi.h>
#include "htmlCreator.h"

const char* ssid = "Escritório 2G";
const char* password = "Maia1234";

#define BOMBA_BASICA 25 
#define BOMBA_ACIDA 26
#define AQUECEDOR 12
#define RESFRIADOR 14

WiFiServer server(80);
HTMLCreator htmlCreator;
String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('-');
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("IP:: ");
  Serial.println(WiFi.localIP());
  server.begin();

  pinMode(BOMBA_BASICA, OUTPUT);
  pinMode(BOMBA_ACIDA, OUTPUT);
  pinMode(AQUECEDOR, OUTPUT);
  pinMode(RESFRIADOR, OUTPUT);

  digitalWrite(BOMBA_BASICA, HIGH); 
  digitalWrite(BOMBA_ACIDA, HIGH); 
  digitalWrite(AQUECEDOR, HIGH);
  digitalWrite(RESFRIADOR, HIGH);
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("Novo cliente conectado.");
    String currentLine = "";
    header = "";

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {

            // Se for uma requisição /update com ações
            if (header.indexOf("GET /update?") >= 0) {
              int phActionIndex = header.indexOf("phAction=");
              int tempActionIndex = header.indexOf("tempAction=");

              String phAction = "";
              String tempAction = "";

              if (phActionIndex >= 0) {
                int end = header.indexOf('&', phActionIndex);
                phAction = header.substring(phActionIndex + 9, end);
              }

              if (tempActionIndex >= 0) {
                int end = header.indexOf(' ', tempActionIndex);
                tempAction = header.substring(tempActionIndex + 11, end);
              }

              if (phAction == "addAcid") {
                digitalWrite(BOMBA_ACIDA, LOW);
                digitalWrite(BOMBA_BASICA, HIGH);
                Serial.println("Bomba Ácida acionada");
              } else if (phAction == "addBase") {
                digitalWrite(BOMBA_BASICA, LOW);
                digitalWrite(BOMBA_ACIDA, HIGH);
                Serial.println("Bomba básica acionada");
              } else {
                digitalWrite(BOMBA_ACIDA, HIGH);
                digitalWrite(BOMBA_BASICA, HIGH);
              }

              if (tempAction == "heat") {
                digitalWrite(AQUECEDOR, LOW);
                digitalWrite(RESFRIADOR, HIGH);

                Serial.println("Aquecedor acionado");
              } else if (tempAction == "cool") {
                digitalWrite(RESFRIADOR, LOW);
                digitalWrite(AQUECEDOR, HIGH);
                Serial.println("Resfriador acionado");
              } else {
                digitalWrite(RESFRIADOR, HIGH);
                digitalWrite(AQUECEDOR, HIGH);
              }

              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/plain");
              client.println("Connection: close");
              client.println();
              client.println("Comandos executados");
            } else {
              // Responde a página HTML normal
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();
              client.println(htmlCreator.getHTMLPage());
            }

            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    delay(1);
    client.stop();
    Serial.println("Cliente desconectado.");
    header = "";
  }
}

