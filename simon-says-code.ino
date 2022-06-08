int grnB; //green button
int redB; //red button
int yelB; //yellow button
int bluB; //blue button
int turB; //turquoise button
int whtB; //white button

int grnL;
int redL;
int yelL;
int bluL;
int turL;
int whtL;

bool grnBOn;
bool redBOn;
bool yelBOn;
bool bluBOn;
bool turBOn;
bool whtBOn;

bool bPressed;

int buzz;

int seedPin;

int ans[20];
int key[20];
int keyLen = 20;
int ansLen = 20;

bool fail;
bool win;
bool gameOn;
//bool correctAns;
bool startOfSeq;
bool initP;

int keyI;
int ansI;

//www.waitingforfriday.com/?p=586
int grnT = 415; //G#4
int redT = 310; //D#4
int yelT = 252; //B3
int bluT = 209; //G#3
int turT = 147; //D#3
int whtT = 123; //B2
int loseT = 42; //E1
int winT = 2637; //E7
//winning song?

void setup() 
{
  Serial.begin(9600);

  grnB = 13;
  grnL = 12;
  redB = 11;
  redL = 10;
  buzz = 9;
  yelB = 8;
  yelL = 7;
  bluB = 6;
  bluL = 5;
  seedPin = A4;
  
  turL = 4;
  turB = 3;
  whtL = 2;
  whtB = A5;
  
  grnBOn = false;
  redBOn = false;
  yelBOn = false;
  bluBOn = false;
  turBOn = false;
  whtBOn = false;
  
  bPressed = false;
  
  fail = false;
  win = false;
  gameOn = false;
  //correctAns = false;
  startOfSeq = true;
  initP = true;
  
  keyI = 0;
  ansI = 0;
  
  pinMode(grnB, INPUT);
  pinMode(redB, INPUT);
  pinMode(yelB, INPUT);
  pinMode(bluB, INPUT);
  pinMode(turB, INPUT);
  pinMode(whtB, INPUT);
  
  pinMode(seedPin, INPUT);
  
  pinMode(grnL, OUTPUT);
  pinMode(redL, OUTPUT);
  pinMode(yelL, OUTPUT);
  pinMode(bluL, OUTPUT);
  pinMode(turL, OUTPUT);
  pinMode(whtL, OUTPUT);
    
  pinMode(buzz, OUTPUT);
  
  //setNewKey at start of game
  setNewKey();
}

void loop() 
{
  //allOn();
  //checkButtonsProgressCheck();
  
 // playTones(int buzz, int tones[], int durations[], int length)

  if(!gameOn)
  {
    if(initP)
      initPattern();//only do this ONCE at start of every GAME
    Serial.println("BEGINNING");
    int onButton = getOnButton(); 
    
    //press green to start
    if(onButton == grnB)
    {
      Serial.println("onButton == grnB");
      //processButton(grnB);
      delay(200);
      Serial.println("gameOn = true");
      gameOn = true;
      fail = false;
    }
    else
      blink(grnL);
  }
  else //gameOn
    game();
    
  
  //when fail, set gameOn to false to startover
}

//UNfinished
//Polishing 1
/*
void initPattern()
{
  //
  int lights[] = {grnL, redL, bluL, yelL, whtL, turL, 0};
  int intervals[] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
  playTones2(lights, intervals, 8);
  
  int notes[] = {grnL, redL, bluL, yelL, whtL, turL, 0};
  int noteLen = 500;
  int intervals[] = {500, 500, 500, 500, 500, 500, 500, 500};

  playTones(buzzer, notes, intervals, 8);
  if()
    initP = false;
} */

//@author Lihan
//Tested
void processButton(int onButton)
{
  //play tone and turn on led for 1s
  int led = getLED(onButton);
  int LEDTone = getTone(led);
    
  tone(buzz, LEDTone);
  turnOn(led);
  delay(500);
  noTone(buzz);
  turnOff(led);
  delay(80);
}

int getOnButton()
{
  readButtonStates();
  
  if(grnBOn)
    return grnB;
  else if(redBOn)
    return redB;
  else if(yelBOn)
    return yelB;
  else if(bluBOn)
    return bluB;
  else if(turBOn)
    return turB;
   else if(whtBOn)
    return whtB;
  else
    return 0;
}

//if grnB is pressed grnL should light up and grnT should play

