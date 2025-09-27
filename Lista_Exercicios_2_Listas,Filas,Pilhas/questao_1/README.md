Operação	Complexidade Big-O	Justificativa		

Inserir_inicio	O(1)	A operação envolve apenas a alocação de um novo nó (O(1)) e a mudança de dois ponteiros: novo->prox = L e retornar o novo nó. Não depende do tamanho da lista N.	

Inserir_ordenado_por_codigo	O(N)	É necessário percorrer a lista (na pior das hipóteses, do início ao fim) para 1) verificar se o código já existe (atualização) ou 2) encontrar a posição correta de inserção. A busca por um nó leva O(N) tempo.		

Remover_por_codigo	O(N)	A remoção requer uma busca linear pelo elemento a ser removido (na pior das hipóteses, o elemento está no fim ou não existe). A busca leva O(N) tempo.	

Ajustar_quantidade	O(N)	A função primeiro chama buscar(), que tem complexidade O(N). O ajuste da quantidade em si é O(1), mas é dominado pela busca.
										
Buscar	O(N)	A busca por um elemento (pelo código) requer percorrer a lista linearmente, no pior caso, até o final.		

Listar	O(N)	É necessário visitar cada um dos N elementos da lista para imprimi-los.			

Limpar	O(N)	É necessário visitar cada um dos N elementos da lista para liberar a memória de cada nó com free().

Gerar_relatorio	O(N)	A geração do relatório (total distintos, valor total, maior valor imobilizado) requer percorrer a lista inteira uma única vez para acumular e comparar os valores.											