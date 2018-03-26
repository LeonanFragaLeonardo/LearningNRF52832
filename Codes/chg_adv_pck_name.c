static void advertising_init(void)
{
    ...
      //Mudando este trecho:
    //advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    //advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
      //Para:
      advdata.name_type               = BLE_ADVDATA_SHORT_NAME;
      advdata.short_name_len          =	6; 
      //O trecho alterado faz com que no advertise, apenas as 6 primeiras letras do nome aparecerão,
      //no entanto, nos detalhes o nome completo será exibido
    ...
}
