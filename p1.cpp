/*
Autores: 
	Alberto Sánchez Amo 		NIA: 152871
	Luis Ángel Rodríguez Viñal 	NIA: 154186
	Alejandro Méndez Díaz		NIA: 163825
Asignatura: Estructuras de Datos y Algoritmos
Profesor: Diego Saez
Fecha: 10-7-2014
*/

//--Librerías--//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "utils.h"

//--Funciones auxiliares: utilizadas para trabajar con los vectores--//
//Devuelve el tamaño del vector mas grande de los dos
inline int getSize(const int & size1,const int & size2){ return (size1 > size2) ? size1 : size2; }
//Dado un string (e.g v1, devuelve el puntero que contiene ese vector)
vector* selectVector(vector** vec,char* string){ return vec[atoi(strtok (string, "v"))-1];}

//Convierte un vector a una string para poder representarlo por pantalla
char* vectorToString(vector* v,char* string)
{
	char* aux = (char *) malloc(sizeof(float) * v->size * 4 * sizeof(char));

   	strcat(string,"[");
    for(unsigned int i = 0; i<v->size; i++){
    	if(i!=v->size-1)
    		sprintf(aux,"%f,",v->data[i]);
    	else
    		sprintf(aux,"%f]",v->data[i]);
    	strcat(string,aux);
    }

    free(aux);
    return string;

}

//-------------------- Métodos Básicos --------------------//

//Construcción de un vector (reserva de memoria)
vector* create_vector(int n, float* data){

	vector * vec;
	vec = (vector *) malloc(sizeof(vector));
	vec->data = (float*) malloc(n * sizeof(float));
	vec->size = n;
	memcpy( vec->data , data, n*sizeof(float));

	return vec;
}

//Destrucción de un vector (liberación de memoria)
void destroy_vector(vector* v){

	if(v){
		free(v->data);
		free(v);
	}
}

//Imprime por pantalla el vector
void print(vector* v)
{
   	printf("[");
    for(unsigned int i = 0; i<v->size; i++){
    	if(i!=v->size-1)
    		printf("%f,", v->data[i]);
    	else
    		printf("%f]\n", v->data[i]);
    }
}

//-------------------- Métodos Intermedios --------------------//

//Producto escalar, simplemente multiplica cada elemento y retorna la suma
double dot(vector* v1, vector* v2){

	double result = 0.0f;
	for(unsigned int i = 0; i < v1->size; i++){
		result = result + v1->data[i]*v2->data[i];
	}
	return result;
}

//Devuelve la norma de un vector
float norm(vector* v){

	float result = 0.0f;
	for(unsigned int i = 0; i < v->size; i++){
		result = result + (v->data[i]*v->data[i]);
	}
	return sqrt(result);
}

//Normaliza un vector, es decir, lo convierte en unitario
void normalize(vector* v){

	float norma = norm(v);

	for(unsigned int i = 0; i < v->size; i++){
		v->data[i] = v->data[i]/norma;
	}

}

//-------------------- Métodos Avanzados --------------------//

//Cálculo de la distancia entre dos vectores
float distance(vector* v1, vector* v2){

	float len = getSize(v1->size,v2->size);
	float result = 0.0f;
	float aux = 0.0f;

	for(unsigned int i = 0; i < len; i++){
		if(v1->size < i+1)
			aux = v2->data[i];
		if(v2->size < i+1)
			aux = v1->data[i];
		else
			aux = v1->data[i] - v2->data[i];

		result = result + (aux*aux);
	}

	return sqrt(result);
}

//Suma de dos vectores, devuelve un puntero ya que es un nuevo vector el resultado de la suma
vector* add(vector* v1, vector* v2){

	float len = getSize(v1->size,v2->size);
	vector * add = (vector *) malloc(sizeof(vector));
	add->data = (float *) malloc(len * sizeof(float));
	add->size = len;

	for(unsigned int i = 0; i < len; i++){
		if(v1->size < i+1)
			add->data[i] = v2->data[i];
		if(v2->size < i+1)
			add->data[i] = v1->data[i];
		else
			add->data[i] = v1->data[i] + v2->data[i];

	}
	return add;
}

//Resta de dos vectores, devuelve un puntero como resultado de la operacion
vector* sub(vector* v1, vector* v2){

	float len = getSize(v1->size,v2->size);
	vector * sub = (vector *) malloc(sizeof(vector));
	sub->data = (float *) malloc(len * sizeof(float));
	sub->size = len;

	for(unsigned int i = 0; i < len; i++){
		if(v1->size < i+1)
			sub->data[i] = v2->data[i];
		if(v2->size < i+1)
			sub->data[i] = v1->data[i];
		else
			sub->data[i] = v1->data[i] - v2->data[i];

	}
	return sub;
}

//Incremento, incrementa el valor del vector dado otro vector
void incr(vector* source, vector* other){

	float len = getSize(source->size,other->size);

	for(unsigned int i = 0; i < len; i++){
		if(source->size < i+1){
			source->data = (float*) realloc(source->data, sizeof(source->data) + sizeof(float));
			source->data[i] = other->data[i];
		}
		if(other->size == source->size)
			source->data[i] = source->data[i] + other->data[i];
	}

}

