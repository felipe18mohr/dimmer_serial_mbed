#include <mbed.h>

PwmOut dimmer(LED1);
Serial pc(USBTX, USBRX, 9600);

void charReceived();

volatile char c = '\0';
bool print_text = false;
float intensidade = 0.5;


int main() {

  pc.attach(&charReceived);
  while(1) {
    if (print_text) {
      if (c == '\0') pc.printf("Caracter invalido");
      else pc.printf("Intensidade: %d", 100*intensidade);
      print_text = false;
    }
  }
}

void charReceived() {
  c = pc.getc();
  print_text = true;
  
  if (c == '+' && intensidade <= 0.95) intensidade += 0.05;
  else if (c == '-' && intensidade >= 0.05) intensidade -= 0.05;
  else if (c == '*') intensidade = 1.0;
  else if (c == '/') intensidade = 0.0;
  else c = '\0';

  dimmer = intensidade;
  wait_ms(100);
  
}
