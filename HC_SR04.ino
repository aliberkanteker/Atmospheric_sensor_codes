// No library required ..

const int trigPin = 8;
const int echoPin = 9;

long duration;
int distance;

void setup() {
  Serial.begin(9600);  // Initialize the serial monitor ..
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Initialize the sensor by setting the Trig pin low ..
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send an ultrasonic wave by setting the Trig pin high ..
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  // Keep it high for 10 microseconds ..
  digitalWrite(trigPin, LOW);

  // Get the duration from the Echo pin ..
  duration = pulseIn(echoPin, HIGH);

  // If the duration cannot be measured or is too long/short, assume the distance is zero ..
  if (duration == 0 || duration > 23529 || duration < 116) {
    // duration > 23529 => Distances over 400 cm ..
    // duration < 116  => Distances under 2 cm ..
    distance = 0;  // Measurement is invalid, set the distance to zero ..
  } else {
    // Measurement is invalid, set the distance to zero ..
    distance = duration * 0.034 / 2;  //Distance in cm ..
  }

  // Print the distance to the serial monitor
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);  // Wait for 500 ms
}
