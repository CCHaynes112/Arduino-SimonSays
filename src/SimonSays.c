// Output pins
const int RED = 2;
const int BLUE = 3;
const int GREEN = 4;
const int YELLOW = 5;

// Input pins
const int RED_BUTTON = A0;
const int BLUE_BUTTON = A1;
const int GREEN_BUTTON = A2;
const int YELLOW_BUTTON = A3;

// Number of rounds
const int NUM_ROUNDS = 3;
int sequence[3]; // NUM_ROUNDS
int playerSequence[3]; // NUM_ROUNDS

int currentRound = 0;


// Buzzer
int BUZZER_PIN = 6;
int c = 261;
int d = 293;
int e = 329;
int f = 349;
int g = 386;
int a = 440;
int Bb = 466;
int b = 493;


void setup() {
	Serial.begin(9600);
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);

	randomSeed(analogRead(0) + millis());

	// Generate random sequence
	for (int i = 0; i < NUM_ROUNDS; i++) {
		sequence[i] = random(4);
		playerSequence[i] = -1;
	}
}

void loop() {
	delay(1000);
	for (int i = 0; i < NUM_ROUNDS; i++) {
		delay(200);
		currentRound = i;
		bool playerWonRound = handleCurrentRound(currentRound);
		// If the player lost, end the game
		if (!playerWonRound) {
			Serial.println("Player lost");
			gameOverLightShow();
			break;
		}
		// If the player won, end the game
		if (i == NUM_ROUNDS - 1) {
			Serial.println("Player won");
			victoryLightShow();
			break;
		}
	}
}

bool handleCurrentRound(int round) {
	int amountOflightsToFlashThisTurn = round + 1;
	for (int i = 0; i < amountOflightsToFlashThisTurn; i++) {
		int light = getLightFromSequence(i);
		playTone(light);
		flashLight(light);
	}
	// Wait for player to enter sequence
	for (int i = 0; i < amountOflightsToFlashThisTurn; i++) {
		// Wait for player to press button
		while (true) {
			int redButtonState = analogRead(RED_BUTTON);
			int blueButtonState = analogRead(BLUE_BUTTON);
			int greenButtonState = analogRead(GREEN_BUTTON);
			int yellowButtonState = analogRead(YELLOW_BUTTON);

			if (isButtonPressed(redButtonState)) {
				playTone(RED);
				flashLight(RED);
				playerSequence[i] = RED;
				break;
			}
			else if (isButtonPressed(blueButtonState)) {
				playTone(BLUE);
				flashLight(BLUE);
				playerSequence[i] = BLUE;
				break;
			}
			else if (isButtonPressed(greenButtonState)) {
				playTone(GREEN);
				flashLight(GREEN);
				playerSequence[i] = GREEN;
				break;
			}
			else if (isButtonPressed(yellowButtonState)) {
				playTone(YELLOW);
				flashLight(YELLOW);
				playerSequence[i] = YELLOW;
				break;
			}
		}
		if (playerSequence[i] != getLightFromSequence(i)) {
			return false;
		}
	}
	return true;
}
bool isButtonPressed(int buttonState) {
	return buttonState > 500;
}

int getLightFromSequence(int index) {
	if(index == 0) {
		return RED;
	} else if (index == 1) {
		return BLUE;
	} else if (index == 2) {
		return GREEN;
	} else if (index == 3) {
		return YELLOW;
	} else {
		return -1;
	}
}

void playTone(int light, int duration=300) {
	if (light == RED) {
		tone(BUZZER_PIN, c, duration);
	}
	else if (light == BLUE) {
		tone(BUZZER_PIN, d, duration);
	}
	else if (light == GREEN) {
		tone(BUZZER_PIN, e, duration);
	}
	else if (light == YELLOW) {
		tone(BUZZER_PIN, f, duration);
	}
}

void victoryLightShow() {
	for (int i = 0; i < 10; i++) {
		digitalWrite(RED, HIGH);
		delay(100);
		digitalWrite(RED, LOW);
		digitalWrite(BLUE, HIGH);
		delay(100);
		digitalWrite(BLUE, LOW);
		digitalWrite(GREEN, HIGH);
		delay(100);
		digitalWrite(GREEN, LOW);
		digitalWrite(YELLOW, HIGH);
		delay(100);
		digitalWrite(YELLOW, LOW);
	}
}

void gameOverLightShow() {
	for (int i = 0; i < 10; i++) {
		digitalWrite(RED, HIGH);
		delay(100);
		digitalWrite(RED, LOW);
		delay(100);
	}
}

void flashLight(int light, int delayTime=300) {
	turnOnLight(light);
	delay(delayTime);
	turnOffLight(light);
	delay(delayTime);
}

void turnOnLight(int light) {
	digitalWrite(light, HIGH);
}

void turnOffLight(int light) {
	digitalWrite(light, LOW);
}

void turnOnAllLights() {
	turnOnLight(RED);
	turnOnLight(BLUE);
	turnOnLight(GREEN);
	turnOnLight(YELLOW);
}

void turnOffAllLights() {
	turnOffLight(RED);
	turnOffLight(BLUE);
	turnOffLight(GREEN);
	turnOffLight(YELLOW);
}
