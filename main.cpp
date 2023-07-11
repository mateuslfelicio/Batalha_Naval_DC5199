#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale.h>
#define M 12
#if defined(_WIN32)
    #define Plataforma 'w'
#elif defined(_WIN64)
    #define Plataforma 'w'
#elif defined(__linux__)
    #define Plataforma 'l'
#endif
#define RESET "\x1b[0m"
#define PRETO "\x1b[30m"
#define VERDE "\x1b[32m"
#define FBRANCO "\x1b[47m"
#define VERMELHO "\x1b[91m"
#define VERDEC "\x1b[92m"
#define AZUL "\x1b[94m"
#define AZULC "\x1b[96m"
#define FCINZA "\x1b[100m"

using namespace std;

void limpa()
{ //limpar o console
    if(Plataforma == 'w')
                system("cls");
            else
                system("clear");
}

void pausa()
{ //pausa o programa
    cout << "Pressione [enter] para prosseguir!";
    cin.get();
    limpa();
}

int verifica_em_volta (char tabuleiro[M][M], int linha, int coluna)
{ //verifica se existe outra embarcação em volta de um ponto (auxiliar para a verifica_embarcacao)
    int cont =0;
    for(int i = (linha-1); i<= (linha+1); i++){
        for(int j = (coluna - 1); j <= (coluna+1); j++){
            if((tabuleiro[i][j] == 'X' or tabuleiro[i][j] == '#') and (i != linha or j != coluna))
                cont++;
        }
    }
    return cont;
}

void altera_destruidos(char tabuleiro[M][M], int linha, int coluna, int l1, int c1, int l2, int c2, int l3, int c3)
{
    tabuleiro[linha][coluna] = tabuleiro[l1][c1] = tabuleiro[l2][c2] = tabuleiro[l3][c3] = '=';
}

