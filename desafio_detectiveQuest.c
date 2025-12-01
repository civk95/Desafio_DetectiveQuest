#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definição da struct Sala
struct Sala {
    char nome[30];              
    struct Sala* esquerda;      
    struct Sala* direita;       
};

// protótipos das funções
struct Sala* criarSala(const char* nome);
void explorarMansao(struct Sala* raiz);
void liberarArvore(struct Sala* raiz);
void mostrarMapa(struct Sala* sala, int nivel);

int main() {
    printf("=== DETECTIVE QUEST - EXPLORACAO DA MANSAO ===\n");
    printf("Enigma Studios - Ensino de Logica e Programacao\n\n");
    printf("Voce e um detetive investigando um misterio numa antiga mansao.\n");
    printf("Explore os comodos em busca de pistas!\n\n");
    
    // construção do mapa da mansão como uma árvore binária
    // a árvore é montada de forma manual para representar o layout fixo da mansão
    
    // nível 0: hall de entrada (raiz)
    struct Sala* hall = criarSala("Hall de Entrada");
    
    // nível 1: salas conectadas ao Hall
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Sala de Jantar");
    
    // nível 2: salas conectadas à Sala de Estar
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Escritorio");
    
    // nível 2: salas conectadas à Sala de Jantar
    hall->direita->esquerda = criarSala("Cozinha");
    hall->direita->direita = criarSala("Jardim de Inverno");
    
    // nível 3: salas mais profundas
    hall->esquerda->esquerda->esquerda = criarSala("Sala Secreta");
    hall->esquerda->direita->direita = criarSala("Quarto de Hospedes");
    hall->direita->esquerda->esquerda = criarSala("Despensa");
    hall->direita->direita->direita = criarSala("Estufa");
    
    printf("Mapa da Mansao (visualizacao hierarquica):\n");
    printf("==========================================\n");
    mostrarMapa(hall, 0);
    printf("\n");
    
    // inicia a exploração interativa da mansão
    explorarMansao(hall);
    
    // libera a memória alocada para a árvore
    liberarArvore(hall);
    
    printf("\nInvestigacao concluida! Volte sempre, Detetive.\n");
    return 0;
}

// função para criar uma nova sala dinamicamente
// parâmetro: nome - string com o nome do cômodo
// retorno: ponteiro para a sala criada
struct Sala* criarSala(const char* nome) {
    // aloca memória para uma nova sala
    struct Sala* novaSala = (struct Sala*)malloc(sizeof(struct Sala));
    
    // copia o nome para a sala
    strcpy(novaSala->nome, nome);
    
    // inicializa os ponteiros como NULL (sem conexões)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// função para explorar interativamente a mansão
// parâmetro: raiz - ponteiro para a sala inicial (Hall de Entrada)
void explorarMansao(struct Sala* raiz) {
    struct Sala* salaAtual = raiz;
    char escolha;
    
    printf("=== INICIANDO EXPLORACAO ===\n");
    printf("Voce comeca no: %s\n\n", salaAtual->nome);
    
    // loop principal de exploração
    while(1) {
        // verifica se chegou a um cômodo sem saídas (nó folha)
        if(salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf(">>> Voce chegou ao: %s\n", salaAtual->nome);
            printf("Este e um comodo sem saidas. Fim da exploracao neste caminho.\n");
            break;
        }
        
        // exibe as opções disponíveis
        printf("Voce esta no: %s\n", salaAtual->nome);
        printf("Opcoes de exploracao:\n");
        
        if(salaAtual->esquerda != NULL) {
            printf("  [e] - Ir para ESQUERDA (%s)\n", salaAtual->esquerda->nome);
        }
        
        if(salaAtual->direita != NULL) {
            printf("  [d] - Ir para DIREITA (%s)\n", salaAtual->direita->nome);
        }
        
        printf("  [s] - Sair da exploracao\n");
        
        // obtém a escolha do jogador
        printf("\nPara onde deseja ir? ");
        scanf(" %c", &escolha);
        
        // processa a escolha do jogador
        switch(escolha) {
            case 'e':
            case 'E':
                if(salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                    printf(">>> Indo para: %s\n\n", salaAtual->nome);
                } else {
                    printf("ERRO: Nao ha caminho a esquerda!\n\n");
                }
                break;
                
            case 'd':
            case 'D':
                if(salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                    printf(">>> Indo para: %s\n\n", salaAtual->nome);
                } else {
                    printf("ERRO: Nao ha caminho a direita!\n\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("Saindo da exploracao...\n");
                return;
                
            default:
                printf("Opcao invalida! Use 'e' para esquerda, 'd' para direita ou 's' para sair.\n\n");
        }
    }
}

// função para liberar a memória da árvore (pós-ordem)
// parâmetro: sala - ponteiro para a raiz da árvore/subárvore
void liberarArvore(struct Sala* sala) {
    if(sala == NULL) {
        return;
    }
    
    // libera recursivamente as subárvores esquerda e direita
    liberarArvore(sala->esquerda);
    liberarArvore(sala->direita);
    
    // libera o nó atual
    free(sala);
}

// função auxiliar para mostrar a estrutura da árvore
// parâmetro: sala - ponteiro para a sala atual
// parâmetro: nivel - nível atual na hierarquia (para indentação)
void mostrarMapa(struct Sala* sala, int nivel) {
    if(sala == NULL) {
        return;
    }
    
    // indenta de acordo com o nível
    for(int i = 0; i < nivel; i++) {
        printf("  ");
    }
    
    // mostra a sala atual
    printf("|- %s\n", sala->nome);
    
    // Mmostra recursivamente as salas à esquerda e direita
    mostrarMapa(sala->esquerda, nivel + 1);
    mostrarMapa(sala->direita, nivel + 1);
}