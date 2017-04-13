#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#if defined (__APPLE__) || defined(MACOSX)
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "EstruturasDeDados.h"
#include "winGL.h"
#include "quadtree.h"
		
unsigned char* 	imageGray = NULL;	// image file
int 			iHeight, 
				iWidth;

tNoArvore* 		raiz = NULL;

bool desenha = false;
bool option = true;
int j, level=1;
float errMin=0;

// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaQuadtree(tNoArvore *r) {

	//printf("Aqui eu vou desenhar a quadtree\n");
	
	// rotina que deve ser implementada para visualizacao da quadtree
	// utilize a rotina desenhaQuadrante(p0, p1, cor)
	// fornecendo os pontos inicial e final do quadrante e a sua cor
	// funcao do valor do pixel ou da regiao que voce quer desenhar

	

	//Condição por nível da árvore
	if(option){

		tNoArvore* Condition = r;
		int lCount;
		for(lCount=1 ; lCount<level ; lCount++){
			if(Condition!=NULL);
				Condition = Condition->filho[0];
		}


		if(Condition!=NULL){
			tPonto p0, p1;
			p0.x = r->q.pBase.x;
			p0.y = r->q.pBase.y;
			p1.x = p0.x + r->q.w;
			p1.y = p0.y + r->q.h;
			if(Condition->filho[1] == NULL){
				desenhaQuadrante(p0, p1, r->q.cor);
			}
			int p;
			for(p=0 ; p<4 ; p++){
				desenhaQuadtree(r->filho[p]);
			}
		}
	}

	//Condição por erro de cada nó
	else{

		if(r!=NULL){
			tPonto p0, p1;
			p0.x = r->q.pBase.x;
			p0.y = r->q.pBase.y;
			p1.x = p0.x + r->q.w;
			p1.y = p0.y + r->q.h;
			if(r->q.erro > errMin){
				desenhaQuadrante(p0, p1, r->q.cor);
			}
			int p;
			for(p=0 ; p<4 ; p++){
				desenhaQuadtree(r->filho[p]);
			}
		}
	}
}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void montaQuadtree() {
	
	printf("Aqui eu vou montar a quadtree\n");
	
	// codifique aqui a sua rotina de montagem da quadtree 
	tPonto base;
	base.x = 0;
	base.y = 0;
	
	// Não sei porque precisa chamar duas vezes
	j=0;
	geraQuadrantes(&raiz, iHeight, base, 0, 0);
	j=0;
	geraQuadrantes(&raiz, iHeight, base, 0, 0);

	cor_erro(&raiz);

}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {

	switch (key) {
		//ESC Fecha programa
		case 27		: 	exit(0);
						break;
		//Alterar Nível da árvore para compressão
		case 'm'	:
		case 'M'	: 	level++;
						break;
		case 'n'	:
		case 'N'	: 	level--;
						break;
		//Alterar o erro permitido para compressão
		case 'p'	:
		case 'P'	: 	errMin+=0.05;
						break;
		case 'o'	:
		case 'O'	: 	errMin-=0.05;
						break;
		//Montar a árvore
		case 'q'	:
		case 'Q'	: 	montaQuadtree();
						break;
		//Alterar Entre desenho normal e pela árvore				
		case 'i'	:
		case 'I'	: 	desenha = !desenha;
						break;
		//Muda a opção de compressão
		case 'c'	:
		case 'C'	: 	option = !option;
						break;		
		//Utilizado para debugar o programa		
		case 'd'	:
		case 'D'	:	debug();
						break;				
		}
	glutPostRedisplay();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenho(void) {

    glClear (GL_COLOR_BUFFER_BIT); 
    
    glColor3f (1.0, 1.0, 1.0);
    
    if (desenha){
    	if(option){
    		//Ajusta o valor do level
    		if(level < 2) level = 1;
			if(level > log2(iHeight)+1) level = log2(iHeight)+1;
    		printf("Level: %d\n", level);
    	}
    	else{
    		//Desenha a cor de fundo
    		tPonto adj, jda;
    		adj.x = 0;
    		adj.y = 0;
    		jda.x = iWidth;
    		jda.y = iHeight;
    		desenhaQuadrante(adj,jda,raiz->q.cor);
    		//Ajusta o valor do erro máximo
    		if(errMin < 0.0) errMin = 0.0; //0%
			if(errMin > 1.0) errMin = 1.0; //100%
    		printf("Erro: %3.0f %% \n", errMin*100);
    	}
    	desenhaQuadtree(raiz);
    }
    else
    	glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, imageGray );
   	
    glutSwapBuffers ();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int main(int argc, char** argv) {
	
char* filename = "IMGs/lena.png";

    if (argc > 1)
		filename = argv[1];

	imageGray = leImagem(filename);
			
	criaJanela(argc, argv);

    initOpenGL();
    
    initEventos();
    
    return 0;   
}


/// ***********************************************************************
/// ** 
/// ***********************************************************************

void debug(void)  {


printf("Heig %d Wid %d \n", iHeight, iWidth);

printf("DEEBUG: %d \n", 
	raiz->filho[2]->q.w);
}



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
