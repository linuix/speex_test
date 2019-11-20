#include<stdio.h>
#include<speex/speex_echo.h>
#include<speex/speex_preprocess.h>

#define NN 320
#define TAIL 1600


int main(int argc, char **argv){
    FILE *outFile;
    FILE *inFile;

    SpeexPreprocessState *preprocessState;
    SpeexEchoState *echoState;
    int sampleRate  16000;

    short inBuffer[NN],outBuffer[NN];

    if (argc = 2)
    {
        inFile = fopen(argv[1]);
        outFile = fopen(argv[2]);
    }else if (argc == 1)
    {
        inFile = fopen(argv[1]);
        outFile = fopen("./outFile.pcm");
    }
    else
    {
        inFile = fopen("./inFile.pcm");
        outFile = fopen("./outFile.pcm");
    }

    echoState = speex_echo_state_init(NN,TAIL);
    preprocessState = speex_preprocess_state_init(NN,sampleRate)
    speex_echo_ctl(echoState, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
    speex_preprocess_ctl(preprocessState, SPEEX_PREPROCESS_SET_ECHO_STATE, echoState);



    while (!feof(inFile))
    {
        fread(inBuffer,NN,1,inFile);
        
    }
    


    int err = 0;
    return 0;
}