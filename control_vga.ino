int data_0 = 5, data_1 = 6, data_2 = 7, data_3 = 8,
   data_4 = 9, data_5 = 10, data_6 = 11, data_7 = 12; 

int write_pin = 4;
int enable_pin = 3;
int data_enable = 13;
int control_enable = 2;

unsigned char mySprite[120] = {
//  0xa,1,1,0xb,0xc,1,1,0xd,1,1,
  0xA,0xA,0xA,0xA,0xA,0,0,0,0,0,
  0,7,7,0,0,0,0,8,8,0,
  0,0,3,3,0,0,3,3,0,0,
  0,0,0,4,4,4,4,0,0,0,
  1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
//  1,1,1,1,1,1,1,1,1,1
  0,0,0,0,0,0,0,0,0,0
};

void setup() {
  for (int i = data_0; i <= data_7; i++) {
    pinMode(i, OUTPUT);
  }
  digitalWrite(write_pin, HIGH);
  digitalWrite(enable_pin, HIGH);

  digitalWrite(data_enable, HIGH);
  digitalWrite(control_enable, HIGH);
  
  pinMode(data_enable, OUTPUT);
  pinMode(control_enable, OUTPUT);

  pinMode(write_pin, OUTPUT);
  pinMode(enable_pin, OUTPUT);

//  Serial.begin(57600);
//  Serial.println();

//  updateSprite(3, mySprite);

//  setSprite(5, 0, 2);

//  setup85Sprites();

//  setCellSprite(0, 0, 3);
//  setCellSprite(0, 0, 4);
//  setCellSprite(0, 0, 5);



//  outputText(0, 0, "ABCDEFGIJKLMNOPQRSTUVWXYZ");

//  outputText(0, 0, "well HELLO there!");
//  outputText(0, 0, "A");

//  outputText(0, 10, "Testing output on line 10");
//
//  outputText(0, 15, "Testing continuous output on line 15 offset by 1");

//  setCellSprite(0, 0, 31);
//  setCellSprite(0, 0, 32);


  setAllTheSprites();

  sweepScreen(0);

}

void setAllTheSprites() {
  char sprite[120];
  int sprite_color;

  for (int i = 0; i < 85; i++) {
    for (int j = 0; j < i; j++) {
      sprite[j] = sprite_color;
    }
    updateSprite(i, sprite);
  }
  
}


void writeDataPinsSlow(byte data) {
  for (int i = 0; i <= 7; i++) {
      digitalWrite(i + data_0, (data >> i) & 1);
  }
}

#define setPin(b) ( (b)<8 ? PORTD |=(1<<(b)) : PORTB |=(1<<(b-8)) )

#define clrPin(b) ( (b)<8 ? PORTD &=~(1<<(b)) : PORTB &=~(1<<(b-8)) )

void writeDataPinsFast(byte data) {
    //pins: 5..12
    (data & 1) ? setPin(5) : clrPin(5);
    ((data >> 1) & 1) ? setPin(6) : clrPin(6);
    ((data >> 2) & 1) ? setPin(7) : clrPin(7);
    ((data >> 3) & 1) ? setPin(8) : clrPin(8);
    ((data >> 4) & 1) ? setPin(9) : clrPin(9);
    ((data >> 5) & 1) ? setPin(10) : clrPin(10);
    ((data >> 6) & 1) ? setPin(11) : clrPin(11);
    ((data >> 7) & 1) ? setPin(12) : clrPin(12);
}

void writeDataPins(byte data) {
  writeDataPinsFast(data);
}

int INTR_DELAY = 0;
void pushInstruction2(byte instruction, byte arg1, byte arg2) {

  setPin(data_enable);
  delayMicroseconds(INTR_DELAY);

  writeDataPins(instruction);
  
  clrPin(data_enable);
  delayMicroseconds(INTR_DELAY);

  clrPin(control_enable);
  delayMicroseconds(INTR_DELAY);

  clrPin(write_pin);
  delayMicroseconds(INTR_DELAY);
  clrPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  setPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  
  writeDataPins(arg1);
  delayMicroseconds(INTR_DELAY);
  
  clrPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  setPin(enable_pin);
  delayMicroseconds(INTR_DELAY);

  bool write3rdByte = true;
  if (write3rdByte) {
    writeDataPins(arg2);

    clrPin(enable_pin);
    delayMicroseconds(INTR_DELAY);
    setPin(enable_pin);
    delayMicroseconds(INTR_DELAY);
  }

  setPin(write_pin);
  delayMicroseconds(INTR_DELAY);

  setPin(control_enable);
  delayMicroseconds(INTR_DELAY);

  writeDataPins(0);
}

