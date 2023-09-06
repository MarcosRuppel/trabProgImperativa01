// PUCPR - Bacharelado em Ciência da Computação
// Autor: Marcos Paulo Ruppel - Turma 2U (Noite)
#include <stdio.h>
#include <locale.h>
#include "structs.h"

int main(void) {

    // Abrindo os arquivos TXT
    FILE *vendasFile = fopen("../vendas.txt", "r");
    FILE *produtosFile = fopen("../produtos.txt", "r");
    FILE *vendedoresFile = fopen("../vendedores.txt", "r");

    // Validando se os arquivos foram encontrados
    if (!vendasFile || !produtosFile || !vendedoresFile) {
        printf("Arquivos de entrada nao encontrados.\n");
        return 1;
    }

    Produto produtos[100];
    Vendedor vendedores[100];
    Venda vendas[1000];
    int numProdutos = 0, numVendedores = 0, numVendas = 0;

    // Le os produtos do arquivo
    while (fscanf(produtosFile, "%d %lf %[^\n]", &produtos[numProdutos].codigo,
                  &produtos[numProdutos].preco, produtos[numProdutos].descricao) != EOF) {
        numProdutos++;
    }

    // Le os vendedores do arquivo
    while (fscanf(vendedoresFile, "%d %[^\n]", &vendedores[numVendedores].codigo,
                  vendedores[numVendedores].nome) != EOF) {
        numVendedores++;
    }

    // Le as vendas do arquivo
    while (fscanf(vendasFile, "%d %d %d", &vendas[numVendas].codigoVendedor,
                  &vendas[numVendas].codigoProduto, &vendas[numVendas].quantidade) != EOF) {
        numVendas++;
    }

    // Acumuladores dos totais
    double totalGeral = 0.0;
    double totalPorProduto[100] = {0};
    double totalPorVendedor[100] = {0};

    for (int i = 0; i < numVendas; i++) {
        int codigoProduto = vendas[i].codigoProduto;
        int codigoVendedor = vendas[i].codigoVendedor;
        int quantidade = vendas[i].quantidade;

        double precoProduto = 0.0;
        for (int j = 0; j < numProdutos; j++) {
            if (produtos[j].codigo == codigoProduto) {
                precoProduto = produtos[j].preco;
                break;
            }
        }

        totalGeral += (precoProduto * quantidade);
        totalPorProduto[codigoProduto - 1] += (precoProduto * quantidade);
        totalPorVendedor[codigoVendedor - 1] += (precoProduto * quantidade);
    }

    // Cria o arquivo de saida
    FILE *totaisFile = fopen("../totais.txt", "w");
    if (!totaisFile) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }

    // Grava os totais no arquivo de saída
    fprintf(totaisFile, "Total Geral Vendido:\t R$ %5.2lf\n", totalGeral);
    fprintf(totaisFile, "\nTotal Vendido por Produto:\n");
    for (int i = 0; i < numProdutos; i++) {
        fprintf(totaisFile, "%d \t %s:\t R$ %5.2lf\n", produtos[i].codigo, produtos[i].descricao,
                totalPorProduto[i]);
    }
    fprintf(totaisFile, "\nTotal Vendido por Vendedor:\n");
    for (int i = 0; i < numVendedores; i++) {
        fprintf(totaisFile, "%d \t %s:\t R$ %5.2lf\n", vendedores[i].codigo, vendedores[i].nome,
                totalPorVendedor[i]);
    }

    // Fecha os arquivos
    fclose(vendasFile);
    fclose(produtosFile);
    fclose(vendedoresFile);
    fclose(totaisFile);

    printf("Relatório gerado com sucesso em 'totais.txt'\n");

    return 0;
}
