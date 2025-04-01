const int analogPin = A0;     // Pino do sensor KY-037
const int ledPin = 13;        // Pino do LED
const int limiar = 515;       // Valor médio de silêncio encontrado - pode aumentar ou diminuir um pouco (512 ~ 515)
const int amostras = 10;      // Número de amostras para filtrar ruídos

void setup() {
  pinMode(ledPin, OUTPUT);    // Configura o LED como saída
  Serial.begin(9600);         // Inicia a comunicação serial
}

void loop() {
int soma = 0;
  
  // Filtro: média de 10 leituras para reduzir ruídos
  for (int i = 0; i < amostras; i++) {
    soma += analogRead(analogPin);
    delay(5);                 // Pequeno intervalo entre leituras
  }
  
  int valorFiltrado = soma / amostras;
  
  // Exibe o valor no Monitor Serial (para debug)
  Serial.print("Valor lido: ");
  Serial.println(valorFiltrado);
  
  // Acende o LED apenas se o som ultrapassar o limiar
  if (valorFiltrado > limiar) {
    digitalWrite(ledPin, HIGH);  // LED acende
    Serial.println("-- SOM DETECTADO! --");
    delay(100);                  // Tempo mínimo de acionamento
  } else {
    digitalWrite(ledPin, LOW);   // LED apaga
  }
  
  delay(50);  // Atraso para estabilidade
}

// Forma simples
// void loop() {
//   int valorRaw = analogRead(analogPin);  // Leitura direta
  
//   Serial.print("Valor lido: ");
//   Serial.println(valorRaw);
  
//   if (valorRaw > limiar) {
//     digitalWrite(ledPin, HIGH);
//     Serial.println("-- SOM DETECTADO! --");
//     delay(100);  // Tempo mínimo que o LED fica aceso
//   } else {
//     digitalWrite(ledPin, LOW);
//   }
  
//   delay(delayLeitura);  // Reduza este valor para resposta mais rápida
// }


// Forma híbrida
// void loop() {
//   int valorRaw = analogRead(analogPin);
  
//   // Só aciona se o valor ultrapassar MUITO o limiar (ex: +20%)
//   if (valorRaw > limiar * 1.2) {  // Ex: limiar = 512 → aciona acima de ~614
//     digitalWrite(ledPin, HIGH);
//     delay(50);  // Atraso mínimo
//   } else {
//     digitalWrite(ledPin, LOW);
//   }
  
//   delay(10);  // Leitura mais rápida (10ms = 100 leituras/segundo)
// }