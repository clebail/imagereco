#include <iostream>
#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define POINT_SIZE				8
#define WIDTH					512
#define HEIGHT					512
#define TAB_SIZE				((WIDTH / POINT_SIZE) * (HEIGHT / POINT_SIZE))
#define TAILLE_POPULATION		200

typedef unsigned char uchar;

typedef struct _SColor {
	uchar r;
	uchar g;
	uchar b;
}SColor;

typedef struct _SHistogramme {
	int r[256];
	int g[256];
	int b[256];
}SHistogramme;

typedef struct _SIndividu {
	SColor colors[TAB_SIZE];
	SHistogramme histogramme;
	int histoScore;
	int score;
}SIndividu;


void initPopulation(SIndividu *population);
void initIndividu(SIndividu *individu);
void swapIndividus(SIndividu *i1, SIndividu *i2);
void createImage(SIndividu *individu, const char *fileName);
void createGene(SColor *color);
void transformeBase(const char *src, const char *dst, SHistogramme *histogramme);

void evalPopulationH(SIndividu *population, SHistogramme *hRef);
void triPopulationH(SIndividu *population);
int croiseIndividusH(SIndividu *population);
void croiseH(SIndividu *individus, int i1, int i2, int ir);

int main(void) {
	SIndividu population[TAILLE_POPULATION];
	bool fini = false;
	int step = 0;
	int oldScore = -1;
	SHistogramme hRef;
	
	transformeBase("Lenna.jpg", "/tmp/base.jpg", &hRef);
	srand(time(NULL));

	initPopulation(population);
	evalPopulationH(population, &hRef);
	triPopulationH(population);
	
	do {
		croiseIndividusH(population);
		evalPopulationH(population, &hRef);
		triPopulationH(population);
		
		if(population[0].histoScore != oldScore) {
			char fileName[255];
		
			sprintf(fileName, "images/img_%06d.jpg", step);
			
			createImage(&population[0], fileName);
			
			std::cout << "Meilleur " << population[0].histoScore << std::endl;
			
			step++;
		}
		fini = population[0].histoScore == 0;
		oldScore = population[0].histoScore;
	}while(!fini);

	return 0;
}

void initPopulation(SIndividu *population) {
	int i;
	
	for(i=0;i<TAILLE_POPULATION;i++) {
		initIndividu(&population[i]);
	}
}

void evalPopulationH(SIndividu *population, SHistogramme *hRef) {
	int i, j;
	
	for(i=0;i<TAILLE_POPULATION;i++) {
		population[i].histoScore = 0;
		for(j=0;j<256;j++) {
			population[i].histoScore += abs(hRef->r[j] - population[i].histogramme.r[j]);
			population[i].histoScore += abs(hRef->g[j] - population[i].histogramme.g[j]);
			population[i].histoScore += abs(hRef->b[j] - population[i].histogramme.b[j]);
		}
	}
}

void triPopulationH(SIndividu *population) {
	int i, j;

	for(i=TAILLE_POPULATION-1;i>=1;i--) {
		for(j=0;j<=i-1;j++) {
			if(population[j+1].histoScore < population[j].histoScore) {
				swapIndividus(&population[j+1], &population[j]);
			}
		}
	}
}
void swapIndividus(SIndividu *i1, SIndividu *i2) {
	SIndividu tmp;
	
	memcpy(&tmp, i1, sizeof(SIndividu));
	memcpy(i1, i2, sizeof(SIndividu));
	memcpy(i2, &tmp, sizeof(SIndividu));
}

void initIndividu(SIndividu *individu) {
	int i;

	memset(&individu->histogramme, 0, sizeof(SHistogramme));
	
	for(i=0;i<TAB_SIZE;i++) {
		createGene(&individu->colors[i]);
		
		individu->histogramme.r[individu->colors[i].r]++;
		individu->histogramme.g[individu->colors[i].g]++;
		individu->histogramme.b[individu->colors[i].b]++;
	}
	
	individu->histoScore = 0;
}

