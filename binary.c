#include<stdio.h>
int main(){
    // y = 2^x (x=-10~10)
    for (float x = -10.0; x <= 10.0; x += 0.25){
        // xの固定小数点表現 (少数部23ビット)
        int32_t fxp_x = x * (float)(1 << 23);

        // 整数部に127をオフセット
        int32_t tmp = fxp_x + (127 << 23);
        // float型として解釈すれば概ね 2^x となる
        float y = *(float*)&tmp;

        printf("%f, %f\n", x, y);
    }
    // y = log2(x) (x=0.001 ~ 1000)
    for (float x = 0.001; x <= 1000; x *= 1.1){
        // int32_t型として解釈
        int32_t tmp = *(int32_t*)&x;
        // 指数部に-127をオフセット(float型の指数部の仕様のため)
        // 概ね log2(x) の固定小数点表現となる
        int32_t fxp_y = tmp - (127 << 23);

        // 浮動小数点に換算
        float y = (float)fxp_y / (float)(1 << 23);

        printf("%f, %f\n", x, y);
    }
}