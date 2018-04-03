#include "sdk_common.h"
#include  "ble_cus.h"
#include <string.h>
#include "ble_srv_common.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"           

uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init){
  
  if(p_cus == NULL || p_cus_init == NULL){
    return NRF_ERROR_NULL;
  }
  uint32_t err_code;
  ble_uuid_t ble_uuid;
  
  p_cus->conn_handle            = BLE_CONN_HANDLE_INVALID; //Este valor deve ser inicializado em INVALID porque assumimos que só será válido quando houver conexão.
  
  ble_uuid128_t base_uuid       = {CUSTOM_SERVICE_UUID_BASE};
  SEGGER_RTT_WriteString(0, "Serviço atribuido.\n");
  SEGGER_RTT_printf(0, "Service UUID: %d \n", base_uuid); // Print service UUID should match definition BLE_UUID_OUR_SERVICE
  err_code                      = sd_ble_uuid_vs_add(&base_uuid, &p_cus->uuid_type);
  VERIFY_SUCCESS(err_code);
  //VERIFY_SUCESS(err_code);

  ble_uuid.type = p_cus->uuid_type; //p_cus é a estrutura ble_cus_s definida no ble_cus.h
  ble_uuid.uuid = CUSTOM_SERVICE_UUID;

  

  //Adicionando um Custom Service

  err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_cus->service_handle);
  if(err_code != NRF_SUCCESS){
      return err_code;
  }
  return err_code;

}
