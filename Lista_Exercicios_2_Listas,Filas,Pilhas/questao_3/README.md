Operação	Complexidade Big-O	Justificativa
pilha_init	O(1)	Apenas define topo = NULL.
push	O(1)	Envolve a alocação de um novo nó e a manipulação de dois ponteiros (novo->baixo e p->topo). Não depende do tamanho da pilha N.
pop	O(1)	Envolve a leitura do topo, a mudança do ponteiro p->topo e a liberação de memória (free). Não depende de N.
peek	O(1)	Apenas lê os dados do nó apontado por p->topo.
vazia	O(1)	Verifica se p->topo == NULL.
limpar	O(N)	É necessário percorrer e liberar a memória de cada um dos N Frames.
trace	O(N)	É necessário percorrer cada um dos N Frames da pilha para imprimi-los.