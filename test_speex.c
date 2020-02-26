#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <speex/speex_echo.h>
#include <speex/speex_preprocess.h>

#define NN 160
#define TAIL 1600

#define BUFF_SIZE 320

int main(int argc, char **argv)
{
    FILE *outFile;
    FILE *inFile;

    SpeexPreprocessState *preprocessState;
    SpeexEchoState *echoState;
    int sampleRate = 16000;

    spx_int16_t inBuffer[BUFF_SIZE];

    spx_int16_t micBuff[BUFF_SIZE/2];
    spx_int16_t refBuff[BUFF_SIZE/2];
    spx_int16_t outBuffer[BUFF_SIZE/2];

    int read_size;

    FILE *micFile, *refFile;
    int i;
    float f;
    int isRight = 0;

    printf("length = %d\n", argc);

    switch (argc)
    {
        case 6:
            isRight = atoi(argv[5]);
        case 5:
            refFile = fopen(argv[4], "wb+");
            micFile = fopen(argv[3], "wb+");
        case 3:
            outFile = fopen(argv[2], "wb+");
        case 2:
            inFile = fopen(argv[1], "rb");
            break;
    }

    if (!outFile)
    {
        outFile = fopen("./outFile.pcm", "wb+");
    }
    if (!inFile)
    {
        inFile = fopen("./inFile.pcm", "rb");
    }
    if (!micFile)
    {
        micFile = fopen("micFile.pcm", "wb+");
    }
    if (!refFile)
    {
        refFile = fopen("./refFile.pcm", "wb+");
    }

    echoState = speex_echo_state_init(NN, TAIL);
    preprocessState = speex_preprocess_state_init(NN, sampleRate);
    speex_echo_ctl(echoState, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
    i = 1;
    speex_preprocess_ctl(preprocessState, SPEEX_PREPROCESS_SET_DENOISE, &i);
    i = 0;
    speex_preprocess_ctl(preprocessState, SPEEX_PREPROCESS_SET_AGC, &i);
    i = 16000;
    speex_preprocess_ctl(preprocessState, SPEEX_PREPROCESS_SET_AGC_LEVEL, &i);
    i = 0;
    speex_preprocess_ctl(preprocessState, SPEEX_PREPROCESS_SET_DEREVERB, &i);
    f = .0;
    speex_preprocess_ctl(preprocessState, SPEEX_PREPROCESS_SET_DEREVERB_DECAY, &f);
    f = .0;
    speex_preprocess_ctl(preprocessState, SPEEX_PREPROCESS_SET_DEREVERB_LEVEL, &f);
    speex_preprocess_ctl(preprocessState, SPEEX_PREPROCESS_SET_ECHO_STATE, echoState);

    printf("isRight = %d\n",isRight);

    while (!feof(inFile))
    {
        read_size = fread(inBuffer, sizeof(spx_int16_t), BUFF_SIZE, inFile);
        
        if (isRight == 0)
        {
            for (size_t i = 0; i < read_size; i = i + 2)
            {
                micBuff[i / 2] = inBuffer[i];
                refBuff[i / 2] = inBuffer[i + 1];
            }   
        }else{
            for (size_t i = 0; i < read_size; i = i + 2)
            {
                refBuff[i / 2] = inBuffer[i];
                micBuff[i / 2] = inBuffer[i + 1];
            }   
        }
        


        fwrite(micBuff, sizeof(spx_int16_t), BUFF_SIZE/2, micFile);
        fwrite(refBuff, sizeof(spx_int16_t), BUFF_SIZE/2, refFile);

        speex_echo_cancellation(echoState, micBuff, refBuff, outBuffer);
        speex_preprocess_run(preprocessState, outBuffer);
        fwrite(outBuffer, sizeof(spx_int16_t), BUFF_SIZE/2, outFile);
    }

    speex_echo_state_destroy(echoState);
    speex_preprocess_state_destroy(preprocessState);
    fclose(inFile);
    fclose(outFile);
    fclose(micFile);
    fclose(refFile);
    return 0;
}