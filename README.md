# Sistema de Gestão de Biblioteca (BST e Pilha Dinâmica)

**Curso:** Análise e Desenvolvimento de Sistemas (FATEC Ribeirão Preto)  
**Disciplina:** Estrutura de Dados (3º Semestre)  
**Docente:** Prof. Me. Heber Castro  
**Aluno:** Marcia Matiko Hoshihara
**Tema:** Biblioteca (ID, Título, Autor e Ano de Publicação)  

---

## 📌 Descrição do Projeto

Aplicação de terminal desenvolvida em **C11** para a gestão de acervo bibliográfico. O sistema utiliza uma **Árvore Binária de Busca (BST)** para o armazenamento e busca eficiente dos livros e uma **Pilha Dinâmica Encadeada** como estrutura linear independente para manipulação de IDs.

O sistema conta com um menu interativo e validação rigorosa de entradas de dados, prevenindo travamentos ou encerramentos inesperados por dados inválidos ou *buffers* residuais do teclado.

---

## 🛠️ Requisitos Técnicos Implementados

- **R01**: Aplicação em C11 com structs, ponteiros, funções e menu interativo (opções 0 a 7).
- **R02/R03**: BST com inserção, busca por ID, remoção de nós (0, 1 ou 2 filhos) e listagem em-ordem. Rejeição de IDs duplicados, nulos ou negativos, e validação do ano de publicação (1 a 2026).
- **R05/R06**: Estrutura linear dinamicamente encadeada (Pilha) para IDs inteiros positivos, permitindo repetições e funcionando de forma independente da BST.
- **R07**: Tratamento amigável para remoção em estrutura vazia e liberação total de memória ao encerrar o sistema (`free`).
- **R08/R10**: Repositório Git individual com modularização do código em pastas `include/` e `src/`.

---

## 📂 Estrutura do Repositório

```text
estrutura_de_dados/
├── include/           # Ficheiros de cabeçalho (.h)
│   ├── bst.h          # Protótipos e structs da BST
│   ├── livro.h        # Struct do Livro e funções de criação
│   └── pilha.h        # Protótipos e structs da Pilha
├── src/               # Códigos-fonte (.c)
│   ├── bst.c          # Implementação da BST
│   ├── livro.c        # Implementação do Livro
│   ├── pilha.c        # Implementação da Pilha
│   └── main.c         # Menu principal e validações de input
├── tests/             # Roteiro de testes reproduzíveis
│   └── roteiro_testes.txt
├── docs/              # Documentação técnica e relatório PDF
├── .gitignore         # Configuração de arquivos ignorados pelo Git
└── README.md          # Documentação principal do repositório