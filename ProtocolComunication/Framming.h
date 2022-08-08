//
// Created by Marcone on 15/08/2019.
//

#ifndef PROTOCOLCOMUNICATION_FRAMMING_H
#define PROTOCOLCOMUNICATION_FRAMMING_H

#include <cstdint>
#include "Serial.h"

class Framming {
    public:
        Framming(Serial & dev, int bytes_min, int bytes_max);
        ~Framming();

        // envia o quadro apontado por buffer
        // o tamanho do quadro é dado por bytes
        void envia(char * buffer, int bytes);

        // espera e recebe um quadro, armazenando-o em buffer
        // retorna o tamanho do quadro recebido
        int recebe(char * buffer);

    private:
        int min_bytes, max_bytes; // tamanhos mínimo e máximo de quadro
        Serial & porta;
        char buffer[4096]; // quadros no maximo de 4 kB (hardcoded)

        enum Estados {Ocioso, RX, ESC};

        // bytes recebidos pela MEF até o momento
        int n_bytes;

        // estado atual da MEF
        Estados estado;

        // aqui se implementa a máquina de estados de recepção
        // retorna true se reconheceu um quadro completo
        bool handle(char byte);

};

#endif //PROTOCOLCOMUNICATION_FRAMMING_H
