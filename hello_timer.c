#include <stdio.h>
#include "pico/stdlib.h"

const uint GREEN_PIN = 11;
const uint YELLOW_PIN = 12;
const uint RED_PIN = 13;

volatile uint current_color = 'R';

void turn_on_red() {
    gpio_put(RED_PIN, 1);
    gpio_put(YELLOW_PIN, 0);
    gpio_put(GREEN_PIN, 0);
}

void turn_on_yellow() {
    gpio_put(RED_PIN, 0);
    gpio_put(YELLOW_PIN, 1);
    gpio_put(GREEN_PIN, 0);
}

void turn_on_green() {
    gpio_put(RED_PIN, 0);
    gpio_put(YELLOW_PIN, 0);
    gpio_put(GREEN_PIN, 1);
}

void initialize_gpio() {
    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_init(YELLOW_PIN);
    gpio_set_dir(YELLOW_PIN, GPIO_OUT);
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);

    // Inicializa o semáforo com a luz vermelha acesa
    turn_on_red();
    // Inicializa a variável de estado com a próximo LED na sequência
    current_color = 'Y';
}

// Função de call-back do temporizador
bool repeating_timer_callback(__unused struct repeating_timer *t)  {
    switch (current_color) {
        case 'R':
            turn_on_red();
            current_color = 'Y';
            break;
        case 'Y':
           turn_on_yellow();
            current_color = 'G';
            break;
        default:
            turn_on_green();    
            current_color = 'R';
            break;
    }

    return true;
}

int main() {
    stdio_init_all();
    initialize_gpio();

    // atraso de 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (1) {
        printf("Estado dos pinos atual: R=%d, Y=%d, G=%d\n", gpio_get(RED_PIN), gpio_get(YELLOW_PIN), gpio_get(GREEN_PIN));
        sleep_ms(1000);
    }

    return 0;
}
