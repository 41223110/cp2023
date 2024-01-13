#include <stdio.h>
#include <gd.h>
#include <math.h>

void draw_roc_flag(gdImagePtr img);
void draw_single_diamond(gdImagePtr img, int center_x, int center_y, int sun_radius, int color);

int main() {
    // width 3: height 2
    int width = 1200;
    // 國旗長寬比為 3:2
    int height = (int)(width * 2.0 / 3.0);

    gdImagePtr img = gdImageCreateTrueColor(width, height);
    gdImageAlphaBlending(img, 0);

    draw_roc_flag(img);

    FILE *outputFile = fopen("./../images/single_diamond.png", "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening the output file.\n");
        return 1;
    }
    gdImagePngEx(img, outputFile, 9);
    fclose(outputFile);
    gdImageDestroy(img);
    return 0;
}

void draw_roc_flag(gdImagePtr img) {
    int width = gdImageSX(img);
    int height = gdImageSY(img);
    int red, white, blue;
    int center_x = (int)(width / 4);
    int center_y = (int)(height / 4);
    int sun_radius = (int)(width / 8);

    red = gdImageColorAllocate(img, 255, 0, 0);    // 紅色
    white = gdImageColorAllocate(img, 255, 255, 255); // 白色
    blue = gdImageColorAllocate(img, 0, 0, 149);     // 藍色

    gdImageFilledRectangle(img, 0, 0, width, height, red);
    gdImageFilledRectangle(img, 0, 0, (int)(width / 2.0), (int)(height / 2.0), blue);
    draw_single_diamond(img, center_x, center_y, sun_radius, white);
}

void draw_single_diamond(gdImagePtr img, int center_x, int center_y, int sun_radius, int color) {
    float deg = M_PI / 180;
    float sr = sun_radius / tan(75 * deg);
    int ax, ay, bx, by, dx, dy, ex, ey;
    gdPoint points[4];

    ax = center_x;
    ay = center_y - sun_radius;
    bx = center_x - sun_radius * tan(15 * deg);
    by = center_y;
    ex = center_x;
    ey = center_y + sun_radius;
    dx = center_x + sun_radius * tan(15 * deg);
    dy = center_y;

    // A
    points[0].x = ax + sun_radius * sin(30 * deg);
    points[0].y = ay + sun_radius - sun_radius * cos(30 * deg);
    // B
    points[1].x = bx + sr - sr * cos(30 * deg);
    points[1].y = by - sr * sin(30 * deg);
    // E
    points[2].x = ex - sun_radius * sin(30 * deg);
    points[2].y = ey - (sun_radius - sun_radius * cos(30 * deg));
    // D
    points[3].x = dx - (sr - sr * cos(30 * deg));
    points[3].y = dy + sr * sin(30 * deg);

    // 對單一菱形區域範圍塗色
    gdImageFilledPolygon(img, points, 4, color);
    // 在菱形區域外圍畫線, 明確界定菱形範圍
    gdImagePolygon(img, points, 4, color);
}
