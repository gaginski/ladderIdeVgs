// bibliotecas
#include <U8glib.h>

// Pinagem
#define rxPin 18
#define txPin 19
#define AUMENTAR_PIN 8
#define DIMINUIR_PIN 7



// Variaveis Globais
String opcoes[4] = {"Gravar", "Executar", "Selecionar", "Status"};
 int op = 1;
 SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

// Declarando Display
U8GLIB_ST7920_128X64_1X u8g( 6,  //E
                             5,  //R/W
                             4,  //RS
                             7); //RST

// Imagem - Logo IF
const uint8_t logoIf[] U8G_PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xc1, 0xff,
                                       0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0xff, 0xc3, 0xff, 0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0xc0, 0xff, 0xcf, 0xff, 0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xcf, 0xff, 0xe3, 0xff, 0x01, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xcf, 0xff,
                                       0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0xc0, 0xff, 0xcf, 0xff, 0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0xff, 0xc3, 0xff, 0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xc1, 0xff, 0xe3, 0xff, 0x01, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x01, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0xe3, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff,
                                       0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00
                                     };

// Imagem - Logo VGS
const uint8_t logoVgs[] U8G_PROGMEM = {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x0f, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff,
                                           0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff,
                                           0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff,
                                           0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff,
                                           0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff,
                                           0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
                                           0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                           0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff,
                                           0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
                                           0xfe, 0xff, 0xcf, 0xff, 0xbf, 0xff, 0xff, 0xe3, 0x07, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x18, 0xfe, 0xff, 0x07, 0xff, 0x83, 0xff, 0x7f, 0xe0,
                                           0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0xfc, 0xff, 0x87, 0xff,
                                           0x80, 0xff, 0x1f, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
                                           0xf8, 0xff, 0xc3, 0x1f, 0xf0, 0xff, 0x0f, 0xff, 0x1f, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x7c, 0xf8, 0xff, 0xe1, 0x07, 0xfc, 0xff, 0x83, 0xff,
                                           0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xf8, 0xff, 0xe0, 0x81,
                                           0xff, 0xff, 0xc3, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
                                           0xf8, 0xff, 0xf0, 0xe0, 0xff, 0xff, 0xc1, 0xff, 0x3f, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xfe, 0xf1, 0x7f, 0x78, 0xf8, 0xff, 0xff, 0x83, 0xff,
                                           0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xf1, 0x3f, 0x7c, 0xfc,
                                           0xff, 0xff, 0x03, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
                                           0xe1, 0x3f, 0x3e, 0xfe, 0xff, 0xff, 0x0f, 0xfc, 0x7f, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xfe, 0xc3, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0x3f, 0xe0,
                                           0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xc3, 0x1f, 0x1f, 0xff,
                                           0xff, 0xff, 0xff, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
                                           0x87, 0x8f, 0x1f, 0xff, 0x7f, 0xf8, 0xff, 0x83, 0x7f, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xfe, 0x0f, 0xc7, 0x1f, 0xff, 0x7f, 0xf8, 0xff, 0x83,
                                           0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x0f, 0xc2, 0x1f, 0xff,
                                           0x7f, 0xf8, 0xff, 0x87, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
                                           0x1f, 0xe2, 0x1f, 0xfe, 0x7f, 0xf8, 0xff, 0xc3, 0x7f, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xfe, 0x3f, 0xe0, 0x3f, 0xfc, 0x7f, 0xf8, 0xff, 0xc1,
                                           0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0xf0, 0x7f, 0xf0,
                                           0x7f, 0xf8, 0x3f, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
                                           0x7f, 0xf8, 0xff, 0x00, 0x3f, 0xf8, 0x03, 0xfc, 0x1f, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xfc, 0xff, 0xfc, 0xff, 0x03, 0x00, 0xf8, 0x87, 0xff,
                                           0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x3f,
                                           0x80, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
                                           0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                           0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff,
                                           0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
                                           0xff, 0x3f, 0x20, 0xf8, 0x33, 0x0c, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xc0, 0xff, 0x3f, 0x20, 0x40, 0x30, 0x0c, 0xff, 0xff,
                                           0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x3f, 0x20, 0x40,
                                           0x30, 0x0c, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x07, 0x00, 0x20, 0x40, 0x30, 0x0c, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0xfe, 0x3f, 0x20, 0x40, 0x30, 0x0c, 0xff, 0x7f,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x20, 0x40,
                                           0x30, 0x0c, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0xf8, 0x3f, 0x20, 0xf8, 0x33, 0x0c, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff,
                                           0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff,
                                           0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
                                           0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0xf0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x1f, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00
                                      };

