## SIMULAÇÃO: VENDA DE INGRESSOS
Informe a quantidade inicial de ingressos (Estoque > 0): 100

> ADD Cliente_A 30
Cliente Cliente_A com solicitação de 30 ingressos adicionado à fila.
> ADD Cliente_B 50
Cliente Cliente_B com solicitação de 50 ingressos adicionado à fila.
> ADD Cliente_C 40
Cliente Cliente_C com solicitação de 40 ingressos adicionado à fila.
> ADD Cliente_D 25
Cliente Cliente_D com solicitação de 25 ingressos adicionado à fila.

> START
--- INÍCIO DO PROCESSAMENTO DE VENDAS ---
Estoque inicial para a venda: 100 ingressos.

Atendendo cliente Cliente_A (solicitou 30 ingressos). Estoque atual: 100.
  Venda CONFIRMADA: 30 ingressos. Novo estoque: 70.

Atendendo cliente Cliente_B (solicitou 50 ingressos). Estoque atual: 70.
  Venda CONFIRMADA: 50 ingressos. Novo estoque: 20.

Atendendo cliente Cliente_C (solicitou 40 ingressos). Estoque atual: 20.
  Estoque insuficiente. Podemos oferecer 20 ingressos. Aceita (S/N)? S 
  Oferta aceita. Venda PARCIAL de 20 ingressos. Estoque zerado.

Atendendo cliente Cliente_D (solicitou 25 ingressos). Estoque atual: 0.
ESTOQUE ZERADO. O cliente Cliente_D não pode ser atendido.
PROCESSO DE VENDA FINALIZADO. ESTOQUE ZERADO.

> REL
======================================================
                  RELATÓRIO DE VENDAS
======================================================
Estoque Restante: 0 ingressos
Total de Ingressos Vendidos: 100
Clientes Atendidos (Total ou Parcialmente): 3

--- Top 3 Maiores Compras ---
  #1: Cliente_B - 50 ingressos
  #2: Cliente_A - 30 ingressos
  #3: Cliente_C - 20 ingressos

--- Clientes NÃO Atendidos ---
  ID: Cliente_D - Solicitado: 25 ingressos
======================================================

> EXIT
Saindo do sistema. Limpando a memória...