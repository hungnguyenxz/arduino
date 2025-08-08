// C++ code
//
int leds[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int ledCount;
void A2B();
void B2A();
void M2AB();
void xen_ke();
void turnOffAll();

void setup() {
  ledCount = sizeof(leds) / sizeof(int);
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  A2B();
  delay(200);
  B2A();
  delay(200);
  M2AB();
  delay(200);
  xen_ke();
  delay(200);
}

void A2B() {
  // Sáng tuần tự A -> B
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
    delay(1000);
  }
  // Tắt tuần tự A -> B
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], LOW);
    delay(1000);
  }
}

void B2A() {
  // Sáng tuần tự B -> A
  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(1000);
  }
  // Tắt tuần tự B -> A
  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(leds[i], LOW);
    delay(1000);
  }
}

void M2AB() {
  bool even = ledCount % 2 == 0;
  int mid;
  if (even) {
    mid = ledCount / 2 - 1;
  } else {
    mid = (ledCount + 1) / 2 - 1;
  }
  // Sáng từ giữa ra 2 bên
  for (int i = mid; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    digitalWrite(leds[ledCount - 1 - i], HIGH);
    delay(1500);
  }

  // Tắt từ 2 bên vào giữa
  for (int i = 0; i <= mid; i++) {
    digitalWrite(leds[i], LOW);
    digitalWrite(leds[ledCount - 1 - i], LOW);
    delay(1500);
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
    delay(1500);
    for (int i = 1; i <= ledCount; i += 2) {
      digitalWrite(leds[i], HIGH);
      digitalWrite(leds[i - 1], LOW);
    }
    delay(1500);
  }
  turnOffAll();
}

void turnOffAll() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], LOW);
  }
}