void setup() {
  pinMode(10, INPUT); 
digitalWrite(10, 1);
pinMode(9, INPUT); 
digitalWrite(9, 1); 
pinMode(11, INPUT); 
digitalWrite(11, 1);  

  disp_graph_init();
  apresentaLogo();

}

void loop() {
 
 int setaCima = digitalRead(10); 
 int setaBaixo = digitalRead(11); 
 int enter = digitalRead(9);


 if(op == 1){
 u8g.firstPage();
  do {
    ApresentaOpcoes();
  } while ( u8g.nextPage() );
 }
 if(setaCima == 0){
  AtuCarrossel(1);
   op = 1;
  delay(200);
 }else if(setaBaixo ==0){
   AtuCarrossel(0);
   op = 1;
   delay(200);
 }else if(enter == 0){
  mySerial.write(opS);
  op = 0;
  u8g.firstPage();
   do {
    u8g.setFont(u8g_font_helvB08);
    u8g.drawStr(0,40, "Executando opcao");
    
  } while ( u8g.nextPage() );
 
 
 }
 

}
void disp_graph_init()
{
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     //branco
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         //máxima intensidade
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }


}

void apresentaLogo() {
  u8g.firstPage();
  do {
    u8g.drawXBMP( 0, 0, 128, 64, logoIf);
  } while ( u8g.nextPage() );
  delay(2000);


  u8g.firstPage();
  do {
    u8g.drawXBMP( 0, 0, 128, 64, logoVgs);
  } while ( u8g.nextPage() );
  delay(2000);
}

void AtuCarrossel(int o) {
  String aux[4] = {};
  if(o == 1){
  for (int i = 0; i <= 3; i++) {
    aux[i] = opcoes[i];
  }


  opcoes[0] = aux[3];

  for (int i = 0; i < 3; i++) {
    opcoes[i + 1] = aux[i];
  }

  }else{
   for (int i = 3; i >= 0; i--) {
    aux[i] = opcoes[i];
  }


  opcoes[3] = aux[0];

  for (int i = 3; i > 0; i--) {
    opcoes[i - 1] = aux[i];
  } 
  }
}

void ApresentaOpcoes() {
  int t1 = sizeof(opcoes[0]);
  char op1[18];
  opcoes[0].toCharArray(op1, 18);

  int t2 = sizeof(opcoes[1]);
  char op2[18];
  opcoes[1].toCharArray(op2, 18);

  int t3 = sizeof(opcoes[2]);
  char op3[18];
  opcoes[2].toCharArray(op3, 18);

  int t4 = sizeof(opcoes[3]);
  char op4[18];
  opcoes[3].toCharArray(op4, 18);


  u8g.setFont(u8g_font_helvB08);
  u8g.drawStr(0, 13, op1);

  u8g.setFont(u8g_font_helvB08);
  u8g.drawStr(0, 25, op2);

  u8g.setFont(u8g_font_8x13);
  u8g.drawBox(0, 31, 120, 13);
  u8g.setColorIndex(0);
  u8g.drawStr(0, 41, op3);

  u8g.setFont(u8g_font_helvB08);
  u8g.setColorIndex(1);
  u8g.drawStr(0, 60, op4);


}

// Inicia tela de confirmação e veirific cliques

boolean confirmacao() {
  boolean conf = false;
  boolean enter = false;

  desenhaNao();

  do {

    // VERIFICAÇÃO BOTAO
    if (1 == 1) {
      desenhaSim();
      conf = true;
    }

    if (1 == 2) {
      desenhaNao();
      conf = false;
    }

    enter = varreEnter();

  } while (enter);

    return conf;
}

// Desenha botoes graficos com "sim" selecionado
void desenhaSim() {

  // botão sim
  u8g.setFont(u8g_font_8x13);
  u8g.drawBox(0, 31, 96, 13);
  u8g.setColorIndex(0);
  u8g.drawStr(0, 41, "SIM");

  //não
  u8g.setFont(u8g_font_helvB08);
  u8g.drawStr(0, 25, "NAO");
}

// Desenha botoes graficos com "nao" selecionado
void desenhaNao() {

  // botão sim
  u8g.setFont(u8g_font_8x13);
  u8g.drawBox(0, 31, 96, 13);
  u8g.setColorIndex(0);
  u8g.drawStr(0, 41, "SIM");

  //não
  u8g.setFont(u8g_font_helvB08);
  u8g.drawStr(0, 25, "NÃO");
}

// Varredura enter
boolean varreEnter() {
  boolean enter = false;

  //ADICIONAR VERIFICACAO BOTAO ENTER

  return enter;
}