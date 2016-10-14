#include <config.h>
#include <app.h>
#include <SmingCore/SmingCore.h>
#include <Libraries/DHT/DHT.h>

Timer procTimer;
int sensorValue = 0;
HttpClient koorIO;

#define WORK_PIN 4
#define LED_PIN 5

bool state = true;

void blink()
{
	digitalWrite(LED_PIN, state);
	state = !state;
}

DHT dht(WORK_PIN, 11);

void displayComfort();


void onDataSent(HttpClient& client, bool successful)
{
	if (successful)
		Serial.println("Success sent");
	else
		Serial.println("Failed");

	String response = client.getResponseString();
	Serial.println("Server response: '" + response + "'");
	if (response.length() > 0)
	{
		int intVal = response.toInt();

		if (intVal == 0)
			Serial.println("Sensor value wasn't accepted. May be we need to wait a little?");
	}
}

void sendData()
{
	if (koorIO.isProcessing()) return; // We need to wait while request processing was completed
        // DHT start
	Serial.println("\t\t DHT improved lib");
	Serial.println("wait 1 second for the sensor to boot up");

	//disable watchdog
	WDT.enable(false);
	//wait for sensor startup
	delay(1000);
	dht.begin();

	/*first reading method (Adafruit compatible) */
	Serial.print("Read using Adafruit API methods\n");
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	// check if returns are valid, if they are NaN (not a number) then something went wrong!
	if (isnan(t) || isnan(h))
	{
		Serial.println("Failed to read from DHT");
	} else {
		Serial.print("\tHumidity: ");
		Serial.print(h);
		Serial.print("% Temperature: ");
		Serial.print(t);
		Serial.print(" *C\n");
	}


	/* improved reading method */
	Serial.print("\nRead using new API methods\n");
	TempAndHumidity th;
	if(dht.readTempAndHumidity(th))
	{
		Serial.print("\tHumidity: ");
		Serial.print(h);
		Serial.print("% Temperature: ");
		Serial.print(t);
		Serial.print(" *C\n");
	}
	else
	{
		Serial.print("Failed to read from DHT: ");
		Serial.print(dht.getLastError());
	}

	/* other goodies */

	/*
	 * Heatindex is the percieved temperature taking humidity into account
	 * More: https://en.wikipedia.org/wiki/Heat_index
	 * */
	Serial.print("Heatindex: ");
	Serial.print(dht.getHeatIndex());
	Serial.print("*C\n");

	/*
	 * Dewpoint is the temperature where condensation starts.
	 * Water vapors will start condensing on an object having this temperature or below.
	 * More: https://en.wikipedia.org/wiki/Dew_point
	 * */
	Serial.printf("Dewpoint: ");
	Serial.print(dht.getDewPoint(DEW_ACCURATE_FAST));
	Serial.print("*C\n");

	// DHT end
	blink();
	koorIO.downloadString(String(HTTP_URL) + "?" + String(CHANEL_ONE) + "=" + String(t) + "&" + String(CHANEL_TWO) + "=" + String(h), onDataSent);
	blink();
}

// Will be called when WiFi station was connected to AP
void connectOk()
{
	Serial.println("I'm CONNECTED");

	Serial.begin(57600); // 115200 by default
	Serial.systemDebugOutput(true); // Allow debug output to serial

	// Start send data loop
	procTimer.initializeMs(25 * 1000, sendData).start(); // every 25 seconds
}

// Will be called when WiFi station timeout was reached
void connectFail()
{
	Serial.println("I'm NOT CONNECTED. Need help :(");

	// Start soft access point
	WifiAccessPoint.enable(true);
	WifiAccessPoint.config("CONFIG ME PLEEEEASE...", "", AUTH_OPEN);

	// .. some you code for configuration ..
}

void init()
{
	pinMode(LED_PIN, OUTPUT);
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(false); // Disable debug output to serial

	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiStation.enable(true);
	WifiAccessPoint.enable(false);

	// Run our method when station was connected to AP (or not connected)
	WifiStation.waitConnection(connectOk, 20, connectFail); // We recommend 20+ seconds for connection timeout at start
}


