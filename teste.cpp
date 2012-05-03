#include "teste.inl"

template<typename FP>
void Teste<FP>::bla2(FP x){
  printf("bla2\n");
}

void Instancie(){
  Teste<double> ble;
  ble.bla(10.0);
  ble.bla2(20.0);
}

int main(){
  Instancie();
  return 0;
}
