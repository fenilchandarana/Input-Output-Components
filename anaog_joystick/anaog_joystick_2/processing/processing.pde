import processing.serial.*;
Serial myPort;

int x; 
int y;
int b;
PFont f;
String portName;
String val;

void setup()
{
  size ( 512 , 512 ) ; 
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n'); 
  f = createFont("Arial", 16, true);
  textFont ( f, 16 ) ; 
}


void draw()
{
  fill(0) ;
  clear() ; 
  fill(255) ; 
  if (b == 1)
  {
    ellipse(x/2,y/2, 50, 50);
  } 
  else
  {
    ellipse(x/2,y/2, 25, 25);
  }
  text("AnalogX="+(1023-x)+" AnalogY="+(1023-y),10,20);
}


void serialEvent( Serial myPort) 
{
  val = myPort.readStringUntil('\n');
  if (val != null)
  {
        val = trim(val);
    int[] vals = int(splitTokens(val, ","));
    x = vals[0];
    y = vals[1] ;
    b = vals[2];

  }
}