int verifica_embarcacao(char tabuleiroB[M][M],char tabuleiro[M][M], int linha, int coluna, int naviosD[4])
{ //verificar o tipo de embarcação atingida e retornar o modificador de pontos de acordo com tal tipo
    int l1 =0, c1 = 0, l2 = 0, c2 = 0, l3 = 0, c3 = 0, cont1 = 0, cont2 = 0, cont3 = 0;
    cont1 = verifica_em_volta(tabuleiro,linha,coluna);
    if (cont1 == 1){ //verifica se existem trechos da embarcação ao redor do local atingido
        for(int i = linha-1; i <= linha+1; i++){
            for(int j = coluna-1; j <= coluna+1; j++){
                if((tabuleiro[i][j]=='X' or tabuleiro[i][j]=='#') and (i != linha or j != coluna)){ //salva a coordenada caso ache trecho de embarcação
                    l1 = i;
                    c1 = j;
                    break;
                }
            }
        }
        cont2 = verifica_em_volta(tabuleiro,l1,c1); //verifica se existem mais trechos de embarcação(barcos tamanho dois, três ou quatro)
        if (cont2 == 2){
            for(int i = l1-1; i <= l1+1; i++){
                for(int j = c1-1; j <= c1+1; j++){
                    if((tabuleiro[i][j]=='X' or tabuleiro[i][j]=='#') and (i != l1 or j != c1) and (i != linha or j != coluna)){
                        l2 = i;
                        c2 = j;
                        break;
                    }
                }
            }
        }
        cont3 = verifica_em_volta(tabuleiro,l2,c2); //verifica se existem mais trechos de embarcação(barcos tamanho três ou quatro)
        if (cont3 == 2){
            for(int i = l2-1; i <= l2+1; i++){
                for(int j = c2-1; j <= c2+1; j++){
                    if((tabuleiro[i][j]=='X' or tabuleiro[i][j]=='#') and (i != l1 or j != c1) and (i != l2 or j != c2)){
                        l3 = i;
                        c3 = j;
                        break;
                    }
                }
            }
        }
    }
    if(cont1 == 0){ //caso não haja pedaços de embarcação ao redor retorna imediatamente
        cout <<  VERDE << " Você destruiu um barco!" << RESET << endl;
        naviosD[3]++;
        altera_destruidos(tabuleiroB,linha,coluna,l1,c1,l2,c2,l3,c3);
        return 4; //destruir tamanho 1 = 10 pts
    }
    if(cont1 == 2){ //mesma verificação realizada anteriormente porem para outra configuração de posições da embarcação
        for(int i = linha-1; i <= linha+1; i++){
            for(int j = coluna-1; j <= coluna+1; j++){
                if((tabuleiro[i][j]=='X' or tabuleiro[i][j]=='#') and (i != linha or j != coluna)){
                    cont1++;
                    l1 = i;
                    c1 = j;
                    break;
                }
            }
        }
        for(int i = linha-1; i <= linha+1; i++){
            for(int j = coluna-1; j <= coluna+1; j++){
                if((tabuleiro[i][j]=='X' or tabuleiro[i][j]=='#') and (i != l1 or j != c1) and (i != linha or j != coluna)){
                    l2 = i;
                    c2 = j;
                    break;
                }
            }
        }
        cont2 = verifica_em_volta(tabuleiro,l1,c1);
        if (cont2 == 2){ //verifica se existem mais trechos de embarcação(barcos tamanho quatro)
            for(int i = l1-1; i <= l1+1; i++){
                for(int j = c1-1; j <= c1+1; j++){
                    if((tabuleiro[i][j]=='X' or tabuleiro[i][j]=='#') and (i != l1 or j != c1) and (i != linha or j != coluna)){
                        l3 = i;
                        c3 = j;
                        break;
                    }
                }
            }
        }
        cont3 = verifica_em_volta(tabuleiro,l2,c2);
        if (cont3 == 2){ //verifica se existem mais trechos de embarcação(barcos tamanho quatro)(configuração de posição diferente)
            for(int i = l2-1; i <= l2+1; i++){
                for(int j = c2-1; j <= c2+1; j++){
                    if((tabuleiro[i][j]=='X' or tabuleiro[i][j]=='#') and (i != linha or j != coluna) and (i != l2 or j != c2)){
                        l3 = i;
                        c3 = j;
                        break;
                    }
                }
            }
        }
    }
    if(l2 !=0 and c2 !=0 and l3 !=0 and c3 !=0){
        if(tabuleiro[linha][coluna] == tabuleiro[l1][c1] and tabuleiro[linha][coluna] == tabuleiro[l2][c2] and tabuleiro[linha][coluna] == tabuleiro[l3][c3]){
            cout <<  VERDE << " Você destruiu um barco!" << RESET << endl;
            naviosD[0]++;
            altera_destruidos(tabuleiroB,linha,coluna,l1,c1,l2,c2,l3,c3);
            return 3; //destruir totalmente tamanho 4 = 15 pts
        }
        if(tabuleiro[linha][coluna] != tabuleiro[l1][c1] and tabuleiro[linha][coluna] != tabuleiro[l2][c2] and tabuleiro[linha][coluna] != tabuleiro[l3][c3]){
            return 2; //detruir primeira parte barco 4 = 10 pts
        }
        else{
            return 1; //detruir parcialmente barco 4 = 5 pts
        }
    }

    if(l2 !=0 and c2 !=0){
        if(tabuleiro[linha][coluna] == tabuleiro[l1][c1] and tabuleiro[linha][coluna] == tabuleiro[l2][c2]){
            cout <<  VERDE << " Você destruiu um barco!" << RESET << endl;
            naviosD[1]++;
            altera_destruidos(tabuleiroB,linha,coluna,l1,c1,l2,c2,l3,c3);
            return 3; //destruir totalmente tamanho 3 = 15 pts
        }
        else{
            if(tabuleiro[linha][coluna] != tabuleiro[l1][c1] && tabuleiro[linha][coluna] != tabuleiro[l2][c2]){
                return 2; //detruir primeira parte barco 3 = 10 pts
            }
            else{
                return 1; //detruir parcialmente barco 3 = 5 pts
            }
        }
    }
    else{
        if(tabuleiro[linha][coluna] == tabuleiro[l1][c1]){
            cout <<  VERDE << " Você destruiu um barco!" << RESET << endl;
            naviosD[2]++;
            altera_destruidos(tabuleiroB,linha,coluna,l1,c1,l2,c2,l3,c3);
            return 3; //destruir totalmente tamanho 2 = 15 pts
        }
        else{
            return 2; //detruir primeira parte barco 2 = 10 pts
        }
    }
}

