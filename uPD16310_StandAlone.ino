/**********************************************************************/
/*This code is not clean and OFFCOURSE will be possible do it better! */
/*this is only a group of functions to be used as independent code,   */
/*and by this way will be possible to any person can do the changes   */
/*of code and see what happen.                                        */
/*The code don't depend of any external library or extenal functions  */
/*complicated.                                                        */
/*I'm let the values to sent as binnary, this allow swap bit by bit   */
/* to is possible test segment by segment without convert to HEX      */
/**********************************************************************/
/* This code show how is possible work with the driver SN75518        */
/*     Used at VFD StandAlone of RENAULT SPACE III                    */
/**********************************************************************/
#include <Arduino.h>
#include <String.h>

#define VFD_in 3  //This is the pin number 3 on Arduino UNO
#define VFD_clk 4 //This is the pin number 4 on Arduino UNO
#define VFD_stb 5 //This is the pin number 5 on Arduino UNO
#define VFD_latch 14 //This is the pin number A0 on Arduino UNO

#define sn75518_in 6  //This is the pin number 6 on Arduino UNO
#define sn75518_clk 7 //This is the pin number 7 on Arduino UNO
#define sn75518_stb 8 //This is the pin number 8 on Arduino UNO
#define sn75518_latch 9//This is the pin number 9 on Arduino UNO

int ledPin = 13; // LED connected to digital pin 13
// don't define the other pins, but is A0 to input analog signal, pins D2 & D3 is trigger input,

//ATT: On the Uno and other ATMEGA based boards, unsigned ints (unsigned integers) are the same as ints in that they store a 2 byte value.
//Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.
unsigned char word0 = 0x00;
unsigned char word1 = 0x00;
unsigned char word2 = 0x00;
unsigned char word3 = 0x00;
unsigned char word4 = 0x00;
unsigned char word5 = 0x00;
unsigned char word6 = 0x00;
unsigned char word7 = 0x00;
bool flag = true;

    //........................66666555555555544444444443333333//..33322222222221111111111000000000
    //........................43210987654321098765432109876543//..21098765432109876543210987654321
    //........................hgfedcba543210......................hgfedcba543210.. Please confirme your VFD have the same order of segments and grids!!!
   unsigned long arr[12]  ={0b11111111111111111111111111111111, 0b11111111111111111111111111111111,//0 & 1
                            0b11111111111111111111111111111111, 0b11111111111111111111111111111111,//2 & 3
                            0b11111111111111111111111111111111, 0b11111111111111111111111111111111,//4 & 5
                            0b11111111111111111111111111111111, 0b11111111111111111111111111111111,//6 & 7
                            0b11111111111111111111111111111111, 0b11111111111111111111111111111111,//8 & 9
                            0b11111111111111111111111111111111, 0b11111111111111111111111111111111,//empty & empty        
    };
