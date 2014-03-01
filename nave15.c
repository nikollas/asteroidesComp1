#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <time.h>

#define TRUE  1
#define FALSE 0
#define MAX 50

#define MAX_ARRAY 10
#define MAX_NOME 50

typedef struct
{
    char nome[MAX_NOME];
    int pontuacao;
} RECORDE;

typedef struct
{
    RECORDE vetor[MAX_ARRAY];
    int n;

} ARRAY;

RECORDE elemento(ARRAY *, int);
int tamanho(ARRAY *);
void insere(ARRAY *, RECORDE);

void remove_posicao(ARRAY *, int);
void imprime(ARRAY *);
void sort(ARRAY *);
void bubble_sort(RECORDE *, int);

	
	SDL_Surface* screenranking;
	SDL_Surface* fundo2 = NULL;

typedef struct _ASTEROIDE
{
	int angulo;
	SDL_Rect quad;
	int destruido;
	int tipo;
	int pos;
	float xasteroide;
	float yasteroide;
	int explosao;
	int contexplosao;
	int explosao2;

} ASTEROIDE;

typedef struct _TIRO
{
	int angletiro;
	SDL_Rect rectiro;
	int tiroativo;
	float ytiro;
	float xtiro;
} TIRO;

int tempo = 100;
ASTEROIDE asteroides[MAX];
TIRO tiros[MAX];

int colisao(SDL_Rect quad1, SDL_Rect quad2)
{
	 if(quad2.x + quad2.w < quad1.x) 
	    return 0;
	 if(quad2.x > quad1.x + quad1.w) 
	    return 0;
	 if(quad2.y + quad2.h < quad1.y) 
	    return 0;
	 if(quad2.y > quad1.y + quad1.h) 
	    return 0;

	 return 1; 
}

void destruirasteroides()
{
	int i;
	
	for(i = 0;i < MAX;i++)
	{
		asteroides[i].destruido = 1;
		asteroides[i].tipo = 1;
		asteroides[i].pos = 1;
	}
}

void criarasteroides()
{
	int i,k;
	int j = 0;

	if(tempo == 100)
	{
		for(k = 0;k < MAX;k++)
		{
			if(asteroides[k].tipo == 1)
			{
				if(asteroides[k].destruido == 0)
				{
					j++;
				}
			}
		}

		if(j<=2)
		{
			for(i = 0;i < MAX;i++)
			{
				if(asteroides[i].tipo == 1)
				{
					if(asteroides[i].destruido == 1)
					{
						asteroides[i].destruido = 0;
						asteroides[i].pos = 0;
						break;
					}
				}
			}
		}
		tempo = 0;	
	}
	tempo++;
	
}

void moveasteroides()
{
		
	int i,j;
	for(j=0;j<MAX;j++)
	{
		if(asteroides[j].destruido == 0)
		{
			srand(time(NULL));
			i = rand()%4;
	
			if(asteroides[j].pos == 0 )
			{
				if (i==0)
				{
					asteroides[j].xasteroide = -90;
					asteroides[j].yasteroide = rand()%601;
					asteroides[j].angulo = rand()%121+210;
				}
				if (i==1)
				{
					asteroides[j].xasteroide = rand()%801;
					asteroides[j].yasteroide = -90;
					asteroides[j].angulo = rand()%121+120;
				}
				if(i==2)
				{
					asteroides[j].xasteroide = 800;
					asteroides[j].yasteroide = rand()%601;
					asteroides[j].angulo = rand()%121+30;
				}
				if(i==3)
				{
					asteroides[j].xasteroide = rand()%801;
					asteroides[j].yasteroide = 600;

					if(i==0||2)
					asteroides[j].angulo = rand()%61;

					if(i==1||3)
					asteroides[j].angulo = rand()%61+300;
				}

				asteroides[j].pos = 1;
			}
	
			if(asteroides[j].explosao == 0)
			{
				asteroides[j].xasteroide-=sin(asteroides[j].angulo*M_PI/180.0)*1.5;
				asteroides[j].yasteroide-=cos(asteroides[j].angulo*M_PI/180.0)*1.5;

				asteroides[j].quad.x = (int)asteroides[j].xasteroide;
				asteroides[j].quad.y = (int)asteroides[j].yasteroide;
			}
			
		}
	}
}

