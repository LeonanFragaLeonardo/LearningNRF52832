//Este código foi retirado na íntegra de:
//https://devzone.nordicsemi.com/tutorials/b/bluetooth-low-energy/posts/ble-advertising-a-beginners-tutorial
//Todos os direitos autorais estão reservados ao autor do post, MartinBL.

static void advertising_init(void)
{
    uint32_t      err_code;
    ble_advdata_t advdata;  // Struct containing advertising parameters
    
    ble_advdata_manuf_data_t        manuf_data; // Variable to hold manufacturer specific data
    uint8_t data[]                      = "SomeData!"; // Our data to adverise
    manuf_data.company_identifier       = 0x0059; // Nordics company ID
    manuf_data.data.p_data              = data;     
    manuf_data.data.size                = sizeof(data);

    // Build advertising data struct to pass into @ref ble_advertising_init.
    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_SHORT_NAME;
    advdata.short_name_len          = 3;
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    advdata.p_manuf_specific_data   = &manuf_data;
    //------------------------------------------------------------------------
    //Este valor não altera a potência de transmissão, apenas o valor exibido.
    int8_t tx_power                 = -4;
    advdata.p_tx_power_level        = &tx_power;
    //------------------------------------------------------------------------
    
    //Habilita a opção de exibir o ícone no advertise.
    advdata.include_appearance      = true;
    
    // Prepara a resposta do Scan com um pacote específico com dados extras.
    // Este é um recurso utilizado caso seja necessário utilizar mais que 31 bytes no packet de Advertise.
    
    ble_advdata_manuf_data_t                manuf_data_response;
    uint8_t                                 data_response[] = "Many_bytes_of_data"; // Remember there is a 0 terminator at the end of string
    manuf_data_response.company_identifier       = 0x0059;               
    manuf_data_response.data.p_data              = data_response;        
    manuf_data_response.data.size                = sizeof(data_response);

    ble_advdata_t   advdata_response;// Declare and populate a scan response packet
    
    // Always initialize all fields in structs to zero or you might get unexpected behaviour
    memset(&advdata_response, 0, sizeof(advdata_response));
    // Populate the scan response packet
    advdata_response.name_type               = BLE_ADVDATA_NO_NAME; 
    advdata_response.p_manuf_specific_data   = &manuf_data_response;

    ble_adv_modes_config_t options = {0};
    options.ble_adv_fast_enabled  = BLE_ADV_FAST_ENABLED;
    options.ble_adv_fast_interval = APP_ADV_INTERVAL;
    options.ble_adv_fast_timeout  = APP_ADV_TIMEOUT_IN_SECONDS;

    err_code = ble_advertising_init(&advdata, &advdata_response, &options, on_adv_evt, NULL);
    APP_ERROR_CHECK(err_code);
}
