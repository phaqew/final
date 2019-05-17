#include <cmath>
#include "bitmap.cpp"

void lpls(Bitmap *p){//Laplace edge detection
	float **c = new float*[p->height];
	for(int i = 0; i < p->height; i++) c[i] = new float[p->width];
	float m = 0;
	for(int y = 1; y < p->height - 1; y++){
		for(int x = 1; x < p->width - 1; x++){
			c[y][x] = fabs((float)p->px[y - 1][x] + (float)p->px[y + 1][x] + (float)p->px[y][x - 1]
			+ (float)p->px[y][x + 1] + (float)p->px[y - 1][x - 1] + (float)p->px[y - 1][x + 1]
			+ (float)p->px[y + 1][x - 1] + (float)p->px[y + 1][x + 1] - 8.0 * (float)p->px[y][x]);
			if(c[y][x] > m) m = c[y][x];
		}
	}
	m = 255.0 / m;
	for(int y = 1; y < p->height - 1; y++)
		for(int x = 1; x < p->width - 1; x++)
			p->px[y][x] = m * c[y][x];
	//remove undefined zones
	for(int i = 0; i < p->height; i++) {p->px[i][0] = 0; p->px[i][p->width - 1] = 0;}
	for(int i = 0; i < p->width; i++) {p->px[0][i] = 0; p->px[p->height - 1][i] = 0;}
}

void sobe(Bitmap *p){//Sobel edge detector
	float **c = new float*[p->height];
	for(int i = 0; i < p->height; i++) c[i] = new float[p->width];
	float q = 1e9, a = 0;
	for(int y = 1; y < p->height - 1; y++){
		for(int x = 1; x < p->width - 1; x++){
			c[y][x] = fabs(p->px[y - 1][x - 1] + 2 * p->px[y - 1][x] + p->px[y - 1][x + 1]
				- p->px[y + 1][x - 1] - 2 * p->px[y + 1][x] - p->px[y + 1][x + 1])
				+ fabs(p->px[y - 1][x - 1] + 2 * p->px[y][x - 1] + p->px[y + 1][x - 1]
				- p->px[y - 1][x + 1] - 2 * p->px[y][x + 1] - p->px[y + 1][x + 1]);
			if(c[y][x] > a) a = c[y][x];
			if(c[y][x] < q) q = c[y][x];
		}
	}
	a = 255.0 / (a - q);
	for(int y = 1; y < p->height - 1; y++)
		for(int x = 1; x < p->width - 1; x++)
			p->px[y][x] = a * (c[y][x] - q);
	//remove undefined zones
	for(int i = 0; i < p->height; i++) {p->px[i][0] = 0; p->px[i][p->width - 1] = 0;}
	for(int i = 0; i < p->width; i++) {p->px[0][i] = 0; p->px[p->height - 1][i] = 0;}
}

void rns(Bitmap *p, bool **f, int l, int y, int x){ //recursive naignbor search
	if(x < 0 || y < 0 || x >= p->width || y >= p->height) return;
	if(x > 0) if(!f[y][x-1]) if(p->px[y][x-1] > l) {
		f[y][x-1] = true;
		rns(p, f, l, y, x - 1);
	}
	if(y > 0) if(!f[y-1][x]) if(p->px[y-1][x] > l) {
		f[y-1][x] = true;
		rns(p, f, l, y - 1, x);
	}
	if(x < p->width - 1) if(!f[y][x+1]) if(p->px[y][x+1] > l) {
		f[y][x+1] = true;
		rns(p, f, l, y, x + 1);
	}
	if(y < p->height - 1) if(!f[y+1][x]) if(p->px[y+1][x] > l) {
		f[y+1][x] = true;
		rns(p, f, l, y + 1, x);
	}
	return;
}

void cany(Bitmap *p, int l, int h){//supression for canny algorithm
	bool **f = new bool*[p->height];
	for(int i = 0; i < p->height; i++){
		f[i] = new bool[p->width];
		for(int j = 0; j < p->width; j++) f[i][j] = (p->px[i][j] > h);
	}
	for(int y = 0; y < p->height; y++)
		for(int x = 0; x < p->width; x++)
			if(f[y][x]) rns(p, f, l, y, x);
	for(int y = 0; y < p->height; y++)
		for(int x = 0; x < p->width; x++)
			p->px[y][x] = f[y][x] ? 255 : 0;
}

//draw line y=kx+b on g in given color using DDA
void drawLine(Bitmap* g, double k, double b, BYTE C = 255){
	if(k <= 1 && k >= -1){
		double r = b + 0.5;
		for(int x = 0; x < g->width; x++){
			if(r >= 0 && r < g->height - 1)
				if(g->px[(int)r][x] < C) g->px[(int)r][x] = C;
			r += k;
		}
	}
	else{
		b /= -k;
		k = 1 / k;
		double r = b + 0.5;
		for(int y = 0; y < g->height; y++){
			if(r >= 0 && r < g->width - 1)
				if(g->px[y][(int)r] < C) g->px[y][(int)r] = C;
			r += k;
		}
	}
}

void hough(Bitmap* p){
	int **h = new int*[180]; //calculate h for each degree
	int N = p->width + p->height;
	for(int i = 0; i < 180; i++){
		h[i] = new int[N];
		for(int d = 0; d < N; d++) h[i][d] = 0;
	}
	double x, y = -(double)p->height / 2.0;
	for(int yi = 0; yi < p->height; yi++){
		x = -(double)p->width / 2.0;
		for(int xi = 0; xi < p->width; xi++){
			for(int i = 0; i < 180; i++){
				double d = y * cos(((double)i - 90) / 180 * M_PI)
					- x * sin(((double)i - 90) / 180 * M_PI);
				h[i][(int)((double)N / 2 + d + 0.5)] += p->px[yi][xi];
			}
			p->px[yi][xi] = 0;
			x += 1;
		}
		y += 1;
	}
	int m = 0;
	for(int i = 0; i < 180; i++)
		for(int d = 0; d < N; d++)
			if(h[i][d] > m) m = h[i][d];
	
	for(int i = 1; i < 179; i++){
		for(int d = 1; d < N-1; d++){
			if(h[i][d] >= h[i-1][d] && h[i][d] >= h[i+1][d] && h[i][d] >= h[i][d-1] && h[i][d] >= h[i][d+1]){
				double t = ((double)i - 90) / 180 * M_PI;
				int c = 255 * ((double)h[i][d] / (double)m) * ((double)h[i][d] / (double)m);
				drawLine(p, tan(t), (double)p->height / 2 - (double)p->width / 2 * tan(t) 
					+ ((double)d - (double)N / 2) / cos(t), c);
			}
		}
	}
}

int main(){
	BMP256 *p[6][3];
	//read files and extract edges
	char n[] = "test0.bmp";
	for(int i = 0; i < 6; i++){
		n[4] = '1' + i;
		p[i][0] = new BMP256(n);
		p[i][1] = new BMP256(p[i][0]);
		lpls(p[i][0]);
		p[i][0]->addNameSuffix("_lpls");
		p[i][0]->writeFile();
		sobe(p[i][1]);
		p[i][1]->addNameSuffix("_sobe");
		p[i][1]->writeFile();
		p[i][2] = new BMP256(p[i][1]);
		cany(p[i][2], 50, 140); //high and low gate
		p[i][2]->addNameSuffix("_cany");
		p[i][2]->writeFile();
	}
	//process hough transformation
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 3; j++){
			hough(p[i][j]);
			p[i][j]->addNameSuffix("_hough");
			p[i][j]->writeFile();
		}
	}
	return 0;
}
