void loop() {
  client.loop();

  if (!client.connected()) {
    Serial.print("MQTT Client not connected");
    ConnectMQTT();
  }
 
  if (POWER == 1)
  {
    if (V_Sec_Check > seconds())
    {
      V_LICHT_TIMEOUT = seconds() + V_DAUER_LICHT_SEK;
    }
    if (debug == 1) Serial.print("V_DAUER_LICHT_SEK: ");
    if (debug == 1) Serial.println(V_DAUER_LICHT_SEK);
    V_Sec_Check = seconds();
    if (debug == 1) Serial.print("V_LICHT_TIMEOUT: ");
    if (debug == 1) Serial.println(V_LICHT_TIMEOUT);
    if (debug == 1) Serial.print("V_Sec_Check: ");
    if (debug == 1) Serial.println(V_Sec_Check);
      
    if (P_BEWEGUNG1.status()) client.publish("/Treppenhaus_LED/States/Bewegungssensor1", String(P_BEWEGUNG1.status()));
    if (debug == 1) Serial.print("P_BEWEGUNG1: ");
    if (debug == 1) Serial.println(P_BEWEGUNG1.status());
      
    if (debug == 1) Serial.print("P_BEWEGUNG2: ");
    if (debug == 1) Serial.println(P_BEWEGUNG2.status());
    if (P_BEWEGUNG2.status()) client.publish("/Treppenhaus_LED/States/Bewegungssensor2", String(P_BEWEGUNG2.status()));
  
    if (P_HELLIGKEIT.status()) client.publish("/Treppenhaus_LED/States/Helligkeit", String(P_HELLIGKEIT.status()));
    if (debug == 1) Serial.print("P_HELLIGKEIT: ");
    if (debug == 1) Serial.println(P_HELLIGKEIT.status());
    
    if (P_HELLIGKEIT.status())
    {
      if (P_BEWEGUNG1.status() || P_BEWEGUNG2.status())
      {
        Einschalten();
      }
      else
      {
        Ausschalten();
      }
    }
    else
    {
      Ausschalten();
    }
    delay(10);
    
    if (debug == 1) Serial.print("Aktuelles Intervall: ");
    if (debug == 1) Serial.println(seconds()/60/1);
    ZeitenMelden();
    delay(2000);
  }
}

