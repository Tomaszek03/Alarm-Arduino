#define trigPin 12
#define echoPin 11

bool item = true;
int czas = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT_PULLUP);
}

int zmierz_odl()
{
  long czas, dystans;

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  czas = pulseIn(echoPin,HIGH);
  dystans = czas/58;

  return dystans;
}

void zawyj(int x)
{
  int odl = zmierz_odl();
  while(odl > x)
  {
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    delay(100);
    odl = zmierz_odl();
    if(odl <= x) break;
    if(digitalRead(6)==LOW) break;;
  }

}

void loop() 
{
  item = false;
  digitalWrite(5,HIGH);

  delay(200);
  while(digitalRead(4)==HIGH) {}

  digitalWrite(5,LOW);

  item = true;
  while(item)
  {
    zawyj(10);
    Serial.println(zmierz_odl());
    delay(500);
    if(digitalRead(6)==LOW) break;;
  }
}
