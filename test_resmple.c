#include<stdio.h>
#include<speex/speex_resampler.h>

int main(){
    SpeexResamplerState *resampler;
    int err = 0;
    resampler = speex_resampler_init(1,48000,16000,10,&err);
    FILE *f;
    f = fopen("/mnt/d/workSpacess/test.pcm", "rb+");
    return 0;
}