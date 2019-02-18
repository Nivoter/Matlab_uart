#include <ch.h>
#include <hal.h>
#include <stdint.h>
#include <chprintf.h>

#define ADC1_NUM_CHANNELS 1
#define ADC1_BUF_DEPTH 1

static adcsample_t samples1[ADC1_NUM_CHANNELS * ADC1_BUF_DEPTH];

static const GPTConfig gpt4cfg1 = {
                                   .frequency = 100000,
                                   .callback = NULL,
                                   .cr2 = TIM_CR2_MMS_1,
                                   .dier = 0U
};

uint16_t *value = 0;

static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
  (void)adcp;
  value = buffer[0];
  (void)n;

}

static adcerrorcallback (ADCDriver *adcp, adcerror_t err)
{
  (void)adcp;
  (void)err;
}

static const ADCConversionGroup adcgrpcfg1 =
{
   .circular = true,
   .num_channels = ADC1_NUM_CHANNELS,
   .end_cb = adccallback,
   .error_cb = adcerrorcallback,
   .cr1 = 0,
   .cr2 = ADC_CR2_EXTEN_RISING | ADC_CR2_EXTSEL_SRC(0b1100),
   .smpr1 = ADC_SMPR1_SMP_AN10(ADC_SAMPLE_144),
   .smpr2 = 0,
   .sqr1 = ADC_SQR1_NUM_CH(ADC1_NUM_CHANNELS),
   .sqr2 = 0,
   .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)
};


static const SerialConfig letsgo= {
                                   .speed =115200,
                                   .cr1 = 0,
                                   .cr2 = 0,
                                   .cr3 = 0,
};


int main(void)
{

    char i = 0;
    int com = 2000;
    chSysInit();    //#
    halInit(); //#

    sdStart(&SD7,&letsgo);
    palSetPadMode(GPIOE,8,PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE,7,PAL_MODE_ALTERNATE(8));


    gptStart(&GPTD4, &gpt4cfg1);
    adcStart(&ADCD1, NULL);

    palSetLineMode(LINE_ADC123_IN10, PAL_MODE_INPUT_ANALOG);

    adcStartConversion(&ADCD1, &adcgrpcfg1, samples1, ADC1_BUF_DEPTH);
    gptStartContinuous(&GPTD4,gpt4cfg1.frequency/1000);

    palSetLine(LINE_LED1);

    while ( 1 )
    {

//            chprintf(((BaseSequentialStream *)&SD7), "%c",value%255);
//            chThdSleepMilliseconds(3);
//            chprintf(((BaseSequentialStream *)&SD7), "%d",value),
        sdWrite(&SD7,&value,2);
        chThdSleepMilliseconds(3);

    }
}
