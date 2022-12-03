#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct STitulo{
    int Libertadores;
    int Estadual;
    int CopaDoBrasil;
    int Brasileirao;
    int Mundial;
}Ttitulos;
  
typedef struct Stime
{
    char Nome[MAX];
    char Sigla[MAX];
    char Estadio[MAX];
    char Mascote[MAX];
    Ttitulos titulos;

}Ttime;

int countRow(){
    int row;
    FILE* EQ = fopen("rankingCbf.csv", "r");


        char buffer[1024];
        row = 0;
        if (!EQ)
        printf("Can't open file\n");
        
        else{
            while (fgets(buffer, 1024, EQ))
            {
                row++;
            }
        }
  
    fclose(EQ);
    if(row == 0){
        row = 1;
    };
    return row;
}

void printTabelaCbf(){
    FILE* fp = fopen("rankingCbf.csv", "r");
  
    if (!fp)
        printf("Can't open file\n");
  
    else {

        char buffer[1024];
        int row = 0;
        int column = 0;
  
        while (fgets(buffer,
                     1024, fp)) {
            column = 0;
            row++;
            
            if (row == 1){
                continue;
            }
            
            char* value = strtok(buffer, ", ");
  
            while (value) {
            
                if (column == 0){
                    printf("%d. Time: ", row -1);
                }
                if (column == 1){
                    printf("\tPontos: ");
                }
                
                printf("%s", value);
                value = strtok(NULL, ", ");
                column++;
            }
  
            printf("\n......................................................................\n");
        }
  
        fclose(fp);
    }
};

void order(int count, Ttime time[]){
    /*
    Libertadores = 10;
    Estadual = 1;
    CopaDoBrasil = 3;
    Brasileirao = 5;
    Mundial = 10;
    */

    for (int i = 0; i < count; i++){
        int pontos = ((time[i].titulos.Libertadores * 10) + (time[i].titulos.Mundial * 10) + (time[i].titulos.CopaDoBrasil * 3) + (time[i].titulos.Brasileirao * 5) + (time[i].titulos.Estadual * 1));
        for (int j = i + 1; j < count; j++){
            int pontos2 = ((time[j].titulos.Libertadores * 10) + (time[j].titulos.Mundial * 10) + (time[j].titulos.CopaDoBrasil * 3) + (time[j].titulos.Brasileirao * 5) + (time[j].titulos.Estadual * 1));
            if ( pontos < pontos2){
                Ttime aux = time[i];
                time[i] = time[j];
                time[j] = aux;
            };
        };
    };    
};

void getTime(Ttime time[]){
    FILE* EQ = fopen("times.csv", "r");
    FILE* TI = fopen("titulos.csv", "r");
    FILE* EM = fopen("EM.csv", "r");

    if (!EQ || !TI || !EM)
        printf("Can't open file\n");
  
    else {

        char buffer[1024];
        int row = 0;
        int column = 0;
  
        while (fgets(buffer,
                     1024, EQ)) {
            column = 0;
            row++;
            
            if (row == 1){
                continue;
            }
            
            char* value = strtok(buffer, ", ");
  
            while (value) {
            
                if (column == 0){
                    strcpy(time[row - 2].Nome, value);
                }
                if (column == 1){
                    strcpy(time[row - 2].Sigla, value);
                }
                
                value = strtok(NULL, ", ");
                column++;
            }
        };
        row = 0;
        while (fgets(buffer,
                     1024, TI)) {
            column = 0;
            row++;
            
            if (row == 1){
                continue;
            }
            
            char* value = strtok(buffer, ", ");
  
            while (value) {
            
                if (column == 0){
                    time[row - 2].titulos.Libertadores = atoi(value);
                }
                if (column == 1){
                    time[row - 2].titulos.Estadual = atoi(value);
                }
                if (column == 2){
                    time[row - 2].titulos.CopaDoBrasil = atoi(value);
                }
                if (column == 3){
                    time[row - 2].titulos.Brasileirao = atoi(value);
                }
                if (column == 4){
                    time[row - 2].titulos.Mundial = atoi(value);
                }
                
                value = strtok(NULL, ", ");
                column++;
            };
        };
        row = 0;
        while (fgets(buffer,
                     1024, EM)) {
            column = 0;
            row++;
            
            if (row == 1){
                continue;
            }
            
            char* value = strtok(buffer, ", ");
  
            while (value) {
                if (column == 0){
                    strcpy(time[row - 2].Estadio, value);
                }
                if (column == 1){
                    strcpy(time[row - 2].Mascote, value);
                }
                
                value = strtok(NULL, ", ");
                column++;
            };
        };
        fclose(EQ);
        fclose(TI);
        fclose(EM);
    };
};

