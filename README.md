# LearningNRF52832
Guia enumerado para desenvolvimento de aplicações utilizando o módulo NRF52832 da Nordic. 

# About

ATENÇÃO, este guia está em desenvolvimento, as informações contidas nele são sugestões que por sua vez
estão sendo criadas por um desenvolvedor em fase de aprendizado dentro deste contexto. Toda e qualquer sugestão no que diz respeito
ao conteúdo e uma forma de agregar valor ao mesmo será bem-vinda.

Este guia tem como estrutura uma lista enumerada em ordem crescente, que por sua vez tem relação direta com a conexão entre os conteúdos, 
ou seja, a ordem da lista é uma sugestão de conteúdos para serem estudados de maneira subsequente.
O conteúdo dos items são tutoriais relacionados ao desenvolvimento de aplicações para o módulo NRF52832 da marca Nordic.

Grande parte dos tutoriais utilizados foram retirados do site oficial da [Nordic](https://devzone.nordicsemi.com/tutorials/). 

# How to

Esta lista tem como propósito auxiliar os desenvolvedores que queiram aprender a desenvolver aplicações utilizando o módulo NRF52.
Para fazer o uso basta utilizar o atalho: <kbd>CTRL</kbd> + <kbd>F</kbd> em um SO Windows ou <kbd>command</kbd> + <kbd>F</kbd> em um Windows 

***
# Getting Started

	
[Iniciar o desenvolvimento com NRF](https://devzone.nordicsemi.com/tutorials/) - Nordic Official Page.

1. Este [link](https://devzone.nordicsemi.com/tutorials/b/getting-started/posts/introduction-to-bluetooth-low-energy-and-ble-devel)
	contém uma visão geral em torno do BLE. Estes dois vídeos são massivos, em contrapartida muito esclarecedor para quem está começando.
	Alguns conceitos não foram abordados de maneira detalhada, portanto qualquer dúvida, este é o momento para pesquisar.
	Abaixo há uma breve explicação no que tange a alguns aspectos que ficaram pouco clarificados.
	
	- [Device Manager](#device-manager)
	- [Button Support Package](#bsp-button-support-package)
	- [Connection Events](#connection-events)
	
2. Aqui há um [Tutorial](https://devzone.nordicsemi.com/tutorials/b/getting-started/posts/getting-started-with-the-nrf5-development-kit) excelente que explica de maneira sucinta os procedimentos necessário para compilação. 
Portanto, este tutorial serve apenas para aprender a compilar e não abrange os conceitos do código. 

3. [Este](https://devzone.nordicsemi.com/b/blog/posts/bluetooth-smart-and-the-nordics-softdevices-part-1) tutorial aborda detalhadamente o conceito de Advertising.

4. O seguinte [Tutorial](https://devzone.nordicsemi.com/tutorials/b/bluetooth-low-energy/posts/ble-advertising-a-beginners-tutorial) apresenta os conceitos iniciais do BLE em prática, mais especificamente sobre **advertising**. O código disponível é referente ao modelo nrf51 e por este motivo não foi possível compilar o exemplo, mas o código está comentado e o tutorial explica mais alguns conceitos básicos, portanto mesmo não compilando é possível aprimorar o conhecimento a nível de código com este tutorial. 
	
***
# Some Concepts

## Advertising

Advertising é o ato de realizar broadcast em dados. O broadcast de dados é feito para descobrir dispositivos e publicar dados. 
Existem dois tipos de pacotes de dados que podem ser transmitidos, pacotes Advertising e Scan Response, podendo ter uma carga de até 31 bytes. O endereço de advertiser/anunciante é incluído nos dados de broadcast adicionalmente, além da carga útil de 31 bytes. Portanto são 31 bytes + o endereço do anunciante.

Para poupar energia, quando não esperamos uma conexão e não temos dados extras no scan response packet, basta emitir um “advertise” como non-connectable mode e o processo de RX é evitado, economizando energia.

O único pacote que o scanner ativo pode enviar para o anunciante(advertiser) é o pacote de requisição de consulta, que por sua vez contém apenas o endereço do scanner. O examinador/varredor(scanner) passivo não pode fazer requisições de scan. A seguir são listados 4 tipos de advertising.

### Types
* **ADV_IND**: connectable undirected advertising. Este é o tipo comum de anuncio, onde algum dispositivo pode enviar pacotes de resposta de varredura e conectar ao pedido do anunciante. Por exemplo: Dispositivo liga o bluetooh e avisa que está apto a ser encontrado.
* **ADV_DIRECT_IND**: connectable directed advertising: Este é usado para direcionar o pacote de anuncio para uma central específica para pedir por conexão. Ele ainda é um pacote de broadcast, mas outros varredores(scanners) irão ignorar o pacote se o endereço de um peer não bater com o dele. Neste caso a solicitação de conexão ou de varredura de uma central que não coincidir será ignorada pelo anunciante. (ideal para evitar conexões de dispositivos externos)
* **ADV_NONCONN_IND**: non-connectable undirected advertising. Este é um modo não RX, significa que o anunciante não vai aceitar qualquer requisição de conexão ou de varredura. Ficando dentro deste modo o anunciante que não precisa trocar para o modo receptor e podendo economizar energia. A aplicação “beacon” é a aplicação principal para isto, onde maximizar o tempo de vida da bateria é mais importante e o “beacon” não precisa interagir co o scanner.
* **ADV_SCAN_IND**: scannable undirected advertising. Este pacote de advertising não aceita requisições de conexão, mas aceita requisições de varredura (scan request).




## Device Manager

É um modulo que lida com pontos ativos e vinculados (Active Peers and Bonded Peers). Importante ressaltar que este módulo apenas permite o gerenciamento de informações contextuais, ou seja o gerenciamento de conexões não é o escopo deste módulo. 

- **Active Peers** são dispositivos que estão conectados e podem ou não estarem vinculados;
- **Bonded Peers** são dispositivos que são vinculados e podem ou não estarem ativos (conectados);
- **Active Bonded** Peers são dispositivos os quais estão conectados e vinculados.
- **Paired Devices** são dispositivos pares conectados entre si e tenha necessariamente que realizar o estabelecimento/troca de contexto para a sessão de conexão atual. Quando desconectados, toda informação contextual é descarregada e algumas informações são perdidas, como por exemplo SMP e a configuração GATT.
- Para os peers vinculados, é necessário que se mantenha uma informação de contexto na desconexão e no ciclo de energia. Este módulo lida com o armazenamento de informações de contexto e o mesmo as categoriza em 3 tipos:
	- **Bonding Information** é a informação trocada entre o dispositivo local e o dispositivo de ponta (o par, peer) para estabelecer um vínculo. Ele também inclui informações de identificação peer, como endereço ou IRK ou ambos. Esta categoria de informação é relacionada a Informações de Contexto do Dispositivo (Device Context).
	- **Service/Protocol Information** é a informação mantida para o peer objetivando economizar em procedimentos únicos como os procedimentos de Descoberta de Serviços GATT e Configurações de Serviços. Este permite que os dispositivos retomem a troca de dados em uma reconexão subsequente sem ter que executar os procedimentos iniciais de configuração a cada vez em que for necessário. Esta categoria de informação está relacionada Contexto de Serviço (Service Context);
	- **Application Information** é a informação de contexto em que a aplicação gostaria de associar com cada dispositivo vinculado. For exemplo se uma aplicação escolhe fazer um rank para gerenciar os melhores, a informação do rank deve ser tratada como uma Application Information. Este espaço de armazenamento é fornecido para poupar a aplicação de manter uma tabela de mapeamento entre Instancia do Dispositivo e Application Information. Contudo, se a aplicação não tenha que fazer o uso deste recurso, é possível não usá-lo ou empregar isso em tempo de compilação. Esta categoria de informação está relacionada com o Contexto da Aplicação (Application Context).
***	
## BSP – Button Support Package

Este modulo é utilizado para lidar com LEDs e Botões.  
Ele fornece uma camada de abstração da placa. Também permite aos usuários indicarem determinados estados nos LEDs de uma maneira simples. 
***
## CE - Connection Events

Connection Event (CE) é o tempo cronometrado dentro de um evento reservado para enviar e receber pacotes.
O SoftDevice pode ser habilitado para estender dinamicamente o tamanho do CE
para que o número máximo de pacotes caiba dentro do CE antes mesmo do CE terminar. 
O tempo estendido será um par de pacotes por vez até que o tempo estendido seja alcançado.
A camada de Ligação dentro do estado de conexão (Link layer) deve apenas transmitir Data Channel PDUs. 
Durante um CE, o Master e o Slave alternam pacotes de envio e recebimento.
O CE pode ser fechado por qualquer device.
O início de um CE é chamado de ponto de ancoragem (AP – do inglês Anchor Point). No AP, o Master deve começar a transmitir Data Channel PDU para o Slave. O inicio de um CE são espaçados de forma regular com um interval de connInterval e não deve se sobrepor. O Slave ouve por pacotes enviados pelo máster no AP. 
Portanto, CEs ocorrem de maneira regular, a cada intervalo de tempo e são utilizados para transmitir dados, em contrapartida podem ser ignorados pelo Slave sem que o Master assuma um fim de conexão.
***

## Bluetooth Address Type.

* Um endereço Bluetooth pode ser de 4 tipos distintos, conforme explicado a seguir:
 
	- Public. É um endereço fixo e global, ou seja, não deve mudar nunca durante o ciclo de vida do dispositivo. Ele deve ser registrado na IEEE Registration Authority. 
	- Random Static. É um número aleatório que pode ser gerado cada vez que dispositivo é iniciado ou pode ser mantido um mesmo valor durante o ciclo de vida do dispositivo. Importante ressaltar que ele não pode ser alterado dentro de um único ciclo de vida.

	- **Private Resolvable. Estes valores são gerados a partir de uma IRK (Identity Resolving Key) e um número aleatório. Este pode ser alterado até mesmo durante o ciclo de vida de uma conexão, dificultando o rastreamento realizado por dispositivos desconhecidos. Apenas dispositivos que tenham um determinado IRK pode resolver este endereço e permitir a identificação do dispositivo.**

	- Private Non-Resolvable. São números aleatórios e não são muito utilizados. (Precisa-se entender melhor o conceito)
	
Este conteúdo tem como base a resposta de Carles no [Fórum da Nordic](https://devzone.nordicsemi.com/f/nordic-q-a/2084/gap-address-types) 

## Services e Characteristics

 Os serviços e as characteristics existem como uma maneira de obter flexibilidade, eficacia, compatibilidade entre diferentes plataformas e facilitar a implementação. Por exemplo, quando há um dispositivo fazendo advertising de um Heart Rate Service, e uma plataforma como Android ou iOS detectam este serviço, é garantido que será apresentado um valor padronizado referente à medida dos batimentos cardíacos. Se um dispositivo contém mais que um serviço, é possível selecionar as informações desejadas de qualquer serviço apresentado. Agrupando informações seguindo este princípio, os dispositivos podem descobrir quais informações estão disponíveis e realizar a comunicação apenas no que cabe à aplicação, poupando tempo e consumo energético.

### Services

Por definição da BCS, um serviço é uma coleção de dados e comportamentos associados para realizar uma função ou um recurso particular.
Em outras palavras, um serviço é uma coleção de informações como exemplo, valores de sensores. Há uma associação chamada Bluetooth Special Interest Group (Bluetooth SIG) em que contém serviços pré-definidos como exemplo, Heart Rate Service e alguns outros que por sua vez são acompanhados de uma documentação bem definida. Esta definição tem como propósito facilitar o desenvolvimento de aplicações e firmwares compatíveis com os serviços disponíveis no Bluetooth SIG. Portanto, este é um recurso que objetiva facilitar alguns conceitos, mas é possível desenvolver um serviço personalizado que não está definido na Bluetooth SIG.

### Characteristics

 A BCS define Characteristic como sendo um valor utilizando em serviço juntamente com propriedades e informações no que diz respeito a como o valor é acessado, bem como apresentado.
 EM linhas gerias, a characteristic é o local onde os valores e a informações atuais são apresentados. Parâmetros de segurança, unidades e outros metadados referentes às informações também são encapsulados nas characteristics. Uma abstração das characteristics pode ser uma sala repleta de armários e cada armário tem várias gavetas. Pensando assim, O GATT seria a sala, os armários são os serviços e as gavetas são characteristcs que contém várias informações. Algumas gavetas podem conter restrições ou "configurações" de acesso à informação ali contida.
 
### Universally Unique ID (UUID)

Um UUID é uma abreviação para Universally Unique ID (Identificador Unico Universal, ou ainda ID universalmente único) e significa que é um número único usado para identificação de ***services***, ***characteristics*** e ***descriptors***, também são conhecidos como ***attributes***. Estes IDs são transmitidos pelo ar ede modo que um ***peripheral*** pode informar uma ***central*** quais ***services*** ela fornece. Para economizar tempo de transmissão e memória, há dois tipos de UUIDs:
 - O primeiro é UUID do tipo short de 16-bits. O Heart rate service por exemplo, tem o UUID "0X180D" (0001 1000 0000 1101, esta é a representação binária de 16 bits do UUID). Este tipo é mais eficiente no que tange à memória e energia, no entanto, como é fornecido um número limitado de IDs exclusivos, há uma regra que infere diretamente na maneira como a transmissão dos UUIDs devem ser realizadas. A transmissão de UUIDs BSIG predefinido deve ser realizada apenas pelo ar. 
 - O segundo tipo é um UUID de 128 bits, algumas vezes é referenciado como ***Vendor Specific UUID***. Este tipo de UUID é necessário utilizar quando é desenvolvido ***Custom Services *** e ***Custom Characteristics***, ou seja, quando é necessário desenvolver um service personalizado com suas respectivas characteristics. Um exemplo de "base UUID" é o seguinte valor: "96F3####-D80A-41DB-B9C9-F5F9CF289A98" onde os valores "####" representam um campo onde será inserido o UUID de 16 bits para os custom services e suas characteristics. Este valor pode ser gerado pelo nRFGO Studio, basta ir no menu de ajuda e pesquisar sobre UUID.
 
Fonte: [Nordic](https://devzone.nordicsemi.com/tutorials/b/bluetooth-low-energy/posts/ble-services-a-beginners-tutorial)

## Attribute Protocol (ATT) e Generic Attribute Profile (GATT)


### Attribute Protocol

 O protocolo BLE é construído sob um número de camadas, conforme mostra a Figura 1. A camada de aplicação é construida sob o GATT, que por sua vez é construído sob o ATT. O Att é baseado numa relação Cliente-Servidor, onde o servidor mantém informações como o valor dos sensores, dados de posição e o estado em que se encontra o dispositivo. Esta informação é organizada em uma tabela a qual é definida como sendo uma **tabela de atributos** . Cada atributo dentro da tabela é um valor ou uma parte da informação com algumas propriedades associadas. Portanto, quando um client necessita dos valor de um sensor, ele consulta uma linha da tabela, por exemplo para consultar o valor do sensor de temperatura, ele consulta a linha 17 na tabela. 
 
 ![alt text](https://devzone.nordicsemi.com/cfs-file/__key/communityserver-blogs-components-weblogfiles/00-00-00-00-12-DZ-17/Layer-model.png). 
 
 Figura 1. Protocolo BLE. 
 
 Um exemplo da tabela de atributos pode ser visto no Quadro 1, o qual é um exemplo de uma aplicação comum. Este quadro está relacionado ao Hear Rate Profile. Os valores presentes na coluna Attribute permission não pode ser acessado usando o ATT.
 
 ![alt text](https://devzone.nordicsemi.com/cfs-file/__key/communityserver-blogs-components-weblogfiles/00-00-00-00-12-DZ-17/Attribute-table.png)
 
 Quadro 1. Tabela de atributos.
 
 ### Attribute Handles
 O ***attribute handle*** identifica de maneira exclusiva um atributo em um servidor permitindo que um cliente faça referencia ao atributo em requisições de leitura ou escrita. Em linhas gerais, o handle pode ser considerado o número da linha dentro da tabela de atributos, contudo o handle pode não ser sequencial. Os handles são estruturas numérica de 16-bit. O SoftDevice faz o uso constante dos handles para referenciar uma vasta gama de atributos. Para um programador, esta é uma maneira eficaz de passar valores e informações entre funções. Isso facilita o rastreamento de atributos e obtenção de informações necessárias pela aplicação. O número de handles varia dependendo de quantos atributos há na aplicação.
 
 
 
 ### GATT
  A BCS define GATT como sendo uma estrutura em que profile datas são trocados. Esta estrutura define elementos básicos como serviços e características utilizados em um profile.
  Em linhas gerais, GATT é um conjunto de regras que descreve como agrupar, apresentar e transferir dados usando o BLE.**ler a BCS a respeito de GATT Vol.3 Part G**
 
 Fonte: [Nordic](https://devzone.nordicsemi.com/tutorials/b/bluetooth-low-energy/posts/ble-services-a-beginners-tutorial) e [BCS](https://www.bluetooth.org/en-us/specification/adopted-specifications)


## Extras
### Links

* [Programando comandos no KeilUVision](https://devzone.nordicsemi.com/b/blog/posts/keil-nrfjprog-true).
	
* [Implementação de Alguns recursos com NRF52](https://github.com/NordicPlayground/nrf52-hardware-startup-hands-on).

* [Lista de Advertise Data Types](https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile)

* [Converter Projeto Keil para o Segger](https://devzone.nordicsemi.com/b/blog/posts/segger-embedded-studio-a-cross-platform-ide)

* [Tutorial de como Criar um Custom BLE Service](https://github.com/bjornspockeli/custom_ble_service_example)

* [Entendendo o que são Fixed Points, ex: "2Q30"](https://pt.scribd.com/document/98529714/Fixed-Point-Conversion)
	
### Aumentar a quantidade de Dados enviados em um Advertise Packet

- Crie uma nova variável do tipo "ble_advdata_manuf_data_t" chamada "manuf_data_response".
- Popule a variável "manuf_data_response" com os dados utilizados anteriormente (CompanyID, data[],.., se houver dúvidas siga o código "chg_adv_pck_moresize_complete" disponível em [Code](Codes/chg_adv_pck_moresize_complete).
- Crie uma nova variável do tipo "ble_advdata_t" chamada "advdata_response".
- Popule a variável "advdata_response" com o name_type "BLE_ADVDATA_NO_NAME".
- Popule a variável "advdata_response" com os novos dados específicos do fabricante (Manufacturer).
- Altere a linha de código 
	err_code = ble_advertising_init(&advdata, NULL, &options, on_adv_evt, NULL);
  para:
	err_code = ble_advertising_init(&advdata, advdata_response, &options, on_adv_evt, NULL);
***

### Segurança
	
- Ver [neste tutorial](https://devzone.nordicsemi.com/tutorials/b/bluetooth-low-energy/posts/ble-characteristics-a-beginners-tutorial) nos desafios do Step 2.H

## Erros

* Ao realizar o tutorial (2.) referente à compilação do projeto UART, aparece a seguinte mensagem de erro: "error:flash downloaded failed - could not load file..", mesmo após executar os comandos --eraseall e --program na linha de comando não resolveu, algumas pessoas disseram que executar o "eraseall" pelo nRFGO Studio resolveria o problema, mas acredito que a versão do SDK (15.0.0) que estava utilizando era muito recente e alguns packages ainda não estavam disponíveis, fiz o downgrade para (14.2.0) e funcionou corretamente.
* Ao realizar o tutorial (3.) pode-se perceber um erro comum, adicionar muitas informações no Advertising Packet pode estourar o limite de bytes. Este problema ocorreu com um desenvolvedor e uma possível solução foi tentar diminuir o tamanho da informação, que ficou da seguinte forma: 
	Device name field: 8 bytes
	Flag field: Length (1), type (1), flag(1) = 3 bytes
	16-bit Service Class UUID: Length(1), type(1), UUID(2) = 4 bytes
	Manufacturer Specific: Lenght(1), type(1), company ID(2), data(10) = 14 bytes.
este foi um problema notado na [resposta](https://devzone.nordicsemi.com/f/nordic-q-a/7066/setting-tx_power_level/24976#24976) de MartinBL marcada como solução.
* Ao tentar alterar o valor da Caracteristica Device Name, ela não alterava. A solução encontrada foi na linha de inicialização do valor máximo do tamanho do valor da caracteristica "attr_char_value.max_len".
	Este valor estava com uma constante, por exemplo:
		attr_char_value.max_len = 20;
	Quando alterado para para o tamanho da struct, o erro foi corrigido, ficando assim.
		attr_char_value.max_len = sizeof(ble_wcs_dev_name_t);
