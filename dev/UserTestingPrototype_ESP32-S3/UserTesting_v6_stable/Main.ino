void mainLoop() {
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  //runBLE();
  //updateTelemetry();
  updateInputs();
  vending(vendingState);
}