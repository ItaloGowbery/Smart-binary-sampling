#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Configuração Wi-Fi
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    
    // Conectar ao Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao Wi-Fi...");
    }
    Serial.println("Wi-Fi Conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // Servir a página HTML
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "<h1>Controle ESP</h1><button onclick='fetch(\"/ligar\")'>Ligar</button><button onclick='fetch(\"/desligar\")'>Desligar</button>");
    });

    // Endpoints para ligar/desligar um LED no pino 2
    pinMode(2, OUTPUT);
    server.on("/ligar", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(2, HIGH);
        request->send(200, "text/plain", "Ligado");
    });

    server.on("/desligar", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(2, LOW);
        request->send(200, "text/plain", "Desligado");
    });

    server.begin();
}

void loop() {
}