void addTime(Ttime time[], int count){

    printf("Digite o Nome do Time: ");
    scanf("%s", time[count].Nome);
    printf("Digite a Sigla do Time: ");
    scanf("%s", time[count].Sigla);
    printf("Qual o Estadio do Time: ");
    scanf("%s", time[count].Estadio);
    printf("Qual o Mascote do Time: ");
    scanf("%s", time[count].Mascote);
    printf("Vamos agora adicionar os titulos do time: \n");
    printf("Quantos Titulos de Libertadores: ");
    scanf("%d", &time[count].titulos.Libertadores);
    printf("Quantos Titulos de Estadual: ");
    scanf("%d", &time[count].titulos.Estadual);
    printf("Quantos Titulos de Copa do Brasil: ");
    scanf("%d", &time[count].titulos.CopaDoBrasil);
    printf("Quantos Titulos de Brasileirao: ");
    scanf("%d", &time[count].titulos.Brasileirao);
    printf("Quantos Titulos de Mundial: ");
    scanf("%d", &time[count].titulos.Mundial);

};

void saveTime(Ttime time[], int count){
    FILE* EQ = fopen("times.csv", "w");
    FILE* TT = fopen("titulos.csv", "w");
    FILE* EM = fopen("EM.csv", "w");
    FILE* fp = fopen("rankingCbf.csv", "w");
  
    if (!EQ || !TT || !EM)
        printf("Can't open file\n");
  
    else {
        for (int i = 0; i < count; i++){
            fprintf(EQ, "\n%s, %s", time[i].Nome,time[i].Sigla);
            fprintf(EM, "\n%s, %s", time[i].Estadio, time[i].Mascote);
            fprintf(TT, "\n%d, %d, %d, %d, %d", time[i].titulos.Libertadores, time[i].titulos.Estadual, time[i].titulos.CopaDoBrasil, time[i].titulos.Brasileirao, time[i].titulos.Mundial);
            fprintf(fp, "\n%s, %d", time[i].Nome, ((time[i].titulos.Libertadores * 10) 
                                                + (time[i].titulos.Mundial * 10) 
                                                + (time[i].titulos.CopaDoBrasil * 3) 
                                                + (time[i].titulos.Brasileirao * 5) 
                                                + (time[i].titulos.Estadual * 1)));
        };
    };
    fclose(EQ);
    fclose(EM);
    fclose(TT);
    fclose(fp);
};

void showTime( Ttime time[], int i){

    printf("%s\n", time[i].Nome);
    printf("Sigla: %s\n", time[i].Sigla);
    printf("Estadio: %s\n", time[i].Estadio);
    printf("Mascote: %s\n", time[i].Mascote);
    printf("Titulos de Libertadores: %d\n", time[i].titulos.Libertadores);
    printf("Titulos de Estadual %d\n", time[i].titulos.Estadual);
    printf("Titulos de Copa do Brasil: %d\n", time[i].titulos.CopaDoBrasil);
    printf("Titulos de Brasileirao: %d\n", time[i].titulos.Brasileirao);
    printf("Titulos de Mundial: %d\n", time[i].titulos.Mundial);

};

