# Compressao_Imagens
Utiliza uma árvore quaternária para realizar a compressão de imagens. 
Segundo trabalho da matéria Estrutura de dados e algoritimos


## Comandos do declado

   Q => Monta a QuadTree
   I => Desenha a QuadTree
   C => Altera entre os tipos de compressão (Por erro e por nível da árvore)   

   M => Diminui o número do último nível a ser desenhado
   N => Aumenta o número do último nível a ser desenhado   
   
   P => Diminui o Valor do erro a ser considerado
   O => Aumenta o valor do erro a ser considerado
   

## Verificação da compressão

   Para ver as diferentes formas de compressão você deve seguir os seguintes passos:
	
	1.Monte a quadtree apertando Q
	2.Desenhe a quadtree apertando I
	3.Vá apertando as teclas M e N para verificar a compressão por nível
	4.Aperte C para trocar o tipo de compressão
	5.Vá apertando as teclas P e O para verificar a compressão por erro

## Como funciona?

   O programa cria uma arvore com altura log2(height) e já separa os quadrantes com
seus pontos base, altura e comprimento já definidos. Nesse mesmo passo, é colocado
os valores de cinza (somente nas folhas)
   Depois é chamado uma rotina em que calcula as cores e os erros para os nós. Os 
erros das folhas são zero.
   Para desenhar, há uma verificação quanto ao número do erro ou nível que está se 
trabalhando no momento.
