#include <iostream>
#include <vector>
#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pHash.h>
#include "commun.h"
#include "CHistogramme.h"
#include "CGeneticHistogramme.h"
#include "CGeneticHistogramme2.h"

#define POINT_SIZE				32
#define WIDTH					512
#define HEIGHT					512
#define NB_COLOR                ((WIDTH / POINT_SIZE) * (HEIGHT / POINT_SIZE))
#define TAILLE_POPULATION       200
#define SEUIL					((NB_COLOR / 100) * 3)

void transformeBase(const char *src, const char *dst, CHistogramme *histogramme, Digest& digest);
void initPopulationH(CIndividuHistogramme **population);
void initPopulationH2(CIndividuHistogramme2 **population, CIndividuHistogramme *best);

int main(void) {
	CHistogramme hReference;
	Digest dReference;
    CIndividuHistogramme *populationH[TAILLE_POPULATION];
	CIndividuHistogramme2 *populationH2[20];
	time_t debut = time(NULL);
	
	transformeBase("Lenna.jpg", "/tmp/base.png", &hReference, dReference);
	srand(debut);
	
	initPopulationH(populationH);
    CGeneticHistogramme gh(populationH, TAILLE_POPULATION, 0, SEUIL);
    gh.run(&hReference,debut);
	
	initPopulationH2(populationH2, populationH[0]);
	CGeneticHistogramme2 gh2(populationH2, 20, gh.getStep(), SEUIL);
	gh2.run(&hReference, debut);
	
	return 0;
}

void transformeBase(const char *src, const char *dst, CHistogramme *histogramme, Digest& digest) {
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
	//gdImageJpg(imDst, out, -1);
	gdImagePng(imDst, out);
	
	fclose(out);
	gdImageDestroy(imDst);
	gdImageDestroy(imSrc);
	
	ph_image_digest(dst, 1.0, 1.0, digest, 180);
}

void initPopulationH(CIndividuHistogramme **population) {
    int i;
    
    for(i=0;i<TAILLE_POPULATION;i++) {
        population[i] = new CIndividuHistogramme(WIDTH, HEIGHT, POINT_SIZE);
    }
}

void initPopulationH2(CIndividuHistogramme2 **population, CIndividuHistogramme *best) {
	int i;
    
    for(i=0;i<TAILLE_POPULATION;i++) {
        population[i] = new CIndividuHistogramme2(best);
    }
}
