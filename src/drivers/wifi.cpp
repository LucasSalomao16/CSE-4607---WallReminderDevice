#include "wifi.h"
#include <cstdio>
#include <pico/cyw43_arch.h>
#include <lwip/netif.h>
#include <lwip/ip4_addr.h>
#include "wifi_secrets.h"

bool connectWiFi(const char* ssid, const char* password) {
    // Enable station mode (connecting to an access point)
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000)){
        printf("Failed to connect to Wifi, err %d\n", cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000));
        return false;
    }
        printf("Connected to Wifi\n");
    
    // Getting the IP address
    if(netif_default == nullptr){
        printf("Failed to get default network interface\n");
        return false;
    }
    printf("IP Address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));
    return true;
}

