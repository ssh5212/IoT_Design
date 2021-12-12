int value1;
int value2;
int value3;

float amp1;
float amp3;
float amp2;

void setup(){
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}



void loop(){
  value1 = analogRead(A1);
  value2 = analogRead(A2);
  value3 = analogRead(A3);
  
  amp1 = (((value1-511)*5/0.185)/1024)*1000;
  amp2 = (((value2-511)*5/0.185)/1024)*1000;
  amp3 = (((value3-511)*5/0.185)/1024)*1000;
  
  Serial.write(amp1);
  Serial.write(" ");
  Serial.write(amp2);
  Serial.write(" ");
  Serial.write(amp3);
  
  delay(250);
}
