#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quarto.h"
#include "apresentacao.h"
#include "tempo.h"
#include "reserva.h"
#include "hospedagem.h"
#include "cliente.h"


int main(int argc, char const *argv[])
{
    /*
    printf("*************************************************\n");
    printf("Testando sobreposição de datas de duas reservas\n");
    printf("*************************************************\n");
    DATA entradaReserva, saidaReserva, checkin, checkout;
    char tempStringData[20];
    printf("Reserva (Entrada prevista): ");
    scanf(" %[^\n]s", tempStringData);
    StringToData(tempStringData, &entradaReserva);
    printf("Reserva (Saida prevista): ");
    scanf(" %[^\n]s", tempStringData);    
    StringToData(tempStringData, &saidaReserva);
    printf("Checkin : ");
    scanf(" %[^\n]s", tempStringData);    
    StringToData(tempStringData, &checkin);
    printf("Checkout : ");
    scanf(" %[^\n]s", tempStringData);
    StringToData(tempStringData, &checkout);

    if ( verificaSobreposicaoReserva(entradaReserva, saidaReserva, checkin, checkout))
        printf("Reserva não sobreposta\n");
    else
        printf("Reserva sobreposta\n");

    printf("*************************************************\n");
    printf("Tecle enter para continuar: ");
    getchar();
    */

    printf("*************************************************\n");
    printf("Testando leitura de Hospedagens\n");
    printf("*************************************************\n");
    HOSPEDAGEM *listaHospedagens;
    int qtdeHospedagens = quantidadeHospedagensCSV();
    listaHospedagens = (HOSPEDAGEM *) malloc(qtdeHospedagens * sizeof(HOSPEDAGEM));
    lerHospedagensCSV(listaHospedagens);
    for (int i = 0 ; i < qtdeHospedagens; i++)
        exibirHospedagem(listaHospedagens[i]);
    printf("*************************************************\n");
    getchar();
    getchar();
    
    printf("*************************************************\n");
    printf("Testando leitura de Reservas\n");
    printf("*************************************************\n");
    RESERVA *listaReservas;
    int qtdeReservas = quantidadeReservasCSV();
    listaReservas = (RESERVA *) malloc(qtdeReservas * sizeof(RESERVA));
    lerReservasCSV(listaReservas);
    for (int i = 0 ; i < qtdeReservas; i++)
    {
        exibirReserva(listaReservas[i]);
        //gravarReservaDAT(listaReservas[i]);
    }    
    printf("*************************************************\n");
    printf("Tecle enter para continuar: ");
    getchar();
    getchar();
    free(listaReservas);
    qtdeReservas = quantidadeReservasDAT();
    listaReservas = (RESERVA *) malloc(qtdeReservas * sizeof(RESERVA));
    lerReservasDAT(listaReservas);
    printf("Exibindo dados do arquivo Reservas.dat\n");
    for (int i = 0 ; i < qtdeReservas; i++)
    {
        printf("*************************************************\n");
        exibirReserva(listaReservas[i]);        
        printf("*************************************************\n");
    }    
 

    printf("*************************************************\n");
    printf("Testando leitura de Clientes\n");
    printf("*************************************************\n");
    CLIENTE *listaClientes;
    int qtdeClientes = quantidadeClientesCSV();
    listaClientes = (CLIENTE *) malloc(qtdeClientes * sizeof(CLIENTE));
    lerClientesCSV(listaClientes);
    for (int i = 0 ; i < qtdeClientes; i++)
        exibirCliente(listaClientes[i]);
    printf("*************************************************\n");
    free(listaClientes) ;
    printf("Tecle enter para continuar: ");
    getchar();
    getchar();
    
    
    printf("################################\n");
    printf("Testando a realização de uma reserva usando arquivo CSV\n");
    printf("################################\n");   
    RESERVA reservaTeste;        
    char CPF[16];
    char tipoQuarto[10];
    char strData[15];     
    DATA data1, data2;
    printf("CPF do Cliente: ");
    scanf(" %[^\n]s", CPF);
    printf("Tipo de quarto: ");
    scanf(" %[^\n]s", tipoQuarto);
    printf("Data de entrada (DD/MM/AAAA): ");
    scanf(" %[^\n]s", strData);
    StringToData(strData, &data1);
    printf("Data de saida (DD/MM/AAAA): ");
    scanf(" %[^\n]s", strData);
    StringToData(strData, &data2);
    int dias = DataDiff(data2, data1);
    bool sucesso = reservarQuarto(CPF, tipoQuarto, data1, data2, &reservaTeste);
    if (sucesso)
    {
        gravarReservaCSV(reservaTeste);
        exibirReserva(reservaTeste);
        printf("################################\n");
        printf("Reserva realizada com sucesso!\nCodigo da reserva é %d \n", reservaTeste.id);
        printf("Dia de hospedagem: %d dias\n",dias);
        printf("################################\n");
    }
    else
    {
        printf("Não foi possível reservar um quarto nesse período\n");
 
    }

    printf("Tecle enter para continuar: ");
    getchar();      
    getchar();
        
    
    QUARTO q, *lista, *listaBusca=NULL;
    int opcao = MenuPrincipal();
    if (opcao == 4 )
    {
        // testando leitura, exibição e gravação de quarto no CSV e no DAT                 
        lerQuarto(&q);
        exibirQuarto(q);
        gravarQuartoCSV(q);
        gravarQuartoDAT(q);    
    }
    // testando leitura de quartos armazenados em disco
    int qtde = quantidadeQuartosCSV();
    lista = (QUARTO *) malloc(sizeof(QUARTO)*qtde);    
    lerQuartosCSV(lista);
    for (int i = 0; i < qtde; i++)
    {
       exibirQuarto(lista[i]);
    }
    // testando a busca de um tipo de quarto específico definido pelo usuário    
    
    char tipoQuartoBusca[10];
    printf("Entre com o tipo de quarto desejado ->");
    scanf(" %[^\n]s", tipoQuartoBusca);
    int qtdeTipo; 
    buscarQuartosPorTipo(tipoQuartoBusca,lista, qtde, listaBusca, &qtdeTipo);    
    getchar();
    for (int j = 0; j < qtdeTipo; j++)    
    {
        exibirQuarto(listaBusca[j]);
    }
    getchar();
    free(listaBusca);
    free(lista);
    /*
    // testando a função de reservarQuarto (função ainda incompleta)
    RESERVA res;    
    reservarQuarto(data1, data2, "triplo");
    exibirReserva(res);
    */
    return 0;
}


