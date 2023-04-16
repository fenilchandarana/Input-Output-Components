#include <RH_ASK.h>

#include <SPI.h>


RH_ASK driver(2000, 2, 4, 5); //attach data on pin2

void setup()
{

  Serial.begin(9600);
  if (!driver.init())

    Serial.println("init failed");

}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    //	int i;

    // Message with a good checksum received, dump it.
    driver.printBuffer("Got:", buf, buflen);

    String rcv;

    for (int i = 0; i < buflen; i++) {
      rcv += (char) buf[i];
    }

    Serial.println(rcv);
    delay(100);
  }
}
