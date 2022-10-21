/*ESQUELETO PARA UM JOGO DE LABIRINTO UTILIZANDO RECURSOS APRENDIDOS EM AULA
OBS: O programa tem melhorias �bvias considerando os conte�dos vistos em aula
- Por exemplo, o arquivo n�o � atualizado no final da execu��o
Enunciado da atividade feita em aula:
Fa�a um programa que l� um arquivo com indica��es de espa�o livre(0), barreira(1), personagem(2)
O jogo deve ter uma fun��o que permite o movimento do personagem pelas posi��es livres sem deixar rastro
*/
#include <iostream>
#include <fstream>
#include <conio.h> //getch()
#include <windows.h> ///remover
#include <locale.h>
#include <chrono>
#include <iomanip>
#include <time.h>

using namespace std;
using namespace chrono;

struct PLAYER {
    int x,y;

    void coord (int li, int co){
        x=li;
        y=co;
    }
};

struct ARQUIVO {
    char* nome;
    int x, y;
    int** m;


    void tam(int li, int co){
        x=li;
        y=co;
    }


    void carrega (){
        m = new int*[x];
        for (int i=0; i<x; i++){
            m[i]=new int[y];
        }

        ifstream tela;
        tela.open(nome);
        char c;

        ///coloca na matriz o mapa
        for(int i=0; i<28;i++){
            for(int j=0; j<38;j++){
                    tela>>c;
                    m[i][j]=c-48;
            }
        }
        tela.close();
    }

};
void mostrarCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void colorir (int cor) {

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(out, cor);
}
void posicaoxy( int column, int line )
    {
        COORD coord;
        coord.X = column;
        coord.Y = line;
        SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
    }

void mostra_mapa (ARQUIVO a, PLAYER p1, PLAYER p2, int v1=0, int v2=0) {
    posicaoxy(0,0);
    cout << "Jogador 1:          Jogador 2:";
    int li=1;
    for (int i=p1.x-2+v1; i<p1.x+3-v1; i++){
        posicaoxy(0+v1,li+v1);
        for (int j=p1.y-3+v1; j<p1.y+4-v1; j++){
            switch(a.m[i][j]){
            case 0: cout<<" "; break;
            case 1: cout<<char(219); break;
            case 2: cout<<char(1); break;
            case 3: cout<<char(1); break;
            case 4: cout<<char(3); break;
            case 5: cout<<char(5); break;
            case 6: cout<<char(6); break;
            default: cout<<" "; break;
            }
        }
        li++;
    }
    li=1;
    for (int i=p2.x+5-(2*v2); i>p2.x-6+(2*v2); i--){
        posicaoxy(20+(3*v2),li+(2*v2));
        for (int j=p2.y+7-(3*v2); j>p2.y-8+(3*v2); j--){
            switch(a.m[i][j]){
            case 0: cout<<" "; break;
            case 1: cout<<char(219); break;
            case 2: cout<<char(1); break;
            case 3: cout<<char(1); break;
            case 4: cout<<char(3); break;
            case 5: cout<<char(5); break;
            case 6: cout<<char(6); break;
            default: cout<<" "; break;
            }
        }
        li++;
    }

}

void campo(PLAYER p1, ARQUIVO mapa, int &jogo){
    for (int i=p1.x-2; i<p1.x+3; i++){
        for (int j=p1.y-3; j<p1.y+4; j++){
            if(mapa.m[i][j]==3){
                jogo = 1;
                Sleep(1000);
                system("pause");
                system("cls");
            }
        }
    }
}