void createImage(SIndividu *individu, const char *fileName) {
	int x, y, i;
	gdImagePtr im = gdImageCreateTrueColor(WIDTH, HEIGHT);
	FILE *out;
	
	for(y=i=0;y<HEIGHT;y+=POINT_SIZE) {
		for(x=0;x<WIDTH;x+=POINT_SIZE,i++) {
			int c = gdImageColorAllocate(im, individu->colors[i].r, individu->colors[i].g, individu->colors[i].b);
			
			gdImageFilledRectangle(im, x, y, x+POINT_SIZE, y+POINT_SIZE, c);
		}
	}
	
	out = fopen(fileName, "w");
	gdImageJpeg(im, out, -1);
	
	fclose(out);
	gdImageDestroy(im);
}

int croiseIndividusH(SIndividu *population) {
	int i, ir, max;
	
	i = 1;
	ir = TAILLE_POPULATION - 1;
	max = TAILLE_POPULATION / 2;
	
	while(i < max) {
		croiseH(population, i-1, i, ir);
		croiseH(population, i, i-1, ir-1);
		
		i+=2;
		ir-=2;
	}
	
	return 0;
}

void croiseH(SIndividu *population, int i1, int i2, int ir) {
	int i, j;
	int idx = rand() % TAB_SIZE;
	
	j = i1;
	for(i=0;i<TAB_SIZE;i+=2) {
		memcpy(&population[ir].colors[i], &population[j].colors[i], 2 * sizeof(SColor));
		j = (i1 + i2) - j;
	}
	
	if(rand() % 2) {
		population[ir].colors[idx].r = (uchar)(rand() % 256);
	}
	if(rand() % 2) {
		population[ir].colors[idx].g = (uchar)(rand() % 256);
	}
	if(rand() % 2) {
		population[ir].colors[idx].b = (uchar)(rand() % 256);
	}
	
	memset(&population[ir].histogramme, 0, sizeof(SHistogramme));
	
	for(i=0;i<TAB_SIZE;i++) {
		population[ir].histogramme.r[population[ir].colors[i].r]++;
		population[ir].histogramme.g[population[ir].colors[i].g]++;
		population[ir].histogramme.b[population[ir].colors[i].b]++;
	}
	
	population[ir].histoScore = 0;
}

void createGene(SColor *color) {
	color->r = (uchar)(rand() % 256);
	color->g = (uchar)(rand() % 256);
	color->b = (uchar)(rand() % 256);
}

void transformeBase(const char *src, const char *dst, SHistogramme *histogramme) {
	gdImagePtr imSrc;
	gdImagePtr imDst = gdImageCreateTrueColor(WIDTH, HEIGHT);
	int x, y;
	FILE *out;
	FILE *in;
	
	in = fopen(src, "r");
	imSrc = gdImageCreateFromJpeg(in);
	fclose(in);
	
	memset(histogramme, 0, sizeof(SHistogramme));
	
	for(y=0;y<HEIGHT;y+=POINT_SIZE) {
		for(x=0;x<WIDTH;x+=POINT_SIZE) {
			int r, g, b;
			int yIn, xIn, nb;
			
			r = g = b = 0;
			
			for(yIn=nb=0;yIn<POINT_SIZE;yIn++) {
				for(xIn=0;xIn<POINT_SIZE;xIn++,nb++) {
					int rgb = gdImageGetPixel(imSrc, xIn+x, yIn+y);
					int cR, cG, cB;
					
					cR = (rgb >> 16) & 0xFF;
					cG = (rgb >> 8) & 0xFF;
					cB = rgb & 0xFF;
					
					r += cR;
					g += cG;
					b += cB;
				}
			}
			
			r /= nb;
			g /= nb;
			b /= nb;
			
			histogramme->r[r]++;
			histogramme->g[g]++;
			histogramme->b[b]++;
			
			gdImageFilledRectangle(imDst, x, y, x + POINT_SIZE, y + POINT_SIZE, gdImageColorAllocate(imDst, r, g, b));
		}
	}
	
	out = fopen(dst, "w");
	gdImageJpeg(imDst, out, -1);
	
	fclose(out);
	gdImageDestroy(imDst);
	gdImageDestroy(imSrc);
}
