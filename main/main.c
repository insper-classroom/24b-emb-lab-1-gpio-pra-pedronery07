/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

int main() {
    stdio_init_all();
    const int LED_PIN = 18;
    const int LED2_PIN = 17;
    const int BTN_PIN = 5;
    const int BTN2_PIN = 20;
    int LED_STATE = 0;
    int LED2_STATE = 0;
    const int PIN1 = 10;
    const int PIN2 = 11;
    const int PIN3 = 12;
    const int PIN4 = 13;

    // LED
    gpio_init(LED_PIN);
    gpio_init(LED2_PIN);
    gpio_init(BTN_PIN);
    gpio_init(BTN2_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(LED2_PIN, GPIO_OUT);

    // Botão
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);
    gpio_set_dir(BTN2_PIN, GPIO_IN);
    gpio_pull_up(BTN2_PIN);
    
    // Motor
    gpio_init(PIN1);
    gpio_init(PIN2);
    gpio_init(PIN3);
    gpio_init(PIN4);
    gpio_set_dir(PIN1, GPIO_OUT);
    gpio_set_dir(PIN2, GPIO_OUT);
    gpio_set_dir(PIN3, GPIO_OUT);
    gpio_set_dir(PIN4, GPIO_OUT);

    while (true) {
        if (!gpio_get(BTN_PIN)) { 
            printf("Botao apertado!\n");
            // Acende e apaga LED pelo botão
            gpio_put(LED_PIN, !LED_STATE);
            LED_STATE = !LED_STATE;
            // Funcionamento do motor
            for (int i = 0; i <= 512; i++) {
                gpio_put(LED_PIN, 1);
                LED_STATE = 1;
                gpio_put(PIN1, 1);
                sleep_ms(10);
                gpio_put(PIN1, 0);
                gpio_put(PIN2, 1);
                sleep_ms(10);
                gpio_put(PIN2, 0);
                gpio_put(PIN3, 1);
                sleep_ms(10);
                gpio_put(PIN3, 0);
                gpio_put(PIN4, 1);
                sleep_ms(10);
                gpio_put(PIN4, 0);
                if (!gpio_get(BTN_PIN)) {
                    sleep_ms(50);
                    gpio_put(LED_PIN, 0);
                    LED_STATE = 0;
                    while (true) {
                        if (!gpio_get(BTN_PIN)) {
                            break;
                        }
                    }
                }
            }
            while (!gpio_get(BTN_PIN)) {
            };
        }
        else if (!gpio_get(BTN2_PIN)) {
            gpio_put(LED2_PIN, !LED2_STATE);
            LED2_STATE = !LED2_STATE;
            for (int i = 0; i <= 512; i++) {
                gpio_put(LED2_PIN, 1);
                LED2_STATE = 1;
                gpio_put(PIN4, 1);
                sleep_ms(10);
                gpio_put(PIN4, 0);
                gpio_put(PIN3, 1);
                sleep_ms(10);
                gpio_put(PIN3, 0);
                gpio_put(PIN2, 1);
                sleep_ms(10);
                gpio_put(PIN2, 0);
                gpio_put(PIN1, 1);
                sleep_ms(10);
                gpio_put(PIN1, 0);
                if (!gpio_get(BTN2_PIN)) {
                    sleep_ms(50);
                    gpio_put(LED2_PIN, 0);
                    LED2_STATE = 0;
                    while (true) {
                        if (!gpio_get(BTN2_PIN)) {
                            break;
                        }
                    }
                }
            }
            while (!gpio_get(BTN2_PIN)) {
            };
        }
        gpio_put(LED_PIN, 0);
        gpio_put(LED2_PIN, 0);
    }
}
