#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define TOTAL_NIVEIS 3
#define PERGUNTAS_POR_NIVEL 5
#define MAX_NOME 50

typedef struct {
    char enunciado[200];
    char opcoes[4][100];
    char correta; // 'A', 'B', 'C', 'D'
} Pergunta;

// Perguntas por nível
Pergunta niveis[TOTAL_NIVEIS][PERGUNTAS_POR_NIVEL] = {
    {
        {"Qual é a capital de França?", {"A) Madrid", "B) Roma", "C) Paris", "D) Berlim"}, 'C'},
        {"Quanto é 2 + 2?", {"A) 3", "B) 4", "C) 5", "D) 22"}, 'B'},
        {"Qual é a cor do céu num dia claro?", {"A) Azul", "B) Vermelho", "C) Cinzento", "D) Verde"}, 'A'},
        {"Quantos dias tem uma semana?", {"A) 5", "B) 6", "C) 7", "D) 8"}, 'C'},
        {"Que animal é conhecido como o rei da selva?", {"A) Elefante", "B) Leão", "C) Tigre", "D) Gato"}, 'B'}
    },
    {
        {"Quanto é 5 x 6?", {"A) 30", "B) 11", "C) 56", "D) 60"}, 'A'},
        {"Qual o menor planeta do sistema solar?", {"A) Marte", "B) Vênus", "C) Mercúrio", "D) Plutão"}, 'C'},
        {"Quem escreveu 'Dom Quixote'?", {"A) Camões", "B) Cervantes", "C) Shakespeare", "D) Pessoa"}, 'B'},
        {"Qual a capital de Angola?", {"A) Lubango", "B) Huambo", "C) Luanda", "D) Namibe"}, 'C'},
        {"Qual o resultado de 10 / 2?", {"A) 2", "B) 10", "C) 5", "D) 8"}, 'C'}
    },
    {
        {"Em que continente está o Egito?", {"A) Europa", "B) Ásia", "C) África", "D) América"}, 'C'},
        {"Qual é o símbolo químico da água?", {"A) H", "B) O2", "C) CO2", "D) H2O"}, 'D'},
        {"Quem descobriu o Brasil?", {"A) Cabral", "B) Colombo", "C) Vasco da Gama", "D) Américo Vespúcio"}, 'A'},
        {"Quantos segundos tem um minuto?", {"A) 100", "B) 60", "C) 30", "D) 90"}, 'B'},
        {"Qual é a moeda oficial de Angola?", {"A) Real", "B) Euro", "C) Kwanza", "D) Dólar"}, 'C'}
    }
};

int main() {
    setlocale(LC_ALL, "portuguese"); // Configura o locale para português
    char nome[MAX_NOME];
    int idade;
    char jogar_novamente;

    // Cadastro
    printf("=== CADASTRO INICIAL ===\n");
    printf("Digite seu nome: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' do final

    printf("Digite sua idade: ");
    scanf("%d", &idade);
    getchar(); // Limpa o buffer do teclado

    if (idade <= 12) {
        printf("Desculpe %s, você precisa ter mais de 12 anos para jogar.\n", nome);
        return 0;
    }

    // Loop principal do jogo
    do {
        int pontuacao = 0;
        int tentativas = 3;
        int perdeu = 0;

        printf("\n=== Bem-vindo ao Quiz, %s! ===\n", nome);

        for (int nivel = 0; nivel < TOTAL_NIVEIS; nivel++) {
            printf("\n--- Nível %d ---\n", nivel + 1);

            for (int i = 0; i < PERGUNTAS_POR_NIVEL && tentativas > 0; i++) {
                Pergunta p = niveis[nivel][i];

                printf("\n%s\n", p.enunciado);
                for (int j = 0; j < 4; j++) {
                    printf("%s\n", p.opcoes[j]);
                }

                printf("Sua resposta (A, B, C ou D): ");
                char resposta_usuario;
                scanf(" %c", &resposta_usuario);
                resposta_usuario = toupper(resposta_usuario);

                if (resposta_usuario == p.correta) {
                    printf("Resposta correta!\n");
                    pontuacao += 10;
                } else {
                    printf("Resposta errada. A correta era: %c\n", p.correta);
                    pontuacao -= 5;
                    tentativas--;
                    if (tentativas > 0) {
                        printf("Tentativas restantes: %d\n", tentativas);
                    } else {
                        printf("Você esgotou todas as tentativas. Fim do jogo!\n");
                        perdeu = 1;
                        break;
                    }
                }
            }

            if (perdeu) break;
            else if (nivel < TOTAL_NIVEIS - 1) {
                printf("Parabéns, %s! Você passou para o próximo nível!\n", nome);
            }
        }

        printf("\nPontuação final de %s: %d\n", nome, pontuacao);
        if (!perdeu) {
            printf("Parabéns %s! Você completou todos os níveis!\n", nome);
        }

        printf("\nDeseja jogar novamente? (s/n): ");
        scanf(" %c", &jogar_novamente);
        getchar(); // Limpa o buffer novamente

    } while (jogar_novamente == 's' || jogar_novamente == 'S');

    printf("Obrigado por jogar, %s! Até a próxima!\n", nome);
    return 0;
}
