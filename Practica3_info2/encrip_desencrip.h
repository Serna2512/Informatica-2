#ifndef ENCRIP_DESENCRIP_H
#define ENCRIP_DESENCRIP_H

char XOR(unsigned char entrada, unsigned char clave);
void x_or(unsigned char *ptr, unsigned int l1, unsigned char *clave);
void rotacion(unsigned char *ptr, unsigned int l1, unsigned short int nRot);
void encriptamiento(unsigned char *ptr, unsigned int l1, unsigned char *clave, unsigned short int nRot, bool opc);
unsigned char rotacion_izquierda(unsigned char input, unsigned short int nRot);

#endif // ENCRIP_DESENCRIP_H
