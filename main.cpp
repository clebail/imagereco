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
#include "CGeneticDigest.h"

#define POINT_SIZE				2
#define WIDTH					512
#define HEIGHT					512
#define NB_COLOR                ((WIDTH / POINT_SIZE) * (HEIGHT / POINT_SIZE))
#define TAILLE_POPULATION       200

void transformeBase(const char *src, const char *dst, CHistogramme *histogramme, Digest& digest);
void initPopulationH(CIndividuHistogramme **population);
void initPopulationD(CIndividuDigest **population, CIndividuHistogramme *individu);

int main(void) {
	CHistogramme hReference;
	Digest dReference;
    CIndividuHistogramme *populationH[TAILLE_POPULATION];
	CIndividuDigest *populationD[TAILLE_POPULATION];
	
	transformeBase("Lenna.jpg", "/tmp/base.png", &hReference, dReference);
	srand(time(NULL));
	
	initPopulationH(populationH);
    CGeneticHistogramme gh(populationH, TAILLE_POPULATION, 0);
    gh.run(&hReference, time(NULL));
	
	initPopulationD(populationD, populationH[0]);
	CGeneticDigest gd(populationD, TAILLE_POPULATION, gh.getStep());
	gd.run(&dReference, gh.getTime());
	
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

void initPopulationD(CIndividuDigest **population, CIndividuHistogramme *individu) {
	int i;
    
    for(i=0;i<TAILLE_POPULATION;i++) {
		population[i] = new CIndividuDigest(dynamic_cast<CIndividu<CHistogramme *, int> *>(individu));
    }
}
