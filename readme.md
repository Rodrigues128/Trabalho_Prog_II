# 🛒 Supermercado Produtos++ - Sistema de Vendas

Este projeto é um trabalho prático da disciplina **Algoritmos e Programação II**, desenvolvido em **C/C++**, com o objetivo de simular o controle de vendas online do supermercado fictício **Produtos++**.

## 📚 Descrição

O sistema permite gerenciar as vendas de um supermercado, incluindo cadastro de produtos, controle de estoque, registro de vendas por data, alteração de preços e geração de relatórios em arquivos.

As vendas são armazenadas em um vetor, cada uma contendo uma **lista encadeada de itens vendidos** (lista simplesmente ou duplamente encadeada). Já os produtos são armazenados em um vetor ordenado por nome, utilizando algoritmos de ordenação como **Insertion Sort**, **Selection Sort**, **Mergesort** ou **Quicksort**.

---

## 🧩 Funcionalidades

- 📂 **Importação de arquivo com estoque inicial**
- 🧾 **Cadastro de vendas com controle de estoque**
- 📅 **Listagem de vendas por data**
- 🔄 **Alteração de preço e quantidade em estoque**
- ❌ **Remoção de produtos não vendidos**
- 💾 **Geração de arquivos atualizados de produtos e vendas**

---

## 📑 Menu de opções

```text
[1] Cadastrar Venda
[2] Listar vendas por data
[3] Alterar estoque e preço de produto
[4] Remover produto do estoque
[5] Sair
```

---

## 💡 Exemplo de entrada de produtos (arquivo)

```
3
1010
Sabão em pó OMO
26.00
50

2020
Arroz Tio João
25.00
100

3030
Feijão Sabiá
5.25
200
```

---

## 💻 Execução

### 🔧 Compilação (com GCC):

```bash
g++ main.cpp src/*.cpp -Iinclude -o out.exe
ou
g++ .\main.cpp .\src\*.cpp -Iinclude -o out.exe

```

> Certifique-se de que todos os arquivos `.cpp` e `.h` estejam no mesmo diretório ao compilar.

### ▶️ Execução:

```power
./out.exe
```

Durante a execução, o programa solicitará o nome do arquivo com os dados de produtos.

---

## 📁 Saída

Ao finalizar o programa, serão gerados dois arquivos:

- `produtos.txt` (atualizado com novas quantidades e preços)
- `vendasDDMMYYYY.txt` (com os dados das vendas do dia, no formato mostrado abaixo)

### Exemplo de saída `vendas12052025.txt`:

```
12/05/2025
08:05:02
765765765-08
1015 Sabão em pó OMO  2 52,00
2387 Arroz Tio João   1 25,00
Total: 129,00
```

---

## 🗂 Estrutura do Projeto

```
📁 include/ — Headers do projeto (.h)
 ┗ 📚 sales.ch
🗃️ src/ - Código-fonte principal (.cpp)
 ┗ 🔧 sales.cpp
🧪 tests/ — Arquivos de teste
 ┣ 📄 5_produtos.txt
 ┣ 📄 20_produtos.txt
 ┗ 📄 100_produtos.txt

💻 main.cpp
```

---

## 👨‍🏫 Informações Acadêmicas

```
Nome(s): Paulo Henrique Rodrigues Corrêa
Disciplina: Algoritmos e Programação II
Professora: Graziela Santos de Araujo
```