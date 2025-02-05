**Autor:** Izaías Araújo  
**Atividade:** EMBARCATECH_AS_U4C5O1234E_29_01_2025

## Descrição

Este projeto implementa um sistema de temporização para o acionamento de LEDs utilizando um microcontrolador Raspberry Pi Pico W. O sistema é ativado a partir do clique em um botão (pushbutton).

## Componentes Utilizados

1. Microcontrolador Raspberry Pi Pico W
2. 03 LEDs (azul, vermelho e verde)
3. 03 Resistores de 330 Ω
4. Botão (Pushbutton)

## Funcionamento

1. **Inicialização dos GPIOs:**
   - Os pinos GPIO para os LEDs (azul, vermelho e verde) são configurados como saída.
   - O pino GPIO para o botão é configurado como entrada e resistor de pull-up interno.

2. **Callback do Botão:**
   - Quando o botão é pressionado, todos os LEDs são ligados.
   - Um ciclo de desligamento é iniciado, onde os LEDs são desligados um a um em intervalos de 3 segundos.

3. **Callback do Temporizador:**
   - A função `turn_off_callback` é chamada a cada 3 segundos para desligar um LED por vez na sequência: azul, vermelho e verde.
   - Após desligar todos os LEDs, a flag `turn_off_in_process` é limpa para indicar que o ciclo foi concluído.

4. **Loop Principal:**
   - O loop principal verifica se o botão foi pressionado e, se sim, inicia o ciclo de desligamento dos LEDs.


## Como Executar

1. Conecte os LEDs e o botão aos pinos GPIO do Raspberry Pi Pico W conforme especificado no código.
2. Compile e carregue o código no Raspberry Pi Pico W.
3. Pressione o botão para iniciar o ciclo de acionamento dos LEDs.

## Observações

- Certifique-se de que os resistores de 330 Ω estão conectados em série com os LEDs para limitar a corrente.
- O código utiliza a biblioteca `pico/stdlib.h` para manipulação dos GPIOs e temporizadores.
