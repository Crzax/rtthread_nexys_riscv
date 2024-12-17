#if defined(D_NEXYS_A7)
   #include "bsp_printf.h"
   #include "bsp_mem_map.h"
   #include "bsp_version.h"
#else
   PRE_COMPILED_MSG("no platform was defined")
#endif
#include "psp_api.h"
#include <rtthread.h>
#include "appdef.h"

typedef struct {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} RGB;

#define SIZE128

#ifdef SIZE128
    #define N 128
    #define M 128
    extern unsigned char SIZE_128x128[];
#else
    #define N 256
    #define M 256
    extern unsigned char SIZE_256x256[];
#endif

void continue_next(void) {
    rt_kprintf("请置状态为sw[15,14]=10来退出\n");
    while (1) { 
        unsigned int value = READ_SW();
        if (((value >> 15) & 1) == 1 && ((value >> 14) & 1) == 0) {
            return;
        }
    }
}

RGB ColourImage[N][M];
unsigned char GreyImage[N][M];


int whites;
int blacks;


void initColourImage(RGB image[N][M]) {
    int i,j;

    for (i=0;i<N;i++)
        for (j=0; j<M; j++) {
#ifdef SIZE128
            image[i][j].R = SIZE_128x128[(i*M + j)*3];
            image[i][j].G = SIZE_128x128[(i*M + j)*3 + 1];
            image[i][j].B = SIZE_128x128[(i*M + j)*3 + 2];
#else
            image[i][j].R = SIZE_256x256[(i*M + j)*3];
            image[i][j].G = SIZE_256x256[(i*M + j)*3 + 1];
            image[i][j].B = SIZE_256x256[(i*M + j)*3 + 2];
#endif
        }
}


int ColourToGrey_Pixel(int R, int G, int B) {
    return  (3483*R + 11718*G + 1183*B) /16384;
}


void WhiteAndBlackElements(unsigned char mat[N][M]) {
    int i,j;

    for (i=0;i<N;i++) {
        for (j=0; j<M; j++) {
            if ( mat[i][j] > 235) whites++;
            if ( mat[i][j] < 20)  blacks++;
        }
    }
}


#define filterSize 3

double filter[filterSize][filterSize] = {{0, 0.2, 0}, {0.2, 0.2, 0.2}, {0, 0.2, 0}};

RGB FilterColourImage[N][M];

void ImageFilter(RGB orig[N][M], RGB dest[N][M]){
    int i, j;
    int red, green, blue;
    int filterX, filterY;

    for(i = (filterSize-1)/2; i<(N-((filterSize-1)/2)); i++){
        for(j = (filterSize-1)/2; j<(M-((filterSize-1)/2)); j++){
            
            red=0;
            green=0;
            blue=0;

            for(filterX = 0; filterX<filterSize; filterX++){
                for(filterY = 0; filterY<filterSize; filterY++){
                    red += orig[i+filterX-1][j+filterY-1].R * filter[filterX][filterY];
                    green += orig[i+filterX-1][j+filterY-1].G * filter[filterX][filterY];
                    blue += orig[i+filterX-1][j+filterY-1].B * filter[filterX][filterY];
                }
            }

            dest[i][j].R = red;
            dest[i][j].G = green;
            dest[i][j].B = blue;
        }
    }
}


void ColourToGrey(RGB Colour[N][M], unsigned char Grey[N][M]) {
    int i,j;
    
    for (i=0;i<N;i++)
        for (j=0; j<M; j++)
            Grey[i][j] =  ColourToGrey_Pixel(Colour[i][j].R, Colour[i][j].G, Colour[i][j].B); 
}

void color2grey(void *parameter) {
    initColourImage(ColourImage);
    
    ColourToGrey(ColourImage,GreyImage);
    
    rt_kprintf("成功在内存生成灰度图像!\n");

    whites=0;
    blacks=0;
    WhiteAndBlackElements(GreyImage);

    rt_kprintf("Whites: %d\n", whites);
    rt_kprintf("Blacks: %d\n", blacks);
}

void color2grey_MSH(void) {
    rt_thread_t tid = rt_thread_create("color to greay",
                        color2grey, RT_NULL,
                        THREAD_STACK_SIZE,
                        THREAD_PRIORITY,
                        THREAD_TIMESLICE);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    rt_thread_delete(tid);
    rt_kprintf("成功退出灰度进程!\n");
}

MSH_CMD_EXPORT(color2grey_MSH, color to grey);

void blur_filter(void *parameter) {
    ImageFilter(ColourImage,FilterColourImage);
    
    ColourToGrey(ColourImage,GreyImage);
    
    rt_kprintf("成功在内存生成高斯模糊图像!\n");
}

void blur_filter_MSH(void) {
    rt_thread_t tid = rt_thread_create("blur filter",
                        blur_filter, RT_NULL,
                        THREAD_STACK_SIZE,
                        THREAD_PRIORITY,
                        THREAD_TIMESLICE);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    rt_thread_delete(tid);
    rt_kprintf("成功退出高斯模糊进程!\n");
}

MSH_CMD_EXPORT(blur_filter_MSH, blur filter);

void image_process(void) {
    rt_thread_t tid1 = rt_thread_create("color to greay",
                        color2grey, RT_NULL,
                        THREAD_STACK_SIZE,
                        THREAD_PRIORITY,
                        THREAD_TIMESLICE);

    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    rt_thread_t tid2 = rt_thread_create("blur filter",
                        blur_filter, RT_NULL,
                        THREAD_STACK_SIZE,
                        THREAD_PRIORITY,
                        THREAD_TIMESLICE);

    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    continue_next();
    rt_thread_delete(tid1);
    rt_thread_delete(tid2);
}

MSH_CMD_EXPORT(image_process, image process);

int main(void) {    
    return 0;
}