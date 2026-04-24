#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
// Configuração do Display LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
// Arrays com os pinos dos 3 sensores de cada trave
const int SENS_TRAVE_A[3] = {32, 33, 25};
const int SENS_TRAVE_B[3] = {27, 14, 13};
 
#define BOTAO_RESET 26
 
// Configuração da Lógica do Sensor (Mude para HIGH se o sensor for invertido)
const int ESTADO_COM_DISCO = LOW;
 
// Variáveis do Placar e Cooldown
int golsTimeA = 0;
int golsTimeB = 0;
unsigned long tempoUltimoGolA = 0;
unsigned long tempoUltimoGolB = 0;
const unsigned long TEMPO_BLOQUEIO = 2000; // 2 segundos de bloqueio na trave após gol
 
// --- VARIÁVEIS DO CRONÔMETRO ---
bool jogoRolando = false;
int tempoRestanteSegundos = 300; // 5 Minutos = 300 Segundos
unsigned long tempoUltimoSegundo = 0;
 
void setup() {
  Serial.begin(115200);
 
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
 
  for (int i = 0; i < 3; i++) {
    pinMode(SENS_TRAVE_A[i], INPUT_PULLUP);
    pinMode(SENS_TRAVE_B[i], INPUT_PULLUP);
  }
 
  pinMode(BOTAO_RESET, INPUT_PULLUP);
 
  lcd.setCursor(0, 0);
  lcd.print("  MESA DEDOBOL  ");
  lcd.setCursor(0, 1);
  lcd.print(" Iniciando...   ");
  delay(2000);
 
  iniciarPartida();
}
 
void loop() {
  // Lê o botão de reset a qualquer momento
  if (digitalRead(BOTAO_RESET) == LOW) {
    iniciarPartida();
    delay(500); // Evita clique duplo acidental
  }
 
  // Só checa os gols e o relógio se o jogo estiver rolando!
  if (jogoRolando) {
   
    // --- LÓGICA DO CRONÔMETRO ---
    if (millis() - tempoUltimoSegundo >= 1000) {
      tempoUltimoSegundo = millis();
      tempoRestanteSegundos--;
      atualizarPlacar();
 
      // Verifica se o tempo acabou
      if (tempoRestanteSegundos <= 0) {
        finalizarPartida();
      }
    }
 
    // --- LÓGICA DOS GOLS ---
    bool discoNaTraveA = verificarTrave(SENS_TRAVE_A);
    bool discoNaTraveB = verificarTrave(SENS_TRAVE_B);
 
    if (discoNaTraveA && (millis() - tempoUltimoGolA > TEMPO_BLOQUEIO)) {
      golsTimeB++;
      tempoUltimoGolA = millis();
      mostrarGol("TIME B");
    }
 
    if (discoNaTraveB && (millis() - tempoUltimoGolB > TEMPO_BLOQUEIO)) {
      golsTimeA++;
      tempoUltimoGolB = millis();
      mostrarGol("TIME A");
    }
  }
}
 
// -------- FUNÇÃO DE LEITURA DOS SENSORES --------
bool verificarTrave(const int pinos[3]) {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(pinos[i]) == ESTADO_COM_DISCO) {
      delay(10); // Filtro Anti-Ruído
      if (digitalRead(pinos[i]) == ESTADO_COM_DISCO) {
        return true;
      }
    }
  }
  return false;
}
 
// -------- FUNÇÕES DO JOGO E DISPLAY --------
 
void iniciarPartida() {
  golsTimeA = 0;
  golsTimeB = 0;
  tempoRestanteSegundos = 300; // Reseta para 5 minutos
  jogoRolando = true;
  tempoUltimoSegundo = millis();
 
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("BOLA NA MESA!");
  delay(1500);
  lcd.clear();
  atualizarPlacar();
}
 
void finalizarPartida() {
  jogoRolando = false; // Trava o jogo (ignora os sensores)
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("FIM DE JOGO!");
 
  // Mostra o placar final com formatação bonitinha na segunda linha
  char bufferFinal[17];
  sprintf(bufferFinal, "  A: %02d x %02d :B", golsTimeA, golsTimeB);
  lcd.setCursor(0, 1);
  lcd.print(bufferFinal);
}
 
void atualizarPlacar() {
  if (!jogoRolando) return;
 
  lcd.setCursor(0, 0);
  lcd.print(" TIME A x TIME B");
 
  // Calcula os minutos e segundos restantes
  int minutos = tempoRestanteSegundos / 60;
  int segundos = tempoRestanteSegundos % 60;
 
  // Cria uma "frase" formatada com os gols e o tempo
  // %02d garante que o número sempre tenha 2 dígitos (Ex: 05, 09, 12)
  char bufferTela[17];
  sprintf(bufferTela, " %02d  %02d:%02d  %02d ", golsTimeA, minutos, segundos, golsTimeB);
 
  // Escreve tudo de uma vez só na linha de baixo
  lcd.setCursor(0, 1);
  lcd.print(bufferTela);
}
 
void mostrarGol(String time) {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("G O O O L ! !");
 
  lcd.setCursor(5, 1);
  lcd.print(time);
 
  delay(2000);  // Comemora por 2 segundos
 
  // Deduz os 2 segundos da comemoração do relógio para não desincronizar
  if (tempoRestanteSegundos > 2) {
    tempoRestanteSegundos -= 2;
  } else {
    tempoRestanteSegundos = 0;
  }
 
  tempoUltimoSegundo = millis(); // Sincroniza o "tique-taque" novamente
 
  if (tempoRestanteSegundos > 0) {
    lcd.clear();
    atualizarPlacar();
  }
}
 