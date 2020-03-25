int pulse = 0;
int pos = 0;
int spd = 0;

// a = dV/dt = (d^2r/dt^2)

// dV = v1 - v0
//where v0 is the initial velocity/speed 
//while v1 is the final velocity/speed of the moving object.

void setup() {
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(7, INPUT);
digitalWrite(8, LOW);
digitalWrite(9, LOW);
Serial.begin(9600);
}
void loop() {delay(.02);
digitalWrite(9, HIGH);
delay(.02);
digitalWrite(9, LOW);
pos = digitalRead(7);
Serial.println(pos);
}
