const int ledPins[] = {3, 4, 5, 6, 7,8,9,10,11,12};         // Khai báo mảng chứa các chân kết nối của lED với Arduino
const int buttonPin = 2;                                    // Khai báo chân kết nối của nút nhấn với Arduino
int buttonState = 0;                                        // Trạng thái hiện tại của nút nhấn
int dem=0;
int ledCount;

void setup()
{
  ledCount = sizeof(ledPins) / sizeof(int);
  Serial.begin(9600);                                       // Mở cổng Serial để Hiển thị đèn LED sáng hiện tại
  for (int i = 0; i < ledCount; i++)
  {
    pinMode(ledPins[i], OUTPUT);                            // Cài đặt chân là OUTPUT để điều khiển LED
    digitalWrite(ledPins[i], LOW);                          // Tắt tất cả các LED ban đầu
  }
  pinMode(buttonPin, INPUT_PULLUP);                         // Cài đặt chân nút nhấn là INPUT_PULLUP
}

void loop()
{
  buttonState = digitalRead(buttonPin);                    // Đọc trạng thái nút nhấn
  if (buttonState == LOW)                                  // Nếu nút nhấn được nhấn xuống
  {
    for (int i = 0; i < ledCount; i++)                     // Dùng for để bật lần lượt các LED
    {
      digitalWrite(ledPins[i], HIGH);                      // Hiển thị LED với các giá trị i tương ứng
      dem=i+1;                                             // Biến 'dem' là số thứ tự đèn LED đang sáng hiện tại
      Serial.print("Den LED đang sáng la den so: ");       // Hiển thị trên cổng Serial đèn LED hiện tại đang sáng
      Serial.println(dem);                                 // Sau 1 giây sẽ bật 1 LED, LED được bật cuối cùng là LED số 5
      delay(200); 
    }
  }
  else                                                    // Ngược lại nếu nút nhấn được nhả ra
  {
    for (int i = 0; i < ledCount; i++)                    // Dùng for để tắt các LED
    {
      digitalWrite(ledPins[i], LOW);                      // LED được tắt cuối cùng là LED số 5                    
      delay(200);
    } 
  }
  
}
