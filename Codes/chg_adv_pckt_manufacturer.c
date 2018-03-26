//Este código foi retirado intergralmente do tutorial oficial da NORDIC.
//https://devzone.nordicsemi.com/tutorials/b/bluetooth-low-energy/posts/ble-advertising-a-beginners-tutorial
//Todos os direitos autorais estão reservados ao autor do post MartinBL.

static void advertising_init(void)
{
    uint32_t      err_code;
    ble_advdata_t advdata;  // Struct containing advertising parameters

    // Build advertising data struct to pass into @ref ble_advertising_init.
    memset(&amp;advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;

    ble_adv_modes_config_t options = {0};
    options.ble_adv_fast_enabled  = BLE_ADV_FAST_ENABLED;
    options.ble_adv_fast_interval = APP_ADV_INTERVAL;
    options.ble_adv_fast_timeout  = APP_ADV_TIMEOUT_IN_SECONDS;

    err_code = ble_advertising_init(&amp;advdata, NULL, &amp;options, on_adv_evt, NULL);
    APP_ERROR_CHECK(err_code);
}
