# Semáforo 

# Documentação do Código

**Autor:** Izaías Araújo  
**Atividade:** EMBARCATECH_AS_U4C5O1234E_29_01_2025

## Descrição

Este código implementa um semáforo simples utilizando um microcontrolador Raspberry Pi Pico W. O semáforo possui três LEDs representando as cores verde, amarelo e vermelho. O código alterna entre essas cores em intervalos de tempo definidos.

## Funcionalidades

### Constantes e Variáveis

- `GREEN_PIN`, `YELLOW_PIN`, `RED_PIN`: Constantes que definem os pinos GPIO para os LEDs verde, amarelo e vermelho, respectivamente.
- `current_color`: Variável que armazena a cor atual do semáforo.

### Funções

#### `turn_on_red()`

Acende o LED vermelho e apaga os LEDs amarelo e verde.

#### `turn_on_yellow()`

Acende o LED amarelo e apaga os LEDs vermelho e verde.

#### `turn_on_green()`

Acende o LED verde e apaga os LEDs vermelho e amarelo.

#### `initialize_gpio()`

Inicializa os pinos GPIO dos LEDs e acende o LED vermelho como estado inicial do semáforo.

#### `repeating_timer_callback(struct repeating_timer *t)`

Função de callback do temporizador que alterna a cor do semáforo a cada intervalo de tempo. A sequência de cores é vermelho -> amarelo -> verde -> vermelho.

### Função Principal

#### `int main()`

1. Inicializa a comunicação padrão de entrada e saída.
2. Chama a função `initialize_gpio()` para configurar os pinos GPIO.
3. Configura um temporizador que chama a função `repeating_timer_callback` a cada 3 segundos.
4. Em um loop infinito, imprime o estado atual dos pinos dos LEDs a cada segundo.

## Fluxo de Execução

1. O semáforo começa com o LED vermelho aceso.
2. A cada 3 segundos, a cor do semáforo muda na sequência: vermelho -> amarelo -> verde -> vermelho.
3. O estado dos pinos dos LEDs é impresso no console a cada segundo.

