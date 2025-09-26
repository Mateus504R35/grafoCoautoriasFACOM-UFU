# Grafo de Coautorias FACOM/UFU

![C](https://img.shields.io/badge/language-C-blue)
![Build](https://img.shields.io/badge/build-gcc%20%7C%20make-informational)


Aplicação em **C** que constrói e analisa um grafo de coautorias entre professores da FACOM/UFU a partir de um arquivo de dados (`dados.txt`), obtido segundo o DBLP (https://dblp.org/) até o ano de 2023. O programa oferece um menu interativo com operações de exploração do grafo (coautorias, conectividade forte, caminho mínimo, etc.).

> Autores (do código): declarados no `main.c`.

---

## Estrutura do projeto

```
grafoCoautoriasFACOM-UFU/
├── Grafo.h        # Declarações de tipos (grafo, vértice, aresta) e assinaturas das funções
├── grafo.c        # Implementação das operações sobre o grafo
├── main.c         # Interface de linha de comando (menu) e leitura de dados
└── dados.txt      # Base de dados: pares de professores e número de coautorias
```

---

## Formato do arquivo de entrada (`dados.txt`)

Cada linha descreve uma relação de coautoria no formato:

```
<Professor A>   <Professor B | "Não Há Coautores">   <N>
```

- Quando o campo do **Professor B** é `"Não Há Coautores"` e `N = 0`, indica que o Professor A não possui coautorias cadastradas.
- Caso contrário, `N` é o número total de coautorias entre A e B.

Exemplo (recortado do arquivo fornecido):

```
André Ricardo Backes   Marcelo Keese Albertini   5
Alessandra Aparecida Paulino   Não Há Coautores   0
```

> Observação: Certifique-se de salvar o arquivo como **UTF-8** para preservar acentos.

---

## Compilação

### Usando Makefile

```bash
make        # compila (alvo padrão)
make run    # compila e executa ./grafo_facom
make debug  # recompila com símbolos de depuração
make clean  # remove artefatos de build
```

---

### Compilando manualmente

Sem `Makefile`, você pode compilar com **gcc**:

```bash
gcc -std=c11 -Wall -Wextra -O2 -o grafo_facom main.c grafo.c
```

---

## Execução

1. Certifique-se de que `dados.txt` está **no mesmo diretório** do executável.
2. Rode o programa:
   ```bash
   ./grafo_facom
   ```

Ao iniciar, será exibido um **menu interativo**:

```
(1) - Imprimir grafo 'Professores e Coautores'
(2) - Exibir coautorias de um professor com até D passos de distancia
(3) - Exibir professores colaboradores por quantidade minima de artigos
(4) - Exibir professores fortemente conectados a outro
(5) - Exibir caminho de custo minimo entre dois professores
(6) - Sair
```

### Descrição das opções

1. **Imprimir grafo**: lista os professores, seus vizinhos (coautores) e pesos (nº de coautorias).
2. **Coautorias até D passos**: usa o algoritmo **BFS** para listar colaboradores alcançáveis a uma distância máxima `D` a partir de um professor.
3. **Colaboradores com coautorias ≥ K**: filtra e exibe professores que possuem pelo menos `K` coautorias com um alvo.
4. **Fortemente conectados**: identifica componentes **fortemente conectadas** (usa o algoritmo DFS sobre o grafo).
5. **Caminho de custo mínimo**: encontra um caminho de menor custo entre dois professores (usa estrutura de **min-heap** e rotina de caminho mínimo).
6. **Sair**: encerra o programa.

> As assinaturas e estruturas principais estão em `Grafo.h` (ex.: `grafo`, `vertice`, `aresta`, filas e min-heap).

---

## Exemplos de uso

- Listar coautorias de **"André Ricardo Backes"** a até **2 passos**:
  1. Escolha a opção `2`.
  2. Informe o nome exatamente como aparece em `dados.txt`.
  3. Informe `2` quando solicitado pela distância.

- Encontrar **caminho de custo mínimo** entre dois docentes:
  1. Escolha a opção `5`.
  2. Digite os dois nomes (origem e destino) exatamente como no `dados.txt`.

---

## Requisitos

- Compilador **C** compatível com C11 (ex.: `gcc`)
- Sistema Unix-like (Linux/macOS) ou Windows (via MinGW/WSL)
- Terminal com suporte a UTF-8

---

## Testes rápidos

Depois de compilar:

```bash
./grafo_facom << 'EOF'
1
2
André Ricardo Backes
2
6
EOF
```

---

## Créditos

- Base de dados: https://dblp.org/ (coautorias FACOM/UFU)
- Implementação do grafo e rotinas: ver **autores no cabeçalho de `main.c`**