void mover1 (PLAYER &p1, ARQUIVO &mapa, int &jogo, steady_clock::time_point &t3, steady_clock::time_point &t5){
    char tecla;
    if(kbhit()){
        tecla = getch();
        switch (tecla){
        case 'w':
            if(mapa.m[p1.x-1][p1.y]==0){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x-1][p1.y]=2;
                p1.x=p1.x-1;
            }
            else if(mapa.m[p1.x-1][p1.y]==4){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x-1][p1.y]=2;
                p1.x=p1.x-1;
                t3 = steady_clock::now();
                system("cls");
            }
            else if(mapa.m[p1.x-1][p1.y]==6){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x-1][p1.y]=2;
                p1.x=p1.x-1;
                t5 = steady_clock::now();
            }
            else if(mapa.m[p1.x-1][p1.y]==5){
                mapa.m[p1.x][p1.y]=0;
                do{
                    p1.x = rand()%18 + 6;
                    p1.y = rand()%28 + 5;
                }while(mapa.m[p1.x][p1.y]!=0);
                mapa.m[p1.x][p1.y]=2;
            }
            break;
        case 's':
             if(mapa.m[p1.x+1][p1.y]==0){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x+1][p1.y]=2;
                p1.x=p1.x+1;
            }
            else if(mapa.m[p1.x+1][p1.y]==4){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x+1][p1.y]=2;
                p1.x=p1.x+1;
                t3 = steady_clock::now();
                system("cls");
            }
            else if(mapa.m[p1.x+1][p1.y]==6){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x+1][p1.y]=2;
                p1.x=p1.x+1;
                t5 = steady_clock::now();
            }
            else if(mapa.m[p1.x+1][p1.y]==5){
                mapa.m[p1.x][p1.y]=0;
                do{
                    p1.x = rand()%18 + 6;
                    p1.y = rand()%28 + 5;
                }while(mapa.m[p1.x][p1.y]!=0);
                mapa.m[p1.x][p1.y]=2;
            }
            break;
        case 'a':
            if(mapa.m[p1.x][p1.y-1]==0){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x][p1.y-1]=2;
                p1.y=p1.y-1;
            }
            else if(mapa.m[p1.x][p1.y-1]==4){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x][p1.y-1]=2;
                p1.y=p1.y-1;
                t3 = steady_clock::now();
                system("cls");
            }
            else if(mapa.m[p1.x][p1.y-1]==6){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x][p1.y-1]=2;
                p1.y=p1.y-1;
                t5 = steady_clock::now();
            }
            else if(mapa.m[p1.x][p1.y-1]==5){
                mapa.m[p1.x][p1.y]=0;
                do{
                    p1.x = rand()%18 + 6;
                    p1.y = rand()%28 + 5;
                }while(mapa.m[p1.x][p1.y]!=0);
                mapa.m[p1.x][p1.y]=2;
            }
            break;
        case 'd':
            if(mapa.m[p1.x][p1.y+1]==0){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x][p1.y+1]=2;
                p1.y=p1.y+1;
            }
            else if(mapa.m[p1.x][p1.y+1]==4){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x][p1.y+1]=2;
                p1.y=p1.y+1;
                t3 = steady_clock::now();
                system("cls");
            }
            else if(mapa.m[p1.x][p1.y+1]==6){
                mapa.m[p1.x][p1.y]=0;
                mapa.m[p1.x][p1.y+1]=2;
                p1.y=p1.y+1;
                t5 = steady_clock::now();
            }
            else if(mapa.m[p1.x][p1.y+1]==5){
                mapa.m[p1.x][p1.y]=0;
                do{
                    p1.x = rand()%18 + 6;
                    p1.y = rand()%28 + 5;
                }while(mapa.m[p1.x][p1.y]!=0);
                mapa.m[p1.x][p1.y]=2;
            }
            break;
            case 'p':
                jogo = 3;
            break;
        }
    }
}

