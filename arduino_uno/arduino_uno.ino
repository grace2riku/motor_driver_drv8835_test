int IN1 = 10;
int IN2 = 11;
int VR_PIN = A0;
int DIR_PIN = 8;
int VR_VALUE;
int PWM_VALUE;
int STATUS = 0;
char buff[128];

void READ_VR(void) {
#if 1
  VR_VALUE = analogRead(VR_PIN);
#else
  VR_VALUE = analogRead(VR_PIN);
  if ((VR_VALUE >= 500) && (VR_VALUE <= 523)) STATUS = 0; // BRAKE
  if (VR_VALUE <= 499) {  // CCW
    STATUS = 1;
    PWM_VALUE = (500 - VR_VALUE) / 2; // 1 to 500
  }
  if (VR_VALUE >= 524) {  // CW
    STATUS = 2;
    PWM_VALUE = (VR_VALUE - 523) / 2;
  }
#endif
}

void PWM_SYORI() {
#if 1

#else
  if (STATUS == 0) {
    analogWrite(IN1, 255);
    analogWrite(IN2, 255);
  }
  if (STATUS == 1) {  // CCW
    analogWrite(IN1, PWM_VALUE);
    analogWrite(IN2, 0);
  }
  if (STATUS == 2) {  // CW
    analogWrite(IN1, 0);
    analogWrite(IN2, PWM_VALUE);
  }
#endif
}

void setup() {
  // put your setup code here, to run once:
  pinMode(DIR_PIN, INPUT);
  Serial.begin(9600);
  while (!Serial)
    ;
}

void loop() {
  // put your main code here, to run repeatedly:
  READ_VR();

  int dir = digitalRead(DIR_PIN);
  if (!dir) {
    // CCWで前進
    analogWrite(IN1, VR_VALUE / 4);
    analogWrite(IN2, 0);
  } else {
    // CWで後進しなかった
    analogWrite(IN1, 0);
    analogWrite(IN2, VR_VALUE / 4);
  }

  PWM_SYORI();

  sprintf(buff, "dir = %d, STATUS = %d, VR_VALUE = %d, PWM_VALUE = %d", dir, STATUS, VR_VALUE, PWM_VALUE);
  Serial.println(buff);

  delay(50);
}
