#include "EstruturasDeDados.h"

extern unsigned char* imageGray;
extern int j;

tNoArvore* alocaNo(int niv, tPonto pon, int h, 
	int w, int c, float e){

	tNoArvore* novo = (tNoArvore*) malloc(sizeof(tNoArvore));


	if(novo != NULL){
		novo->q.h = h;
		novo->q.w = w;
		novo->q.nivel = niv; 
		novo->q.pBase = pon;
		novo->q.cor = c;
		novo->q.erro = e;
		}

	return novo;
}




void geraQuadrantes(tNoArvore **r, int height, tPonto base,
	int nivel, int count ){

	if(nivel<=log2(height)){

		//Calcula o ponto base
		tPonto pon;
		switch(count){
			case 0: 
				pon.x = base.x;
				pon.y = base.y;
				break;
			case 1: 
				pon.x = (height/pow(2,nivel)) + base.x;
				pon.y = base.y;
				break;
			case 2: 
				pon.x = (height/pow(2,nivel)) + base.x;
				pon.y = (height/pow(2,nivel)) + base.y;
				break;
			case 3: 
				pon.x = base.x;
				pon.y = (height/pow(2,nivel)) + base.y;
				break;
		}
		
		//Aloca o nó sem cor e sem o valor do erro
		(*r) = alocaNo(nivel, pon, ((height)/pow(2,nivel)), 
		((height)/pow(2,nivel)), 255, 0);

		//Chama recursivamente, criando 4 filhos
		int i;
		for(i=0 ; i<4 ; i++){			
			geraQuadrantes( &((*r)->filho[i]), height, (*r)->q.pBase,
				nivel+1, i );
		}
	}

	//Se o nó é folha
	if(nivel==log2(height)){

		//Gerando o índice correto para cada posição
		int index = (*r)->q.pBase.x + ((*r)->q.pBase.y*height);
		//Garantir que o index não vai ser um número acima do possível
		if(index>pow(height,2))
			index = 0;
		(*r)->q.cor = imageGray[index];
	}

}



int media(int input[]){
	int output = (input[0]+input[1]+input[2]+input[3]) / 4;
	return output;
}

void cor_erro(tNoArvore **r){


	
	//Se não for folha
	if((*r)->filho[0] != NULL){

		int i;
		for(i=0 ; i<4 ; i++)	
			cor_erro(&((*r)->filho[i]));


		//Calcula a cor média caso não seja folha
		int cores[4], l;
		for(l=0 ; l<4 ; l++)
			cores[l] = (*r)->filho[l]->q.cor;
		(*r)->q.cor = media(cores);

		//Calcula o erro médio caso não seja folha
		float erros[4];
		for(l=0 ; l<4 ; l++)
			erros[l] = fabs( (float)cores[l]-(float)(*r)->q.cor );
		(*r)->q.erro = (erros[0]+erros[1]+erros[2]+erros[3]) / 4.0;
		(*r)->q.erro = (*r)->q.erro / (*r)->q.cor; //Transformando em %
	}

}
