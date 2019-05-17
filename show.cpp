#include "bitmap.cpp"
#define DIM 0.5
int main() {
	char f[] = "test-.bmp";
	char g[3][26] = {"test-_lpls_hough.bmp", "test-_sobe_hough.bmp", "test-_sobe_cany_hough.bmp"};
	char h[] = "show--.bmp";
	BMP256 *a, *b;
	BMP24 *c;
	for(int n = 0; n < 6; n++) {
		f[4] = h[4] = '1' + n;
		a = new BMP256(f);
		for(int m = 0; m < 3; m++) {
			g[m][4] = '1' + n;
			h[5] = '1' + m;
			b = new BMP256(g[m]);
			c = new BMP24(a);
			for(int i = 0; i < c->height; i++) {
				for(int j = 0; j < c->width; j++) {
					double t = (double)a->px[i][j] * DIM;
					c->px[i][j].R = t;
					c->px[i][j].G = t + (255.0 - t) * (double)b->px[i][j] / 255.0;
					c->px[i][j].B = t;
				}
			}
			c->writeFile(h);
		}
	}
}
