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

//draw line (y-H/2)cost-(x-W/2)sint=b on g in given color
void drawLine(Bitmap* g, double t, double d, BYTE C = 255){
	if(t == -90){ //vertical
		int r = g->width / 2 + d;
		if(r >= 0 && r < g->width)
			for(int y = 0; y < g->height; y++)
				if(g->px[y][r] < C) g->px[y][r] = C;
	}
	else if(t < -45 || t > 45){
		t *= M_PI / 180;
		d /= sin(t); 
		t = 1 / tan(t);
		double s = (double)g->width / 2 - t * (double)g->height / 2 - d + 0.5;
		for(int y = 0; y < g->height; y++){
			if(s >= 0 && s < g->width)
				if(g->px[y][(int)s] < C) g->px[y][(int)s] = C;
			s += t;
		}
	}
	else{
		t *= M_PI / 180;
		d /= cos(t); 
		t = tan(t);
		double s = (double)g->height / 2 - t * (double)g->width / 2 + d + 0.5;
		for(int x = 0; x < g->width; x++){
			if(s >= 0 && s < g->height)
				if(g->px[(int)s][x] < C) g->px[(int)s][x] = C;
			s += t;
		}
	}
}

void hough(Bitmap* p){
	//initial
	double **h = new double*[180];
	double cs[180], sn[180];
	int N = p->width + p->height;
	for(int i = 0; i < 180; i++){
		h[i] = new double[N];
		cs[i] = cos(((double)i - 90) / 180 * M_PI);
		sn[i] = sin(((double)i - 90) / 180 * M_PI);
		for(int d = 0; d < N; d++) h[i][d] = 0;
	}
	//calculate hough
	double x, y = -(double)p->height / 2.0;
	for(int yi = 0; yi < p->height; yi++){
		x = -(double)p->width / 2.0;
		for(int xi = 0; xi < p->width; xi++){
			for(int i = 0; i < 180; i++){
				double d = y * cs[i] - x * sn[i];
				h[i][(int)((double)N / 2 + d + 0.5)] += p->px[yi][xi];
			}
			p->px[yi][xi] = 0;
			x += 1;
		}
		y += 1;
	}
	//output hough space
	double m = 0;
	for(int i = 0; i < 180; i++)
		for(int d = 0; d < N; d++)
			if(h[i][d] > m) m = h[i][d];
	BMP256 f(N, 180);
	for(int i = 0; i < 180; i++){
		for(int d = 0; d < N; d++){
			h[i][d] = 255.0 * h[i][d] / m * h[i][d] / m;
			f.px[d][i] = (int)h[i][d];
		}
	}
	f.setName(p->name, "bmp");
	f.addNameSuffix("_hough");
	f.writeFile();
	//get lines
	for(int i = 0; i < 180; i++){
		for(int d = 0; d < N; d++){
			//if(h[i][d] >= h[i-1][d] && h[i][d] >= h[i+1][d] && h[i][d] >= h[i][d-1] && h[i][d] >= h[i][d+1]){
				drawLine(p, i - 90, d - N / 2, h[i][d]);
			//}
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
		p[i][1]->addNameSuffix("_sob");
		p[i][1]->writeFile();
		p[i][2] = new BMP256(p[i][1]);
		cany(p[i][2], 50, 140); //high and low gate
		p[i][2]->addNameSuffix("cny");
		p[i][2]->writeFile();
	}
	//process hough transformation
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 3; j++){
			hough(p[i][j]);
			p[i][j]->addNameSuffix("_line");
			p[i][j]->writeFile();
		}
	}
	return 0;
}