void mover2 (PLAYER &p2, ARQUIVO &mapa, int &jogo, steady_clock::time_point &t4, steady_clock::time_point &t6){
    int tecla;
    if(kbhit()){
        tecla = getch();
        switch (tecla){
        case 80:
            if(mapa.m[p2.x-1][p2.y]==0){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x-1][p2.y]=3;
                p2.x=p2.x-1;
            }
            else if(mapa.m[p2.x-1][p2.y]==4){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x-1][p2.y]=3;
                p2.x=p2.x-1;
                t4 = steady_clock::now();
                system("cls");
            }
            else if(mapa.m[p2.x-1][p2.y]==6){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x-1][p2.y]=3;
                p2.x=p2.x-1;
                t6 = steady_clock::now();
            }
            else if(mapa.m[p2.x-1][p2.y]==5){
                mapa.m[p2.x][p2.y]=0;
                do{
                    p2.x = rand()%18 + 6;
                    p2.y = rand()%28 + 5;
                }while(mapa.m[p2.x][p2.y]!=0);
                mapa.m[p2.x][p2.y]=3;
            }
            break;
        case 72:
             if(mapa.m[p2.x+1][p2.y]==0){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x+1][p2.y]=3;
                p2.x=p2.x+1;
            }
            else if(mapa.m[p2.x+1][p2.y]==4){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x+1][p2.y]=3;
                p2.x=p2.x+1;
                t4 = steady_clock::now();
                system("cls");
            }
            else if(mapa.m[p2.x+1][p2.y]==6){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x+1][p2.y]=3;
                p2.x=p2.x+1;
            }
            else if(mapa.m[p2.x+1][p2.y]==5){
                mapa.m[p2.x][p2.y]=0;
                do{
                    p2.x = rand()%18 + 6;
                    p2.y = rand()%28 + 5;
                }while(mapa.m[p2.x][p2.y]!=0);
                mapa.m[p2.x][p2.y]=3;
            }
            break;
        case 77:
            if(mapa.m[p2.x][p2.y-1]==0){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x][p2.y-1]=3;
                p2.y=p2.y-1;
            }
            else if(mapa.m[p2.x][p2.y-1]==4){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x][p2.y-1]=3;
                p2.y=p2.y-1;
                t4 = steady_clock::now();
                system("cls");

            }
            else if(mapa.m[p2.x][p2.y-1]==6){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x][p2.y-1]=3;
                p2.y=p2.y-1;
                t6 = steady_clock::now();

            }
            else if(mapa.m[p2.x][p2.y-1]==5){
                mapa.m[p2.x][p2.y]=0;
                do{
                    p2.x = rand()%18 + 6;
                    p2.y = rand()%28 + 5;
                }while(mapa.m[p2.x][p2.y]!=0);
                mapa.m[p2.x][p2.y]=3;
            }
            break;
        case 75:
            if(mapa.m[p2.x][p2.y+1]==0){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x][p2.y+1]=3;
                p2.y=p2.y+1;
            }
            else if(mapa.m[p2.x][p2.y+1]==4){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x][p2.y+1]=3;
                p2.y=p2.y+1;
                t4 = steady_clock::now();
                system("cls");
            }
            else if(mapa.m[p2.x][p2.y+1]==6){
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x][p2.y+1]=3;
                p2.y=p2.y+1;
                t6 = steady_clock::now();
            }
            else if(mapa.m[p2.x][p2.y+1]==5){
                mapa.m[p2.x][p2.y]=0;
                do{
                    p2.x = rand()%18 + 6;
                    p2.y = rand()%28 + 5;
                }while(mapa.m[p2.x][p2.y]!=0);
                mapa.m[p2.x][p2.y]=3;
            }
            break;
        case 'p':
                jogo = 3;
            break;
        }
    }
}

void fim(){
    cout << "Fim de jogo!!\n\n";
    system("pause");
    system("cls");
}

void visao(int &v, steady_clock::time_point t2, steady_clock::time_point t1){
    duration<double> tempo = duration_cast<duration<double>>(t2-t1);
    if(tempo.count() >= 0 && tempo.count() < 5){
        v = 1;
    }
    else{
        v=0;
    }
}

void jogar(PLAYER &p1, PLAYER &p2, ARQUIVO &mapa, int &jogo, duration<double> &tempo, bool &cont){
    steady_clock::time_point t1 = steady_clock::now();
    steady_clock::time_point t2 = steady_clock::now();
    steady_clock::time_point t3, t4, t5, t6;
    int static v1=0, v2=0;
    duration<double> static tempo2, tempo3;
    duration<double> static s_tempo = duration_cast<duration<double>>(t2-t1);
    while (jogo == 0){
        t2 = steady_clock::now();
        visao(v2, t2, t3);
        visao(v1, t2, t4);
        tempo = duration_cast<duration<double>>(t2-t1) + s_tempo;
        tempo2 = duration_cast<duration<double>>(t2-t5);
        tempo3 = duration_cast<duration<double>>(t2-t6);
        mostra_mapa(mapa, p1, p2, v1, v2);
        campo(p1, mapa, jogo);
        if(tempo3.count() > 0 && tempo3.count() < 5){

        }else{
            mover1(p1, mapa, jogo, t3, t5);
        }
        if(tempo2.count() > 0 && tempo2.count() < 5){

        }else{
            mover2(p2, mapa, jogo, t4, t6);
        }
        posicaoxy(40,0);
        cout << fixed << setprecision(2);
        cout << tempo.count() << " Segundos";
    }
    s_tempo = tempo;

    if(jogo == 1){
        system("cls");
        cout << "JOGADOR 1 VENCEU!!!\n\n";
        cout << "TEMPO NECESSARIO: " << tempo.count() << "\n\n";
        system("pause");
        system("cls");
        cont = false;
        t1 = steady_clock::now();
        t2 = steady_clock::now();
        s_tempo = duration_cast<duration<double>>(t2-t1);
    }
    else if(jogo == 2){
        system("cls");
        cout << "JOGADOR 2 VENCEU!!!\n\n";
        cout << "TEMPO NECESSARIO: " << tempo.count() << "\n\n";
        system("pause");
        system("cls");
        cont = false;
        t1 = steady_clock::now();
        t2 = steady_clock::now();
        s_tempo = duration_cast<duration<double>>(t2-t1);
    }
}

