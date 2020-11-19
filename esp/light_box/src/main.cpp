#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include <Adafruit_NeoPixel.h>

#define X 150

Adafruit_NeoPixel strip(23, 16, NEO_GRB + NEO_KHZ800);
AsyncWebServer server(80);
const char *ssid = "se-ma";
const char *password = "sewlan#42";
void notFound(AsyncWebServerRequest *request)
{
	request->send(404, "application/json", "{\"message\":\"Not found\"}");
}
void setColor(uint32_t ledColor)
{
	for (int i = 0; i < strip.numPixels(); i++)
	{
		strip.setPixelColor(i, ledColor);
	}
	strip.show();
}
void setupPixel()
{
	strip.begin();
	strip.setBrightness(100);
	strip.show();

	setColor(strip.Color(0, 0, X));
	delay(2000);
	setColor(strip.Color(0, 0, 0));
}

void setup()
{
	Serial.begin(9600);
	setupPixel();
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		Serial.printf("WiFi Failed!\n");
	}
	Serial.print("IP Address: ");
	Serial.println(WiFi.localIP());
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(200, "application/json", "{\"message\":\"Welcome\"}");
	});

	server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
		setColor(strip.Color(X, 0, 0));
		request->send(200, "application/json", "{\"message\":\"ok\"}");
	});

	server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
		setColor(strip.Color(0, 0, 0));
		request->send(200, "application/json", "{\"message\":\"ok\"}");
	});

	server.onNotFound(notFound);
	server.begin();
}


void loop()
{
}
