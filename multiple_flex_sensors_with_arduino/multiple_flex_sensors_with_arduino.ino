int flex_1 = A0;
int flex_2 = A1;
int flex_3 = A2;
// int flex_4 = A3;

int data1 = 0;
int data2 = 0;
int data3 = 0;
// int data4 = 0;

void setup(){
  Serial.begin(9600);
  pinMode(flex_1, INPUT);
  pinMode(flex_2, INPUT);
  pinMode(flex_3, INPUT);
  // pinMode(flex_4, INPUT);
}

void loop(){
  delay(1000);
  data1 = analogRead(flex_1);
  data2 = analogRead(flex_2);
  data3 = analogRead(flex_3);
  // data4 = analogRead(flex_4);
  Serial.print("Flex Sensor 1 : " + String(data1));
  Serial.print(", ");
  Serial.print("Flex Sensor 2 : " + String(data2));
  Serial.print(", ");
  Serial.println("Flex Sensor 3 : " + String(data3));
  // Serial.print(", ");
  // Serial.println("Flex Sensor 4 : " + String(data4));
}