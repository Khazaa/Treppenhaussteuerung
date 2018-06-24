void ConnectMQTT() {
  Serial.println("----MQTT----");
  Serial.print("\nconnecting...");
  while (!client.connect(MQTT_Broker, MQTT_Username, MQTT_Password)) 
  {
    Serial.print(".");
    delay(1500);
  }
  Serial.println("");
  Serial.println("MQTT connected");
  Serial.println("------------");
  Serial.println("");
  
  client.subscribe("/Treppenhaus_LED/SET/Licht_Dauer_Sekunden");
  client.subscribe("/Treppenhaus_LED/SET/POWER");
  client.subscribe("/Treppenhaus_LED/SET/DEBUG");
}

void messageReceived(String &topic, String &payload) {
  if (debug == 1) Serial.println("incoming: " + topic + " - " + payload);
  if (topic == "/Treppenhaus_LED/SET/Licht_Dauer_Sekunden")
  {
    if (isValidNumber(payload))
    {
      V_DAUER_LICHT_SEK = payload.toInt();
    }
    
  }
  else if (topic == "/Treppenhaus_LED/SET/POWER")
  {
    if (payload == "OFF")
    {
      POWER = 0;
      client.publish("/Treppenhaus_LED/INFO/STATUS", "OFF");
    }
    else
    {
      POWER = 1;
      client.publish("/Treppenhaus_LED/INFO/STATUS", "ON");
    }
  }
  else if (topic == "/Treppenhaus_LED/SET/DEBUG")
  {
    if (payload == "OFF")
    {
      debug = 0;
      //client.publish("/Treppenhaus_LED/INFO/STATUS", "OFF");
    }
    else
    {
      debug = 1;
      //client.publish("/Treppenhaus_LED/INFO/STATUS", "ON");
    }
  }
}
