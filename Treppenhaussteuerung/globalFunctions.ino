boolean isValidNumber(String str)
{
   for(byte i=0;i<str.length();i++)
   {
      if(isDigit(str.charAt(i))) return true;
   }
   return false;
} 

void Ausschalten()
{
  if (debug == 1) Serial.println("Ausschalten()");
  if (debug == 1) Serial.print("seconds() = ");
  if (debug == 1) Serial.println(seconds());
  if (debug == 1) Serial.print("V_LICHT_TIMEOUT = ");
  if (debug == 1) Serial.println(V_LICHT_TIMEOUT);
  
  if (seconds() >= V_LICHT_TIMEOUT)
  {
    if (debug == 1) Serial.println("seconds() >=  V_LICHT_TIMEOUT");
    V_Licht = 0;
      if (debug == 1) Serial.print("V_Licht_alt = ");
      if (debug == 1) Serial.println(V_Licht_alt);
    if (V_Licht != V_Licht_alt)
    {
      if (debug == 1) Serial.println("V_Licht != V_Licht_alt");
      mySwitch.send(RC433Off,24);
      client.publish("/Treppenhaus_LED/States/Licht", "0");
          if (debug == 1) Serial.println("licht ausschalten");
      V_Licht_alt = V_Licht;
    }
  }
}

void Einschalten()
{
  V_Licht = 1;
  if (V_Licht != V_Licht_alt)
  {
    mySwitch.send(RC433On,24);
    client.publish("/Treppenhaus_LED/States/Licht", "1");
    V_Licht_alt = V_Licht;
  }
  V_LICHT_TIMEOUT = seconds() + V_DAUER_LICHT_SEK;
        if (debug == 1) Serial.println("licht einschalten");
}

PString leadZero(int number)
{
  char txt[3];  // room for two characters plus a terminator
  PString str(txt, sizeof(txt));
  str = "";
  if (number < 10)
  {
    str += "0";
  }
  str += number;
  return str;
}

