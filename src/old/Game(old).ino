const int SW_pin = 2;
const int X_pin = A0;
const int Y_pin = A1;

const int GREEN = 8;
const int YELLOW = 9;
const int BLUE = 10;
const int RED = 11;

int delayTime;
bool playerTurn;
int roundCount;
int currentInputIndex;  //Tracks the current index of player inputs

int combos[30]; //Store's Simon's lights
int playerCombos[30]; //Store's the player's inputs

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);

  randomSeed(analogRead(5));

  for (int i = 0; i < 30; i++)  //Normalizes both arrays
  {
    combos[i] = -1;
    playerCombos[i] = -1;
  }
  
  playerTurn == false;
  roundCount = 0;
  delayTime = 650;
}

void loop()
{
  if (playerTurn == false)
  {
    int randNum = random(4);
    combos[roundCount] = randNum;
    for (int i = 0; i <= roundCount; i++)
    {
      shineLight(combos[i]);
    }
    currentInputIndex = 0;
    playerTurn = true;
  }

  if (playerTurn == true)
  {
    while (playerCombos[roundCount] == -1)
    {
      playerChoose();
    }

    for (int i = 0; i <= roundCount; i++)
    {
      if (combos[i] != playerCombos[i])
      {
        for (int i = 0; i < 6; i++)
        {
          digitalWrite(RED, HIGH);
          delay(200);
          digitalWrite(RED, LOW);
          delay(200);

          //Reset Game
          roundCount = -1;
          for (int i = 0; i < 30; i++)
          {
            combos[i] = -1;
            playerCombos[i] = -1;
          }
        }
        delay(500);
      }
    }

    if (combos[29] != -1)
    {
      for (int i = 0; i < 5; i++)
      {
        digitalWrite(BLUE, HIGH);
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, HIGH);
        delay(500);
        digitalWrite(BLUE, LOW);
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        delay(500);
      }
      //Reset Game
      roundCount = -1;
      for (int i = 0; i < 30; i++)
      {
        combos[i] = -1;
        playerCombos[i] = -1;
      }
      delay(500);
    }

    playerTurn = false;
    delay(500);
    roundCount++;
  }
}

void shineLight(int light)
{
  if (light == 0)
  {
    digitalWrite(GREEN, HIGH);
    delay(delayTime);
    digitalWrite(GREEN, LOW);
    delay(delayTime);
  }

  if (light == 1)
  {
    digitalWrite(YELLOW, HIGH);
    delay(delayTime);
    digitalWrite(YELLOW, LOW);
    delay(delayTime);
  }

  if (light == 2)
  {
    digitalWrite(BLUE, HIGH);
    delay(delayTime);
    digitalWrite(BLUE, LOW);
    delay(delayTime);
  }

  if (light == 3)
  {
    digitalWrite(RED, HIGH);
    delay(delayTime);
    digitalWrite(RED, LOW);
    delay(delayTime);
  }
}

void playerChoose()
{
  //GREEN
  if (analogRead(X_pin) <= 300)
  {
    digitalWrite(GREEN, HIGH);
    delay(delayTime);
    digitalWrite(GREEN, LOW);
    playerCombos[currentInputIndex] = 0;
    currentInputIndex++;
  }

  //YELLOW
  if (analogRead(Y_pin) >= 700)
  {
    digitalWrite(YELLOW, HIGH);
    delay(delayTime);
    digitalWrite(YELLOW, LOW);
    playerCombos[currentInputIndex] = 1;
    currentInputIndex++;
  }

  //BLUE
  if (analogRead(Y_pin) <= 300)
  {
    digitalWrite(BLUE, HIGH);
    delay(delayTime);
    digitalWrite(BLUE, LOW);
    playerCombos[currentInputIndex] = 2;
    currentInputIndex++;
  }
  //RED
  if (analogRead(X_pin) >= 700)
  {
    digitalWrite(RED, HIGH);
    delay(delayTime);
    digitalWrite(RED, LOW);
    playerCombos[currentInputIndex] = 3;
    currentInputIndex++;
  }

  if (analogRead(Y_pin) > 300 && analogRead(Y_pin) < 700 && analogRead(X_pin) > 300 && analogRead(X_pin) < 700)
  {
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }
}
