void mainLoop() {
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  if (!mqttClient.connected()) {
    mqttConnect();
  }
  mqttClient.loop();
  updateTelemetry();
  updateInputs();
  vending(vendingState);
}