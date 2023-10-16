int IN1 = 5;
int IN2 = 6;
int VR_PIN = A0;
int VR_VALUE;
int PWM_VALUE;
int STATUS = 0;
char buff[128];

void READ_VR(void) {
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
}

void PWM_SYORI() {
  if (STATUS == 0) {
    analogWrite(IN1, 255);
    analogWrite(IN2, 255);
  }
  if (STATUS == 1) {  // CCW
    analogWrite(IN1, 255);
    analogWrite(IN2, 0);
  }
  if (STATUS == 2) {  // CW
    analogWrite(IN1, 0);
    analogWrite(IN2, 255);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
    ;
}

void loop() {
  // put your main code here, to run repeatedly:
  READ_VR();

  sprintf(buff, "STATUS = %d, VR_VALUE = %d, PWM_VALUE = %d", STATUS, VR_VALUE, PWM_VALUE);
  Serial.println(buff);

  PWM_SYORI();
  delay(50);
}
