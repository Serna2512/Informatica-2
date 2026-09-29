char XOR(unsigned char entrada, unsigned char clave){
    return entrada^clave;
}


unsigned char rotacion_izquierda(unsigned char input, unsigned short int nRot){
    return (input << nRot) | (input >> (8-nRot));

}

//input: 80: 01010000
//nRot: 2 entonces: 01000000

//nRot: 6: 00000110
//input >> 6: 00000001

//salida: 01000000
//        00000001
//        01000001

