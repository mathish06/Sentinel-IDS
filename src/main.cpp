#include <Arduino.h>
#include <WiFi.h>

// Cette fonction s'exécute UNE fois au démarrage (comme une init)
void setup() {
  // Initialisation du port série pour parler au PC
  Serial.begin(115200);
  Serial.println("Sentinel System Starting...");

  // Initialisation du Wifi en mode Station (juste pour tester la lib)
  WiFi.mode(WIFI_STA);
  Serial.println("Wifi Stack Loaded.");
}

// Cette fonction s'exécute en boucle infinie (while(1))
void loop() {
  Serial.println("System alive...");
  delay(1000); // Pause de 1000ms (1 seconde)
}