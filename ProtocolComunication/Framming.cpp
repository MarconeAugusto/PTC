//
// Created by Marcone on 15/08/2019.
//

#include "Framming.h"

Framming::Framming(Serial &dev, int bytes_min, int bytes_max) {
    porta = dev;
    min_bytes = bytes_min;
    max_bytes = bytes_max;
    n_bytes = 0;
    estado = Ocioso;
}

Framming::~Framming() { }

void Framming::envia(char *buffer, int bytes) {

}

int Framming::recebe(char *buffer){
    if (estado != Ocioso){
        throw -2;
    }
    while (true){
        uint8_t octeto;
        if(porta.read(char*)&octeto, 1,true)!= 1){
            throw -3;
        }
        if(handle(octeto))
    }
    return 0;
}

bool Framming::handle(char byte) {
    switch (estado) {
        case Ocioso: // estado Ocioso
            if(byte == '7E') {
                n_bytes = 0;
                estado = RX; // muda para RX
            }
            break;
        case RX: // estado RX
            if((byte == '7E') && (n_bytes > min_bytes)){
                estado = Ocioso;
                return true;
            }
            if((byte != '7E' && (byte != '7D'))){
                n_bytes++;
            }
            if((byte == '7E')&& (n_bytes == min_bytes)) {
                estado = RX; // muda para RX
            }
            if((byte == '7D')){
                estado = ESC; // muda para ESC
            }
            if(n_bytes >= max_bytes){
                estado = Ocioso;
                return false;
            }
            break;
        case ESC: // estado ESC
            if((byte != '7E') || (byte != '7D')){
                // fazer a operação xor
                byte = (byte xor 0x20);
                n_bytes++;
            }else{
                estado = Ocioso; // muda para Ocioso
                return false;
            }

            break;
    }
}