void game()
{
  if(win)
  {
    Serial.println("win == true");
    //winning tune combo
    //UNfinished
    //Polishing 2
  }
  else if(!fail)
  {
    if(startOfSeq)
    {
      //play key
      Serial.println("keys: ");
      delay(200);
      for(int i = 0; i <= keyI; i++)
      {
        processButton(key[i]);
        //custom printing (pins to buttons)
        printlnButton(key[i]);
      }
      //reset ansI
      ansI = 0;
      startOfSeq = false; //only play key seq once every round
    }
    
    //get user input
    //one button press and release
    if(getOnButton() == 0)
      bPressed = false;
    else if(getOnButton() != 0 && !bPressed)
    {
      //get the button pressed by user
      int onButton = getOnButton();
      //play corresponding tone and turn on corresponding led
      processButton(onButton);
      //printing
      printlnButton(onButton);
      //update ans[]
      ans[ansI] = onButton;
      //check ans[] with key[]
      bool correctAns = checkAns(ansI);
      if(correctAns)
      {
        if(ansI == keyI) //end of this round
        {
          //update keyI
          keyI += 1;
          //play key at start of seq
          startOfSeq = true;
          //winning condition
          if(keyI == keyLen)
            win = true;
        }
        else
          ansI += 1; //input the next
      }
      else
      {
        fail = true;
        startOfSeq = true;
      }
      
      bPressed = true;
    }
  }
  else //fail && !win
  {
    Serial.println("fail == true");
    //play failure tune combo
    //UNfinished
    //Polishing 3
    
    //reset key[] for new game
    setNewKey();
    
    //reset game
    gameOn = false;
    Serial.println(gameOn);
  }
  
}

//custom printing
void printlnButton(int button)
{
  if(button == grnB)
    Serial.println("grn");
  else if(button == redB)
    Serial.println("red");
  else if(button == yelB)
    Serial.println("yel");
  else if(button == bluB)
    Serial.println("blu");
  else if(button == turB)
    Serial.println("tur");
  else if(button == whtB)
    Serial.println("wht");
}

int getTone(int led)
{
  if(led == grnL)
    return grnT;
  else if(led == redL)
    return redT;
  else if(led == yelL)
    return yelT;
  else if(led == bluL)
    return bluT;
  else if(led == turL)
    return turT;
  else if(led == whtL)
    return whtT;
}

int getLED(int button)
{
  if(button == grnB)
    return grnL;
  else if(button == redB)
    return redL;
  else if(button == yelB)
    return yelL;
  else if(button == bluB)
    return bluL;
  else if(button == turB)
    return turL;
  else if(button == whtB)
    return whtL;
}

void setNewKey()
{
  for(int i = 0; i < keyLen; i++)
  {
    key[i] = getRandButton();
    //Serial.println(key[i]);
  }
  keyI = 0;
}

//helper to setNewKey()
int getRandButton()
{
  randomSeed(analogRead(seedPin));
  
  int randNum = random(6);
  
  if(randNum == 0)
    return grnB;
  else if(randNum == 1)
    return redB;
  else if(randNum == 2)
    return yelB;
  else if(randNum == 3)
    return bluB;
  else if(randNum == 4)
    return turB;
  else //randNum == 5
    return whtB;
}

bool checkAns(int endIndex)
{
  //compare each elem of ans[] with key[]
  for(int i = 0; i <= endIndex; i++)
  {
    if(ans[i] != key[i])
      return false;
  }
  return true;
}

void blink(int led)
{
  long time = millis();
  long sec = time/700;
  if(sec%2 == 0)
  {
    digitalWrite(led, HIGH);
    //tone(buzz, getTone(led));
  }
  else
  {
    digitalWrite(led, LOW);
    //noTone(buzz);
  }
}

void readButtonStates()
{
  grnBOn = digitalRead(grnB)==HIGH;
  redBOn = digitalRead(redB)==HIGH;
  yelBOn = digitalRead(yelB)==HIGH;
  bluBOn = digitalRead(bluB)==HIGH;
  turBOn = digitalRead(turB)==HIGH;
  whtBOn = digitalRead(whtB)==HIGH;
}

void turnOn(int led)
{
  digitalWrite(led, HIGH);
}

void turnOff(int led)
{
  digitalWrite(led, LOW);
}