void imprimetabuleiro(char tabuleiro[M][M])
{ //imprimir o tabuleiro
    cout << FBRANCO; //troca a cor do plano de fundo
    cout << PRETO << "   ";
    for(int i = 1; i < 11; i++){
        cout << PRETO  << " " << i;
    }
    cout << endl;
    for(int i = 1; i < 11; i++){
        cout << FBRANCO;
        if (i<10){
            cout << PRETO  << i << " | ";
        }
        else{
            cout << PRETO  << i << "| ";
        }
        for(int j = 1; j < 11; j++){
        if(tabuleiro[i][j] == '-' or tabuleiro[i][j] == 'O')
            cout << AZUL << FBRANCO << tabuleiro[i][j] << " ";
        else
            cout << VERMELHO  << FBRANCO << tabuleiro[i][j] << " ";
        }
        cout << RESET << endl;
    }
    cout << endl;
}

void preenche_tabuleiro( char tabuleiro[M][M])
{ //preencher o tabuleiro com "espaços vazios"
    for(int i = 0; i < M; i++){
        for(int j = 0; j < M; j++){
            tabuleiro[i][j] = '-';
        }
    }
}

int preenche_embarcacao( char tabuleiro[M][M], int linha, int coluna, int direcao, int tamanho)
{ //distribuir cada barco no tabuleiro
    if (direcao == 0){ //verifica a direção(horizontal)
        if((tamanho+coluna)>=11){ //verifica se o barco cabe no tabuleiro (margens)
            return 0;
        }
        for(int i = (coluna - 1); i <= (coluna+tamanho); i++){ //verifica se há espaço disponível para o barco
            if(tabuleiro[linha - 1][i] != '-' or tabuleiro[linha][i] != '-' or tabuleiro[linha + 1][i] != '-')
            {
                return 0;
            }
        }
        for(int i = coluna; i<(coluna+tamanho); i++){ //se houver espaço distribui a embarcação
            tabuleiro[linha][i] = 'X';
        }
    }
    if (direcao == 1){ //verifica a direção(vertical)
        if((tamanho+linha)>=11){ //verifica se o barco cabe no tabuleiro (margens)
            return 0;
        }
        for(int i = (linha-1); i <= (linha+tamanho); i++){ //verifica se há espaço disponível para o barco
            if(tabuleiro[i][coluna - 1] != '-' or tabuleiro[i][coluna] != '-' or tabuleiro[i][coluna + 1] != '-')
            {
                return 0;
            }
        }
        for(int i = linha; i<(linha+tamanho); i++){ //se houver espaço distribui a embarcação
            tabuleiro[i][coluna] = 'X';
        }
    }
    return 1;
}

void distribui_barcos(char tabuleiro[M][M], int tamanho,int num_emb)
{ //randomiza a posição dos barcos no tabuleiro
    int linha, coluna, direcao, aux = 0;
    while(num_emb > 0){
        linha = rand()%10+1;
        coluna = rand()%10+1;
        direcao = rand()%2;
        aux = preenche_embarcacao(tabuleiro, linha, coluna, direcao, tamanho);
        if(aux == 1){ //caso seja bem sucedido em posicionar o barco atualiza o contador
            num_emb--;
        }
    }
}

