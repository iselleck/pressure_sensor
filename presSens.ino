int sensorPin = A0;
int ledPin1 = 8;
int ledPin2 = 9;
int ledPin3 = 10;
int ledPin4 = 11;
int ledPin5 = 12;
int ledPin6 = 13;

int sensorValue = 0;
int aSize = 6;
int rangeValue[] = {0, 0, 0, 0, 0, 0};
int modE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  digitalWrite(sensorPin, HIGH);

  delay(500);
}

void loop() {

  // put your main code here, to run repeatedly:


  for (int i = 0; i < aSize; i++)
  {
    sensorValue = analogRead(sensorPin);
    rangeValue[i] = sensorValue / 2;
    // delay(10);
  }
  /*
    Serial.println(sensorValue);
    if (sensorValue > 1000){
    digitalWrite(ledPin, HIGH);
    } else {
    digitalWrite(ledPin, LOW);
    }
  */

  Serial.print("Unsorted: ");
  printArray(rangeValue, aSize);
  isort(rangeValue, aSize);
  Serial.print("Sorted: ");
  printArray(rangeValue, aSize);
  modE = mode(rangeValue, aSize);
  Serial.print("The mode/median is: ");
  Serial.print(modE);
  Serial.println();

  if (modE > 70) {
    digitalWrite(ledPin1, HIGH);
    delay(1000);

    if (modE > 80) {
      digitalWrite(ledPin2, HIGH);
      delay(100);

      if (modE > 85) {

        digitalWrite(ledPin3, HIGH);
        delay(100);

        if (modE > 90) {

          digitalWrite(ledPin4, HIGH);
          delay(100);

          if (modE > 101) {

            digitalWrite(ledPin5, HIGH);
            delay(100);

            if (modE > 115) {

              digitalWrite(ledPin6, HIGH);
              delay(100);
            } else {
              digitalWrite(ledPin6, LOW);
            }
          } else {
            digitalWrite(ledPin5, LOW);
          }
        } else {
          digitalWrite(ledPin4, LOW);
        }
      } else {
        digitalWrite(ledPin3, LOW);
      }
    } else {
      digitalWrite(ledPin2, LOW);
    }
  }

  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
    digitalWrite(ledPin6, LOW);
  }

  // delay(1000);


}

void printArray(int *a, int n) {

  for (int i = 0; i < n; i++)
  {
    Serial.print(a[i], DEC);
    Serial.print(' ');
  }
  Serial.println();
}

//sort function for a array
void isort(int *a, int n) {
  for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

//function to return mode or median
int mode(int *x, int n) {

  int i = 0;
  int count = 0;
  int maxCount = 0;
  int mode = 0;
  int bimodal;
  int prevCount = 0;
  while (i < (n - 1)) {
    prevCount = count;
    count = 0;
    while (x[i] == x[i + 1]) {
      count++;
      i++;
    }
    if (count > prevCount & count > maxCount) {
      mode = x[i];
      maxCount = count;
      bimodal = 0;
    }
    if (count == 0) {
      i++;
    }
    if (count == maxCount) { //If the dataset has 2 or more modes.
      bimodal = 1;
    }
    if (mode == 0 || bimodal == 1) { //Return the median if there is no mode.
      mode = x[(n / 2)];
    }
    return mode;
  }
}
