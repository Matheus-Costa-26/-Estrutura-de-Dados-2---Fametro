Fila (FIFO) O(1): As operações de enfileirar e desenfileirar são estritamente O(1), pois a fila usa ponteiros para ini e fim, evitando a necessidade de percorrer a estrutura.

Lista de Não Atendidos: Os clientes não atendidos são armazenados em uma lista encadeada separada (NaoAtendido). A adição é O(1) (no início da lista).

Relatório (Top-3): A função atualizar_top_compras mantém o top-3 em um array fixo de tamanho 3. A complexidade é O(1) porque a inserção/comparação ocorre sempre em um número máximo de 3 posições.

Processamento Interativo: A função processar_vendas lida com o caso de oferta parcial de ingressos, solicitando a confirmação do usuário (S/N) via entrada padrão (stdin), conforme o requisito.