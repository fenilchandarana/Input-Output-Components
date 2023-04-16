#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000, 4, 2, 5); //attach data on pin2

void setup()
{
  Serial.begin(9600);

  if (!driver.init())
    Serial.println("init failed");

}

void loop()
{
  const char *msg = "this is ";

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(200);
}
