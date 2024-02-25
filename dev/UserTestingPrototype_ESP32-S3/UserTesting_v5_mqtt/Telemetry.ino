void updateTelemetry () {
  String t_sleep = String(timerSleep.read());

  mqttPublish("state", String(vendingState));
  mqttPublish("t_sleep", t_sleep);
}
