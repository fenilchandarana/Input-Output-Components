int en = 6;
int in1 = 7;
int in2 = 8;




void setup() {
  // put your setup code here, to run once:


  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);


}


void loop() {
  // put your main code here, to run repeatedly:




digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(en, 250);
//delay(2000);


//digitalWrite(in1, LOW);
//digitalWrite(in2, LOW);
//delay(2000);
//
//digitalWrite(in2, HIGH);
//digitalWrite(in1, LOW);
//analogWrite(en, 255);
//delay(2000);
//
//digitalWrite(in1, LOW);
//digitalWrite(in2, LOW);
//delay(2000);


}
