#include <iostream>
#include <vector>
#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "commun.h"
#include "CHistogramme.h"
#include "CGeneticHistogramme.h"
#include "CGeneticDigest.h"

#define POINT_SIZE				16
#define WIDTH					512
#define HEIGHT					512
#define NB_COLOR                ((WIDTH / POINT_SIZE) * (HEIGHT / POINT_SIZE))
#define TAILLE_POPULATION       200

void transformeBase(const char *src, const char *dst, CHistogramme *histogramme);
void initPopulationH(CIndividuHistogramme **population);

int main(void) {
	CHistogramme reference;
    CIndividuHistogramme *populationH[TAILLE_POPULATION];
	CGeneticDigest *populationD[TAILLE_POPULATION];
    
    initPopulationH(populationH);
    
    CGeneticHistogramme gh(populationH, TAILLE_POPULATION, 0);
    
    transformeBase("Lenna.jpg", "/tmp/base.jpg", &reference);
	srand(time(NULL));
    
    gh.run(&reference);
	
	return 0;
}

void transformeBase(const char *src, const char *dst, CHistogramme *histogramme) {
	gdImagePtr imSrc;
	gdImagePtr imDst = gdImageCreateTrueColor(WIDTH, HEIGHT);
	int x, y, i;
	FILE *out;
	FILE *in;
    SColor colors[NB_COLOR];
	
	in = fopen(src, "r");
	imSrc = gdImageCreateFromJpeg(in);
	fclose(in);
	
	for(y=i=0;y<HEIGHT;y+=POINT_SIZE) {
		for(x=0;x<WIDTH;x+=POINT_SIZE,i++) {
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
			
			colors[i].r = r;
			colors[i].g = g;
			colors[i].b = b;
			
			gdImageFilledRectangle(imDst, x, y, x + POINT_SIZE, y + POINT_SIZE, gdImageColorAllocate(imDst, r, g, b));
		}
	}
	
	histogramme->calcul(colors, NB_COLOR);
	
	out = fopen(dst, "w");
	gdImageJpeg(imDst, out, -1);
	
	fclose(out);
	gdImageDestroy(imDst);
	gdImageDestroy(imSrc);
}

void initPopulationH(CIndividuHistogramme **population) {
    int i;
    
    for(i=0;i<TAILLE_POPULATION;i++) {
        population[i] = new CIndividuHistogramme(WIDTH, HEIGHT, POINT_SIZE);
    }
}
