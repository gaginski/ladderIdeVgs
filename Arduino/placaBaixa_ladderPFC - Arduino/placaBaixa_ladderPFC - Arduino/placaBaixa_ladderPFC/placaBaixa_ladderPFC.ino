/*.....:: Include Dependencias/Bibliotecas ::.....*/
#include <Javino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

/*.....:: Define pinagem de comunicação com a interface e disco::.....*/
#define rxPin 18
#define txPin 19
#define disk1 0x50

/*.....:: Váriaveis Globais ::.....*/
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
Javino javino;
String pacote[6][9] = {""};
int nLinhas = 6, nColunas = 9;
String msgProg = "";
int opExecutar = 0;


/*.....:: Definição portas de input ::.....*/
#define const int i1 =3;
#define const int i2 =4;
#define const int i3 =5;
#define const int i4 =6;
#define const int i5 =7;
#define const int i6 =8;
int arrayEntrada[] = {3, 4, 5, 6, 7, 8}

/*.....:: Definição portas de output ::.....*/
#define const int o1 =9;
#define const int o2 =10;
#define const int o3 =11;
#define const int o4 =12;
#define const int o5 =13;
#define const int o6 =14;
int arraySaida[] = {9, 10, 11, 12, 13}
 
/*.....:: Definição operações ::.....*/
#define const int iniciado = 0;
#define const int executaProg = 1;
#define const int programando = 2;

void setup() {
  Serial.begin(9600);

  /*Configurando modo das portas input e output*/
  pinMode(i1 INPUT);
  pinMode(i2 INPUT);
  pinMode(i3 INPUT);
  pinMode(i4 INPUT);
  pinMode(i5 INPUT);
  pinMode(i6 INPUT);
  pinMode(o1 OUTPUT);
  pinMode(o2 OUTPUT);
  pinMode(o3 OUTPUT);
  pinMode(o4 OUTPUT);
  pinMode(o5 OUTPUT);
  pinMode(o6 OUTPUT);
}

void loop() {

  /* ...:: Executa verificação da comunicação com a interface ::...*/
  opExecutar =  atualizaOp();

  /* ...:: Executa opção selecionada  ::...*/
  switch (opExecutar) {
    case (iniciado):
      if (msgProg == "") {
        separaPacotes(leProg(0));
      }
      break;
    case (executaProg):
      executaProg();
      break;
    case (programando):
      modeProgramacao();
      break;
    default: break;
  }
}
int atualizaOp() {
  int op = 0;
  if ( mySerial.available() )
  {
    while (mySerial.available()) {
      opAux = mySerial.read().toInt()
    }
    op = opAux.toInt();
  } else {
    op = opExecutar;
  }
  return op;
}

void modeProgramacao() {
  if (javino.availablemsg()) {
    if (javino.getmsg() == "ini") {
      void recebePacotes() {
      }
    }
  }
}

void recebePacotes() {
  String value = "";
  int i = 0;
  msgProg = "";
  while (value != "fim") {
    if (javino.availablemsg()) {
      value = javino.getmsg();
      if (value == "rept") {
        msgProg = "";
        i = 0;
        tm.displayText("Break");
        break;
      }
      i++;
      tm.displayText(String(i));
      javino.sendmsg(value);
      delay(10);
      if (value != "fim") {
        msgProg.concat(value);
      }
    }
  }
  salvaProg(0, msgProg);
  separaPacotes(msgProg);
}

void separaPacotes(String value) {
  int linha = -1, coluna = 0;
  for (int i = 0; i < value.length(); i++) {
    if (value[i] != '-') {
      if (value[i] == 'L') {
        linha++;
        coluna = 0;
        //Serial.println("Pulou linha"); // debug
      } else if (value[i - 1] == '-') {
        if (value[i] == '0') {
          pacote[linha][coluna] = "";
        } else {
          pacote[linha][coluna] = "";
          pacote[linha][coluna].concat(value[i]);
          pacote[linha][coluna].concat(value[i + 1]);
          pacote[linha][coluna].concat(value[i + 2]);
          pacote[linha][coluna].concat(value[i + 3]);
          i = i + 4;
        }
        coluna++;
      }
    }
  }
}