void escrever(int LinhaI, int LinhaF,int escolha=0){
    string linha;
    fstream menu;
    menu.open("menu.txt");
    for(int i=0; i<LinhaF; i++)
    {
        getline(menu, linha);
        if(i >= LinhaI){
            cout << linha << endl;
        }
    }
    menu.close();
}

void salvar(double ranking[], PLAYER p1, PLAYER p2, ARQUIVO mapa, bool cont){
    fstream save;
    save.open("save.txt");
    for(int i=0; i<5; i++){
        save << ranking[i];
        save << " ";
    }
    save << "\n";
    for(int i=0; i<24; i++){
        for(int j=0; j<38; j++){
            save << mapa.m[i][j];
        }
        save << "\n";
    }
    save << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << cont;
    save.close();
    cout << "Salvamento realizado com sucesso!!\n";
    Sleep(2000);
    system("cls");
}

void carregar(double ranking[], PLAYER &p1, PLAYER &p2, ARQUIVO &mapa, bool &cont){
    fstream save;
    save.open("save.txt");
    string load;
    char c;
    for(int i=0; i<5; i++){
        save >> ranking[i];
    }
    for(int i=0; i<24;i++){
        for(int j=0; j<38;j++){
            save>>c;
            mapa.m[i][j]=c-48;
        }
    }
    save >> p1.x;
    save >> p1.y;
    save >> p2.x;
    save >> p2.y;
    save >> cont;
    save.close();
    cout << "Carregamento realizado com sucesso!!\n";
    Sleep(2000);
    system("cls");
}

int conf_rank(double ranking[], duration<double> tempo){
    for(int i=0; i<5; i++){
        if(tempo.count() < ranking[i] || ranking[i] == 0){
            for(int j=3; j>=i; j--){
                ranking[j+1] = ranking[j];
            }
        ranking[i] = tempo.count();
        return 0;
        }
    }
}

void menu(PLAYER &p1, PLAYER &p2, ARQUIVO &mapa, double ranking[]){
    string linha;
    duration<double> tempo;
    bool static cont = false;
    int escolha, jogo=0;
    escrever(0,15);
    cin >> escolha;
    system("cls");
    switch(escolha){
    case 1:
        cont = true;
        mapa.carrega();
        p1.coord(8,9);
        p2.coord(21,28);
        cout << "O Jogo ira comecar!!!\n\n";
        Sleep(1300);
        system("cls");
        jogar(p1, p2, mapa, jogo, tempo, cont);
        if(jogo == 3){
            system("cls");
            menu(p1, p2, mapa, ranking);
        }
        conf_rank(ranking, tempo);
        menu(p1, p2, mapa, ranking);
        break;
    case 2:
        if(cont == false){
            cout << "Nenhum jogo para continuar!!\n\n";
            Sleep(1500);
            system("cls");
        }
        else{
            cout << "O Jogo ira continuar!!!\n\n";
            Sleep(1300);
            system("cls");
            jogar(p1, p2, mapa, jogo, tempo, cont);
            if(jogo == 3){
                system("cls");
                menu(p1, p2, mapa, ranking);
            }
            conf_rank(ranking, tempo);
        }
        menu(p1, p2, mapa, ranking);
        break;
    case 3:
        salvar(ranking, p1, p2, mapa, cont);
        menu(p1, p2, mapa, ranking);
        break;
    case 4:
        carregar(ranking, p1, p2, mapa, cont);
        menu(p1, p2, mapa, ranking);
        break;
    case 5:
        cout << "RANKING:\n\n";
        for(int i=0; i<5; i++){
            cout << ranking[i] << endl;
        }
        cout << endl;
        system("pause");
        system("cls");
        menu(p1, p2, mapa, ranking);
        break;
    case 6:
        jogo = 4;
        break;
    }
}

int main()
{
    mostrarCursor(false);

    srand(time(NULL));

    PLAYER p1, p2;

    ARQUIVO mapa;
    mapa.nome="labirinto.txt";
    mapa.tam(30,46);
    mapa.carrega();

    double *ranking = new double[5];
    for(int i=0; i<5; i++){
        ranking[i] = 0;
    }

    menu(p1, p2, mapa, ranking);

    fim();


    return 0;
}
