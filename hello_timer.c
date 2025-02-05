#include <stdio.h>
#include "pico/stdlib.h"

const uint BLUE_PIN = 11;
const uint RED_PIN = 12;
const uint GREEN_PIN = 13;

const uint BUTTON_A_PIN = 5;

volatile uint current_color = 'B'; // Qual cor será desativada nesse momento
volatile bool button_pressed = false; // Flag para indicar que o botão foi pressionado
volatile bool turn_off_in_process = false;  // Flag para indicar se o ciclo de desligamento está em andamento

void initialize_gpio() {
    // Inicializa os pinos GPIO para os LEDs
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    
    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
    
    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    
    // Inicializa o pino GPIO para o botão
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
}

int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    // Executa o ciclo de desligamento: Blue, depois Red, depois Green
    // e finalmente limpa a flag para indicar que o ciclo foi concluído.
    printf("Current color: %c\n", current_color);
    switch (current_color) {

        case 'B':
            printf("Desligando o LED azul\n");
            gpio_put(BLUE_PIN, 0);  
            current_color = 'R';
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            break;
        case 'R':
            printf("Desligando o LED vermelho\n");
            gpio_put(RED_PIN, 0);   
            current_color = 'G';
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            break;
        case 'G':
            printf("Desligando o LED verde\n");
            gpio_put(GREEN_PIN, 0);   
            current_color = 'B';
            turn_off_in_process = false;  // Ciclo completo, limpa a flag
            break;
        default:
            break;
    }

    // Retorna 0 para indicar que o alarme foi tratado com sucesso
    // e não precisa ser reagendado.
    return 0;
}

void button_callback(uint gpio, uint32_t events) {
    // Inicia um novo ciclo apenas se não houver outro em andamento.
    if (!turn_off_in_process) {
        button_pressed = true;
        turn_off_in_process = true;   // Marca que o ciclo está em andamento

        // Liga todos os LEDs.
        gpio_put(RED_PIN, 1);
        gpio_put(BLUE_PIN, 1);
        gpio_put(GREEN_PIN, 1);

        // Agenda o ciclo de desligamento.
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();
    initialize_gpio();

    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (1) {
        if (button_pressed) {
            button_pressed = false;
        }
        sleep_ms(100); // Atraso para debounce
    }
    return 0;
}
