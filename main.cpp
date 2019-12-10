/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: link
 *
 * Created on 2 de junio de 2018, 19:38
 */

#include <cstdlib>
#include <stdio.h>
#include <string.h>

#define N 9

using namespace std;

/*
 * 
 */

void iniciarTablero(int t[N][N]);
void leerTablero(int t[N][N], char* fichero);
void solucionarTablero(int t[N][N], bool* sol, int nivel);
int posicionValida(int t[N][N], int fil, int col, int valor);
void imprimirTablero(int t[N][N]);

int main(int argc, char** argv) {
    int tablero[N][N]; // Tablero del juego
    bool solucion = false;
    int nivel = 0;
    
    iniciarTablero(tablero);
    leerTablero(tablero, "tablero.txt");
    
    printf("Sudoku a resolver\n");
    imprimirTablero(tablero);
    
    solucionarTablero(tablero, &solucion, nivel);
    
    if(solucion==true){
        printf("Solucion:\n");
        imprimirTablero(tablero);
    }else{
        printf("Sin solucion");
    }
}

void iniciarTablero(int t[N][N]){
    for(int i=0; i<N;i++){
        for(int j=0; j<N; j++){
            t[i][j]=0;
        }
    }
}

//Función para leer el fichero
void leerTablero(int t[N][N], char* fichero){
    char linea[50];
    FILE *f = fopen(fichero,"r");
    if(f!=NULL){
        //printf("Fichero encotrado\n");
        //leemos linea a linea
        // com maximo N Lineas
        for(int i=0;i<N;i++){
            //leemos la linea
            fscanf(f,"%s", linea);
            //Extraemos los tokens
            char *token;
            token = strtok(linea, ";");
            int j =0; // Fijamos la columna
            // Navegamos por el resto de los tokens
            while( token != NULL ) {
                //printf( " %s\n", token ); 
                t[i][j]=atoi(token);
                j++;
                token = strtok(NULL, ";");
            }
        }
        
    }else{
        printf("Error, fichero %s no encotrado\n",fichero);
    }
    
    
}

// imprime el tablero
void imprimirTablero(int t[N][N]){
    int i=0,j=0;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d ",t[i][j]);
        }
        printf("\n");
    }
}

// Busca la solucion del tablero
void solucionarTablero(int t[N][N], bool* sol, int nivel){
    bool llena = true; // si está llena
    int i,j,k;
     // buscamos si hay casilla vacía
    for(i=0;i<N && llena; i++){
        for(j=0;j<N && llena; j++){
            if(t[i][j]==0)
                llena= false;
        }
    }
    // si está llena
    if(llena==true){
        *sol=true;
    }else{
        // Como hemos salido del for, retrocemos la variables de fila y columna
        i--; 
        j--;
        // buscamos la solución para los N posibles valores
        for(k=1;k<=N && (*sol==false);k++){
            if(posicionValida(t,i,j,k)){
                t[i][j]=k;
                printf("\nFila: %d Columna: %d Valor: %d Nivel: %d\n", i,j,k, nivel);
                solucionarTablero(t,sol, nivel+1);
                if(*sol==false){
                    t[i][j]=0;
                }
            }
        }
    }
}

int posicionValida(int t[N][N], int fil, int col, int valor){
    bool val=true;
    int i=0,j=0;
    int N3 = (int)N/3;
    
    //comprobamos si esta en la fila fil, recorremos la columnas
    for(i=0;i<N && val;i++) {
        if(t[fil][i]==valor){ // esta localizado
            return false;
        }
    }
    
    //comprobamos si esta en la columna col, recorremos la fila
    for(i=0;i<N && val;i++) {
        if(t[i][col]==valor){ // esta localizado
            return false;
        }
    }
    
    // no sería necesario porque saltaría con los return, pero lo dejo ahora.
    // construimos el cuadrante
    int f_ini=(int)(fil/N3)*N3;
    int f_fin = f_ini+(N3-1);
    int c_ini=(int)(col/N3)*N3;
    int c_fin = c_ini+(N3-1);
    for(i=f_ini;i<=f_fin && val; i++){
        for(j=c_ini;j<=c_fin && val; j++){
            if(t[i][j]==valor){
                return false;
            }
        }
    }
    return val;
}