#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
// ================= PINOS =================
#define SS_PIN 10
#define RST_PIN 9
 
#define LED_VERDE 6
#define LED_AMARELO 5
#define LED_VERMELHO 4
 
#define SERVO_PIN 3
 
// ================= OBJETOS =================
MFRC522 rfid(SS_PIN, RST_PIN);
Servo servoMotor;
 
// ================= CONFIG =================
const int ANGULO_FECHADO = 70;
const int ANGULO_ABERTO  = 0;
 
// 🔧 AJUSTE A VELOCIDADE AQUI
const unsigned long TEMPO_PASSO_SERVO = 35;
 
const unsigned long TEMPO_ABERTO = 5000;
const unsigned long TEMPO_PISCAR = 300;
 
// UID autorizado
byte uid_autorizado[] = {0x03, 0x72, 0xC2, 0x2C};
 
// ================= ESTADOS =================
enum EstadoPortao {
  FECHADO,
  ABRINDO,
  ABERTO,
  FECHANDO
};
 
EstadoPortao estado = FECHADO;
 
int anguloAtual = ANGULO_FECHADO;
unsigned long tempoServo = 0;
unsigned long tempoAberto = 0;
 
// ================= ERRO =================
int piscadasRestantes = 0;
bool ledLigado = false;
unsigned long ultimoPisca = 0;
 
// ================= SETUP =================
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
 
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(anguloAtual);
 
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
 
  atualizarSemaforo();
 
  Serial.println("Sistema pronto");
}
 
// ================= LOOP =================
void loop() {
  verificarCartao();
  atualizarServo();
  atualizarErro();
}
 
// ================= RFID =================
void verificarCartao() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;
 
  if (verificarUID(rfid.uid.uidByte, rfid.uid.size)) {
    Serial.println("Acesso liberado");
    iniciarAbertura();
  } else {
    Serial.println("Acesso negado");
    iniciarErro();
  }
 
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
 
bool verificarUID(byte *uid, byte tamanho) {
  if (tamanho != 4) return false;
 
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != uid_autorizado[i]) {
      return false;
    }
  }
  return true;
}
 
// ================= PORTÃO =================
void iniciarAbertura() {
  estado = ABRINDO;
  Serial.println("Portão abrindo");
  atualizarSemaforo();
}
 
void atualizarServo() {
  unsigned long agora = millis();
 
  // ===== ABRINDO =====
  if (estado == ABRINDO) {
    if (agora - tempoServo >= TEMPO_PASSO_SERVO) {
      tempoServo = agora;
 
      if (anguloAtual > ANGULO_ABERTO) {
        anguloAtual--;
        servoMotor.write(anguloAtual);
      } else {
        estado = ABERTO;
        tempoAberto = agora;
        Serial.println("Portão aberto");
        atualizarSemaforo();
      }
    }
  }
 
  // ===== TEMPO ABERTO → COMEÇA A FECHAR =====
  if (estado == ABERTO && agora - tempoAberto >= TEMPO_ABERTO) {
    estado = FECHANDO;
    Serial.println("Portão fechando");
    atualizarSemaforo();
  }
 
  // ===== FECHANDO =====
  if (estado == FECHANDO) {
    if (agora - tempoServo >= TEMPO_PASSO_SERVO) {
      tempoServo = agora;
 
      if (anguloAtual < ANGULO_FECHADO) {
        anguloAtual++;
        servoMotor.write(anguloAtual);
      } else {
        estado = FECHADO;
        Serial.println("Portão fechado");
        atualizarSemaforo();
      }
    }
  }
}
 
// ================= SEMÁFORO =================
void atualizarSemaforo() {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
 
  if (estado == FECHADO) {
    digitalWrite(LED_VERMELHO, HIGH);
  }
 
  if (estado == ABRINDO || estado == FECHANDO) {
    digitalWrite(LED_AMARELO, HIGH);
  }
 
  if (estado == ABERTO) {
    digitalWrite(LED_VERDE, HIGH);
  }
}
 
// ================= ERRO =================
void iniciarErro() {
  piscadasRestantes = 6; // 3 piscadas
  ledLigado = false;
  ultimoPisca = millis();
}
 
void atualizarErro() {
  if (piscadasRestantes <= 0) return;
 
  unsigned long agora = millis();
 
  if (agora - ultimoPisca >= TEMPO_PISCAR) {
    ultimoPisca = agora;
 
    ledLigado = !ledLigado;
    digitalWrite(LED_VERMELHO, ledLigado);
 
    piscadasRestantes--;
 
    if (piscadasRestantes == 0) {
      digitalWrite(LED_VERMELHO, LOW);
      atualizarSemaforo();
    }
  }
}