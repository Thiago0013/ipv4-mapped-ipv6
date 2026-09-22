#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void decToBin(int num, int *ipv4Binary, int octetIndex);
void binToHex(int ipv4Binary[32], char *ipv6);

int main(){
    int ipv4Binary[32] = {0};
    int i = 0;
    int numbers[4];

    char ipv4[32];
    char ipv6[50];

    printf("Digite o endereço de IP(EX: 192.168.0.10):");
    fgets(ipv4, sizeof(ipv4), stdin);
    ipv4[strcspn(ipv4, "\n")] = '\0';
    
    printf("Traduzindo endereço IPV4: %s para IPV6... \nTraduzindo bin: ", ipv4);
    
    char *token = strtok(ipv4, ".");
    while(token != NULL && i < 4){
        numbers[i] = atoi(token);
        
        token = strtok(NULL, ".");
        i++;
    }

    for(int j=0; j<i; j++){
        decToBin(numbers[j], ipv4Binary, j);
    }
    
    for(int j=0; j<32; j++){
        printf("%d", ipv4Binary[j]);
        if((j + 1) % 8 == 0 && j != 31){
            printf(".");
        }
    }
    printf(" ...\n");

    printf("Traduzindo para IPV6 .... \n");

    binToHex(ipv4Binary, ipv6);

    printf("IPV6 traduzido: %s\n", ipv6);

    return 0;
}

void binToHex(int ipv4Binary[32], char *ipv6){
    strcpy(ipv6, "::FFFF:");

    for(int j=0; j<32; j+=4){
        int soma = 0;
        int peso = 8;

        for(int k=0; k<4; k++){
            if(ipv4Binary[j+k] == 1){
                soma += peso;
            }
            peso = peso / 2;
        }

        char temp[3];

        sprintf(temp, "%X", soma);
        strcat(ipv6, temp);

        if(j == 12){
            strcat(ipv6, ":");
        }

    }
}

void decToBin(int num, int *ipv4Binary, int octetIndex){
    int bin[8] = {0};

    for(int j=7; j>=0; j--){
        bin[j] = num % 2;
        num = num / 2;
    }

    for(int j=0; j < 8; j++){
        int pos = (octetIndex * 8) + j;
        ipv4Binary[pos] = bin[j];
    }

}