
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

#define BKGD_PIN PA0
#define RESET_PIN PA1

#define HIGH true
#define LOW false

typedef bool pinState;


void serial_init(void);
int serial_send( char data, FILE *stream);
uint8_t serial_receive(void);
void waitEnter(void);

void set_RESET_low(void);
void set_RESET_high(void);
void set_BKGD_low(void);
void set_BKGD_high(void);
void configure_BKGD_input(void);
void configure_BKGD_output(void);
pinState get_pin_state(uint8_t pin);

void enter_background(void);
void Sync_Command(void);

static FILE out_stream = FDEV_SETUP_STREAM(serial_send, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    DDRA = (1<<BKGD_PIN) | (1<<RESET_PIN);
    PORTA = 0;
    set_RESET_low();
    set_BKGD_low();

    serial_init();
    stdout = &out_stream;

    enter_background();
    printf("\n\rPres enter to generate sync");
    waitEnter();
    Sync_Command();

    return 0;
}

void Sync_Command(void)
{
  configure_BKGD_output();
  set_BKGD_low();
  _delay_us(50); //should take at least 128 BDM cycles of target MCU
  set_BKGD_high();
  configure_BKGD_input();
  //wait for falling slope
  uint16_t wait_counter = 0;
  while(get_pin_state(BKGD_PIN) == HIGH)
  {
    wait_counter++;
    _delay_us(1);
    if(wait_counter > 1000)
    {
        printf("\n\rSync timeout. BKGD Pin state not changed. Target not responding.\n\rPress reset button.");
        while(1){}
    }
  }
  uint16_t sync_time = 0;
  while(get_pin_state(BKGD_PIN)== LOW)
  {
    sync_time++;
    _delay_us(1);
    if(sync_time > 1000)
    {
        printf("\n\rSync timeout. Press reset button.");
        while(1){}
    }
  }
  printf("\nSync time: %d us", sync_time);
}

void enter_background(void)
{
    set_RESET_low();
    printf("\n\rReset supply and press enter");
    waitEnter();
    set_RESET_high();
    _delay_us(10);
    set_BKGD_high();
    configure_BKGD_input();
    printf("\n\rTarget should be in background mode");
}

void waitEnter(void)
{
    while(1)
    {
        char c = serial_receive();
        if(c == '\r')
        {
            break;
        }
    }
}

pinState get_pin_state(uint8_t pin)
{
    uint8_t state = PINA & (1 << pin);
    if(state)
    {
        return HIGH;
    }
    else
    {
        return LOW;
    }
}

void set_RESET_low(void)
{
    PORTA &= ~(1 << RESET_PIN);
}

void set_RESET_high(void)
{
    PORTA |= (1 << RESET_PIN);
}

void set_BKGD_low(void)
{
    PORTA &= ~(1 << BKGD_PIN);
}
void set_BKGD_high(void)
{
    PORTA |= (1 << BKGD_PIN);
}

void configure_BKGD_input(void)
{
      DDRA &= ~(1<<BKGD_PIN);
}

void configure_BKGD_output(void)
{
      DDRA |= (1<<BKGD_PIN);
}

void serial_init(void)
{
    //Arduino Atmega2560 uses PE0(RX0) i PE1(TX0)
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // set character data size to 8
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    //9600, crystal 16Mhz UBRR = 16000000/(16*baudrate)-1
    UBRR0 = 103;
}

uint8_t serial_receive(void)
{
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

int serial_send( char data, FILE *stream)
{
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
    return 0;
}