#include <Javino.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Wire.h>

#define disk1 0x50

#define rxPin 18
#define txPin 19

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

Javino j;

int operacao = 0;
String progAux = "";
int comandosEntrada[54][3];
int comandosSaida[54][3];

void setup() {

  Serial.begin(9600);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // pinMode CLP
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  operacao = atualizaOp();

  carregaProg();
}

void loop() {

  operacao = atualizaOp();

  switch (operacao) {
    case (1):
      iniciado();
      break;

    case (2):
      runProg();
      break;

    case (3):
      pause();
      break;

    case (4):
      gravacao();
      break;

    default: break;
  }

}

int atualizaOp() {
  int op = 0;
  String opAux = "";

  if ( mySerial.available() )
  {
    while ( mySerial.available() )
      opAux = mySerial.read();

    op = opAux.toInt();
  } else {
    op = operacao;
  }

  return op;
}

void verificaEntradas() {
  // verifica comunicação javino e responde a requisições
}

void iniciado() {
  unsigned int address = 0;
  operacao = (readEEPROM(disk1, address), DEC);//verificar conversão bit -> int
}

void runProg() {
  int contaComandos = 0, contaValidos = 0;
  for(int i = 0; i < 6; i++){
    for(int x = 0; x < 54; x++){
      if(comandosEntrada[x][0] == i){
        if(comandosEntrada[x][1] == 0 && digitalRead(comandosEntrada[x][2]) == LOW ){
          contaValidos++;
        } else if(comandosEntrada[x][1] == 1 && digitalRead(comandosEntrada[x][2]) == HIGH){
          contaValidos++;
        }
        contaComandos++;
      }
    }
    if(contaComandos == contaValidos && contaValidos != 0){
      executaLinha(i);
    }
    contaComandos = 0;
    contaValidos = 0;
  }
}
void executaLinha(int linha){
  for(int i = 0; i < 54; i++){
    if(comandosSaida[i][0] == linha){
      if(comandosSaida[i][1] == 4){
        digitalWrite(comandosSaida[2], LOW);
      }else if(comandosSaida[i][1] == 5){
        digitalWrite(comandosSaida[2], HIGH);
      }
    }
  }
}
void pause() {
  verificaEntradas();
}

void gravacao() {
  if (j.availablemsg()) {

    if (j.getmsg().equals("Ini_envio_prog")) {

      boolean verifica = false;
      int pacotes = "";

      do {

        if (j.availablemsg()) {

          pacotes = j.getmsg().toInt();
          digitalWrite(10, HIGH);
          verifica = true;

        }

      } while (verifica == false);

      delay(300);
      verifica = false;

      for (int i = 0; i < pacotes; i = i) {

        do {

          if (j.availablemsg()) {
            i++;
            progAux += j.getmsg();
            verifica = true;
          }

        } while (verifica == false);
      }
      salvaJson();
      carregaProg();
    }
  }
}

void salvaJson() {
  StaticJsonDocument<200> ln;
  StaticJsonDocument<200> in;
  StaticJsonDocument<200> out;
  StaticJsonDocument<200> json;

  deserializeJson(json, progAux);
  int contPosicao = 0;
  for (int i = 0; i < 2; i++) {

    ln = json[(String("ln") + i)];
    in = ln["in"];
    out = ln["out"];

    if (ln["in"] != "null" || ln["out"] != "null") {

      for (int x =  0; x < 3; x++) {

        contPosicao++;

        if (in[String("cm" + x)] != "null" || out["cm" + x] != "null") {

          String saida = out[String("cm") + x];
          String entrada = in[String("cm") + x];

          // valida comandos nulos pela porta = 0
          if(String(entrada[2]) == "null"){
            saida[2] = 0;
          }
          if(String(saida[2]) == "null"){
            saida[2] = 0;
          }

          int dado = (String(saida[0]) + String(saida[2])  + String(entrada[0]) + String(entrada[2]) + i).toInt(); // comando saida, porta saida, comando entrada, porta entrada

          unsigned int address = contPosicao;
          writeEEPROM(disk1, address, dado);
        }
      }
    }
  }
  // marca finalização da escrita
  unsigned int address = contPosicao++;
  writeEEPROM(disk1, address, 0);


}
void carregaProg() {
  int proxPos = 0, cont = 1;
  String aux = "";

  unsigned int address = 0;

  do {
    address = cont;

    aux = (readEEPROM(disk1, address), DEC);

     // valida comandos entrada nulos pela porta = 0
    if (aux[3] != "0") {
      comandosEntrada[cont][0] = aux[4]; // linha
      comandosEntrada[cont][1] = aux[2]; // comando
      comandosEntrada[cont][2] = aux[3]; // porta
    }
     // valida comandos saida nulos pela porta = 0
    if (aux[1] != "0" && aux[4] != "") {
      comandosSaida[cont][0] = aux[4]; // linha 
      comandosSaida[cont][1] = aux[0]; // comando 
      comandosSaida[cont][2] = aux[1]; // porta 
    }

    cont++;
    address = cont++;
    proxPos = (readEEPROM(disk1, address), DEC);

  } while (proxPos != 0);
}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {

  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // Byte mais significativo
  Wire.write((int)(eeaddress & 0xFF)); // Byte menos significativo
  Wire.write(data);
  Wire.endTransmission();

  delay(5);
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));
  Wire.write((int)(eeaddress & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress, 1);
  if (Wire.available()) rdata = Wire.read();

  return rdata;
}
