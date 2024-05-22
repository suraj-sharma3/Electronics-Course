int flex_sensor = A0;
int data = 0;

void setup(){
  Serial.begin(9600);
  pinMode(flex_sensor, INPUT);
}

void loop(){
  data = analogRead(flex_sensor);
  Serial.println(data);
  delay(1000);
}