int main(int argc, char** argv)
{
	char *nome_arquivo = "recordes.dat";
	FILE *p_arquivo;

	ARRAY array;
	array.n = 0;

	RECORDE reco1;

	int quit  = 0;

	SDL_Surface* fundo = NULL;
	SDL_Surface* supernave = NULL;
	SDL_Surface* nave1 = NULL;
	SDL_Surface* nave2 = NULL;
	SDL_Surface* nave3 = NULL;
	SDL_Surface* nave4 = NULL;
	SDL_Surface* nave5 = NULL;
	SDL_Surface* nave6 = NULL;
	SDL_Surface* nave7 = NULL;
	SDL_Surface* nave8 = NULL;
	SDL_Surface* nave9 = NULL;
	SDL_Surface* nave10 = NULL;
	SDL_Surface* nomenave1 = NULL;
	SDL_Surface* nomenave2 = NULL;
	SDL_Surface* nomenave3 = NULL;
	SDL_Surface* nomenave4 = NULL;
	SDL_Surface* nomenave5 = NULL;
	SDL_Surface* nomenave6 = NULL;
	SDL_Surface* nomenave7 = NULL;
	SDL_Surface* nomenave8 = NULL;
	SDL_Surface* nomenave9 = NULL;
	SDL_Surface* nomenave10 = NULL;
	SDL_Surface* bala = NULL;
	SDL_Surface* asteroide1 = NULL;
	SDL_Surface* asteroide2 = NULL;
	SDL_Surface* asteroide3 = NULL;
	SDL_Surface* screen;
	SDL_Surface* screeninicial;
	SDL_Surface* screentutorial;
	SDL_Surface* screenparticipantes;
	SDL_Surface* logo = NULL;
	SDL_Surface* fundoinicial = NULL;
	SDL_Surface* iniciar = NULL;
	SDL_Surface* tutorial = NULL;
	SDL_Surface* tutorial2 = NULL;
	SDL_Surface* participantes = NULL;
	SDL_Surface* participantes5 = NULL;
	SDL_Surface* ranking = NULL;
	SDL_Surface* seta = NULL;
	SDL_Surface* sair = NULL;
	SDL_Surface* sair1 = NULL;
	SDL_Surface* ttf;
	SDL_Surface* ttftraco;
	SDL_Surface* dignome;
	SDL_Surface* borda;
	SDL_Surface* ttfnome;
	SDL_Surface* coracao1;
	SDL_Surface* coracao2;
	SDL_Surface* coracao3;
	SDL_Surface* logotutorial = NULL;
	SDL_Surface* logoparticipantes = NULL;
	SDL_Surface* logoranking = NULL;
	SDL_Surface* rotatedimage;
	SDL_Surface* rotatednaveexplo1;
	SDL_Surface* rotatednaveexplo2;
	SDL_Surface* rotatednaveexplo3;
	SDL_Surface* rotatednaveexplo4;
	SDL_Surface* rotatednaveexplo5;
	SDL_Surface* rotatednaveexplo6;
	SDL_Surface* rotatednaveexplo7;
	SDL_Surface* rotatednaveexplo8;
	SDL_Surface* rotatednaveexplo9;
	SDL_Surface* rotatednaveexplo10;
	SDL_Surface* rotatednaveexplo11;
	SDL_Surface* rotatednaveexplo12;
	SDL_Surface* rotatednaveexplo13;
	SDL_Surface* rotatednaveexplo14;
	SDL_Surface* rotatednaveexplo15;
	SDL_Surface* rotatednaveexplo16;
	SDL_Surface* rotatednaveexplo17;
	SDL_Surface* gameover;
	SDL_Surface* play;
	SDL_Surface* pause;
	SDL_Surface* naves;
	SDL_Surface* explosao901;
	SDL_Surface* explosao902;
	SDL_Surface* explosao903;
	SDL_Surface* explosao904;
	SDL_Surface* explosao905;
	SDL_Surface* explosao906;
	SDL_Surface* explosao907;
	SDL_Surface* explosao908;
	SDL_Surface* explosao909;
	SDL_Surface* explosao9010;
	SDL_Surface* explosao9011;
	SDL_Surface* explosao9012;
	SDL_Surface* explosao9013;
	SDL_Surface* explosao9014;
	SDL_Surface* explosao9015;
	SDL_Surface* explosao9016;
	SDL_Surface* explosao9017;
	SDL_Surface* explosao601;
	SDL_Surface* explosao602;
	SDL_Surface* explosao603;
	SDL_Surface* explosao604;
	SDL_Surface* explosao605;
	SDL_Surface* explosao606;
	SDL_Surface* explosao607;
	SDL_Surface* explosao608;
	SDL_Surface* explosao609;
	SDL_Surface* explosao6010;
	SDL_Surface* explosao6011;
	SDL_Surface* explosao6012;
	SDL_Surface* explosao6013;
	SDL_Surface* explosao6014;
	SDL_Surface* explosao6015;
	SDL_Surface* explosao6016;
	SDL_Surface* explosao6017;
	SDL_Surface* explosao301;
	SDL_Surface* explosao302;
	SDL_Surface* explosao303;
	SDL_Surface* explosao304;
	SDL_Surface* explosao305;
	SDL_Surface* explosao306;
	SDL_Surface* explosao307;
	SDL_Surface* explosao308;
	SDL_Surface* explosao309;
	SDL_Surface* explosao3010;
	SDL_Surface* explosao3011;
	SDL_Surface* explosao3012;
	SDL_Surface* explosao3013;
	SDL_Surface* explosao3014;
	SDL_Surface* explosao3015;
	SDL_Surface* explosao3016;
	SDL_Surface* explosao3017;
	SDL_Surface* naveexplo1;
	SDL_Surface* naveexplo2;
	SDL_Surface* naveexplo3;
	SDL_Surface* naveexplo4;
	SDL_Surface* naveexplo5;
	SDL_Surface* naveexplo6;
	SDL_Surface* naveexplo7;
	SDL_Surface* naveexplo8;
	SDL_Surface* naveexplo9;
	SDL_Surface* naveexplo10;
	SDL_Surface* naveexplo11;
	SDL_Surface* naveexplo12;
	SDL_Surface* naveexplo13;
	SDL_Surface* naveexplo14;
	SDL_Surface* naveexplo15;
	SDL_Surface* naveexplo16;
	SDL_Surface* naveexplo17;

	srand(time(NULL));

	SDL_Init(SDL_INIT_EVERYTHING);

	if(TTF_Init() == -1)
    	{
        	return -1;
    	}

	SDL_Color cor = {255, 0, 0};

	TTF_Font *fonte;
	TTF_Font *fontenome;

	fonte = TTF_OpenFont("fonte.ttf", 25);
	fontenome = TTF_OpenFont("fonte.ttf", 40);
	//TTF_SetFontStyle(fonte, TTF_STYLE_ITALIC);

	Mix_Music *musica = NULL;
	Mix_Chunk *bomba = NULL;
	Mix_Chunk *tiro = NULL;

	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 );

	musica = Mix_LoadMUS("barracuda.mp3");
	bomba = Mix_LoadWAV("explosao.wav");
	tiro = Mix_LoadWAV("tiro.wav");

	Mix_PlayMusic( musica, -1 );

	screeninicial = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
	screentutorial = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
	screenranking = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
	screenparticipantes = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
	screen = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);

	fundo = IMG_Load( "fundo.jpeg" );
	fundo2 = IMG_Load( "fundo9.png" );

	bala = IMG_Load( "bala.png" );

	play = IMG_Load( "play.png" );
	pause = IMG_Load( "pause.png" );
	naves = IMG_Load( "naves.png" );

	asteroide1 = IMG_Load( "asteroide1.png" );
	asteroide2 = IMG_Load( "asteroide2.png" );
	asteroide3 = IMG_Load( "asteroide3.png" );

	explosao901 = IMG_Load( "1explosao1.png" );
	explosao902 = IMG_Load( "1explosao2.png" );
	explosao903 = IMG_Load( "1explosao3.png" );
	explosao904 = IMG_Load( "1explosao4.png" );
	explosao905 = IMG_Load( "1explosao5.png" );
	explosao906 = IMG_Load( "1explosao6.png" );
	explosao907 = IMG_Load( "1explosao7.png" );
	explosao908 = IMG_Load( "1explosao8.png" );
	explosao909 = IMG_Load( "1explosao9.png" );
	explosao9010 = IMG_Load( "1explosao10.png" );
	explosao9011 = IMG_Load( "1explosao11.png" );
	explosao9012 = IMG_Load( "1explosao12.png" );
	explosao9013 = IMG_Load( "1explosao13.png" );
	explosao9014 = IMG_Load( "1explosao14.png" );
	explosao9015 = IMG_Load( "1explosao15.png" );
	explosao9016 = IMG_Load( "1explosao16.png" );
	explosao9017 = IMG_Load( "1explosao17.png" );
	explosao601 = IMG_Load( "2explosao1.png" );
	explosao602 = IMG_Load( "2explosao2.png" );
	explosao603 = IMG_Load( "2explosao3.png" );
	explosao604 = IMG_Load( "2explosao4.png" );
	explosao605 = IMG_Load( "2explosao5.png" );
	explosao606 = IMG_Load( "2explosao6.png" );
	explosao607 = IMG_Load( "2explosao7.png" );
	explosao608 = IMG_Load( "2explosao8.png" );
	explosao609 = IMG_Load( "2explosao9.png" );
	explosao6010 = IMG_Load( "2explosao10.png" );
	explosao6011 = IMG_Load( "2explosao11.png" );
	explosao6012 = IMG_Load( "2explosao12.png" );
	explosao6013 = IMG_Load( "2explosao13.png" );
	explosao6014 = IMG_Load( "2explosao14.png" );
	explosao6015 = IMG_Load( "2explosao15.png" );
	explosao6016 = IMG_Load( "2explosao16.png" );
	explosao6017 = IMG_Load( "2explosao17.png" );
	explosao301 = IMG_Load( "3explosao1.png" );
	explosao302 = IMG_Load( "3explosao2.png" );
	explosao303 = IMG_Load( "3explosao3.png" );
	explosao304 = IMG_Load( "3explosao4.png" );
	explosao305 = IMG_Load( "3explosao5.png" );
	explosao306 = IMG_Load( "3explosao6.png" );
	explosao307 = IMG_Load( "3explosao7.png" );
	explosao308 = IMG_Load( "3explosao8.png" );
	explosao309 = IMG_Load( "3explosao9.png" );
	explosao3010 = IMG_Load( "3explosao10.png" );
	explosao3011 = IMG_Load( "3explosao11.png" );
	explosao3012 = IMG_Load( "3explosao12.png" );
	explosao3013 = IMG_Load( "3explosao13.png" );
	explosao3014 = IMG_Load( "3explosao14.png" );
	explosao3015 = IMG_Load( "3explosao15.png" );
	explosao3016 = IMG_Load( "3explosao16.png" );
	explosao3017 = IMG_Load( "3explosao17.png" );

	naveexplo1 = IMG_Load( "naveexplo1.png" );
	naveexplo2 = IMG_Load( "naveexplo2.png" );
	naveexplo3 = IMG_Load( "naveexplo3.png" );
	naveexplo4 = IMG_Load( "naveexplo4.png" );
	naveexplo5 = IMG_Load( "naveexplo5.png" );
	naveexplo6 = IMG_Load( "naveexplo6.png" );
	naveexplo7 = IMG_Load( "naveexplo7.png" );
	naveexplo8 = IMG_Load( "naveexplo8.png" );
	naveexplo9 = IMG_Load( "naveexplo9.png" );
	naveexplo10 = IMG_Load( "naveexplo10.png" );
	naveexplo11 = IMG_Load( "naveexplo11.png" );
	naveexplo12 = IMG_Load( "naveexplo12.png" );
	naveexplo13 = IMG_Load( "naveexplo13.png" );
	naveexplo14 = IMG_Load( "naveexplo14.png" );
	naveexplo15 = IMG_Load( "naveexplo15.png" );
	naveexplo16 = IMG_Load( "naveexplo16.png" );
	naveexplo17 = IMG_Load( "naveexplo17.png" );
	
	coracao1 = IMG_Load( "coracao1.png" );
	coracao2 = IMG_Load( "coracao2.png" );
	coracao3 = IMG_Load( "coracao3.png" );

	nave1 = IMG_Load( "1.png" );
	nave2 = IMG_Load( "2.png" );
	nave3 = IMG_Load( "3.png" );
	nave4 = IMG_Load( "4.png" );
	nave5 = IMG_Load( "5.png" );
	nave6 = IMG_Load( "6.png" );
	nave7 = IMG_Load( "7.png" );
	nave8 = IMG_Load( "8.png" );
	nave9 = IMG_Load( "9.png" );
	nave10 = IMG_Load( "10.png" );

	nomenave1 = IMG_Load( "nomenave1.png" );
	nomenave2 = IMG_Load( "nomenave2.png" );
	nomenave3 = IMG_Load( "nomenave3.png" );
	nomenave4 = IMG_Load( "nomenave4.png" );
	nomenave5 = IMG_Load( "nomenave5.png" );
	nomenave6 = IMG_Load( "nomenave6.png" );
	nomenave7 = IMG_Load( "nomenave7.png" );
	nomenave8 = IMG_Load( "nomenave8.png" );
	nomenave9 = IMG_Load( "nomenave9.png" );
	nomenave10 = IMG_Load( "nomenave10.png" );

	dignome = IMG_Load( "dignome.png" );
	gameover = IMG_Load( "gameover.png" );
	borda = IMG_Load( "borda.png" );
	logo = IMG_Load("logo.png" );
	fundoinicial = IMG_Load("fundoinicial.jpg" );
	iniciar = IMG_Load("iniciar.png" );
	tutorial = IMG_Load("tutorial.png" );
	tutorial2 = IMG_Load("tutorial1.png" );
	participantes = IMG_Load("participantes.png" );
	participantes5 = IMG_Load("participantes5.png" );
	ranking = IMG_Load("ranking.png" );
	sair = IMG_Load("sair.png");
	sair1 = IMG_Load("sair1.png");
	seta = IMG_Load("seta.png");
	logotutorial = IMG_Load("logotutorial.png" );
	logoparticipantes = IMG_Load("logoparticipantes.png" );
	logoranking = IMG_Load("logoranking.png" );	

	srand(time(NULL));

	int jogo = 0;

	SDL_Rect rec;

	SDL_Rect reccoracao;
	reccoracao.x = 20;
	reccoracao.y = 20;

	SDL_Rect recttf = {700, 20, 0, 0};

	SDL_Rect rec1;
	rec1.x = 200;
	rec1.y = 50;
	SDL_Rect rec2;
	rec2.x = 340;
	rec2.y = 200;
	SDL_Rect rec3;
	rec3.x = 340;
	rec3.y = 270;
	SDL_Rect rec4;
	rec4.x = 340;
	rec4.y = 340;
	SDL_Rect rec5;
	rec5.x = 340;
	rec5.y = 410;
	SDL_Rect rec6;
	rec6.x = 340;
	rec6.y = 480;
	SDL_Rect rec7;
	rec7.x = 290;
	rec7.y = 200;
	SDL_Rect rec11;
	rec11.x = 40;
	rec11.y = 200;
	SDL_Rect rec12;
	rec12.x = 200;
	rec12.y = 200;
	SDL_Rect rec13;
	rec13.x = 360;
	rec13.y = 200;
	SDL_Rect rec14;
	rec14.x = 520;
	rec14.y = 200;
	SDL_Rect rec15;
	rec15.x = 680;
	rec15.y = 200;
	SDL_Rect rec16;
	rec16.x = 40;
	rec16.y = 350;
	SDL_Rect rec17;
	rec17.x = 200;
	rec17.y = 350;
	SDL_Rect rec18;
	rec18.x = 360;
	rec18.y = 350;
	SDL_Rect rec19;
	rec19.x = 520;
	rec19.y = 350;
	SDL_Rect rec20;
	rec20.x = 680;
	rec20.y = 350;
	SDL_Rect recborda;
	recborda.x = 37;
	recborda.y = 197;
	SDL_Rect recplay;
	recplay.x = 0;
	recplay.y = 550;
	SDL_Rect rectuto;
	rectuto.x = 200;
	rectuto.y = 170;
	SDL_Rect recdig;
	recdig.x = 200;
	recdig.y = 340;

	SDL_Rect rec21;
	SDL_Rect rec22;
	SDL_Rect rec23;
	SDL_Rect rec24;
	SDL_Rect rec25;
	SDL_Rect rec26;
	SDL_Rect rec27;
	SDL_Rect rec28;
	SDL_Rect rec29;
	SDL_Rect rec30;
	SDL_Rect rec31;
	SDL_Rect rec32;
	SDL_Rect rec33;
	SDL_Rect rec34;
	SDL_Rect rec35;
	SDL_Rect rec36;
	SDL_Rect rec37;

	SDL_Rect rec41;
	rec41.x = 40;
	rec41.y = 300;
	SDL_Rect rec42;
	rec42.x = 200;
	rec42.y = 300;
	SDL_Rect rec43;
	rec43.x = 360;
	rec43.y = 300;
	SDL_Rect rec44;
	rec44.x = 520;
	rec44.y = 300;
	SDL_Rect rec45;
	rec45.x = 680;
	rec45.y = 300;
	SDL_Rect rec46;
	rec46.x = 40;
	rec46.y = 450;
	SDL_Rect rec47;
	rec47.x = 200;
	rec47.y = 450;
	SDL_Rect rec48;
	rec48.x = 360;
	rec48.y = 450;
	SDL_Rect rec49;
	rec49.x = 520;
	rec49.y = 450;
	SDL_Rect rec50;
	rec50.x = 680;
	rec50.y = 450;

	
	Uint32 start;
	SDL_Event event;

	while (!quit)
	{
		int contador=0;
		int pontuacao1 = 0;
		float xnave=360,ynave=250;
		int passo = 1;
		int incx = 0;
		int incy  = 0;
		float xvel = 0;
		float yvel = 0;
		int anglenave = 0;
		int g = 0;
		int vida = 0;
		int tempo2 = 11;
		char letra[10];
		int u;
		int j,i,l;
		int tutorial1 = 0;
		int ranking1 = 0;
		int participantes1 = 0;
		int fim = 0;
		char nome1[10];
		int w = 0;
		int play1 = 0;
		int navedestruida = 0;
		int contadornave = 0;
		destruirasteroides();

		for(j = 0;j < 10;j++)
		{
			nome1[w] = ' ';
		}

		for(j = 0;j < MAX;j++)
		{
			asteroides[j].explosao = 0;
			asteroides[j].explosao2 = 0;
			asteroides[j].contexplosao = 0;
		}

		for(j = 0;j < MAX;j++)
		{
			tiros[j].tiroativo = 1;
		}
       
		while(SDL_PollEvent(&event))
		{

			if (event.type == SDL_QUIT)
			{
				quit = TRUE;
			}

			else if( event.type == SDL_KEYDOWN )
			{
				switch( event.key.keysym.sym )
				{
	
				case SDLK_UP:
					rec7.y-=70;
					break;
				
				case SDLK_DOWN:
					rec7.y+=70;
					break;
				case SDLK_ESCAPE:
					quit = TRUE;
					break;
				case SDLK_RETURN:
					if(rec7.y == rec6.y)
					{
						quit = TRUE;
						break;
					}
					
					if(rec7.y == rec2.y)
					{
						jogo = 2;
						break;
					}

					if(rec7.y == rec5.y)
					{
						participantes1 = 1;
						break;
					}

					if(rec7.y == rec3.y)
					{
						tutorial1 = 1;
						break;
					}

					if(rec7.y == rec4.y)
					{
						ranking1 = 1;
						break;
					}
					
					break;
				default:
					break;
				}
			}		       
		}

		if(rec7.y>480)
			rec7.y = 200;

		if(rec7.y<200)
			rec7.y = 480;
		
		SDL_FillRect(screeninicial, NULL, 0);
		SDL_BlitSurface( fundoinicial, NULL, screeninicial, NULL );
		SDL_BlitSurface( logo, NULL, screeninicial, &rec1 );
		SDL_BlitSurface( seta, NULL, screeninicial, &rec7 );
		SDL_BlitSurface( iniciar, NULL, screeninicial, &rec2 );
		SDL_BlitSurface( tutorial, NULL, screeninicial, &rec3 );
		SDL_BlitSurface( ranking, NULL, screeninicial, &rec4 );
		SDL_BlitSurface( participantes, NULL, screeninicial, &rec5 );
		SDL_BlitSurface( sair, NULL, screeninicial, &rec6 );
		SDL_BlitSurface( seta, NULL, screeninicial, &rec7 );

		SDL_Flip(screeninicial);

		while (tutorial1 == 1)
		{
			while(SDL_PollEvent(&event))
			{

				if (event.type == SDL_QUIT)
				{
					tutorial1 = 0;
				}

				else if( event.type == SDL_KEYDOWN )
				{
					switch( event.key.keysym.sym )
					{

					case SDLK_ESCAPE:
						tutorial1 = 0;
						break;
					case SDLK_RETURN:
						tutorial1 = 0;
						break;
					default:
						break;
					}
				}		       
			}

			SDL_FillRect(screentutorial, NULL, 0);
			SDL_BlitSurface( fundo2, NULL, screentutorial, NULL );
			SDL_BlitSurface( tutorial2, NULL, screentutorial, &rectuto );
			SDL_BlitSurface( sair1, NULL, screentutorial, &rec6 );
			SDL_BlitSurface( logotutorial, NULL, screentutorial, &rec1 );
			SDL_Flip(screentutorial);
		}

		while (ranking1 == 1)
		{
			while(SDL_PollEvent(&event))
			{

				if (event.type == SDL_QUIT)
				{
					ranking1 = 0;
				}

				else if( event.type == SDL_KEYDOWN )
				{
					switch( event.key.keysym.sym )
					{

					case SDLK_ESCAPE:
						ranking1 = 0;
						break;
					case SDLK_RETURN:
						ranking1 = 0;
						break;
					default:
						break;
					}
				}		       
			}

			SDL_FillRect(screenranking, NULL, 0);
			if((p_arquivo = fopen(nome_arquivo, "r")) != NULL)
			{
				fread(&array, sizeof(ARRAY), 1, p_arquivo);
				fclose(p_arquivo);
			}
			SDL_BlitSurface( fundo2, NULL, screentutorial, NULL );
			imprime(&array);
			SDL_BlitSurface( sair1, NULL, screenranking, &rec6 );
			SDL_BlitSurface( logoranking, NULL, screenranking, &rec1 );
			SDL_Flip(screenranking);
		}

		while (participantes1 == 1)
		{
			while(SDL_PollEvent(&event))
			{

				if (event.type == SDL_QUIT)
				{
					participantes1 = 0;
				}

				else if( event.type == SDL_KEYDOWN )
				{
					switch( event.key.keysym.sym )
					{

					case SDLK_ESCAPE:
						participantes1 = 0;
						break;
					case SDLK_RETURN:
						participantes1 = 0;
						break;
					default:
						break;
					}
				}		       
			}
			
			SDL_FillRect(screenparticipantes, NULL, 0);
			SDL_BlitSurface( fundo2, NULL, screenparticipantes, NULL );
			SDL_BlitSurface( participantes5, NULL, screenparticipantes, &rectuto );
			SDL_BlitSurface( sair1, NULL, screenparticipantes, &rec6 );
			SDL_BlitSurface( logoparticipantes, NULL, screenparticipantes, &rec1 );
			SDL_Flip(screenparticipantes);
		}

		while (jogo == 2)
		{

			while(SDL_PollEvent(&event))
			{

				if (event.type == SDL_QUIT)
				{
					jogo = 0;
				}
			
				else if( event.type == SDL_KEYDOWN )
				{
					switch( event.key.keysym.sym )
					{
	
					case SDLK_UP:
						recborda.y -= 150;
						break;
					case SDLK_LEFT:
						recborda.x -= 160;
						break;
					case SDLK_RIGHT:
						recborda.x += 160;
						break;
					case SDLK_DOWN:
						recborda.y += 150;
						break;
					case SDLK_ESCAPE:
						jogo = 0;
						break;
					case SDLK_RETURN:
						if((recborda.x == 37)&&(recborda.y == 197))
						{
							jogo = 1;
							supernave = nave1;
							break;
						}

						if((recborda.x == 197)&&(recborda.y == 197))
						{
							jogo = 1;
							supernave = nave2;
							break;
						}

						if((recborda.x == 357)&&(recborda.y == 197))
						{
							jogo = 1;
							supernave = nave3;
							break;
						}

						if((recborda.x == 517)&&(recborda.y == 197))
						{
							jogo = 1;
							supernave = nave4;
							break;
						}

						if((recborda.x == 677)&&(recborda.y == 197))
						{
							jogo = 1;
							supernave = nave5;
							break;
						}

						if((recborda.x == 37)&&(recborda.y == 347))
						{
							jogo = 1;
							supernave = nave6;
							break;
						}

						if((recborda.x == 197)&&(recborda.y == 347))
						{
							jogo = 1;
							supernave = nave7;
							break;
						}

						if((recborda.x == 357)&&(recborda.y == 347))
						{
							jogo = 1;
							supernave = nave8;
							break;
						}

						if((recborda.x == 517)&&(recborda.y == 347))
						{
							jogo = 1;
							supernave = nave9;
							break;
						}

						if((recborda.x == 677)&&(recborda.y == 347))
						{
							jogo = 1;
							supernave = nave10;
							break;
						}
						break;
					default:
						break;
					}
				}
			}

			if(recborda.y < 197)
			{
				recborda.y = 347;
			}

			if(recborda.y > 347)
			{
				recborda.y = 197;
			}

			if(recborda.x < 37)
			{
				recborda.x = 677;
			}

			if(recborda.x > 677)
			{
				recborda.x = 37;
			}

			SDL_FillRect(screen, NULL, 0);
			SDL_BlitSurface( fundo2, NULL, screen, NULL );
			SDL_BlitSurface( naves, NULL, screen, &rec1 );
			SDL_BlitSurface( borda, NULL, screen, &recborda );
			SDL_BlitSurface( nave1, NULL, screen, &rec11 );
			SDL_BlitSurface( nave2, NULL, screen, &rec12 );
			SDL_BlitSurface( nave3, NULL, screen, &rec13 );
			SDL_BlitSurface( nave4, NULL, screen, &rec14 );
			SDL_BlitSurface( nave5, NULL, screen, &rec15 );
			SDL_BlitSurface( nave6, NULL, screen, &rec16 );
			SDL_BlitSurface( nave7, NULL, screen, &rec17 );
			SDL_BlitSurface( nave8, NULL, screen, &rec18 );
			SDL_BlitSurface( nave9, NULL, screen, &rec19 );
			SDL_BlitSurface( nave10, NULL, screen, &rec20 );
			SDL_BlitSurface( nomenave1, NULL, screen, &rec41 );
			SDL_BlitSurface( nomenave2, NULL, screen, &rec42 );
			SDL_BlitSurface( nomenave3, NULL, screen, &rec43 );
			SDL_BlitSurface( nomenave4, NULL, screen, &rec44 );
			SDL_BlitSurface( nomenave5, NULL, screen, &rec45 );
			SDL_BlitSurface( nomenave6, NULL, screen, &rec46 );
			SDL_BlitSurface( nomenave7, NULL, screen, &rec47 );
			SDL_BlitSurface( nomenave8, NULL, screen, &rec48 );
			SDL_BlitSurface( nomenave9, NULL, screen, &rec49 );
			SDL_BlitSurface( nomenave10, NULL, screen, &rec50 );
			SDL_Flip(screen);

		}

		while (jogo == 1)
		{
			start=SDL_GetTicks();
	       
			while(SDL_PollEvent(&event))
			{

				if (event.type == SDL_QUIT)
				{
					jogo = 0;
				}
			
				else if( event.type == SDL_KEYDOWN )
				{
					switch( event.key.keysym.sym )
					{
	
					case SDLK_UP:     
						incy = -passo;
						navedestruida = 0;
						break;
					case SDLK_LEFT:
						incx = -passo;
						navedestruida = 0;
						break;
					case SDLK_RIGHT:
						incx = passo;
						navedestruida = 0;
						break;
					case SDLK_SPACE:
						g = -passo;
						navedestruida = 0;
						break;
					case SDLK_ESCAPE:
						jogo = 0;
						break;
					case SDLK_p:
						play1 = 1;
						break;
					default:
						break;
					}
				}

				else if( event.type == SDL_KEYUP )
				{
					switch( event.key.keysym.sym )
					{
					case SDLK_UP:
						incy = 0;
						break;
					case SDLK_LEFT:
						incx = 0;
						break;
					case SDLK_RIGHT:
						incx = 0;
						break;
					case SDLK_SPACE:
						g = 0;
						break;
					default:
						break;
					}
				}		       
			}

			sprintf(letra,"%i",pontuacao1);

			ttf = TTF_RenderText_Blended(fonte, letra, cor);
			if(navedestruida == 0)
			{
				if(incy<0)
				{
					xvel = 7;
					yvel = 7;
					xnave-=sin(anglenave*M_PI/180.0)*xvel;
					ynave-=cos(anglenave*M_PI/180.0)*yvel;
				}

				if(incy==0)
				{
					if((xvel&&yvel)>0.9)
					{
						xvel=xvel-0.1;
						yvel=yvel-0.1;
						xnave-=sin(anglenave*M_PI/180.0)*xvel;
						ynave-=cos(anglenave*M_PI/180.0)*yvel;
						contador++;

						if(contador>70)
						{
							xvel=0;
							yvel=0;
							contador=0;
						}
					}
				}
	
				if (incx<0)
				{
					anglenave+=5;
				}
	
				if(incx>0)
				{
					anglenave-=5;
				}
			}
	
			rotatedimage=rotozoomSurface(supernave,anglenave,1.0,0);
		
			rec.x = (int)xnave;
			rec.y = (int)ynave;
			rec.x-=rotatedimage->w/2-supernave->w/2;
			rec.y-=rotatedimage->h/2-supernave->h/2;

			rotatednaveexplo1=rotozoomSurface(naveexplo1,anglenave,1.0,0);
			rotatednaveexplo2=rotozoomSurface(naveexplo2,anglenave,1.0,0);
			rotatednaveexplo3=rotozoomSurface(naveexplo3,anglenave,1.0,0);
			rotatednaveexplo4=rotozoomSurface(naveexplo4,anglenave,1.0,0);
			rotatednaveexplo5=rotozoomSurface(naveexplo5,anglenave,1.0,0);
			rotatednaveexplo6=rotozoomSurface(naveexplo6,anglenave,1.0,0);
			rotatednaveexplo7=rotozoomSurface(naveexplo7,anglenave,1.0,0);
			rotatednaveexplo8=rotozoomSurface(naveexplo8,anglenave,1.0,0);
			rotatednaveexplo9=rotozoomSurface(naveexplo9,anglenave,1.0,0);
			rotatednaveexplo10=rotozoomSurface(naveexplo10,anglenave,1.0,0);
			rotatednaveexplo11=rotozoomSurface(naveexplo11,anglenave,1.0,0);
			rotatednaveexplo12=rotozoomSurface(naveexplo12,anglenave,1.0,0);
			rotatednaveexplo13=rotozoomSurface(naveexplo13,anglenave,1.0,0);
			rotatednaveexplo14=rotozoomSurface(naveexplo14,anglenave,1.0,0);
			rotatednaveexplo15=rotozoomSurface(naveexplo15,anglenave,1.0,0);
			rotatednaveexplo16=rotozoomSurface(naveexplo16,anglenave,1.0,0);
			rotatednaveexplo17=rotozoomSurface(naveexplo17,anglenave,1.0,0);

			rec21.x = (int)xnave;
			rec21.y = (int)ynave;
			rec21.x-=rotatednaveexplo1->w/2-naveexplo1->w/2;
			rec21.y-=rotatednaveexplo1->h/2-naveexplo1->h/2;

			rec22.x = (int)xnave;
			rec22.y = (int)ynave;
			rec22.x-=rotatednaveexplo2->w/2-naveexplo2->w/2;
			rec22.y-=rotatednaveexplo2->h/2-naveexplo2->h/2;

			rec23.x = (int)xnave;
			rec23.y = (int)ynave;
			rec23.x-=rotatednaveexplo3->w/2-naveexplo3->w/2;
			rec23.y-=rotatednaveexplo3->h/2-naveexplo3->h/2;

			rec24.x = (int)xnave;
			rec24.y = (int)ynave;
			rec24.x-=rotatednaveexplo4->w/2-naveexplo4->w/2;
			rec24.y-=rotatednaveexplo4->h/2-naveexplo4->h/2;

			rec25.x = (int)xnave;
			rec25.y = (int)ynave;
			rec25.x-=rotatednaveexplo5->w/2-naveexplo5->w/2;
			rec25.y-=rotatednaveexplo5->h/2-naveexplo5->h/2;

			rec26.x = (int)xnave;
			rec26.y = (int)ynave;
			rec26.x-=rotatednaveexplo6->w/2-naveexplo6->w/2;
			rec26.y-=rotatednaveexplo6->h/2-naveexplo6->h/2;

			rec27.x = (int)xnave;
			rec27.y = (int)ynave;
			rec27.x-=rotatednaveexplo7->w/2-naveexplo7->w/2;
			rec27.y-=rotatednaveexplo7->h/2-naveexplo7->h/2;

			rec28.x = (int)xnave;
			rec28.y = (int)ynave;
			rec28.x-=rotatednaveexplo8->w/2-naveexplo8->w/2;
			rec28.y-=rotatednaveexplo8->h/2-naveexplo8->h/2;

			rec29.x = (int)xnave;
			rec29.y = (int)ynave;
			rec29.x-=rotatednaveexplo9->w/2-naveexplo9->w/2;
			rec29.y-=rotatednaveexplo9->h/2-naveexplo9->h/2;

			rec30.x = (int)xnave;
			rec30.y = (int)ynave;
			rec30.x-=rotatednaveexplo10->w/2-naveexplo10->w/2;
			rec30.y-=rotatednaveexplo10->h/2-naveexplo10->h/2;

			rec31.x = (int)xnave;
			rec31.y = (int)ynave;
			rec31.x-=rotatednaveexplo11->w/2-naveexplo11->w/2;
			rec31.y-=rotatednaveexplo11->h/2-naveexplo11->h/2;

			rec32.x = (int)xnave;
			rec32.y = (int)ynave;
			rec32.x-=rotatednaveexplo12->w/2-naveexplo12->w/2;
			rec32.y-=rotatednaveexplo12->h/2-naveexplo12->h/2;

			rec33.x = (int)xnave;
			rec33.y = (int)ynave;
			rec33.x-=rotatednaveexplo13->w/2-naveexplo13->w/2;
			rec33.y-=rotatednaveexplo13->h/2-naveexplo13->h/2;

			rec34.x = (int)xnave;
			rec34.y = (int)ynave;
			rec34.x-=rotatednaveexplo14->w/2-naveexplo14->w/2;
			rec34.y-=rotatednaveexplo14->h/2-naveexplo14->h/2;

			rec35.x = (int)xnave;
			rec35.y = (int)ynave;
			rec35.x-=rotatednaveexplo15->w/2-naveexplo15->w/2;
			rec35.y-=rotatednaveexplo15->h/2-naveexplo15->h/2;

			rec36.x = (int)xnave;
			rec36.y = (int)ynave;
			rec36.x-=rotatednaveexplo16->w/2-naveexplo16->w/2;
			rec36.y-=rotatednaveexplo16->h/2-naveexplo16->h/2;

			rec37.x = (int)xnave;
			rec37.y = (int)ynave;
			rec37.x-=rotatednaveexplo17->w/2-naveexplo17->w/2;
			rec37.y-=rotatednaveexplo17->h/2-naveexplo17->h/2;
		
			if (g<0)
			{
				for(j = 0;j < MAX;j++)
				{
					if(tiros[j].tiroativo == 1)
					{
						if(tempo2 > 10)
						{
							tiros[j].xtiro = (xnave+37);
							tiros[j].ytiro = (ynave+47);
							tiros[j].rectiro.x = (int)tiros[j].xtiro;
							tiros[j].rectiro.y = (int)tiros[j].ytiro;
							tiros[j].angletiro = anglenave;
							tiros[j].tiroativo = 0;
							tempo2 = 0;
							Mix_PlayChannel( -1, tiro, 0 );
							break;
						}
					}
				}
	
			}

			if(anglenave>=360)
				anglenave-=360;
		
			if(anglenave<=-360)
				anglenave+=360;
		
			SDL_FillRect(screen, NULL, 0);
			SDL_BlitSurface( fundo, NULL, screen, NULL );
			criarasteroides();
			moveasteroides();

			for(l = 0;l < MAX;l++)
			{
				for(j = 0;j < MAX;j++)
				{
					if(asteroides[j].destruido == 0)
					{
						if(asteroides[j].tipo==1)
						{
							if(tiros[l].tiroativo == 0)
							{
								if(colisao(asteroides[j].quad,tiros[l].rectiro ) == 1)
								{
									Mix_PlayChannel( -1, bomba, 0 );
									asteroides[j].explosao = 1;
									pontuacao1+=5;
									tiros[l].tiroativo = 1;
									break;
								}
							}
						}
						if(tiros[l].tiroativo == 0)
						{
							if(asteroides[j].tipo==2)
							{
								if(colisao(asteroides[j].quad,tiros[l].rectiro ) == 1)
								{
									Mix_PlayChannel( -1, bomba, 0 );
									asteroides[j].explosao = 1;
									pontuacao1+=10;
									tiros[l].tiroativo = 1;
									break;
								}
							}
						}
						if(tiros[l].tiroativo == 0)
						{
							if(asteroides[j].tipo==3)
							{
								if(colisao(asteroides[j].quad,tiros[l].rectiro ) == 1)
								{
									Mix_PlayChannel( -1, bomba, 0 );
									asteroides[j].explosao = 1;
									pontuacao1+=15;
									tiros[l].tiroativo = 1;
									break;
								}
							}
						}
					}
				}
			}
			if(navedestruida == 0)
			{
			for(j = 0;j < MAX;j++)
	 		{
				if(asteroides[j].explosao2 == 0)
				{
					if(asteroides[j].destruido == 0)
					{
						if(asteroides[j].tipo == 1)
						{
							if(colisao(asteroides[j].quad,rec ) == 1)
							{
								Mix_PlayChannel( -1, bomba, 0 );
								pontuacao1+=5;
								navedestruida = 1;
								asteroides[j].explosao = 1;
								asteroides[j].explosao2 = 1;
								vida++;
								break;
							}
						}

						if(asteroides[j].tipo == 2)
						{
							if(colisao(asteroides[j].quad,rec ) == 1)
							{
								Mix_PlayChannel( -1, bomba, 0 );
								pontuacao1+=10;							
								navedestruida = 1;
								asteroides[j].explosao = 1;
								asteroides[j].explosao2 = 1;
								vida++;
								break;
							}
						}
						if(asteroides[j].tipo == 3)
						{
							if(colisao(asteroides[j].quad,rec ) == 1)
							{
								Mix_PlayChannel( -1, bomba, 0 );
								pontuacao1+=15;							
								navedestruida = 1;
								asteroides[j].explosao = 1;
								asteroides[j].explosao2 = 1;
								vida++;
								break;
							}
						}
					}
				}
			}
			}

			for(j = 0;j < MAX;j++)
			{
				if(tiros[j].tiroativo == 0 )
				{
				tiros[j].rectiro.x-=sin(tiros[j].angletiro*M_PI/180.0)*20.0;
				tiros[j].rectiro.y-=cos(tiros[j].angletiro*M_PI/180.0)*20.0;
				SDL_BlitSurface( bala, NULL, screen, &tiros[j].rectiro );
				}
			}

			SDL_BlitSurface( rotatedimage, NULL, screen, &rec );

			for(j = 0; j < MAX; j++)
			{ 
				if(asteroides[j].destruido == 0)
				{
					if(asteroides[j].tipo==3)
						SDL_BlitSurface( asteroide3, NULL, screen, &asteroides[j].quad );
					if(asteroides[j].tipo==2)
						SDL_BlitSurface( asteroide2, NULL, screen, &asteroides[j].quad );
					if(asteroides[j].tipo==1)
						SDL_BlitSurface( asteroide1, NULL, screen, &asteroides[j].quad );
				}	
			}

			for(j = 0;j < MAX;j++)
			{
				if(asteroides[j].explosao == 1)
				{
					if(asteroides[j].tipo == 1)
					{
						if(asteroides[j].contexplosao == 0)
						{
							SDL_BlitSurface( explosao901, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 1)
						{
							SDL_BlitSurface( explosao902, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 2)
						{
							SDL_BlitSurface( explosao903, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 3)
						{
							SDL_BlitSurface( explosao904, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 4)
						{
							SDL_BlitSurface( explosao905, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 5)
						{
							SDL_BlitSurface( explosao906, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 6)
						{
							SDL_BlitSurface( explosao907, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 7)
						{
							SDL_BlitSurface( explosao908, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 8)
						{
							SDL_BlitSurface( explosao909, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 9)
						{
							SDL_BlitSurface( explosao9010, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 10)
						{
							SDL_BlitSurface( explosao9011, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 11)
						{
							SDL_BlitSurface( explosao9012, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 12)
						{
							SDL_BlitSurface( explosao9013, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 13)
						{
							SDL_BlitSurface( explosao9014, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 14)
						{
							SDL_BlitSurface( explosao9015, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 15)
						{
							SDL_BlitSurface( explosao9016, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 16)
						{
							SDL_BlitSurface( explosao9017, NULL, screen, &asteroides[j].quad );
							asteroides[j].contexplosao = 0;
							asteroides[j].explosao = 0;
							asteroides[j].tipo = 2;
							for(i = 0;i < MAX;i++)
							{
								if(asteroides[i].destruido==1)
								{
									asteroides[i].destruido = 0;
									asteroides[i].tipo = 2;
									u = rand()%360;
									asteroides[i].xasteroide = asteroides[j].xasteroide;
									asteroides[i].yasteroide = asteroides[j].yasteroide;
									asteroides[i].angulo = u;
									break;
								}
							}
							break;
						}
					}
					if(asteroides[j].tipo == 2)
					{
						if(asteroides[j].contexplosao == 0)
						{
							SDL_BlitSurface( explosao601, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 1)
						{
							SDL_BlitSurface( explosao602, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 2)
						{
							SDL_BlitSurface( explosao603, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 3)
						{
							SDL_BlitSurface( explosao604, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 4)
						{
							SDL_BlitSurface( explosao605, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 5)
						{
							SDL_BlitSurface( explosao606, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 6)
						{
							SDL_BlitSurface( explosao607, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 7)
						{
							SDL_BlitSurface( explosao608, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 8)
						{
							SDL_BlitSurface( explosao609, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 9)
						{
							SDL_BlitSurface( explosao6010, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 10)
						{
							SDL_BlitSurface( explosao6011, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 11)
						{
							SDL_BlitSurface( explosao6012, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 12)
						{
							SDL_BlitSurface( explosao6013, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 13)
						{
							SDL_BlitSurface( explosao6014, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 14)
						{
							SDL_BlitSurface( explosao6015, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 15)
						{
							SDL_BlitSurface( explosao6016, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 16)
						{
							SDL_BlitSurface( explosao6017, NULL, screen, &asteroides[j].quad );
							asteroides[j].contexplosao = 0;
							asteroides[j].explosao = 0;
							asteroides[j].tipo = 3;
							for(i = 0;i < MAX;i++)
							{
								if(asteroides[i].destruido==1)
								{
									asteroides[i].destruido = 0;
									asteroides[i].tipo = 3;
									u = rand()%360;
									asteroides[i].xasteroide = asteroides[j].xasteroide;
									asteroides[i].yasteroide = asteroides[j].yasteroide;
									asteroides[i].angulo = u;
									break;
								}
							}
							break;
						}
					}
					if(asteroides[j].tipo == 3)
					{
						if(asteroides[j].contexplosao == 0)
						{
							SDL_BlitSurface( explosao301, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 1)
						{
							SDL_BlitSurface( explosao302, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 2)
						{
							SDL_BlitSurface( explosao303, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 3)
						{
							SDL_BlitSurface( explosao304, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 4)
						{
							SDL_BlitSurface( explosao305, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 5)
						{
							SDL_BlitSurface( explosao306, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 6)
						{
							SDL_BlitSurface( explosao307, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 7)
						{
							SDL_BlitSurface( explosao308, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 8)
						{
							SDL_BlitSurface( explosao309, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 9)
						{
							SDL_BlitSurface( explosao3010, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 10)
						{
							SDL_BlitSurface( explosao3011, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 11)
						{
							SDL_BlitSurface( explosao3012, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 12)
						{
							SDL_BlitSurface( explosao3013, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 13)
						{
							SDL_BlitSurface( explosao3014, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 14)
						{
							SDL_BlitSurface( explosao3015, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 15)
						{
							SDL_BlitSurface( explosao3016, NULL, screen, &asteroides[j].quad );
						}
						if(asteroides[j].contexplosao == 16)
						{
							SDL_BlitSurface( explosao3017, NULL, screen, &asteroides[j].quad );
							asteroides[j].contexplosao = 0;
							asteroides[j].explosao = 0;
							asteroides[j].tipo = 1;
							asteroides[j].pos = 1;
							asteroides[j].destruido = 1;
							break;
						}
					}
					asteroides[j].contexplosao++;
				}
			}
			for(j = 0;j < MAX;j++)
			{
				if(asteroides[j].explosao2 == 1)
				{
					if(navedestruida == 1)
					{
						if(asteroides[j].tipo == 1)
						{
							if(contadornave == 0)
							{
								SDL_BlitSurface( rotatednaveexplo1, NULL, screen, &rec21 );
							}
							if(contadornave == 1)
							{
								SDL_BlitSurface( rotatednaveexplo2, NULL, screen, &rec22 );
							}
							if(contadornave == 2)
							{
								SDL_BlitSurface( rotatednaveexplo3, NULL, screen, &rec23 );
							}
							if(contadornave == 3)
							{
								SDL_BlitSurface( rotatednaveexplo4, NULL, screen, &rec24 );
							}
							if(contadornave == 4)
							{
								SDL_BlitSurface( rotatednaveexplo5, NULL, screen, &rec25 );
							}
							if(contadornave == 5)
							{
								SDL_BlitSurface( rotatednaveexplo6, NULL, screen, &rec26 );
							}
							if(contadornave == 6)
							{
								SDL_BlitSurface( rotatednaveexplo7, NULL, screen, &rec27 );
							}
							if(contadornave == 7)
							{
								SDL_BlitSurface( rotatednaveexplo8, NULL, screen, &rec28 );
							}
							if(contadornave == 8)
							{
								SDL_BlitSurface( rotatednaveexplo9, NULL, screen, &rec29 );
							}
							if(contadornave == 9)
							{
								SDL_BlitSurface( rotatednaveexplo10, NULL, screen, &rec30 );
							}
							if(contadornave == 10)
							{
								SDL_BlitSurface( rotatednaveexplo11, NULL, screen, &rec31 );
							}
							if(contadornave == 11)
							{
								SDL_BlitSurface( rotatednaveexplo12, NULL, screen, &rec32 );
							}
							if(contadornave == 12)
							{
								SDL_BlitSurface( rotatednaveexplo13, NULL, screen, &rec33 );
							}
							if(contadornave == 13)
							{
								SDL_BlitSurface( rotatednaveexplo14, NULL, screen, &rec34 );
							}
							if(contadornave == 14)
							{
								SDL_BlitSurface( rotatednaveexplo15, NULL, screen, &rec35 );
							}
							if(contadornave == 15)
							{
								SDL_BlitSurface( rotatednaveexplo16, NULL, screen, &rec36 );
							}
							if(contadornave == 16)
							{
								SDL_BlitSurface( rotatednaveexplo17, NULL, screen, &rec37 );
								xnave = 360;
								ynave = 250;
								rec.x = (int)xnave;
								rec.y = (int)ynave;
								contadornave = 0;
								incx = 0;
								incy  = 0;
								xvel = 0;
								yvel = 0;
								anglenave = 0;
								asteroides[j].explosao2 = 0;
								break;
							}
							contadornave++;
						}

						if(asteroides[j].tipo == 2)
						{
							if(contadornave == 0)
							{
								SDL_BlitSurface( rotatednaveexplo1, NULL, screen, &rec21 );
							}
							if(contadornave == 1)
							{
								SDL_BlitSurface( rotatednaveexplo2, NULL, screen, &rec22 );
							}
							if(contadornave == 2)
							{
								SDL_BlitSurface( rotatednaveexplo3, NULL, screen, &rec23 );
							}
							if(contadornave == 3)
							{
								SDL_BlitSurface( rotatednaveexplo4, NULL, screen, &rec24 );
							}
							if(contadornave == 4)
							{
								SDL_BlitSurface( rotatednaveexplo5, NULL, screen, &rec25 );
							}
							if(contadornave == 5)
							{
								SDL_BlitSurface( rotatednaveexplo6, NULL, screen, &rec26 );
							}
							if(contadornave == 6)
							{
								SDL_BlitSurface( rotatednaveexplo7, NULL, screen, &rec27 );
							}
							if(contadornave == 7)
							{
								SDL_BlitSurface( rotatednaveexplo8, NULL, screen, &rec28 );
							}
							if(contadornave == 8)
							{
								SDL_BlitSurface( rotatednaveexplo9, NULL, screen, &rec29 );
							}
							if(contadornave == 9)
							{
								SDL_BlitSurface( rotatednaveexplo10, NULL, screen, &rec30 );
							}
							if(contadornave == 10)
							{
								SDL_BlitSurface( rotatednaveexplo11, NULL, screen, &rec31 );
							}
							if(contadornave == 11)
							{
								SDL_BlitSurface( rotatednaveexplo12, NULL, screen, &rec32 );
							}
							if(contadornave == 12)
							{
								SDL_BlitSurface( rotatednaveexplo13, NULL, screen, &rec33 );
							}
							if(contadornave == 13)
							{
								SDL_BlitSurface( rotatednaveexplo14, NULL, screen, &rec34 );
							}
							if(contadornave == 14)
							{
								SDL_BlitSurface( rotatednaveexplo15, NULL, screen, &rec35 );
							}
							if(contadornave == 15)
							{
								SDL_BlitSurface( rotatednaveexplo16, NULL, screen, &rec36 );
							}
							if(contadornave == 16)
							{
								SDL_BlitSurface( rotatednaveexplo17, NULL, screen, &rec37 );
								xnave = 360;
								ynave = 250;
								rec.x = (int)xnave;
								rec.y = (int)ynave;
								contadornave = 0;
								incx = 0;
								incy  = 0;
								xvel = 0;
								yvel = 0;
								anglenave = 0;
								asteroides[j].explosao2 = 0;
								break;
							}
							contadornave++;
						}

						if(asteroides[j].tipo == 3)
						{
							if(contadornave == 0)
							{
								SDL_BlitSurface( rotatednaveexplo1, NULL, screen, &rec21 );
							}
							if(contadornave == 1)
							{
								SDL_BlitSurface( rotatednaveexplo2, NULL, screen, &rec22 );
							}
							if(contadornave == 2)
							{
								SDL_BlitSurface( rotatednaveexplo3, NULL, screen, &rec23 );
							}
							if(contadornave == 3)
							{
								SDL_BlitSurface( rotatednaveexplo4, NULL, screen, &rec24 );
							}
							if(contadornave == 4)
							{
								SDL_BlitSurface( rotatednaveexplo5, NULL, screen, &rec25 );
							}
							if(contadornave == 5)
							{
								SDL_BlitSurface( rotatednaveexplo6, NULL, screen, &rec26 );
							}
							if(contadornave == 6)
							{
								SDL_BlitSurface( rotatednaveexplo7, NULL, screen, &rec27 );
							}
							if(contadornave == 7)
							{
								SDL_BlitSurface( rotatednaveexplo8, NULL, screen, &rec28 );
							}
							if(contadornave == 8)
							{
								SDL_BlitSurface( rotatednaveexplo9, NULL, screen, &rec29 );
							}
							if(contadornave == 9)
							{
								SDL_BlitSurface( rotatednaveexplo10, NULL, screen, &rec30 );
							}
							if(contadornave == 10)
							{
								SDL_BlitSurface( rotatednaveexplo11, NULL, screen, &rec31 );
							}
							if(contadornave == 11)
							{
								SDL_BlitSurface( rotatednaveexplo12, NULL, screen, &rec32 );
							}
							if(contadornave == 12)
							{
								SDL_BlitSurface( rotatednaveexplo13, NULL, screen, &rec33 );
							}
							if(contadornave == 13)
							{
								SDL_BlitSurface( rotatednaveexplo14, NULL, screen, &rec34 );
							}
							if(contadornave == 14)
							{
								SDL_BlitSurface( rotatednaveexplo15, NULL, screen, &rec35 );
							}
							if(contadornave == 15)
							{
								SDL_BlitSurface( rotatednaveexplo16, NULL, screen, &rec36 );
							}
							if(contadornave == 16)
							{
								SDL_BlitSurface( rotatednaveexplo17, NULL, screen, &rec37 );
								xnave = 360;
								ynave = 250;
								rec.x = (int)xnave;
								rec.y = (int)ynave;
								contadornave = 0;
								incx = 0;
								incy  = 0;
								xvel = 0;
								yvel = 0;
								anglenave = 0;
								asteroides[j].explosao2 = 0;
								break;
							}
							contadornave++;
						}
					}
				}
			}
			
			if(vida == 0)
			{
				SDL_BlitSurface( coracao3, NULL, screen, &reccoracao);
			}

			if(vida == 1)
			{
				SDL_BlitSurface( coracao2, NULL, screen, &reccoracao);
			}

			if(vida == 2)
			{
				SDL_BlitSurface( coracao1, NULL, screen, &reccoracao);
			}

			SDL_BlitSurface( ttf, NULL, screen, &recttf);

			if(play1 == 0)
			{
				SDL_BlitSurface( play, NULL, screen, &recplay);
			}

			if(play1 == 1)
			{
				SDL_BlitSurface( pause, NULL, screen, &recplay);
			}

			SDL_FreeSurface(rotatedimage);
			SDL_FreeSurface(rotatednaveexplo1);
			SDL_FreeSurface(rotatednaveexplo2);
			SDL_FreeSurface(rotatednaveexplo3);
			SDL_FreeSurface(rotatednaveexplo4);
			SDL_FreeSurface(rotatednaveexplo5);
			SDL_FreeSurface(rotatednaveexplo6);
			SDL_FreeSurface(rotatednaveexplo7);
			SDL_FreeSurface(rotatednaveexplo8);
			SDL_FreeSurface(rotatednaveexplo9);
			SDL_FreeSurface(rotatednaveexplo10);
			SDL_FreeSurface(rotatednaveexplo11);
			SDL_FreeSurface(rotatednaveexplo12);
			SDL_FreeSurface(rotatednaveexplo13);
			SDL_FreeSurface(rotatednaveexplo14);
			SDL_FreeSurface(rotatednaveexplo15);
			SDL_FreeSurface(rotatednaveexplo16);
			SDL_FreeSurface(rotatednaveexplo17);
			SDL_Flip(screen);
	
			if(1000.0/30>(SDL_GetTicks()-start))
			{
				SDL_Delay(10000.0/30>(SDL_GetTicks()-start));
			}

			/*for(j = 0;j < MAX;j++)
			{	
				if(asteroides[j].destruido == 0)
				{
				if(asteroides[j].tipo == 1)
				{
				if((asteroides[j].xasteroide > 800)||(asteroides[j].xasteroide < -90)||(asteroides[j].yasteroide > 600)||(asteroides[j].yasteroide < -90))

					{
						asteroides[j].pos=0;
					}
				}

				if(asteroides[j].tipo == 2)
				{
				if((asteroides[j].xasteroide > 800)||(asteroides[j].xasteroide < -60)||(asteroides[j].yasteroide > 600)||(asteroides[j].yasteroide < -60))

					{
						asteroides[j].pos=0;
					}
				}

				if(asteroides[j].tipo == 3)
				{
				if((asteroides[j].xasteroide > 800)||(asteroides[j].xasteroide < -30)||(asteroides[j].yasteroide > 600)||(asteroides[j].yasteroide < -30))

					{
						asteroides[j].pos=0;
					}
				}
				}


			}*/

			for(j = 0;j < MAX;j++)
			{	
				if(asteroides[j].destruido == 0)
				{
					if(asteroides[j].tipo == 1)
					{
						if(asteroides[j].xasteroide > 800)
						{
							asteroides[j].xasteroide= -90;
						}
						if(asteroides[j].yasteroide > 600)
						{
							asteroides[j].yasteroide= -90;
						}
						if(asteroides[j].xasteroide < -90)
						{
							asteroides[j].xasteroide=800;
						}
						if(asteroides[j].yasteroide < -90)
						{
							asteroides[j].yasteroide=600;
						}
					}

					if(asteroides[j].tipo == 2)
					{
						if(asteroides[j].xasteroide > 800)
						{
							asteroides[j].xasteroide = -60;
						}
						if(asteroides[j].yasteroide > 600)
						{
							asteroides[j].yasteroide= -60;
						}
						if(asteroides[j].xasteroide < -60)
						{
							asteroides[j].xasteroide=800;
						}
						if(asteroides[j].yasteroide < -60)
						{
							asteroides[j].yasteroide=600;
						}
					}

					if(asteroides[j].tipo == 3)
					{
						if(asteroides[j].xasteroide > 800)
						{
							asteroides[j].xasteroide = -30;
						}
						if(asteroides[j].yasteroide > 600)
						{
							asteroides[j].yasteroide = -30;
						}
						if(asteroides[j].xasteroide < -30)
						{
							asteroides[j].xasteroide = 800;
						}
						if(asteroides[j].yasteroide < -30)
						{
							asteroides[j].yasteroide = 600;
						}
					}
				}
			}
	
			if(xnave > 800)
			{
				xnave= -75;
			}
			if(ynave > 600)
			{
				ynave= -95;
			}
			if(xnave < -75)
			{
				xnave=800;
			}
			if(ynave < -95)
			{
				ynave=600;
			}
		
			for(i = 0;i < MAX;i++)
			{
				if(tiros[i].rectiro.x > 890||tiros[i].rectiro.x < -90||tiros[i].rectiro.y > 690||tiros[i].rectiro.y < -90)
				{
				tiros[i].tiroativo = 1;
				}
			}

			if(vida>2)
			{
				fim = 1;
				jogo = 0;
			}
			tempo2++;

			SDL_Delay(5);

			while(play1 == 1)
			{
				while(SDL_PollEvent(&event))
				{

					if (event.type == SDL_QUIT)
					{
						jogo = 0;
					}

					else if( event.type == SDL_KEYDOWN )
					{
						switch( event.key.keysym.sym )
						{

						case SDLK_ESCAPE:
							jogo = 0;
							play1 = 0;
							break;
						case SDLK_p:
							play1 = 0;
							break;
						default:
							break;
						}
					}
				}
			}
				
		}

		while(fim == 1)
		{
			while(SDL_PollEvent(&event))
			{

				if (event.type == SDL_QUIT)
				{
					fim = 0;
				}

				else if( event.type == SDL_KEYDOWN )
				{
					switch( event.key.keysym.sym )
					{

					case SDLK_ESCAPE:
						fim = 0;
						break;
					case SDLK_RETURN:
						if((p_arquivo = fopen(nome_arquivo, "r")) != NULL)
						{
							fread(&array, sizeof(ARRAY), 1, p_arquivo);
							fclose(p_arquivo);
						}
						for(j = 0;j < 7;j++)
						{
							reco1.nome[j] = nome1[j];
						}
						reco1.pontuacao = pontuacao1;
						insere(&array, reco1);
						if((p_arquivo = fopen(nome_arquivo, "w")) == NULL)
						{
							perror("fopen:");
						}
						fwrite(&array, sizeof(ARRAY), 1, p_arquivo);
						fclose(p_arquivo);
						fim = 0;
						break;
					case SDLK_a:
						if(w<7)
						{
							nome1[w] = 'a';
							w++;
						}
						break;
					case SDLK_b:
						if(w<7)
						{
							nome1[w] = 'b';
							w++;
						}
						break;
					case SDLK_c:
						if(w<7)
						{
							nome1[w] = 'c';
							w++;
						}
						break;
					case SDLK_d:
						if(w<7)
						{
							nome1[w] = 'd';
							w++;
						}
						break;
					case SDLK_e:
						if(w<7)
						{
							nome1[w] = 'e';
							w++;
						}
						break;
					case SDLK_f:
						if(w<7)
						{
							nome1[w] = 'f';
							w++;
						}
						break;
					case SDLK_g:
						if(w<7)
						{
							nome1[w] = 'g';
							w++;
						}
						break;
					case SDLK_h:
						if(w<7)
						{
							nome1[w] = 'h';
							w++;
						}
						break;
					case SDLK_i:
						if(w<7)
						{
							nome1[w] = 'i';
							w++;
						}
						break;
					case SDLK_j:
						if(w<7)
						{
							nome1[w] = 'j';
							w++;
						}
						break;
					case SDLK_k:
						if(w<7)
						{
							nome1[w] = 'k';
							w++;
						}
						break;
					case SDLK_l:
						if(w<7)
						{
							nome1[w] = 'l';
							w++;
						}
						break;
					case SDLK_m:
						if(w<7)
						{
							nome1[w] = 'm';
							w++;
						}
						break;
					case SDLK_n:
						if(w<7)
						{
							nome1[w] = 'n';
							w++;
						}
						break;
					case SDLK_o:
						if(w<7)
						{
							nome1[w] = 'o';
							w++;
						}
						break;
					case SDLK_p:
						if(w<7)
						{
							nome1[w] = 'p';
							w++;
						}
						break;
					case SDLK_q:
						if(w<7)
						{
							nome1[w] = 'q';
							w++;
						}
						break;
					case SDLK_r:
						if(w<7)
						{
							nome1[w] = 'r';
							w++;
						}
						break;
					case SDLK_s:
						if(w<7)
						{
							nome1[w] = 's';
							w++;
						}
						break;
					case SDLK_t:
						if(w<7)
						{
							nome1[w] = 't';
							w++;
						}
						break;
					case SDLK_u:
						if(w<7)
						{
							nome1[w] = 'u';
							w++;
						}
						break;
					case SDLK_v:
						if(w<7)
						{
							nome1[w] = 'v';
							w++;
						}
						break;
					case SDLK_w:
						if(w<7)
						{
							nome1[w] = 'w';
							w++;
						}
						break;
					case SDLK_x:
						if(w<7)
						{
							nome1[w] = 'x';
							w++;
						}
						break;
					case SDLK_y:
						if(w<7)
						{
							nome1[w] = 'y';
							w++;
						}
						break;
					case SDLK_z:
						if(w<7)
						{
							nome1[w] = 'z';
							w++;
						}
						break;
					case SDLK_BACKSPACE:
						if(w>0)
						{
							w--;
							nome1[w]=' ';
						}
						break;
					default:
						break;
					}
				}		       
			}

			SDL_FillRect(screen, NULL, 0);
			SDL_BlitSurface( fundo2, NULL, screen, NULL );
			ttfnome = TTF_RenderText_Blended(fontenome, nome1, cor);
			ttftraco = TTF_RenderText_Blended(fontenome, "_______", cor);
			SDL_BlitSurface( ttfnome, NULL, screen, &rec5);
			SDL_BlitSurface( ttftraco, NULL, screen, &rec5);
			SDL_BlitSurface( dignome, NULL, screen, &recdig );
			SDL_BlitSurface( sair1, NULL, screen, &rec6 );
			SDL_BlitSurface( gameover, NULL, screen, &rec1 );
			SDL_Flip(screen);
		}
	}

	atexit(Mix_CloseAudio);

	TTF_Quit();

	SDL_Quit();

	return 0;
}

RECORDE elemento(ARRAY *array, int posicao)
{
	return array->vetor[posicao];
}

int tamanho(ARRAY *array)
{
	return array->n;
}

void insere(ARRAY *array, RECORDE recorde)
{
    if(tamanho(array) < MAX_ARRAY)
    {
        array->vetor[tamanho(array)] = recorde;
        array->n += 1;
    }
    else
    {
        RECORDE menor_recorde;
        menor_recorde = elemento(array, MAX_ARRAY - 1);
        
        if(menor_recorde.pontuacao >= recorde.pontuacao)
        {
            return;
        }
        else
        {
            remove_posicao(array, MAX_ARRAY - 1);
            insere(array, recorde);
            return;
        }
    }
    
    sort(array);
}

void remove_posicao(ARRAY *array, int posicao)
{
	if(tamanho(array) == 0)
	{
		return;
	}
	else if(tamanho(array) == 1)
	{
		array->n -= 1;
		return;
	}
	else
	{
		array->n -= 1;
		array->vetor[posicao] = array->vetor[tamanho(array)];
	}
    
    sort(array);
}

void imprime(ARRAY *array)
{
	int i,j;
	char nome[tamanho(array)][10];
	char num[tamanho(array)][10];

	//SDL_Init(SDL_INIT_EVERYTHING);

	//TTF_Init();
    	
	//screenranking = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);

	SDL_Surface* ttf[tamanho(array)][3];

	RECORDE recorde;

	SDL_Rect rec[tamanho(array)][3];
	int x;
	int y;
	
	y = 200;

	for(j = 0;j < tamanho(array);j++)
	{
		x = 200;

		for(i = 0;i < 3;i++)
		{
			rec[j][i].x = x;
			rec[j][i].y = y;
			x +=100;
		}
		y+=25;
	}

	TTF_Font *fonte;

	fonte = TTF_OpenFont("fonte.ttf", 25);

	SDL_Color cor = {255, 0, 0};

	for(i = 0; i < tamanho(array); i++)
	{
		recorde = elemento(array, i);
		sprintf(nome[i],"%i",recorde.pontuacao);
		sprintf(num[i],"%i",i+1);
	}

	//SDL_BlitSurface( fundo2, NULL, screenranking, NULL );

	for(j = 0;j < 3;j++)
	{
		for(i = 0; i < tamanho(array); i++)
		{
			recorde = elemento(array, i);
			if(j == 0)
			{
				ttf[i][j] = TTF_RenderText_Blended(fonte,num[i] , cor);
				SDL_BlitSurface( ttf[i][j], NULL, screenranking, &rec[i][j]);
			}
			if(j == 1)
			{
				ttf[i][j] = TTF_RenderText_Blended(fonte,recorde.nome , cor);
				SDL_BlitSurface( ttf[i][j], NULL, screenranking, &rec[i][j]);
			}
			if(j == 2)
			{
				ttf[i][j] = TTF_RenderText_Blended(fonte,nome[i] , cor);
				SDL_BlitSurface( ttf[i][j], NULL, screenranking, &rec[i][j]);
				
			}
		}
	}
	for(j = 0;j < 3;j++)
	{
		for(i = 0; i < tamanho(array); i++)
		{
			SDL_FreeSurface(ttf[i][j]);
		}
	}

	free(fonte);
}

void sort(ARRAY *array)
{
	bubble_sort(array->vetor, array->n);
}

void bubble_sort(RECORDE list[], int n)
{
	int i, j;
    RECORDE swap;

	for(i = 0 ; i < ( n - 1 ); i++)
	{
		for(j = 0 ; j < n - i - 1; j++)
		{
			if(list[j].pontuacao < list[j+1].pontuacao)
			{ 
				swap = list[j];
				list[j] = list[j+1];
				list[j+1] = swap;
			}
		}
	}
}
