#include <stdio.h>
#include <gd.h>

void draw_japan_flag(gdImagePtr img, int width, int height);

int main() {
    // 設定國旗寬度和高度（這裡假設為 600x400）
    int width = 600;
    int height = 400;

    gdImagePtr img = gdImageCreateTrueColor(width, height);
    gdImageAlphaBlending(img, 0);

    draw_japan_flag(img, width, height);

    FILE *outputFile = fopen("./../images/japan_flag_in_gd.png", "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening the output file.\n");
        return 1;
    }
    gdImagePngEx(img, outputFile, 9);
    fclose(outputFile);
    gdImageDestroy(img);

    return 0;
}

void draw_japan_flag(gdImagePtr img, int width, int height) {
    int red, white;

    // 設定顏色值
    red = gdImageColorAllocate(img, 255, 0, 0);   // 紅色
    white = gdImageColorAllocate(img, 255, 255, 255); // 白色

    // 填充整個背景為白色
    gdImageFilledRectangle(img, 0, 0, width, height, white);

    // 計算圓心座標
    int center_x = width / 2;
    int center_y = height / 2;

    // 計算圓的半徑，使其為寬度的 3/5
    int radius = (int)(width * 3.0 / 10.0);

    // 繪製紅色圓（太陽）
    gdImageFilledEllipse(img, center_x, center_y, radius * 1.2, radius * 1.2, red);
}

