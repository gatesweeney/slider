/* 
 * Arduino 101: timer and interrupts
 * 2: Timer1 overflow interrupt example 
 * more infos: http://www.letmakerobots.com/node/28278
 * created by RobotFreak 
 */

int count = 0;
void setup()
{
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(10, HIGH); // high CC, low CCW
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  Serial.begin(115200);

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 62500;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS10);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = 62500;            // preload timer
  count ++;
  if ((count == 100)){           // check counter
    digitalWrite(8, digitalRead(8) ^ 1);
    count = 0;
  }
}

void loop()
{
  //delay(1000);
  //digitalWrite(10, HIGH);
  //delay(1000);
  //digitalWrite(10, LOW);
}
