deps_config := \
	/home/timothy/esp/esp-idf/components/app_trace/Kconfig \
	/home/timothy/esp/esp-idf/components/aws_iot/Kconfig \
	/home/timothy/esp/esp-idf/components/bt/Kconfig \
	/home/timothy/esp/esp-idf/components/driver/Kconfig \
	/home/timothy/esp/esp-idf/components/esp32/Kconfig \
	/home/timothy/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/timothy/esp/esp-idf/components/esp_event/Kconfig \
	/home/timothy/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/timothy/esp/esp-idf/components/esp_http_server/Kconfig \
	/home/timothy/esp/esp-idf/components/esp_https_ota/Kconfig \
	/home/timothy/esp/esp-idf/components/ethernet/Kconfig \
	/home/timothy/esp/esp-idf/components/fatfs/Kconfig \
	/home/timothy/esp/esp-idf/components/freemodbus/Kconfig \
	/home/timothy/esp/esp-idf/components/freertos/Kconfig \
	/home/timothy/esp/esp-idf/components/heap/Kconfig \
	/home/timothy/esp/esp-idf/components/libsodium/Kconfig \
	/home/timothy/esp/esp-idf/components/log/Kconfig \
	/home/timothy/esp/esp-idf/components/lwip/Kconfig \
	/home/timothy/esp/esp-idf/components/mbedtls/Kconfig \
	/home/timothy/esp/esp-idf/components/mdns/Kconfig \
	/home/timothy/esp/esp-idf/components/mqtt/Kconfig \
	/home/timothy/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/timothy/esp/esp-idf/components/openssl/Kconfig \
	/home/timothy/esp/esp-idf/components/pthread/Kconfig \
	/home/timothy/esp/esp-idf/components/spi_flash/Kconfig \
	/home/timothy/esp/esp-idf/components/spiffs/Kconfig \
	/home/timothy/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/timothy/esp/esp-idf/components/unity/Kconfig \
	/home/timothy/esp/esp-idf/components/vfs/Kconfig \
	/home/timothy/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/timothy/esp/esp-idf/components/app_update/Kconfig.projbuild \
	/home/timothy/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/timothy/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/timothy/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/timothy/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
