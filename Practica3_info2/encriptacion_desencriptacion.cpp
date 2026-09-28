char XOR(unsigned char entrada, unsigned char clave){
    return entrada^clave;
}


/*
void x_or(unsigned char input, unsigned int l1, unsigned char *clave){
    for (unsigned int i=0; i<l1; i++) {
        input[i] = input[i]^clave[i];
    }
}

*/

unsigned char rotacion_izquierda(unsigned char input, unsigned short int nRot){
    return (input << nRot) | (input >> (8-nRot));

}

//input: 7: 00000111
//nRot: 2 entonces: 00011100

//nRot: 6: 00000110
//input >> 6: 00000000

//salida: 00011100

/*

void encriptamiento(unsigned char input, unsigned int l1, unsigned char *clave, unsigned short int nRot, bool opc){
    if(opc){
        rotacion(input, l1, nRot);
        x_or(input, l1, clave);
    }else{
        x_or(input, l1, clave);
        rotacion(input, l1, 8-nRot);
    }
}
*/