//Decremento, decrece el valor de los componentes del vector dado otro vector
void decr(vector* source, vector* other){

	float len = getSize(source->size,other->size);

	for(unsigned int i = 0; i < len; i++){
		if(source->size < i+1){
			source->data = (float*) realloc(source->data, sizeof(source->data) + sizeof(float));
			source->data[i] = other->data[i];
		}
		if(other->size == source->size)
			source->data[i] = source->data[i] - other->data[i];
	}

}

//Función que lee el stdin y realiza las operaciones solicitadas
void readInput(){

	//Creamos un archivo auxiliar que guardara nuestros datos leidos
	edafile *ifile = (edafile*) malloc(sizeof(edafile));
	ifile->name = "EdaFile";

	char cadena[2000];

	fgets(cadena, sizeof cadena, stdin);
	ifile->size = atoi(cadena);
	ifile->vectors = (vector**)malloc(ifile->size *sizeof(vector*));

	//Estas lineas se encargan de leer los vectores y crear punteros y alamcenarlos en nuestro puntero de vectores
	for(unsigned int i = 0; i < ifile->size; i++){
		fgets(cadena, sizeof cadena , stdin);
		float *aux = (float*) malloc(20*sizeof(float));
		ifile->aux = strtok(cadena,  "[,]");
		int pdata = 0;
		
		while(ifile->aux != NULL){
			aux[pdata] = atof(ifile->aux);
			ifile->aux = strtok (NULL, "[,]\n");
			pdata++;
		}
		float* idata = (float *) malloc(pdata* sizeof(float));
		memcpy( idata , aux, pdata*sizeof(float));
		ifile->vectors[i] = create_vector(pdata,idata);
		free(aux);
		free(idata);
	}
	

	//Las siguientes lineas seran operaciones que se leen y se escriben.
	while(fgets(cadena, sizeof cadena , stdin) != NULL)
	{
			char* a = (char *) malloc(sizeof cadena * sizeof(char));
			char* b = (char *) malloc(sizeof cadena * sizeof(char));
			char* c = (char *) malloc(sizeof cadena * sizeof(char));
			char* vecname = (char *) calloc(200,sizeof(char));
			ifile->info = (char *)calloc(2000,sizeof(char));

			strtok(cadena, "\n");
			strcat(ifile->info,cadena);
			strcat(ifile->info,": ");
			
			//Dada la operacion que se lee, se ejecutan unas funciones u otras
			if(strchr(cadena,'+') != NULL){
				sscanf(cadena,"%s %s %s",a,b,c);
				vector * vec = add(selectVector(ifile->vectors,a),selectVector(ifile->vectors,c));
				strcat(ifile->info,vectorToString(vec,vecname));
				destroy_vector(vec);
			}
			if(strchr(cadena,'-') != NULL){
				sscanf(cadena,"%s %s %s",a,b,c);
				vector * vec = sub(selectVector(ifile->vectors,a),selectVector(ifile->vectors,c));
				strcat(ifile->info,vectorToString(vec,vecname));
				destroy_vector(vec);
			}
			if(strstr(cadena,"incr") != NULL){
				sscanf(cadena,"%s %s %s",a,b,c);
				incr(selectVector(ifile->vectors,b),selectVector(ifile->vectors,c));
				strcat(ifile->info,vectorToString(selectVector(ifile->vectors,b),vecname));
			
			}
			if(strstr(cadena,"decr") != NULL){
				sscanf(cadena,"%s %s %s",a,b,c);
				decr(selectVector(ifile->vectors,b),selectVector(ifile->vectors,c));
				strcat(ifile->info,vectorToString(selectVector(ifile->vectors,b),vecname));
			}
			if(strstr(cadena,"dot") != NULL){
				sscanf(cadena,"%s %s %s",a,b,c);
				double value = dot(selectVector(ifile->vectors,a),selectVector(ifile->vectors,c));
				sprintf(vecname, "%f", value);
				strcat(ifile->info,vecname);
			}
			if(strstr(cadena,"norm") != NULL){
				sscanf(cadena,"%s %s",a,b);
				if(strstr(cadena,"normalize") != NULL){
					normalize(selectVector(ifile->vectors,b));
					strcat(ifile->info,vectorToString(selectVector(ifile->vectors,b),vecname));
				}
				else{
					sprintf(vecname, "%f", norm(selectVector(ifile->vectors,b)));
					strcat(ifile->info,vecname);
				}
			}
			if(strstr(cadena,"distance") != NULL){
				sscanf(cadena,"%s %s %s",a,b,c);
				float value = distance(selectVector(ifile->vectors,b),selectVector(ifile->vectors,c));
				sprintf(vecname, "%f", value);
				strcat(ifile->info,vecname);
			}
			if(strstr(cadena,"print") != NULL){
				sscanf(cadena,"%s %s",a,b);
				//print(selectVector(ifile.vectors,b)); //Queda comentado ya que utilizamos vector to string para printearlo
				strcat(ifile->info,vectorToString(selectVector(ifile->vectors,b),vecname));
			}
			strcat(ifile->info,"\n");
			fputs(ifile->info,stdout);

			free(ifile->info);
			free(vecname);
			free(a);
			free(b);
			free(c);
	}
	
	//A partir de aqui destruimos todos los vectores creados
	//A la vez destruido el puntero que apunta al conjunto de vectores
	for(unsigned int x = 0; x < ifile->size; x++)
		destroy_vector(ifile->vectors[x]);

	free(ifile->vectors);
	free(ifile);
}

int main(){

	readInput();

	return 0;
}