void distribui(char tabuleiro[M][M], int dificuldade, int navio[4])
{ //controle da distribuição de barcos(quantidade de barcos de acordo com a dificuldade)
    preenche_tabuleiro(tabuleiro);
    if(dificuldade == 0){
        navio[0] = 1;
        navio[1] = 3;
        navio[2] = 4;
        navio[3] = 2;
    }
    if(dificuldade == 1){
        navio[0] = 1;
        navio[1] = 2;
        navio[2] = 3;
        navio[3] = 4;
    }
    if(dificuldade == 2){
        navio[0] = 0;
        navio[1] = 1;
        navio[2] = 3;
        navio[3] = 5;
    }
    distribui_barcos(tabuleiro,4,navio[0]);
    distribui_barcos(tabuleiro,3,navio[1]);
    distribui_barcos(tabuleiro,2,navio[2]);
    distribui_barcos(tabuleiro,1,navio[3]);
}

int jogada(char tabuleiroJ[M][M], char tabuleiroB[M][M], int jogadas, int naviosD[4])
{ //realiza a jogada e retorna os pontos a cada jogador
    int linha, coluna, pont = 1;;
    if (jogadas%2 == 0)
        cout << "Jogador 1, insira linha e coluna da coordenada que deseja bombardear!" << endl;
    else
        cout << "Jogador 2, insira linha e coluna da coordenada que deseja bombardear!" << endl;
    while(true){ //leitura da jogada (linha, coluna)
    cin >> linha;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
    }
    cin >> coluna;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
    }
    if(linha >=1 and linha <=10 and coluna >=1 and coluna <=10)
        break;
    cout << VERMELHO << "Jogada Inválida! Tente novamente!" << endl;
    }
    //verifica se a jogada é valida
    if (linha < 1 or linha > 10 or coluna < 1 or coluna > 10 or tabuleiroB[linha][coluna] == 'O' or tabuleiroB[linha][coluna] == '#'){
        while(linha < 1 or linha > 10 or coluna < 1 or coluna > 10 or tabuleiroB[linha][coluna] == 'O' or tabuleiroB[linha][coluna] == '#'){
            if(linha < 1 or linha > 10 or coluna < 1 or coluna > 10){
                cout << VERMELHO << "Jogada Inválida! Tente novamente!" << endl;
            }
            else{
                if(tabuleiroB[linha][coluna] == 'O' or tabuleiroB[linha][coluna] == '#'){
                    cout << VERMELHO << "Esta posição já foi acertada! Tente novamente!" << endl;
                }
            }
            cin >> linha;
            if(cin.fail()){
                cin.clear();
                cin.ignore();
            }
            cin >> coluna;
            if(cin.fail()){
                cin.clear();
                cin.ignore();
            }
        }
    }
    limpa();
    if(tabuleiroJ[linha][coluna] == '-'){ //verifica o tipo de acerto(agua ou embarcação)
        tabuleiroB[linha][coluna] = 'O';
        return 0;
    }
    if(tabuleiroJ[linha][coluna] == 'X'){ //verifica o tipo de acerto(agua ou embarcação)
        tabuleiroB[linha][coluna] = '#';
        tabuleiroJ[linha][coluna] = '#';
        pont = verifica_embarcacao(tabuleiroB,tabuleiroJ,linha,coluna,naviosD); //caso seja um barco retorna a pontuação de acordo com o acerto
        return 5*pont;
    }
    return 0;
}

int verifica(char tabuleiro[M][M])
{ //verifica se existem navios restantes para verificar se o jogo deve ou não progredir
    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            if (tabuleiro[i][j] == 'X'){
                return 1;
            }
        }
    }
    return 0;
}

void display_navios(int navio[4], int navioD[4])
{
    cout << PRETO << FBRANCO;
    cout << "Navios afundados: " << endl;
    cout << "Tamanho 1: " << navioD[3] << "/" <<navio[3] << "    " <<endl;
    cout << "Tamanho 2: " << navioD[2] << "/" <<navio[2] << "    " <<endl;
    cout << "Tamanho 3: " << navioD[1] << "/" <<navio[1] << "    " <<endl;
    cout << "Tamanho 4: " << navioD[0] << "/" <<navio[0] << "    " <<endl << RESET << endl;
}

