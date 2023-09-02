//
// Created by mruppel on 02/09/23.
//

#ifndef TRABPROGIMPERATIVA01_STRUCTS_H
#define TRABPROGIMPERATIVA01_STRUCTS_H

typedef struct {
    int codigo;
    double preco;
    char descricao[100];
} Produto;

typedef struct {
    int codigo;
    char nome[100];
} Vendedor;

typedef struct {
    int codigoVendedor;
    int codigoProduto;
    int quantidade;
} Venda;

void lerProdutos(Produto produtos[], int *numProdutos, FILE *produtosFile);
void lerVendedores(Vendedor vendedores[], int *numVendedores, FILE *vendedoresFile);
void lerVendas(Venda vendas[], int *numVendas, FILE *vendasFile);
void calcularTotais(double *totalGeral, double totalPorProduto[], double totalPorVendedor[], Produto produtos[],
                    Venda vendas[], int numProdutos, int numVendas);
void escreverRelatorio(double totalGeral, double totalPorProduto[], double totalPorVendedor[], Produto produtos[],
                       Vendedor vendedores[], int numProdutos, int numVendedores);

#endif //TRABPROGIMPERATIVA01_STRUCTS_H
