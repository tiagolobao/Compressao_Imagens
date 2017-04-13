#ifndef __EstruturasDeDados__
#define __EstruturasDeDados__ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


typedef struct point 	{	int x;
							int y;
						} tPonto;
						
typedef struct	Quadrante{ 	int h,w;
					int 	nivel;
					tPonto	pBase;
					int		cor;
					float	erro;
				} tQuadrante;
				
typedef struct tNo	{	tQuadrante q;
						struct tNo* filho[4];
					} tNoArvore;
								
#endif		// __EstruturasDeDados__

//Aloca um no
tNoArvore* alocaNo(int niv, tPonto pon, int h, 
	int w, int c, float e);

//Gera um quadrante na árvore com nivel e num de bytes definido
/*
Sempre chamar essa função com o valor nivel = 0 
Necesśario para não gerar loop infinito com a recursividade
*/
/*
Sempre chamar essa função com o valor count = 0
Necessário para cálculo do ponto base dos filhos
*/
/*
Sempre chamar essa função com o valor base.x = 0 e base.y = 0
Necessário para cálculo do ponto base dos filhos
*/
/*
Sempre chamar essa função com o valor j = 0
Necessário para salvar as cores na árvore
*/
void geraQuadrantes(tNoArvore **r, int height, tPonto base,
	int nivel, int count);

//Calcula a média
int media(int input[]);

//Gera valor de cores para os nós da quadtree
void cor_erro(tNoArvore **r);

/* 
Como o quadrante é dividido

----------------------------
|            |             |
|     4      |      3      |
|            |             |
|            |             |
|------------|-------------|
|            |             |
|            |             |
|     1      |      2      |
|            |             |
----------------------------

*/