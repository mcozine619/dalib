#include <m_pd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define radians 2 * 3.14159265358979323846
#define PI    3.14159265358979323846

static t_class *dadecoder_tilde_class;






//STRUCTURE
typedef struct _dadecoder_tilde {

    t_object  x_obj;
    t_sample APf;
    t_symbol *x_dec;
    t_symbol decodermode;
    float dectype;
    t_sample;

} t_dadecoder_tilde;





//STEREO DECODE PERFORM
t_int *dadecoder_tilde_stereo(t_int *w)
{
    t_dadecoder_tilde *x = (t_dadecoder_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APin2 =    (t_sample *)(w[3]);

    t_sample  *APin3 =    (t_sample *)(w[4]);

    t_sample  *APin4 =    (t_sample *)(w[5]);

    t_sample  *APout1 =    (t_sample *)(w[6]);

    t_sample  *APout2 =    (t_sample *)(w[7]);

    int          APn =           (int)(w[8]);
  
    t_sample sample1, sample2, sample3, sample4;
    
    while (APn--)
    {
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //U
        
        //STEREO DECODE
        (*APout1++) =   sample1 * 0.707 + sample3 * 0.5;
        (*APout2++) =   sample1 * 0.707 + sample3 * -0.5;
        
    }
    
    
    return (w+9);
    
}



t_int *dadecoder_tilde_pent(t_int *w)
{
    t_dadecoder_tilde *x = (t_dadecoder_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APin2 =    (t_sample *)(w[3]);

    t_sample  *APin3 =    (t_sample *)(w[4]);

    t_sample  *APin4 =    (t_sample *)(w[5]);

    t_sample  *APin5 =    (t_sample *)(w[6]);

    t_sample  *APout1 =    (t_sample *)(w[7]);

    t_sample  *APout2 =    (t_sample *)(w[8]);

    t_sample  *APout3 =    (t_sample *)(w[9]);

    t_sample  *APout4 =    (t_sample *)(w[10]);

    t_sample  *APout5 =    (t_sample *)(w[11]);

    int          APn =           (int)(w[12]);
    
    t_sample sample1, sample2, sample3, sample4, sample5;
    
    while (APn--)
    {
        
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //U
        sample5 = (*APin5++); //V
       
        (*APout1++) =   sample1 * 0.405 + sample2 * 0.320 + sample3 * 0.310 + sample4 * 0.085 * sample5 * 0.125;
        (*APout2++) =   sample1 * 0.405 + sample2 * 0.320 + sample3 * -0.310 + sample4 * 0.085 * sample5 * -0.125;
        (*APout3++) =   sample1 * 0.085 + sample2 * 0.040 + sample3 * 0.000 + sample4 * 0.045 * sample5 * 0.000;
        (*APout4++) =   sample1 * 0.635 + sample2 * -0.335 + sample3 * 0.380 + sample4 * -0.080 * sample5 * 0.080;
        (*APout5++) =   sample1 * 0.635 + sample2 * -0.335 + sample3 * -0.280 + sample4 * -0.080 * sample5 * -0.080;
    }
    
    
    return (w+13);
    
}

t_int *dadecoder_tilde_cube(t_int *w)
{
    t_dadecoder_tilde *x = (t_dadecoder_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APin2 =    (t_sample *)(w[3]);

    t_sample  *APin3 =    (t_sample *)(w[4]);

    t_sample  *APin4 =    (t_sample *)(w[5]);

    t_sample  *APout1 =    (t_sample *)(w[6]);

    t_sample  *APout2 =    (t_sample *)(w[7]);

    t_sample  *APout3 =    (t_sample *)(w[8]);

    t_sample  *APout4 =    (t_sample *)(w[9]);

    t_sample  *APout5 =    (t_sample *)(w[10]);

    t_sample  *APout6 =    (t_sample *)(w[11]);

    t_sample  *APout7 =    (t_sample *)(w[12]);

    t_sample  *APout8 =    (t_sample *)(w[13]);

    int          APn =           (int)(w[14]);
    
    t_sample sample1, sample2, sample3, sample4;
    
    while (APn--)
    {
        
        sample1 = (*APin1++); //W
        sample2 = (*APin2++); //X
        sample3 = (*APin3++); //Y
        sample4 = (*APin4++); //Z
        
        (*APout1++) =   sample1 * 0.1768 + sample2 * 0.0722 + sample3 * 0.0722 + sample4 * -0.0722;
        (*APout2++) =   sample1 * 0.1768 + sample2 * 0.0722 + sample3 * 0.0722 + sample4 * 0.0722;
        (*APout3++) =   sample1 * 0.1768 + sample2 * -0.0722 + sample3 * 0.0722 + sample4 * -0.0722;
        (*APout4++) =   sample1 * 0.1768 + sample2 * -0.0722 + sample3 * 0.0722 + sample4 * 0.0722;
        (*APout5++) =   sample1 * 0.1768 + sample2 * -0.0722 + sample3 * -0.0722 + sample4 * -0.0722;
        (*APout6++) =   sample1 * 0.1768 + sample2 * -0.0722 + sample3 * -0.0722 + sample4 * 0.0722;
        (*APout7++) =   sample1 * 0.1768 + sample2 * 0.0722 + sample3 * -0.0722 + sample4 * -0.0722;
        (*APout8++) =   sample1 * 0.1768 + sample2 * 0.0722 + sample3 * -0.0722 + sample4 * 0.0722;
    }
    
    
    return (w+15);
    
}





//DSP ROUTINE
dadecoder_tilde_dsp(t_dadecoder_tilde *x, t_signal **sp)
{
    
    if(x->dectype==1)dsp_add(dadecoder_tilde_stereo, 8, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[0]->s_n);
    
    if(x->dectype==2)dsp_add(dadecoder_tilde_pent, 12, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[0]->s_n);
    
    if(x->dectype==3)dsp_add(dadecoder_tilde_cube, 14, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec,  sp[8]->s_vec,  sp[9]->s_vec, sp[10]->s_vec, sp[11]->s_vec, sp[0]->s_n);
}



void *dadecoder_tilde_new(t_symbol *s, int argc, t_atom *argv) //, t_floatarg test
{
    
    t_dadecoder_tilde *x = (t_dadecoder_tilde *)pd_new(dadecoder_tilde_class);
   
    char teststring[1000];
    if(argc>0)atom_string(argv, teststring, 1000);
    char* type[3] = {"stereo", "pent", "cube"};
    int j = 0;
    int ordertypes[7];
    for(int i = 0; i < 3; i++) {
    
    ordertypes[i] = strcmp(teststring, type[i]);
   

    if(ordertypes[i] != 0) j = 1; if(ordertypes[0] == 0) j = 1;
    if(ordertypes[1] == 0) j = 2; if(ordertypes[2] == 0) j = 4;
    if(ordertypes[3] == 0) j = 5; if(ordertypes[4] == 0) j = 6;
    if(ordertypes[5] == 0) j = 7; if(ordertypes[6] == 0) j = 8;
        
    }
    
    x->dectype = j;
    
    
    switch(j){
    default:
        case 1:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            break;

        case 2:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); 
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            break;

        case 3:
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
            inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal); 
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            outlet_new(&x->x_obj, gensym ("signal"));
            break;
        case 0:
    		break;


    }
    
    
        
    return (void *)x;
}










//SETUP
void dadecoder_tilde_setup(void)
{
    dadecoder_tilde_class = class_new(gensym("dadecoder~"),(t_newmethod)dadecoder_tilde_new,0, sizeof(t_dadecoder_tilde),CLASS_DEFAULT,A_GIMME,0);
    class_addmethod(dadecoder_tilde_class,
                    (t_method)dadecoder_tilde_dsp, gensym("dsp"), 0);
    CLASS_MAINSIGNALIN(dadecoder_tilde_class, t_dadecoder_tilde, APf);
}