void executaProg() {
  for (int l = 0; l < nLinhas; l++) {
    bool verificaComandos = true;
    for (int c = 0; c < nColunas; c++ ) {
      if (verificaComandos) {
        String comando = pacote[l][c];
        if (comando[0] == 'I') {
          String aux = "";
          aux.concat(comando[0]);
          aux.concat(comando[1]);
          String porta = "";
          porta.concat(comando[3]);
          verificaComandos = validaComandoEntrada(retornaComnando(aux), arrayEntrada[porta.toInt()]); // tipo do comando(true normalmente fechado, false normalmente aberto), e porta
        }
      }
    }
    if (verificaComandos) {
      //Serial.println("Executando linha:"); // debug
      //Serial.println(l); // debug
      for (int c = 0; c < nColunas; c++ ) {
        String comando = pacote[l][c];
        String aux = "";
        aux.concat(comando[0]);
        aux.concat(comando[1]);
        String porta = "";
        porta.concat(comando[3]);
        if (comando[0] == 'O'){
          //Serial.println("Mandando executar na função:"); // debug
          executaComandoSaida(retornaComnando(aux), arraySaida[porta.toInt()]);
        }
      }
    } else {
      for (int c = 0; c < nColunas; c++ ) {
        String comando = pacote[l][c];
        String aux = "";
        aux.concat(comando[0]);
        aux.concat(comando[1]);
        String porta = "";
        porta.concat(comando[3]);
        if (comando[0] == 'O') {
          executaComandoSaida(!retornaComnando(aux), arraySaida[porta.toInt()]);
        }
      }
    }
  }
}

bool retornaComnando(String comando) {
  if (comando == "I1" || comando == "O1'") {
    return true; // entrada normalmente fechada
  } else if (comando == "I2" || comando == "O2") {
    return false; //entrada/saida normalmente aberta
  }
  return true;
}

bool validaComandoEntrada(bool NaNf, int porta) {
  /*Serial.println("Valida comando entrada");
    Serial.println((digitalRead(porta) == NaNf));
    Serial.print("Port:");
    Serial.println(porta);
    Serial.print("Comando:");
    Serial.println(NaNf);
    Serial.println(digitalRead(porta));*/ // debug
  if (digitalRead(porta) == HIGH && NaNf) {
    return true;
  }
  if (digitalRead(porta) == LOW && NaNf == false) {
    return true;
  } else {
    return false;
  }
}
void executaComandoSaida(bool saida, int porta) {
  /*Serial.print("Executando comando: Saida: ");
    Serial.print(saida);
    Serial.print(" Porta: ");
    Serial.println(porta); */ // debug
  digitalWrite(porta, saida);
}

void salvaProg(int enderecoBase, String progSalvar) {
  if !((mensagem.length() > EEPROM.length() || (enderecoBase + mensagem.length()) > EEPROM.length() )) {
    writeEEPROM(disk1, enderecoBase, "i");
    enderecoBase++;
    for (int i = 0; i < progSalvar.length(); i++) {
      writeEEPROM(disk1, enderecoBase, progSalvar[i]);
      enderecoBase++;
    }
    writeEEPROM(disk1, enderecoBase, '\0'); // marcador de fim
  }
}
String leProg(int enderecoBase) {
  String mensagem = "";
  if (!(enderecoBase > EEPROM.length()) && readEEPROM(disk1, enderecoBase) == "i") {
    char pos;
    enderecoBase++;
    do {
      pos = readEEPROM(disk1, enderecoBase);
      enderecoBase++;
      mensagem = mensagem + pos;
    }
    while (pos != '\0'); // terminador da string
  }
  return mensagem;
}
