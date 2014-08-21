#define LED_PIN 13
#define BUT_ONE 2
#define BUT_TWO 3
#define STEP 250

int tempo = 0;
int state = 1;
int atraso = 1000;
int parada1 = 0;
int parada2 = 0;

void setup () {
	tempo = millis();
	pinMode(LED_PIN,OUTPUT);
	pinMode(BUT_TWO,INPUT);
	pinMode(BUT_ONE,INPUT);
}

void loop () {
	int novo=millis();
	if(novo>=tempo+atraso){
		tempo = novo;
		digitalWrite(LED_PIN,state);
		state = !state;
	}
	int one = digitalRead(BUT_ONE);
	if(one == HIGH){
		parada1 = millis();
		atraso -= STEP;
	}
	int two = digitalRead(BUT_TWO);
	if(one == HIGH){
		parada2 = millis();
		atraso += STEP;
	}
	int parada = abs(parada1 - parada2);
	if(parada<=500){
		digitalWrite(LED_PIN,LOW);
		while(1);
	}
}
