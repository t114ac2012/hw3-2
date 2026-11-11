const int buttonPin = 7;           // 按鈕接在 Pin 7
const int ledPins[] = {1, 2, 3};   // 3 顆 LED 分別接在 Pin 1, 2, 3
const int numLeds = 3;

int mode = 0;                      // 0: 恆亮, 1: 慢閃, 2: 中閃, 3: 快閃
int lastButtonState = HIGH;        // 預設按鈕未按下 (INPUT_PULLUP)
unsigned long previousMillis = 0;
bool ledState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // 啟用內部上拉電阻（按鈕另一端請接 GND）
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // 1. 讀取按鈕並進行防彈跳與狀態切換
  int currentButtonState = digitalRead(buttonPin);
  
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    mode = (mode + 1) % 4; // 模式在 0, 1, 2, 3 之間循環（按第4下會變回 0）
    delay(50); // 簡易防彈跳延遲
  }
  lastButtonState = currentButtonState;

  // 2. 依照目前模式控制 LED 狀態
  unsigned long currentMillis = millis();

  switch (mode) {
    case 0: // 初始狀態：恆亮
      setLeds(LOW);
      break;

    case 1: // 第 1 下：慢閃 (間隔 1000 毫秒)
      if (currentMillis - previousMillis >= 1000) {
        previousMillis = currentMillis;
        ledState = !ledState;
        setLeds(ledState);
      }
      break;

    case 2: // 第 2 下：不快不慢的閃爍 / 中閃 (間隔 500 毫秒)
      if (currentMillis - previousMillis >= 500) {
        previousMillis = currentMillis;
        ledState = !ledState;
        setLeds(ledState);
      }
      break;

    case 3: // 第 3 下：快閃 (間隔 150 毫秒)
      if (currentMillis - previousMillis >= 150) {
        previousMillis = currentMillis;
        ledState = !ledState;
        setLeds(ledState);
      }
      break;
  }
}

// 輔助函式：同時控制所有 LED 的高低電位
void setLeds(bool state) {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], state);
  }
}