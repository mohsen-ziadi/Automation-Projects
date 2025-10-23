int redButton = 15;
int greenButton = 4;
int blueButton = 5;

int redLed = 19;
int greenLed = 18;
int blueLed = 21;

int redCount = 0;
int greenCount = 0;
int blueCount = 0;

bool lastRedState = HIGH;
bool lastGreenState = HIGH;
bool lastBlueState = HIGH;

String inputCommand = "";  

void setup() {
  Serial.begin(115200);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Off(); 

  Serial.println("ESP32 ready for UART commands...");
  Serial.println("Type RED / GREEN / BLUE / OFF in terminal and press Enter");
}

void OnRed() {
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  Serial.println("LED RED ON");
}

void OnGreen() {
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, LOW);
  Serial.println("LED GREEN ON");
}

void OnBlue() {
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, HIGH);
  Serial.println("LED BLUE ON");
}

void Off() {
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  Serial.println("LEDs OFF");
}

void handleCommand(String cmd) {
  cmd.trim();
  cmd.toUpperCase();

  if (cmd == "RED") OnRed();
  else if (cmd == "GREEN") OnGreen();
  else if (cmd == "BLUE") OnBlue();
  else if (cmd == "OFF") Off();
  else if (cmd == "STATUS") {
    if (digitalRead(redLed) == HIGH) Serial.println("STATUS: RED ON");
    else if (digitalRead(greenLed) == HIGH) Serial.println("STATUS: GREEN ON");
    else if (digitalRead(blueLed) == HIGH) Serial.println("STATUS: BLUE ON");
    else Serial.println("STATUS: ALL OFF");
  }
  else Serial.println("Unknown command!");
}

void loop() {
  bool redState = digitalRead(redButton);
  bool greenState = digitalRead(greenButton);
  bool blueState = digitalRead(blueButton);

  if (redState == LOW && lastRedState == HIGH) {
    Serial.println("BUTTON RED PRESSED");
    redCount++;
    if (redCount % 2 == 1) {
      OnRed();
      greenCount = 0;
      blueCount = 0;
    } else Off();
  }

  if (greenState == LOW && lastGreenState == HIGH) {
    Serial.println("BUTTON GREEN PRESSED");
    greenCount++;
    if (greenCount % 2 == 1) {
      OnGreen();
      redCount = 0;
      blueCount = 0;
    } else Off();
  }

  if (blueState == LOW && lastBlueState == HIGH) {
    Serial.println("BUTTON BLUE PRESSED");
    blueCount++;
    if (blueCount % 2 == 1) {
      OnBlue();
      redCount = 0;
      greenCount = 0;
    } else Off();
  }

  lastRedState = redState;
  lastGreenState = greenState;
  lastBlueState = blueState;

  // --- UART command ---
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (inputCommand.length() > 0) {
        handleCommand(inputCommand);
        inputCommand = "";
      }
    } else {
      inputCommand += c;
    }
  }

  delay(50);
}
