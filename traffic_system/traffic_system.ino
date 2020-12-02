int red = 7;
int green = 9;
int yellow = 12;
int min1 = 2;
int min2 = 3;

void setup()
{
  pinMode(min1, OUTPUT);
  pinMode(min2, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  
}

void loop()
{
  int t = traffic();
  
  if (t==2) run ();
  else stop (); 
  
  delay (1500);
  reset ();
}

int traffic ()
{
  int x = random (1,4);
  if (x==1) {
  	digitalWrite (red, 255);
    return x;
  }
  
  else if (x==2) {
  	digitalWrite (green, 255);
    return x;
  }
  
  else {
  	digitalWrite (yellow, 255);
    return x;
  }
}

void run ()
{
	digitalWrite(min1, 255);
 	digitalWrite(min2, 0);
}

void stop ()
{
	digitalWrite(min1, 0);
 	digitalWrite(min2, 0);
}

void reset ()
{
	digitalWrite (red, 0);
  	digitalWrite (green, 0);
  	digitalWrite (yellow, 0);
} 
