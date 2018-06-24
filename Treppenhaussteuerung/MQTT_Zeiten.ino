void ZeitenMelden()
{
  if (debug == 1) Serial.print("ZeitenMelden() -> min_1_check: ");
  if (debug == 1) Serial.println(min_1_check);
  if (debug == 1) Serial.print("ZeitenMelden() -> gesamt_minuten: ");
  if (debug == 1) Serial.println(seconds()/60);
  if (min_1_check <= seconds()/60/1 || min_1_check == 0)
  {
    gesamt_sekunden = seconds();
    gesamt_minuten = gesamt_sekunden/60;
    gesamt_stunden = gesamt_minuten/60;
    gesamt_tage = gesamt_stunden/24;
    
    if (debug == 1) Serial.print("ZeitenMelden() -> gesamt_tage: ");
    if (debug == 1) Serial.println(gesamt_tage);
    if (debug == 1) Serial.print("ZeitenMelden() -> gesamt_stunden: ");
    if (debug == 1) Serial.println(gesamt_stunden);
    if (debug == 1) Serial.print("ZeitenMelden() -> gesamt_minuten: ");
    if (debug == 1) Serial.println(gesamt_minuten);
   
    stringhelperT=String(gesamt_tage);
    if (debug == 1) Serial.print("ZeitenMelden() -> stringhelperT: ");
    if (debug == 1) Serial.println(stringhelperT);
    stringhelperT.toCharArray(converttimetostringhelperT,5);
    client.publish("/Treppenhaus_LED/INFO/UPTIME_TAGE", converttimetostringhelperT);
    
    stringhelperH=String(gesamt_stunden - (gesamt_tage * 24));
    if (debug == 1) Serial.print("ZeitenMelden() -> stringhelperH: ");
    if (debug == 1) Serial.println(stringhelperH);
    stringhelperH.toCharArray(converttimetostringhelperH,3);
    client.publish("/Treppenhaus_LED/INFO/UPTIME_H", converttimetostringhelperH);
    
    stringhelperM=String(gesamt_minuten - (gesamt_stunden*60));
    if (debug == 1) Serial.print("ZeitenMelden() -> stringhelperM: ");
    if (debug == 1) Serial.println(stringhelperM);
    stringhelperM.toCharArray(converttimetostringhelperM,3);
    client.publish("/Treppenhaus_LED/INFO/UPTIME_MIN", converttimetostringhelperM);
        
    min_1_check = (gesamt_minuten+1)/1;
  }  
}

