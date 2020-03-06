deps_config := \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/app_update/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/aws_iot/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/console/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/esp8266/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/esp_http_client/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/esp_http_server/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/freertos/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/libsodium/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/log/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/lwip/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/mdns/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/mqtt/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/newlib/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/pthread/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/spiffs/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/ssl/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/tcpip_adapter/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/util/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/vfs/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/wifi_provisioning/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/wpa_supplicant/Kconfig \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/bootloader/Kconfig.projbuild \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/esptool_py/Kconfig.projbuild \
	/home/ununtur6/workspace/LIU_test/esp8266_learn/softap_prov/main/Kconfig.projbuild \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/components/partition_table/Kconfig.projbuild \
	/home/ununtur6/workspace/ESP8266/ESP8266_RTOS_SDK/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
