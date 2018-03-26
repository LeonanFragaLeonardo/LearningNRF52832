static void advertising_init(void)
{
  ...
  advdata.include_appearance			= true;
  ...
}
static void gap_params_init(void)
{
  ...
  //Muda o ícone na lista de dispositivos encontrados
  //Uma lista completa pode ser encontrada na documentação
  //https://developer.nordicsemi.com/nRF51_SDK/nRF51_SDK_v7.x.x/doc/7.1.0/s110/html/a00837.html
  sd_ble_gap_appearance_set(BLE_APPEARANCE_HID_MOUSE);
  ...
}
