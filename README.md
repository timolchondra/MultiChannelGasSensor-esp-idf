# MultiChannelGasSensor
This code is meant to port the existing Arduino library for the Seeed MultiChannelGasSensor into ESP-IDF

Working functions right now:
begin();
begin(int addr);
getVersion();
calcGas(int gas);       //this includes all the other functions that are in this function