void pushInstruction3(byte instruction, byte arg1, byte arg2, byte arg3) {

//  char text[16];
//  sprintf(text, "%08B %08b %02b %02B", arg1, arg2, arg3, instruction); 
//  Serial.println(text);
//  BinaryStrZeroPad(arg1, 7);Serial.print(" ");
//  BinaryStrZeroPad(arg2, 7);Serial.print(" ");
//  BinaryStrZeroPad(arg3, 7);Serial.print(" ");
//  BinaryStrZeroPad(instruction, 7);Serial.println();

  setPin(data_enable);
  delayMicroseconds(INTR_DELAY);

  writeDataPins(instruction);
  
  clrPin(data_enable);
  delayMicroseconds(INTR_DELAY);

  clrPin(control_enable);
  delayMicroseconds(INTR_DELAY);

  clrPin(write_pin);
  delayMicroseconds(INTR_DELAY);
  clrPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  setPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  
  writeDataPins(arg1);
  delayMicroseconds(INTR_DELAY);
  
  clrPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  setPin(enable_pin);
  delayMicroseconds(INTR_DELAY);

  writeDataPins(arg2);

  clrPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  setPin(enable_pin);
  delayMicroseconds(INTR_DELAY);

  writeDataPins(arg3);

  clrPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  setPin(enable_pin);
  delayMicroseconds(INTR_DELAY);
  
  setPin(write_pin);
  delayMicroseconds(INTR_DELAY);

  setPin(control_enable);
  delayMicroseconds(INTR_DELAY);

  writeDataPins(0);
}

void setCellSprite(unsigned int x, unsigned int y, unsigned int sprite_index) {
  int offset = y * 30 + x;
  pushInstruction3(0x07, (sprite_index >> 6), ((sprite_index << 2) & 0xff) + (offset >> 8), offset & 0xff);
}

void sweepScreen(int sprite_index) {
  for (int i = 0; i < 600; i++) {
    pushInstruction3(0x07, (sprite_index >> 5), (sprite_index << 2) + (i >> 8), i & 0xff);    
  }
}

int asciiToFontIndex(char ascii_char) {
  if (ascii_char <= 96 || (ascii_char >= 123 && ascii_char <= 126))
    return ascii_char - 32;
  
  if (ascii_char >= 97 && ascii_char <= 122)
    return ascii_char - 64;

//  return ascii_char < 96 ? ascii_char ;
  return 0;
}


void outputText(int x, int y, char *text) {
  int out_char_counter = y * 30 + x;
  int next_char_counter = 0;
  char next_char = text[next_char_counter++];
  while (next_char != '\0') {
    int sprite_index = asciiToFontIndex(next_char);
    pushInstruction3(0x07, (sprite_index >> 6), ((sprite_index << 2) & 0xff) + (out_char_counter >> 8), out_char_counter & 0xff);
    out_char_counter++;
    next_char = text[next_char_counter++];
  }
}


//31..24  : [x, 3 MSB of sprite pixel data]
//23..16  : [ 5 LSB of pixel data, 3 MSB bits of sprite pixel offset]
//15..8 : [4 LSB bits of sprite pixl offset, 4 bits sprite index]
//7..0  : instruction 0x8
void updateSprite(unsigned char sprite_index, const unsigned char input[120]) {
  for (int i = 0; i < 120; i+=2) {
    unsigned char sprite_pixel = input[i];
    unsigned char sprite_pixel2 = input[i+1];
    unsigned char combined_pixels = ((sprite_pixel << 4) & 0xff) + (sprite_pixel2 & 0xf);
    unsigned char offset = i;
    unsigned char offsetX = offset % 10;
    unsigned char offsetY = offset / 10;

//    char text[120];
//    sprintf(text, "Pushing sprite pixels: x:%d, y:%d, sprite:%d, ", offsetX, offsetY, sprite_index);
//    Serial.println(text);

    unsigned char arg0 = combined_pixels; 
    unsigned char arg1 = ((offsetY << 4)& 0xff) + (offsetX & 0xf);
    unsigned char arg2 = (sprite_index & 0xff);
    
    pushInstruction3(0x8, arg0, arg1, arg2);
  }
}


int sprite = 0;

void loop() {

  outputText(0, 12, "                             ");
  outputText(0, 10, "                             ");
  outputText(4, 8, "#freevo may be faster");
  delay(1000);
  outputText(8, 12, "than #bluevo");
  delay(1000);
  outputText(0, 10, "(though it has a built motor)");
  delay(2000);
 
  //setup85Sprites();
//
//  if (sprite++ == 85) sprite = 0;
//    
//  for (int i = 0; i < 30; i++) {
//     setSprite(i, 0, sprite);
//  }
//
//  delay(1000);

}


void setup85Sprites() {

  char sprite[120];

  // 85 total

  int sprite_color;
  for (int i = 0; i < 85; i++) {
    sprite_color = i % 16;
    memset(sprite, 0, 120);
//    memset(sprite, 1, 120);

    for (int j = 0; j < i; j++) {
      sprite[j] = sprite_color;
    }
    updateSprite(i, sprite);
//    delay(10);
  }
  

}


void BinaryStrZeroPad(int Number,char ZeroPadding){
  //ZeroPadding = nth bit, e.g for a 16 bit number nth bit = 15
  signed char i=ZeroPadding;
  while(i>=0){
      if((Number & (1<<i)) > 0) Serial.write('1');
      else Serial.write('0');
      --i;
  }
}
