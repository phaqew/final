# ��������ҵ

### �Զ�����61 ������ 2140506114

ע��������е�[����]()�鿴�����ļ�
������ԭʼδѹ��ͼƬ�϶࣬����ʱ���Ƚϳ�

---

* �����ҵ���˼���PNG��JPG��ʽ��ͼƬ���䲻��λͼ��ʵ���ǳ����ҵ�������Χ�����ò���ת��256ɫλͼ��ʹ��Adobe Photoshop����

* ��ǰ������ҵд��BMP����һ�����ص����⣬�ڴ˴ε������б�¶�˳�����

�ɰ�ģ���BMP256(const char*)��void writeFile(int, int, const char*)�Ⱥ����г��֣���
```
int dataSizePerLine = ((width + 7) / 8) * 8;
```

��һ��������ÿ�����ݶ�Ҫ8Byte���룬Ȼ��BMP�ļ�Ӧ����4Byte���룬ǰ���ε���������512x512����������������133x134�����Ĵ��ɶ��뵽8�ı������������һֱ������û�з��֣��ڴ˴εĶ�������вŸ��ֳ�������test4��739x466��������Ϊ��д�ļ��������󣬳��ֹ���ĺ�ɫб�ߡ�

Ӧ��Ϊ�����[bitmap.cpp](bitmap.cpp)����
```
int dataSizePerLine = ((width + 3) / 4) * 4;
```

* �������ÿ����˲���ȡ��Ե�����ﳢ���˸Ľ���������˹��Sobel���ַ�ʽ����ʽ�ֱ�Ϊ��

![](eqn1.gif)

![](eqn2.gif)

��Ȼ��Ҫ���й�һ�������[hw7.cpp](hw7.cpp)�е�void lpls(Bitmap*)��void sobe(Bitmap*)������

* Canny��ͨ��ǡ����ѡȡ˫���޿��Ժܺõ���ȡ��Ե��һ�������sobel�˲�֮�����[hw7.cpp](hw7.cpp)�е�void cany(Bitmap*, int, int)�������Ƚ����ڸ����޵ĵ�ѡ����Ȼ����õݹ��������������չѡ���ڽӵģ�4���򣩸��ڵ����޵ĵ㡣��Ϊ�����������ͳһѡ��140��50��Ϊ�ߵ����ޣ�

*ע�������͸ߵ����޲���ѡȡ������ܻ�ݹ鱬ջ�����ֶ�����������ѡ��*

* ���������������Ե��ȡ��������Խ���hough�任��һ����ȡͼ�е�ֱ�߱�Ե������ֱ�߷��̵�����������ԭͼ��һ��ֱ�߶�Ӧ�����ռ��һ���㣬ԭͼ��һ�����Ӧ�����ռ��һ���ߣ������ߵ���״�ɲ���������ʽ����������򵥵�ֱ�߷���ʽax+by=1�����ڲ�����ֵ�򲻶����ֲ�Ҳ�ܲ����ȣ�ʵ���Ϻ���ʹ�á��ȽϺõķ�ʽ�Ǽ�������ʽ�����Զ�ֱ�ߴؽ��еȽǶȡ��Ⱦ�������������������Ĳ�ͼ��

![](��ͼ.png)

*x�����ȡֵ��Χ��0,W-1��y�����ȡֵ��Χ��0,H-1*
�������ڵ�(x,y)���Եõ������ռ��һ������(y-H/2)cost-(x-W/2)sint=d����ֵ��ܺ�ȷ����tΪ-90�ȵ�90�ȣ�d��������2/4����W+H�������ǿ��Ա���ÿ���Ƕ�ֵ���������1��ȡ�������Ǻ���ֵ������ǰ������洢�����Լ��ټ��㣩�����d���������뵽�ڽ��ĸ�㣬ʹ�����ռ��иô���ֵ����ԭͼ��(x,y)��ĻҶ�ֵ��

* ����һ����ܸ��Ӷ�HxWxD=���������ԽǶȲ��������õ�hough�ռ�Ķ�Ԫ����ֵ�����еļ�������ֵ��Ͷ�Ӧ��ԭͼ�ļ���ֱ�߱�Ե��
���ڸ߶���ɢ����ȡ��ֵ�����ѣ����������͵���ķ�ʽ���ʵ���ǿ�ϴ�Ĳ��֣�������ƽ�����һ������Ȼ����Ȩֵ�������е��Ӧ�ĵ�ֱ�ߡ����[hw7.cpp](hw7.cpp)�е�void hough(Bitmap*)������

* Ϊ��ֱ�۵ر�ʾ��ֱ����ԭͼ�е�λ�ã�������Bitmap���������BMP24��24λ���ɫλͼ���ࣨ���[bitmap.cpp](bitmap.cpp)������[show.cpp](show.cpp)�ж�ȡǰ�����ɵĽ������ԭͼ�ϵ�����ɫ�ģ���˵��ɫ�Ƚ���Ŀ��ֱ�߱�Ե�����õ��Ľ�����£�

*���ϵ�������Ϊԭͼ����Ե��ȡ��hough�任��ֱ�߱�Ե�����ӽ��*

> test1

![](test1.bmp)

������˹|Sobel|Sobel+Canny
--|--|--
![](test1_lpls.bmp)|![](test1_sob.bmp)|![](test1_sobcny.bmp)
![](test1_lpls_hough.bmp)|![](test1_sob_hough.bmp)|![](test1_sobcny_hough.bmp)
![](test1_lpls_line.bmp)|![](test1_sob_line.bmp)|![](test1_sobcny_line.bmp)
![](test1_lpls_line_show.bmp)|![](test1_sob_line_show.bmp)|![](test1_sobcny_line_show.bmp)

> test2

![](test2.bmp)

������˹|Sobel|Sobel+Canny
--|--|--
![](test2_lpls.bmp)|![](test2_sob.bmp)|![](test2_sobcny.bmp)
![](test2_lpls_hough.bmp)|![](test2_sob_hough.bmp)|![](test2_sobcny_hough.bmp)
![](test2_lpls_line.bmp)|![](test2_sob_line.bmp)|![](test2_sobcny_line.bmp)
![](test2_lpls_line_show.bmp)|![](test2_sob_line_show.bmp)|![](test2_sobcny_line_show.bmp)

> test3

![](test3.bmp)

������˹|Sobel|Sobel+Canny
--|--|--
![](test3_lpls.bmp)|![](test3_sob.bmp)|![](test3_sobcny.bmp)
![](test3_lpls_hough.bmp)|![](test3_sob_hough.bmp)|![](test3_sobcny_hough.bmp)
![](test3_lpls_line.bmp)|![](test3_sob_line.bmp)|![](test3_sobcny_line.bmp)
![](test3_lpls_line_show.bmp)|![](test3_sob_line_show.bmp)|![](test3_sobcny_line_show.bmp)

> test4

![](test4.bmp)

������˹|Sobel|Sobel+Canny
--|--|--
![](test4_lpls.bmp)|![](test4_sob.bmp)|![](test4_sobcny.bmp)
![](test4_lpls_hough.bmp)|![](test4_sob_hough.bmp)|![](test4_sobcny_hough.bmp)
![](test4_lpls_line.bmp)|![](test4_sob_line.bmp)|![](test4_sobcny_line.bmp)
![](test4_lpls_line_show.bmp)|![](test4_sob_line_show.bmp)|![](test4_sobcny_line_show.bmp)

> test5

![](test5.bmp)

������˹|Sobel|Sobel+Canny
--|--|--
![](test5_lpls.bmp)|![](test5_sob.bmp)|![](test5_sobcny.bmp)
![](test5_lpls_hough.bmp)|![](test5_sob_hough.bmp)|![](test5_sobcny_hough.bmp)
![](test5_lpls_line.bmp)|![](test5_sob_line.bmp)|![](test5_sobcny_line.bmp)
![](test5_lpls_line_show.bmp)|![](test5_sob_line_show.bmp)|![](test5_sobcny_line_show.bmp)

> test6

![](test6.bmp)

������˹|Sobel|Sobel+Canny
--|--|--
![](test6_lpls.bmp)|![](test6_sob.bmp)|![](test6_sobcny.bmp)
![](test6_lpls_hough.bmp)|![](test6_sob_hough.bmp)|![](test6_sobcny_hough.bmp)
![](test6_lpls_line.bmp)|![](test6_sob_line.bmp)|![](test6_sobcny_line.bmp)
![](test6_lpls_line_show.bmp)|![](test6_sob_line_show.bmp)|![](test6_sobcny_line_show.bmp)