uint8_t numbers0[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B10111111), //                (20~27)
};
uint8_t numbers1[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B10000110), //                (20~27)
};
uint8_t numbers2[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B11011011), //                (20~27)
};
uint8_t numbers3[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B11001111), //                (20~27)
};
uint8_t numbers4[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B11100110), //                (20~27)
};
uint8_t numbers5[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B11101101), //                (20~27)
};
uint8_t numbers6[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B11111101), //                (20~27)
};
uint8_t numbers7[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B10000111), //                (20~27)
};
uint8_t numbers8[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B11111111), //                (20~27)
};
uint8_t numbers9[8] = {(0B00000000),  (0B00000000), // ( 0~F )
                       (0B00000000),  (0B00000000), // (00~0F)
                       (0B00001011),  (0B11011111), // (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
                       (0B11100111), //                (20~27)
};
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);
//*************************************************//
void sn75518_send_char(unsigned char a) {
  //New data enter the latches while LATCH ENABLE is high. These data are stored while LATCH ENABLE is low.
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 0b00000001; //our bitmask
  data = a;
  // the validation of data happen when clk go from LOW to HIGH.
  digitalWrite(sn75518_stb, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
  
  delayMicroseconds(1);
  digitalWrite(sn75518_clk, LOW); // need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(1);
  for (mask = 0b10000000; mask > 0; mask >>= 1) { //iterate through bit mask
    digitalWrite(sn75518_clk, LOW); // need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(1);
    if (data & mask) { // if bitwise AND resolves to true
      digitalWrite(sn75518_in, HIGH);
      //Serial.print(1);
    }
    else { //if bitwise and resolves to false
      digitalWrite(sn75518_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(sn75518_clk, HIGH); // need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(1);
    //
    digitalWrite(sn75518_stb, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
    
    delayMicroseconds(1);
  }
}
void sn75518_send_char_without(unsigned char a){
  //New data enter the latches while LATCH ENABLE is high. These data are stored while LATCH ENABLE is low.
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  data = a;
  for (mask = 0b10000000; mask > 0; mask >>= 1) { //iterate through bit mask
    digitalWrite(sn75518_clk, LOW);
    delayMicroseconds(1);
    if (data & mask) { // if bitwise AND resolves to true
      digitalWrite(sn75518_in, HIGH);
      //Serial.print(1);
    }
    else { //if bitwise and resolves to false
      digitalWrite(sn75518_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(sn75518_clk, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(1);
  }
  //Serial.println();
}
void VFD_send_char(unsigned char a) {
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 0b00000001; //our bitmask
  data = a;
  // the validation of data happen when clk go from LOW to HIGH.
  digitalWrite(VFD_stb, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
  
  delayMicroseconds(1);
  digitalWrite(VFD_clk, LOW); // need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(1);
  for (mask = 0b10000000; mask > 0; mask >>= 1) { //iterate through bit mask
    digitalWrite(VFD_clk, LOW); // need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(1);
    if (data & mask) { // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else { //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk, HIGH); // need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(1);
    //
    digitalWrite(VFD_stb, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
    
    delayMicroseconds(1);
  }
}
void VFD_send_char_without(unsigned char a){
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  data = a;
  for (mask = 0b10000000; mask > 0; mask >>= 1) { //iterate through bit mask
    digitalWrite(VFD_clk, LOW);
    delayMicroseconds(1);
    if (data & mask) { // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else { //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(1);
  }
  //Serial.println();
}

void allON_SN75518() {
  digitalWrite(sn75518_stb, HIGH); //
  delayMicroseconds(1);
  sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B00000000); //   1:8   -   9:16//    byte 0 & 1
  sn75518_send_char_without(0B00000001);  sn75518_send_char_without(0B11111111); //  17:24  -  25:32//    Byte 2 & 3
  // //second set of 75518 32 outputs
  // sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B00000000); //  33:40  -  41:48//    Byte 4 & 5
  // sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7 Last two byte have the 9 grids of VFD
  digitalWrite(sn75518_stb, LOW); //
  delayMicroseconds(5);
  digitalWrite(sn75518_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(sn75518_latch, LOW); //
  delayMicroseconds(5);
}
void allOFF_SN75518() { 
  digitalWrite(sn75518_stb, HIGH); //

  delayMicroseconds(1);

  sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B00000000); //   1:8   -   9:16//
  sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B00000000); //  17:24  -  25:32//
  // //second set of 75518 32 outputs
  // sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B00000000); //  33:40  -  41:48//
  // sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B11111111); //  49:56  -  57:46//
  digitalWrite(sn75518_stb, LOW); //
  delayMicroseconds(5);
  digitalWrite(sn75518_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(sn75518_latch, LOW); //
  delayMicroseconds(5);
  
}
void grid_SN75518(uint8_t grid0, uint8_t grid1) {
  
  digitalWrite(sn75518_stb, HIGH); //
  
  delayMicroseconds(1);

  sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B00000000); //   1:8   -   9:16//    byte 0 & 1
  sn75518_send_char_without(grid0);  sn75518_send_char_without(grid1); //  17:24  -  25:32//    Byte 2 & 3
  // //second set of 75518 32 outputs
  // sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B00000000); //  33:40  -  41:48//    Byte 4 & 5
  // sn75518_send_char_without(0B00000000);  sn75518_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7 Last byte is the 8 grids of VFD

  digitalWrite(sn75518_stb, LOW); //
  delayMicroseconds(2);
  digitalWrite(sn75518_latch, HIGH); //
  delayMicroseconds(2);
  digitalWrite(sn75518_latch, LOW); //
  delayMicroseconds(2);
}
void km0_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers0[0]);  VFD_send_char_without(numbers0[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers0[2]);  VFD_send_char_without(numbers0[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers0[4]);  VFD_send_char_without(numbers0[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers0[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km1_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers1[0]);  VFD_send_char_without(numbers1[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers1[2]);  VFD_send_char_without(numbers1[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers1[4]);  VFD_send_char_without(numbers1[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers1[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km2_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers2[0]);  VFD_send_char_without(numbers2[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers2[2]);  VFD_send_char_without(numbers2[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers2[4]);  VFD_send_char_without(numbers2[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers2[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km3_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers3[0]);  VFD_send_char_without(numbers3[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers3[2]);  VFD_send_char_without(numbers3[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers3[4]);  VFD_send_char_without(numbers3[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers3[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km4_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers4[0]);  VFD_send_char_without(numbers4[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers4[2]);  VFD_send_char_without(numbers4[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers4[4]);  VFD_send_char_without(numbers4[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers4[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km5_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers5[0]);  VFD_send_char_without(numbers5[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers5[2]);  VFD_send_char_without(numbers5[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers5[4]);  VFD_send_char_without(numbers5[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers5[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km6_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers6[0]);  VFD_send_char_without(numbers6[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers6[2]);  VFD_send_char_without(numbers6[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers6[4]);  VFD_send_char_without(numbers6[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers6[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km7_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers7[0]);  VFD_send_char_without(numbers7[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers7[2]);  VFD_send_char_without(numbers7[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers7[4]);  VFD_send_char_without(numbers7[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers7[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km8_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers8[0]);  VFD_send_char_without(numbers8[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers8[2]);  VFD_send_char_without(numbers8[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers8[4]);  VFD_send_char_without(numbers8[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers8[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void km9_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(numbers9[0]);  VFD_send_char_without(numbers9[1]); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(numbers9[2]);  VFD_send_char_without(numbers9[3]); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(numbers9[4]);  VFD_send_char_without(numbers9[5]); //  33:40  -  41:48//    Byte 4 & 5    (10~1F) (0000SSSS) (SSSSSSSS) (SSSSSSSS)
  VFD_send_char_without(numbers9[6]); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void grid4_HI_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(0B00000100);  VFD_send_char_without(0B10000000); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(0B10100110);  VFD_send_char_without(0B00111000); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set of 75518 32 outputs
  VFD_send_char_without(0B10000000);  VFD_send_char_without(0B00000000); //  33:40  -  41:48//    Byte 4 & 5    (10~1F)
  VFD_send_char_without(0B00000000); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void grid5_spaceF_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(0B00000001);  VFD_send_char_without(0B00011100); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(0B00100000);  VFD_send_char_without(0B00000000); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set
  VFD_send_char_without(0B00000000);  VFD_send_char_without(0B00000000); //  33:40  -  41:48//    Byte 4 & 5    (10~1F)
  VFD_send_char_without(0B00000000); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);
  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void grid6_OL_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(0B00000101);  VFD_send_char_without(0B00000100); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(0B00001110);  VFD_send_char_without(0B00001000); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set
  VFD_send_char_without(0B11000000);  VFD_send_char_without(0B00000000); //  33:40  -  41:48//    Byte 4 & 5    (10~1F)
  VFD_send_char_without(0B00000000); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);
  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void grid7_KS_VFD() {
  digitalWrite(VFD_stb, HIGH); //
  
  delayMicroseconds(1);

  VFD_send_char_without(0B00000110);  VFD_send_char_without(0B00011100); //   1:8   -   9:16//    byte 0 & 1    ( 0~F )
  VFD_send_char_without(0B00100010);  VFD_send_char_without(0B10011100); //  17:24  -  25:32//    Byte 2 & 3    (00~0F)
  // //second set
  VFD_send_char_without(0B00000000);  VFD_send_char_without(0B00000000); //  33:40  -  41:48//    Byte 4 & 5    (10~1F)
  VFD_send_char_without(0B00000000); // VFD_send_char_without(0B11111111); //  49:56  -  57:64//    Byte 6 & 7  (20~27)
  //VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //  digitalWrite(14,HIGH); //Is pin A0 and enable internal pull-up resistor
}
void allON_VFD() { 
  digitalWrite(VFD_stb, HIGH); //

  delayMicroseconds(1);

  VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111); //   1:8   -   9:16//
  VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111); //  17:24  -  25:32//
  // //second set 
   VFD_send_char_without(0B11111111);  VFD_send_char_without(0B11111111); //  33:40  -  41:48//
   VFD_send_char_without(0B11111111);  //VFD_send_char_without(0B00000000); //  49:56  -  57:46//
   //VFD_send_char_without(0B00000000);

  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //
}
void allOFF_VFD() { 
  digitalWrite(VFD_stb, HIGH); //

  delayMicroseconds(1);

  VFD_send_char_without(0B00000000);  VFD_send_char_without(0B00000000); //   1:8   -   9:16//
  VFD_send_char_without(0B00000000);  VFD_send_char_without(0B00000000); //  17:24  -  25:32//
  // //second set 
   VFD_send_char_without(0B00000000);  VFD_send_char_without(0B00000000); //  33:40  -  41:48//
   VFD_send_char_without(0B00000000);  //VFD_send_char_without(0B00000000); //  49:56  -  57:46//
   //
  digitalWrite(VFD_latch, HIGH); //
  delayMicroseconds(5);
  digitalWrite(VFD_latch, LOW); //
  delayMicroseconds(5);
  digitalWrite(VFD_stb, LOW); //
}
void km(){
  grid_SN75518(0x00, 0b00000010);  
  delay(2);
  km0_VFD();
  delay(500);
  km1_VFD();
  delay(500);
  km2_VFD();
  delay(500);
  km3_VFD();
  delay(500);
  km4_VFD();
  delay(500);
  km5_VFD();
  delay(500);
  km6_VFD();
  delay(500);
  km7_VFD();
  delay(500);
  km8_VFD();
  delay(500);  
  km9_VFD();
  delay(500);     
}
void msgHiFolks(){
  for(uint8_t r = 0; r < 100; r++){
    grid_SN75518(0x00, 0b00100000);  
    grid4_HI_VFD();
    delay(5);

    grid_SN75518(0x00, 0b01000000);
    grid5_spaceF_VFD();
    delay(5);

    grid_SN75518(0x00, 0b00001000);
    grid6_OL_VFD();
    delay(5);

    grid_SN75518(0x00, 0b00010000);    
    grid7_KS_VFD();
    delay(5);
  }  
}
void all(){
  for (uint8_t i = 0; i < 5; i++){
  allON_SN75518();
  allON_VFD();
  allON_VFD();
  allON_VFD();
  allON_VFD();
  delay(500); // waits for two second
   allOFF_SN75518(); // All off
   delay(500); // waits for two second
  }
}
void setup() {
  pinMode(VFD_in, OUTPUT);
  pinMode(VFD_clk, OUTPUT);
  pinMode(VFD_stb, OUTPUT);
  pinMode(VFD_latch, OUTPUT);
 
  pinMode(sn75518_in, OUTPUT);
  pinMode(sn75518_clk, OUTPUT);
  pinMode(sn75518_stb, OUTPUT);
  pinMode(sn75518_latch, OUTPUT);

  pinMode(ledPin, OUTPUT); // sets the digital pin as output
  Serial.begin(115200); // only to debug
}
void loop() {
  all();
  msgHiFolks();
  km();
}
