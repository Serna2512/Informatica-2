#ifndef ENCRIP_DESENCRIP_H
#define ENCRIP_DESENCRIP_H

char XOR(unsigned char entrada, unsigned char clave);
unsigned char rotacion_izquierda(unsigned char input, unsigned short int nRot);
unsigned char rotacion_derecha(unsigned char input, unsigned short int nRot);
unsigned char* encript(const char* entrada, unsigned short int nRota);

#endif // ENCRIP_DESENCRIP_H