void deleteTime(Ttime time[], int count, int i){
    for (int j = i; j < count; j++){
        time[j] = time[j + 1];
    };
    count--;
};

void editTime( Ttime time[], int i){
int opcao;
printf("\nO que deseja editar: \n");
printf("1 - Nome do Time\n");
printf("2 - Sigla do Time\n");
printf("3 - Estadio do Time\n");
printf("4 - Mascote do Time\n");
printf("5 - Titulos de Libertadores\n");
printf("6 - Titulos de Estadual\n");
printf("7 - Titulos de Copa do Brasil\n");
printf("8 - Titulos de Brasileirao\n");
printf("9 - Titulos de Mundial\n");
printf("10 - Voltar\n");
scanf("%d", &opcao);

switch (opcao){
    case 1:
        printf("Digite o novo nome do time: ");
        scanf("%s", time[i].Nome);
        break;
    case 2:
        printf("Digite a nova sigla do time: ");
        scanf("%s", time[i].Sigla);
        break;
    case 3:
        printf("Digite o novo estadio do time: ");
        scanf("%s", time[i].Estadio);
        break;
    case 4:
        printf("Digite o novo mascote do time: ");
        scanf("%s", time[i].Mascote);
        break;
    case 5:
        printf("Digite o novo numero de titulos de Libertadores: ");
        scanf("%d", &time[i].titulos.Libertadores);
        break;
    case 6:
        printf("Digite o novo numero de titulos de Estadual: ");
        scanf("%d", &time[i].titulos.Estadual);
        break;
    case 7:
        printf("Digite o novo numero de titulos de Copa do Brasil: ");
        scanf("%d", &time[i].titulos.CopaDoBrasil);
        break;
    case 8:
        printf("Digite o novo numero de titulos de Brasileirao: ");
        scanf("%d", &time[i].titulos.Brasileirao);
        break;
    case 9:
        printf("Digite o novo numero de titulos de Mundial: ");
        scanf("%d", &time[i].titulos.Mundial);
        break;
    case 10:
        break;
    default:
        printf("Opcao invalida\n");
        break;
    };
};

void searchTime(Ttime time[] , int count){
    char nome[MAX];
    printf("Digite o nome do time: ");
    scanf("%s", nome);

    for (int i = 0; i < MAX; i++){
        if (strcmp(time[i].Nome, nome) == 0){
            int opcao;
            printf("Time encontrado, o que deseja fazer? \n");
            printf("1 - Editar Time \n");
            printf("2 - Excluir Time \n");
            printf("3 - Mostar Dados \n");
            printf("4 - Voltar \n");
            scanf("%d", &opcao);
            switch (opcao){
                case 1:
                    editTime(time, i);
                    break;
                case 2:
                    deleteTime(time, i , count);
                    break;
                case 3:
                    showTime(time, i);
                    break;
                case 4:
                    break;
                default:
                    printf("Opcao invalida \n");
                    break;
            };

        }else{
            printf("Time nao encontrado\n");
            break;
        };
    };
};


void Menu(){
    Ttime time[MAX];
    getTime(time);

    while(1){
        int escolha = 0;
        int count = countRow() - 1;
            printf("\nOlá, escolha uma opção.\n");
            printf("\n1.Adicione um time.\n");
            printf("2.Mostre o Ranking da CBF.\n");
            printf("3.Buscar por uma equipe\n");
            printf("4.Sair.\n");
            scanf("%d", &escolha);

            switch (escolha){
                case 1:
                    addTime(time, count);
                    count++;
                    order(count, time);
                    saveTime(time, count);
                    break;
                case 2:
                    system("clear");
                    printTabelaCbf();
                    break;
                case 3:
                    searchTime(time, count);
                    saveTime(time, count);
                    break;
                case 4:
                    break;
                default:
                    printf("Opção inválida.\n");
                    break;
            };
        
    };

};

int main(){

    system("clear");
    Menu();

    return 0;
};