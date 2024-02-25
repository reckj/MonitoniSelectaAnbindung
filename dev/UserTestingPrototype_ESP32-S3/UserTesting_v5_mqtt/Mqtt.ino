void mqttConnect() {
  Serial.print("\nconnecting to mqtt broker");
  while (!mqttClient.connect("Selecta", "test-orbitals", "wykBmo6ZdeO4WZ4p")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to mqtt broker!");
  // client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void mqttPublish(String topic, String value) {
  mqttClient.publish(topic, value);
}