void allOn()
{
  turnOn(grnL);
  turnOn(redL);
  turnOn(yelL);
  turnOn(bluL);
  turnOn(turL);
  turnOn(whtL);
}

void checkButtonsProgressCheck()
{
  int grnBState = digitalRead(grnB);
  int redBState = digitalRead(redB);
  int yelBState = digitalRead(yelB);
  int bluBState = digitalRead(bluB);
  int turBState = digitalRead(turB);
  int whtBState = digitalRead(whtB);
  
  Serial.print("Green: ");
  Serial.println(grnBState);
  
  Serial.print("Red: ");
  Serial.println(redBState);
  
  Serial.print("Yellow: ");
  Serial.println(yelBState);
  
  Serial.print("Blue: ");
  Serial.println(bluBState);
  
  Serial.print("Turquoise: ");
  Serial.println(turBState);
  
  Serial.print("White: ");
  Serial.println(whtBState);
}

//playTones method and examples
/*
void londonBridgeLights()
{
  int lights[] =     {green,  blue,  green,  yellow,  red,  yellow,  green,  red};
  int intervals[] = {500, 500, 500, 500, 500, 500, 500, 500};
  playTones2(lights, intervals, 8);
}

void londonBridgeNew()
{
  int notes[] =     {G4,  noteA4,  G4,  F4,  E4,  F4,  G4,  E4}; //0 represents noTone
  int noteLen = 500;
  int intervals[] = {500, 500, 500, 500, 500, 500, 500, 500}; //line up your notes & durations

  playTones(buzzer, notes, intervals, 8);
}
*/

/**
 * playTones:  Plays an array of tones.  
 * Each for a specified duration.
 * The Arduino can do something else while calling this method.
 * 
 * Precondtions:  1)  tones and durations have the same number of elements
 *                2)  elements of durations are in milliseconds
 *                3)  length is the length of tones and durations
 */
void playTones(int buzz, int tones[], int durations[], int length){
  if(sizeof(tones)/sizeof(int) == sizeof(durations)/sizeof(int))
  {
    long sum = 0;
    for(int i = 0; i<length;i++)
    {
      sum += durations[i];
    }
    //calculate which index we should be working with
    int musicI = 0;
    for(musicI = 0; millis()%sum>=sumUntil(durations,musicI,length);musicI++)//super bananas
    {    }
    if(millis()%sum<sumUntil(durations,musicI,length))    //bananas
    {
      if(tones[musicI]!= 0)
      {
        tone(buzz, tones[musicI]);
        //if note == noteYouWant
        //turn on ledYouWant
        //turn off all others
        //if chain for every note/led
      }
      else
      {
        noTone(buzz);
        //allOff
      }
    }
  }
}
/**
 * sumUntil:  returns the sum of all the values from 0 to index 
 * inside of arr
 * This is a helper method for playTones
 * 
 * Precondtions:  1)  0<=index<=length-1
 *                2)  length is the length of arr
 */
long sumUntil(int arr[], int index,int length)
{
  long sum = 0;
  for(int i = 0;i<=index;i++)
  {
    sum+=arr[i];
  }
  return sum;
}

//LED version of playTones()
void playTones2(int tones[], int durations[], int length){
  if(sizeof(tones)/sizeof(int) == sizeof(durations)/sizeof(int))
  {
    long sum = 0;
    for(int i = 0; i<length;i++)
    {
      sum += durations[i];
    }
    //calculate which index we should be working with
    int musicI = 0;
    for(musicI = 0; millis()%sum>=sumUntil(durations,musicI,length);musicI++)//super bananas
    {    }
    if(millis()%sum<sumUntil(durations,musicI,length))    //bananas
    {
      if(tones[musicI]!= 0)
      {
        if(musicI == 0)
        {
          digitalWrite(tones[length - 1], LOW);
        }
        //if(musicI > 0) //>0 not >1 (!)
        else
        {
          digitalWrite(tones[musicI - 1], LOW);
        }

        //turn off the last one
        //if musicI == 0 turn off[len - 1] 
        //or just always set the last one to 0?
        //give it a pause before starting again?
        //nope
        
        digitalWrite(tones[musicI], HIGH);
        //tone(buzz, tones[musicI]);
      }
      else
      {
        //noTone(buzz);
        digitalWrite(tones[musicI-1], LOW);
      }
    }
  }
}
