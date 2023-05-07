int port_val;

void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    pot_val = analogRead(A0);
    Serial.println(pot_val);
    delay(200);
}