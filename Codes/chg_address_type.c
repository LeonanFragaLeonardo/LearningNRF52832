static void gap_params_init(void){
  ...
	//Esse trecho vai alterar o tipo de endereço para Private resolvable Address. 
	//O qual é aleatório, no entanto a cada "reset" um endereço diferente é gerado.
	//Este código fica no main.c dentro da função acima.
		
	ble_gap_addr_t gap_address;
	gap_address.addr_type = BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE, &gap_address;
	err_code = sd_ble_gap_address_set(BLE_GAP_ADDR_CYCLE_MODE_AYTO, &gap_address);

	APP_ERROR_CHECK(err_code);
}
