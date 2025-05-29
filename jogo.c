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

// Perguntas por nível - TEMÁTICA RELIGIOSA
Pergunta niveis[TOTAL_NIVEIS][PERGUNTAS_POR_NIVEL] = {
    {
        {"Quem construiu a arca para escapar do dilúvio?", {"A) Abraão", "B) Moisés", "C) Noé", "D) Davi"}, 'C'},
        {"Qual é o primeiro livro da Bíblia?", {"A) Gênesis", "B) Salmos", "C) Êxodo", "D) João"}, 'A'},
        {"Quantos mandamentos existem na lei de Deus?", {"A) 5", "B) 7", "C) 10", "D) 12"}, 'C'},
        {"Quem foi lançado na cova dos leões?", {"A) Elias", "B) Daniel", "C) Jonas", "D) Paulo"}, 'B'},
        {"Qual é o nome da mãe de Jesus?", {"A) Marta", "B) Isabel", "C) Ana", "D) Maria"}, 'D'}
    },
    {
        {"Quem guiou os israelitas na travessia do Mar Vermelho?", {"A) Josué", "B) Moisés", "C) Arão", "D) Davi"}, 'B'},
        {"Qual apóstolo negou Jesus três vezes?", {"A) João", "B) Pedro", "C) Tomé", "D) Paulo"}, 'B'},
        {"Qual era a profissão de Mateus antes de seguir Jesus?", {"A) Pescador", "B) Pastor", "C) Soldado", "D) Cobrador de impostos"}, 'D'},
        {"Em que monte Jesus foi crucificado?", {"A) Monte Sinai", "B) Monte das Oliveiras", "C) Monte Carmelo", "D) Gólgota"}, 'D'},
        {"Quantos dias Jesus ficou no deserto sendo tentado?", {"A) 10", "B) 21", "C) 40", "D) 7"}, 'C'}
    },
    {
        {"Quem teve uma visão do Apocalipse na ilha de Patmos?", {"A) Paulo", "B) Pedro", "C) João", "D) Tiago"}, 'C'},
        {"Qual rei teve um sonho com uma estátua de vários materiais?", {"A) Davi", "B) Salomão", "C) Ezequias", "D) Nabucodonosor"}, 'D'},
        {"Qual é o menor versículo da Bíblia?", {"A) 'Jesus chorou'", "B) 'Deus é amor'", "C) 'Orai sem cessar'", "D) 'Sede santos'"}, 'A'},
        {"Qual profeta desafiou os profetas de Baal no Monte Carmelo?", {"A) Isaías", "B) Jeremias", "C) Elias", "D) Ezequiel"}, 'C'},
        {"Qual apóstolo teve a visão do lençol com animais impuros?", {"A) Paulo", "B) Pedro", "C) João", "D) Tiago"}, 'B'}
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

        printf("\n=== Bem-vindo ao Quiz Bíblico, %s! ===\n", nome);

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