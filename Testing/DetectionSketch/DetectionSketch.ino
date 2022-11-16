int thumbDetector = 2;
int pointerDetector = 3;
int middleDetector = 4;
int ringDetector = 5;
int pinkyDetector = 6;
void setup() {
  // put your setup code here, to run once:
  pinMode(thumbDetector,INPUT);
  pinMode(pointerDetector,INPUT);
  pinMode(middleDetector,INPUT);
  pinMode(ringDetector,INPUT);
  pinMode(pinkyDetector,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(thumbDetector) == HIGH){
      Serial.println("Thumb");
    }
      if (digitalRead(pointerDetector) == HIGH){
      Serial.println("pointer");
    }
      if (digitalRead(middleDetector) == HIGH){
      Serial.println("middleDetector");
    }
      if (digitalRead(ringDetector) == HIGH){
      Serial.println("ringDetector");
    }
      if (digitalRead(pinkyDetector) == HIGH){
      Serial.println("pinkyDetector");
    }
}
