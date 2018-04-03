  #include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"


/**@brief Macro para definir uma instancia de ble_cus (Ble Custom Service)
* 
* @param _name Nome da instancia
* @hideinitialize
*
*/

#define BLE_CUS_DEF(_name) \
static ble_cus_t _name; \

//52c8c8fa-41a4-4269-a171-266416
/*
#define CUSTOM_SERVICE_UUID_BASE  {0XA4,0X94,0XEF,0X16,0X64,0X26,0X71,0XA1, \
                                  0X69,0X42,0XA4,0X41,0XFA,0XC8,0XC8,0X52}
#define CUSTOM_SERVICE_UUID 0x1400
#define CUSTOM_VALUE_CHAR_UUID 0x1401*/

//94AExxxx-49CB-4F86-BF22-124AC4A317A8
//94AE7EC4-49CB-4F86-BF22-124AC4A317A8
#define CUSTOM_SERVICE_UUID_BASE         {0xBC, 0x8A, 0xBF, 0x45, 0xCA, 0x05, 0x50, 0xBA, \
                                          0x40, 0x42, 0xB0, 0x00, 0xC9, 0xAD, 0xC8, 0xF3}

#define CUSTOM_SERVICE_UUID               0x1400
#define CUSTOM_VALUE_CHAR_UUID            0x1401

typedef struct ble_cus_s ble_cus_t;

/**@brief Estrutura de inicialização do Serviço customizado (Custom Service). Aqui deve conter todas as opções
  e dados necessários para a inicialização do serviço.*/
typedef struct{
  uint8_t                               initial_custom_value; /**< Valor inicial do serviço */
  ble_srv_cccd_security_mode_t          custom_value_char_attr_md; /**< Inicializador para o valor do Security Level ???*/
} ble_cus_init_t;

/**@brief */

struct ble_cus_s{
  uint16_t                              service_handle; /**< Lida com o CustomService fornecido pela BLESTACK */
  ble_gatts_char_handles_t              custom_value_handles; /**< Identificador relacionado com a caracteristica Custom Value  */
  uint16_t                              conn_handle;          /**< Lida com o estaddo atual da conexão, fornecida pelo BLE_STACK. Se for BLE_CONN_HANDLE_INVALID, então não há conexão */
  uint8_t                               uuid_type;
};



/**@brief Função para inicialização do Custom Service 
*
* @param[out]   p_cus   Estrutura do tipo Custom Service. Esta estrutura deverá ser fornecida pela aplicação. Deverá ser inicializada por esta função e posteriormente
*                       se usada para identificar esta intancia particular desse serviço.
*
* @param[in]    p_cus_init Informação necessária para inicializar o serviço.
*
* @return NRF_SUCESS ao obter sucesso na inicialização do serviço, caso contrario um código "error code" será retornado. 
*/
uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);