int main()
{
    setlocale(LC_ALL,"Portuguese_Brazil");
    srand(time(NULL));
    int pontosJ1 = 0, pontosJ2 = 0, jogadas, jogar = 1 , dificuldade, navios[4],naviosD[4] = {0};
    char tabuleiroJ1[M][M], tabuleiroB1[M][M];
    while(jogar == 1){
        limpa();
        cout << VERDEC << FCINZA << "Pressione enter para iniciar o jogo!" << RESET << endl;
        pausa();
        cout << PRETO << FCINZA;
        cout << "------------------" << AZULC << "Bem vindo ao batalha naval!" << PRETO << "-------------------"<< endl;
        cout << "----------------------------" << VERDE << "Regras!" << PRETO <<"-----------------------------" << endl;
        cout << "------" << VERDEC << "Os barcos são gerados aleatoriamente pelo tabuleiro" <<  PRETO << "-------" <<endl;
        cout << "-------" << VERDEC << "As jogadas alternam entre o jogador 1 e jogador 2" << PRETO << "--------" << endl;
        cout << "----" << VERDEC<< "Aquele que possuir maior numero de pontos ao final ganha" << PRETO << "----" << endl;
        cout << "------" << VERDEC << "A dificuldade altera a frota de navios no tabuleiro" << PRETO << "-------" << endl;
        cout << "------" << VERDEC << "Cada tipo de acerto confere uma pontuação diferente" << PRETO << "-------" << endl;
        cout << "-----" << VERDEC << "As jogadas devem ser feitas no formato *linha* *coluna*" << PRETO << "----" << RESET << endl;
        pausa();
        cout << PRETO << FBRANCO << "Selecione a dificuldade desejada:" << endl;
        cout << "Fácil: 1                         \nMédio: 2                         \nDifícil: 3                       " << RESET << endl;
        while(true){
        cin >> dificuldade;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
        }
        if(dificuldade >=1 and dificuldade <=3)
            break;
        cout << VERMELHO <<"Dificuldade inválida! Tente novamente!" << endl;
        }
        limpa();
        distribui(tabuleiroJ1, dificuldade-1,navios);
        preenche_tabuleiro(tabuleiroB1);
        imprimetabuleiro(tabuleiroB1);
        jogadas = 0;
        while(jogadas < 100){
            pontosJ1 += jogada(tabuleiroJ1,tabuleiroB1,jogadas,naviosD);
            jogadas++;
            if (jogadas > 14)
                if (verifica(tabuleiroJ1) == 0)
                    jogadas = 100;
            imprimetabuleiro(tabuleiroB1);
            cout << "Pontuação: \nJogador 1: " << pontosJ1 << "\nJogador 2: " << pontosJ2 << endl;
            display_navios(navios,naviosD);
            pontosJ2 += jogada(tabuleiroJ1,tabuleiroB1, jogadas,naviosD);
            jogadas++;
            if (jogadas > 14)
                if (verifica(tabuleiroJ1) == 0)
                    jogadas = 100;
            imprimetabuleiro(tabuleiroB1);
            cout << "Pontuação: \nJogador 1: " << pontosJ1 << "\nJogador 2: " << pontosJ2 << endl;
            display_navios(navios,naviosD);
        }
        cout << "Pontuação: \nJogador 1: " << pontosJ1 << "\nJogador 2: " << pontosJ2 << endl << endl;
        if ( pontosJ1 > pontosJ2)
            cout << VERDE << "Jogador 1 venceu!!!" << RESET <<endl;
        else{
            if(pontosJ1 == pontosJ2)
                cout << VERDE << "Empate!" << RESET << endl;
            else
                cout << VERDE <<"Jogador 2 venceu!!!" << RESET<< endl;
        }
        cout << "Caso deseje jogar novamente digite 1!" << endl;
        cout << "Caso deseje encerrar digite 0!" << endl;
        cin >> jogar;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            jogar = 2;
        }
        while(jogar != 1 and jogar !=0){
            cout << VERMELHO << "Opção inválida! Tente novamente!" << endl;
            cin >> jogar;
            if(cin.fail()){
            cin.clear();
            cin.ignore();
            jogar = 2;
        }
        }
    }
    limpa();
    cout << VERDEC << FCINZA <<"Jogo encerrado, obrigado por jogar!" << RESET << endl;
    return 0;
}
