
void setup_advertising(){
  uint32_t             err_code;
  ble_gap_adv_params_t adv_params;
  ble_gap_whitelist_t  whitelist;
  ble_gap_addr_t   * p_whitelist_addr[1];
  ble_gap_addr_t		whitelist_addr={BLE_GAP_ADDR_TYPE_RANDOM_STATIC,{0x71,0xA2,0xEC,0xDA,0x5F,0xE0}} ;
  uint8_t addr[6] = {0x71,0xA2,0xEC,0xDA,0x5F,0xE0};  
  uint8_t adv_data[15] = {0x07,0x09,0x4E,0x6F,0x72,0x64,0x69,0x63,0x02,0x01,0x04,0x03,0x03,0x0F,0x18};
  uint8_t adv_data_length = 15;

  //Setting up the advertising data with scan response data = Null
  err_code = sd_ble_gap_adv_data_set(adv_data, adv_data_length, NULL, NULL);	

  //Configure the advertising parameter and whitelist
  memset(&adv_params, 0, sizeof(adv_params));
  adv_params.type        = BLE_GAP_ADV_TYPE_ADV_IND;
  adv_params.p_peer_addr = NULL;
  adv_params.interval    = 64;
  adv_params.timeout     = 180;
  p_whitelist_addr[0] = &whitelist_addr;
  whitelist.addr_count = 1;
  whitelist.pp_addrs   =  p_whitelist_addr;
  whitelist.pp_irks = NULL;
  whitelist.irk_count =0;
  adv_params.fp          = BLE_GAP_ADV_FP_FILTER_CONNREQ;
  adv_params.p_whitelist = &whitelist;
  err_code = sd_ble_gap_adv_start(&adv_params);
}