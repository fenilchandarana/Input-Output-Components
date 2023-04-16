#define S0 7
#define S1 8
#define S2 15
#define S3 2
#define sensorOut 0

int redfrequency = 0;
int greenfrequency = 0;
int bluefrequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
   redfrequency = pulseIn(sensorOut, LOW);
 
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  greenfrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
 
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  bluefrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor


 if (redfrequency>35 && redfrequency< 45) {Serial.println("RED COLOUR");} else if (bluefrequency>62 && bluefrequency< 72) {Serial.println("BLUE COLOUR");} else if (greenfrequency>50 && greenfrequency< 60){Serial.println("GREEN COLOUR");}

 else
 {Serial.println("NO COLOUR DETECTION");}
}
