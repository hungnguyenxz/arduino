int leds[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int ledCount;
int time = 200;

void A2B();
void B2A();
void M2AB();
void xen_ke();
void turnOffAll();
void randomBlink();
void fastBlink();
void slowBlink();
void allOnOff();
void circularBlink();
void randomBlinkAll();
void alternateBlinkReverse();
void halfOnOff();
void reverseBlink();

void setup() {
  ledCount = sizeof(leds) / sizeof(int);
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  reverseBlink();
  delay(200);
  A2B();
  delay(200);
  B2A();
  delay(200);
  M2AB();
  delay(200);
  xen_ke();
  delay(200);
  
  randomBlink();       // Chế độ nháy ngẫu nhiên
  delay(500);
  
  fastBlink();         // Chế độ nháy nhanh
  delay(500);
  
  slowBlink();         // Chế độ nháy chậm
  delay(500);
  
  allOnOff();          // Chế độ sáng tắt đồng loạt
  delay(500);
  
  circularBlink();     // Chế độ chạy theo vòng
  delay(500);
  
  randomBlinkAll();    // Chế độ chớp ngẫu nhiên
  delay(500);
  
  alternateBlinkReverse(); // Chế độ sáng xen kẽ ngược
  delay(500);
  
  halfOnOff();         // Chế độ nửa sáng
  delay(500);
}

void A2B() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
    delay(time);
  }
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], LOW);
    delay(time);
  }
}

void B2A() {
  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(time);
  }
  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(leds[i], LOW);
    delay(time);
  }
}

void M2AB() {
  bool even = ledCount % 2 == 0;
  int mid = (even) ? ledCount / 2 - 1 : (ledCount + 1) / 2 - 1;
  for (int i = mid; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    digitalWrite(leds[ledCount - 1 - i], HIGH);
    delay(time);
  }
  for (int i = 0; i <= mid; i++) {
    digitalWrite(leds[i], LOW);
    digitalWrite(leds[ledCount - 1 - i], LOW);
    delay(time);
  }
}

void xen_ke() {
  for (int c = 0; c < 6; c++) {
    for (int i = 0; i <= ledCount; i += 2) {
      digitalWrite(leds[i], HIGH);
      if (i + 1 < ledCount) {
        digitalWrite(leds[i + 1], LOW);
      }
    }
    delay(time);
    for (int i = 1; i <= ledCount; i += 2) {
      digitalWrite(leds[i], HIGH);
      digitalWrite(leds[i - 1], LOW);
    }
    delay(time);
  }
  turnOffAll();
}

void turnOffAll() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void randomBlink() {
  int randomLed = random(0, ledCount);
  digitalWrite(leds[randomLed], HIGH);
  delay(time);
  digitalWrite(leds[randomLed], LOW);
}

void fastBlink() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(50);
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(50);
}

void slowBlink() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(500);
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(500);
}

void allOnOff() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(200);
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(200);
}

// Chế độ chạy theo vòng
void circularBlink() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
    delay(time);
    digitalWrite(leds[i], LOW);
  }
  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(time);
    digitalWrite(leds[i], LOW);
  }
}

// Chế độ chớp ngẫu nhiên tất cả LED
void randomBlinkAll() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], random(0, 2)); // 0 hoặc 1, bật/tắt ngẫu nhiên
  }
  delay(time);
  turnOffAll();
}

// Chế độ sáng xen kẽ ngược
void alternateBlinkReverse() {
  for (int i = ledCount - 1; i >= 0; i -= 2) {
    digitalWrite(leds[i], HIGH);
    if (i - 1 >= 0) {
      digitalWrite(leds[i - 1], LOW);
    }
    delay(time);
  }
  turnOffAll();
}

// Chế độ nửa sáng
void halfOnOff() {
  for (int i = 0; i < ledCount / 2; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(500);
  for (int i = 0; i < ledCount / 2; i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(500);
}

void reverseBlink() {
  // Tắt tất cả LED trước
  turnOffAll();
  
  // Chạy từ cuối lên đầu, sáng lần lượt
  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(time); // Thời gian delay giữa các LED
  }
  
  // Tắt tất cả LED sau khi chạy ngược
  turnOffAll();
  delay(200); // Thời gian dừng trước khi tiếp tục
}
