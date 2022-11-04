int detectorPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(detectorPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(detectorPin) == HIGH){
      Serial.println("HIGH");
    }
}
