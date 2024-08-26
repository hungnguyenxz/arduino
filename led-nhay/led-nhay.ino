// C++ code
//
int leds[] = {5,6,7,8,9,10,11, 12};
int ledCount;
void setup()
{
  ledCount = sizeof(leds) / sizeof(int);
  for(int i = 0; i< ledCount;i++){
  	pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop()
{
  // Sáng tuần tự A -> B
  for(int i = 0; i< ledCount;i++){
  	digitalWrite(leds[i], HIGH);
    delay(200);
  }
  // Tắt tuần tự A -> B
  for(int i = 0; i< ledCount;i++){
  	digitalWrite(leds[i], LOW);
    delay(200);
  }
  delay(200);
  // Sáng tuần tự B -> A
  for(int i = ledCount - 1; i>=0;i--){
  	digitalWrite(leds[i], HIGH);
    delay(200);
  }
  // Tắt tuần tự B -> A
  for(int i = ledCount - 1; i>=0;i--){
  	digitalWrite(leds[i], LOW);
    delay(200);
  }
  
  delay(300);
  
  
  bool even = ledCount % 2 == 0;
  int mid;
  if(even){
   	mid = ledCount / 2 - 1; 
  }
  else{
    mid = (ledCount + 1) / 2 - 1;
  }
  // Sáng từ giữa ra 2 bên
  for(int i = mid; i >= 0; i--){
    digitalWrite(leds[i], HIGH);
    digitalWrite(leds[ledCount - 1 - i], HIGH);
    delay(300);
  }
  
  // Tắ từ 2 bên vào giữa
  for(int i = 0; i <= mid; i++){
    digitalWrite(leds[i], LOW);
    digitalWrite(leds[ledCount - 1 - i], LOW);
    delay(150);
  }
}

void turnOffAll(){
  for(int i = 0; i< ledCount;i++){
    digitalWrite(leds[i], LOW);
  }
}