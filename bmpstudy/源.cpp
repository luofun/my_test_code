#pragma pack(1)
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

struct tagBITMAP_FILE
{
	BITMAPFILEHEADER bitmapheader;   //文件头结构       
	BITMAPINFOHEADER bitmapinfoheader;  //位图信息段结构       
	//PALETTEENTRY palette[256];   //调色板结构       
	//UCHAR *buffer;   //UCHAR大小1字节(同BYTE), 在VC6下  
};

struct myRGB
{
	BYTE blue;
	BYTE green;
	BYTE red;
};

int main(int argc,char* argv[])
{
	FILE* fp;
	FILE* fpg;
	tagBITMAP_FILE bmp;
	tagBITMAP_FILE bmpg;
	PALETTEENTRY gpalette[256];
	myRGB *bmpp;
	BYTE *bmpgp;
	int cnt[256];
	double f[256];
	int cntrgb[3][256];
	double frgb[3][256];

	fp = fopen("xue.bmp", "rb");
	fpg = fopen("gxue.bmp", "rb");
	
	system("python bmppy.py");

	fread(&bmp, sizeof(bmp), 1, fp);
	fread(&bmpg, sizeof(bmpg), 1, fpg);
	
	printf("\nxue.bmp cinfo: bftype = %x\tbfsize = %d\tbfreserved1 = %d\tbfreserved2 = %d\tbfoffbits = %d\n", bmp.bitmapheader.bfType, bmp.bitmapheader.bfSize, bmp.bitmapheader.bfReserved1, bmp.bitmapheader.bfReserved2, bmp.bitmapheader.bfOffBits);
	printf("bisize = %d\tbiwidth = %d\tbiheight = %d\tbiplanes = %d\tbibitcount = %d\tbicompression = %d\tbisizeimage = %d\tbixpelspermeter = %d\tbiypelspermeter = %d\tbiclrused = %d\tbiclrused=%d\n", bmp.bitmapinfoheader.biSize, bmp.bitmapinfoheader.biWidth, bmp.bitmapinfoheader.biHeight, bmp.bitmapinfoheader.biPlanes, bmp.bitmapinfoheader.biBitCount, bmp.bitmapinfoheader.biCompression, bmp.bitmapinfoheader.biSizeImage, bmp.bitmapinfoheader.biXPelsPerMeter, bmp.bitmapinfoheader.biYPelsPerMeter, bmp.bitmapinfoheader.biClrUsed, bmp.bitmapinfoheader.biClrImportant);
	
	printf("\ngxue.bmp cinfo: bftype = %x\tbfsize = %d\tbfreserved1 = %d\tbfreserved2 = %d\tbfoffbits = %d\n", bmpg.bitmapheader.bfType, bmpg.bitmapheader.bfSize, bmpg.bitmapheader.bfReserved1, bmpg.bitmapheader.bfReserved2, bmpg.bitmapheader.bfOffBits);
	printf("bisize = %d\tbiwidth = %d\tbiheight = %d\tbiplanes = %d\tbibitcount = %d\tbicompression = %d\tbisizeimage = %d\tbixpelspermeter = %d\tbiypelspermeter = %d\tbiclrused = %d\tbiclrused=%d\n", bmpg.bitmapinfoheader.biSize, bmpg.bitmapinfoheader.biWidth, bmpg.bitmapinfoheader.biHeight, bmpg.bitmapinfoheader.biPlanes, bmpg.bitmapinfoheader.biBitCount, bmpg.bitmapinfoheader.biCompression, bmpg.bitmapinfoheader.biSizeImage, bmpg.bitmapinfoheader.biXPelsPerMeter, bmpg.bitmapinfoheader.biYPelsPerMeter, bmpg.bitmapinfoheader.biClrUsed, bmpg.bitmapinfoheader.biClrImportant);

	fread(gpalette, sizeof(gpalette), 1, fpg);

	bmpp = (myRGB*)malloc(sizeof(myRGB)*bmp.bitmapinfoheader.biSizeImage / 3);
	bmpgp = (BYTE*)malloc(sizeof(BYTE)*bmpg.bitmapinfoheader.biSizeImage);

	fread(bmpp, sizeof(myRGB)*bmp.bitmapinfoheader.biSizeImage / 3, 1, fp);
	fread(bmpgp, sizeof(BYTE)*bmpg.bitmapinfoheader.biSizeImage, 1, fpg);

	memset(cnt, 0, sizeof(cnt));
	memset(f, 0, sizeof(f));
	memset(cntrgb, 0, sizeof(cntrgb));
	memset(frgb, 0, sizeof(frgb));

	for (int i = 0; i < bmpg.bitmapinfoheader.biSizeImage; i++)
	{
		cnt[bmpgp[i]] = cnt[bmpgp[i]] + 1;
	}

	for (int i = 0; i < 256; i++)
	{
		f[i] = (double)cnt[i] / (double)bmpg.bitmapinfoheader.biSizeImage;	
	}

	for (int i = 1; i < 256; i++)
	{
		f[i] = f[i] + f[i - 1];
	}

	for (int i = 0; i < 256; i++)
	{
		f[i] = f[i] * 255;
	}

	for (int i = 0; i < bmpg.bitmapinfoheader.biSizeImage; i++)
	{
		bmpgp[i] = (BYTE)(f[bmpgp[i]] + 0.5);
	}

	for (int i = 0; i < bmp.bitmapinfoheader.biSizeImage / 3; i++)
	{
		cntrgb[0][bmpp[i].blue] = cntrgb[0][bmpp[i].blue] + 1;
		cntrgb[1][bmpp[i].green] = cntrgb[1][bmpp[i].green] + 1;
		cntrgb[2][bmpp[i].red] = cntrgb[2][bmpp[i].red] + 1;
	}

	for (int i = 0; i < 256; i++)
	{
		frgb[0][i] = (double)cntrgb[0][i] / (double)bmp.bitmapinfoheader.biSizeImage * (double)3;
		frgb[1][i] = (double)cntrgb[1][i] / (double)bmp.bitmapinfoheader.biSizeImage * (double)3;
		frgb[2][i] = (double)cntrgb[2][i] / (double)bmp.bitmapinfoheader.biSizeImage * (double)3;
	}

	for (int i = 1; i < 256; i++)
	{
		frgb[0][i] = frgb[0][i] + frgb[0][i - 1];
		frgb[1][i] = frgb[1][i] + frgb[1][i - 1];
		frgb[2][i] = frgb[2][i] + frgb[2][i - 1];
	}

	for (int i = 0; i < 256; i++)
	{
		frgb[0][i] = frgb[0][i] * 255;
		frgb[1][i] = frgb[1][i] * 255;
		frgb[2][i] = frgb[2][i] * 255;
	}

	for (int i = 0; i < bmp.bitmapinfoheader.biSizeImage / 3; i++)
	{
		bmpp[i].blue = (BYTE)(frgb[0][bmpp[i].blue] + 0.5);
		bmpp[i].green = (BYTE)(frgb[1][bmpp[i].green] + 0.5);
		bmpp[i].red = (BYTE)(frgb[2][bmpp[i].red] + 0.5);
	}

	fclose(fp);
	fclose(fpg);

	fp = fopen("xuecolorout.bmp", "wb");
	fpg = fopen("xuegaryout.bmp", "wb");

	fwrite(&bmp, sizeof(bmp), 1, fp);
	fwrite(&bmpg, sizeof(bmpg), 1, fpg);
	fwrite(gpalette, sizeof(gpalette), 1, fpg);
	fwrite(bmpp, sizeof(myRGB)*bmp.bitmapinfoheader.biSizeImage / 3, 1, fp);
	fwrite(bmpgp, sizeof(BYTE)*bmpg.bitmapinfoheader.biSizeImage, 1, fpg);

	fclose(fp);
	fclose(fpg);

	system("python bmpoutpy.py");

	free(bmpp);
	free(bmpgp);	

	return 0;
}