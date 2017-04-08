#include <m_pd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define radians 2 * 3.14159265358979323846
#define PI    3.14159265358979323846


/* **********************************************DAPANNERxyz~************************** ****/
static t_class *dapannerxyz_tilde_class;

//STRUCTURE
typedef struct _dapannerxyz_tilde {
    t_object  x_obj;
    t_sample APf;

    double elevation;
    double elevation_in;
    double azimuth;
    int order;
    double x_in;
    double y_in;


} t_dapannerxyz_tilde;



void dapannerxyz_tilde_x(t_dapannerxyz_tilde *x, t_floatarg x_cord)
{
    x->x_in = x_cord;
    if(x->x_in > 0 && x->y_in >= 0){
        x->azimuth = atan(x->y_in / x->x_in);
    } else if(x->x_in < 0 && x->y_in >= 0){
        x->azimuth = atan(x->y_in / x->x_in) + (PI / 2);
    } else if(x->x_in < 0 && x->y_in < 0){
        x->azimuth = atan(x->y_in / x->x_in) + PI;
    } else if(x->x_in > 0 && x->y_in < 0){
        x->azimuth = atan(x->y_in / x->x_in) + ((3 * PI) / 2);
    } else if (x->x_in == 0 && x->y_in > 0){
        x->azimuth = PI / 2;
    } else if (x->x_in == 0 && x->y_in <= 0){
        x->azimuth = (3 * PI) / 2;
    }

/*
    if(x->azimuth < 0){
        double neg = x->azimuth;
        x->azimuth = radians + neg;
    }
    */
    post("Azimuth: %f", x->azimuth * (180 / PI));
}

void dapannerxyz_tilde_y(t_dapannerxyz_tilde *x, t_floatarg y_cord)
{
    x->y_in = y_cord;
    if(x->x_in > 0 && x->y_in >= 0){
        x->azimuth = atan(x->y_in / x->x_in);
    } else if(x->x_in < 0 && x->y_in >= 0){
        x->azimuth = atan(x->y_in / x->x_in) + (PI / 2);
    } else if(x->x_in < 0 && x->y_in < 0){
        x->azimuth = atan(x->y_in / x->x_in) + PI;
    } else if(x->x_in > 0 && x->y_in < 0){
        x->azimuth = atan(x->y_in / x->x_in) + ((3 * PI) / 2);
    } else if (x->x_in == 0 && x->y_in > 0){
        x->azimuth = PI / 2;
    } else if (x->x_in == 0 && x->y_in <= 0){
        x->azimuth = (3 * PI) / 2;
    }

/*
    if(x->azimuth < 0){
        double neg = x->azimuth;
        x->azimuth = radians + neg;
    }
    */
    post("Azimuth: %f", x->azimuth * (180 / PI));
}


void dapannerxyz_tilde_z(t_dapannerxyz_tilde *x, t_floatarg z_cord)

{
    x->elevation = z_cord;
    x->elevation_in = (z_cord - 0.5) * (PI);
    
}







//Perform Order 1
t_int *dapannerxyz_tilde_perform(t_int *w)

{

    t_dapannerxyz_tilde *x = (t_dapannerxyz_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APout1 =    (t_sample *)(w[3]);

    t_sample  *APout2 =    (t_sample *)(w[4]);

    t_sample  *APout3 =    (t_sample *)(w[5]);

    t_sample  *APout4 =    (t_sample *)(w[6]);

    int          APn =           (int)(w[7]);


    t_sample sample1;
    double l = x->elevation;

    



    while (APn--)

    {        

        sample1 = (*APin1++);

            (*APout1++) =   sample1 * 0.707; //W

            if(l == 0) {
                (*APout2++) =   sample1 * cosf(x->azimuth);
                } else {
                (*APout2++) =   sample1 * cosf(x->azimuth) * cosf(x->elevation_in);
                } //X

            if(l == 0) {
                (*APout3++) =   sample1 * sinf(x->azimuth);
                } else {
                (*APout3++) =   sample1 * sinf(x->azimuth) * (t_sample)cosf(x->elevation_in);
                }           

            if(l == 0) {
                (*APout4++) =   sample1;
                } else {
                (*APout4++) =   sample1 * sinf(x->elevation_in);;
                }

        }    

    return (w+8);  

}




//Perform Order 2
t_int *dapannerxyz_tilde_perform2(t_int *w)

{

    t_dapannerxyz_tilde *x = (t_dapannerxyz_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APout1 =    (t_sample *)(w[3]);

    t_sample  *APout2 =    (t_sample *)(w[4]);

    t_sample  *APout3 =    (t_sample *)(w[5]);

    t_sample  *APout4 =    (t_sample *)(w[6]);

    t_sample  *APout5 =    (t_sample *)(w[7]);

    int          APn =           (int)(w[8]);


    t_sample sample1;
    double l = x->elevation;

    



    while (APn--)

    {        



        sample1 = (*APin1++);

                (*APout1++) =   sample1 * 0.707;
                
                
                if(l == 0) {
                    (*APout2++) =   sample1 * cosf(x->azimuth);
                } else {
                    (*APout2++) =   sample1 * cosf(x->azimuth) * cosf(x->elevation_in);
                }
                
                if(l == 0) {
                    (*APout3++) =   sample1 * sinf(x->azimuth);
                } else {
                    (*APout3++) =   sample1 * sinf(x->azimuth) * cosf(x->elevation_in);
                }
                
                if(l == 0) {
                    (*APout4++) =   sample1 * cosf(2 * x->azimuth);
                } else {
                    (*APout4++) =   sample1 * cosf(2 * x->azimuth) * cosf(x->elevation_in) * cosf(x->elevation_in);;
                }
                
                if(l == 0) {
                    (*APout5++) =   sample1 * sinf(2 * x->azimuth);
                } else {
                    (*APout5++) =   sample1 * sinf(2 * x->azimuth) * cosf(x->elevation_in) * cosf(x->elevation_in);;
                }
                
        
        }    

    return (w+9);  

}

//Perform Order 3
t_int *dapannerxyz_tilde_perform3(t_int *w)

{

    t_dapannerxyz_tilde *x = (t_dapannerxyz_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APout1 =    (t_sample *)(w[3]);

    t_sample  *APout2 =    (t_sample *)(w[4]);

    t_sample  *APout3 =    (t_sample *)(w[5]);

    t_sample  *APout4 =    (t_sample *)(w[6]);

    t_sample  *APout5 =    (t_sample *)(w[7]);

    t_sample  *APout6 =    (t_sample *)(w[8]);

    t_sample  *APout7 =    (t_sample *)(w[9]);

    int          APn =           (int)(w[10]);


    t_sample sample1;
    double l = x->elevation;

    



    while (APn--)

    {        



        sample1 = (*APin1++);

            

                (*APout1++) =   sample1 * 0.707;
                
                
                if(l == 0) {
                    (*APout2++) =   sample1 * cosf(x->azimuth);
                } else {
                    (*APout2++) =   sample1 * cosf(x->azimuth) * cosf(x->elevation_in);
                }
                
                if(l == 0) {
                    (*APout3++) =   sample1 * sinf(x->azimuth);
                } else {
                    (*APout3++) =   sample1 * sinf(x->azimuth) * cosf(x->elevation_in);
                }
                
                if(l == 0) {
                    (*APout4++) =   sample1 * cosf(2 * x->azimuth);
                } else {
                    (*APout4++) =   sample1 * cosf(2 * x->azimuth) * cosf(x->elevation_in) * cosf(x->elevation_in);;
                }
                
                if(l == 0) {
                    (*APout5++) =   sample1 * sinf(2 * x->azimuth);
                } else {
                    (*APout5++) =   sample1 * sinf(2 * x->azimuth) * cosf(x->elevation_in) * cosf(x->elevation_in);
                }
                
                if(l == 0) {
                    (*APout6++) =   sample1 * cosf(3 * x->azimuth);
                } else {
                    (*APout6++) =   sample1 * cosf(3 * x->azimuth) * cosf(x->elevation_in) * cosf(x->elevation_in) * cosf(x->elevation_in);
                }
                
                if(l == 0) {
                    (*APout7++) =   sample1 * sinf(3 * x->azimuth);
                } else {
                    (*APout7++) =   sample1 * sinf(3 * x->azimuth) * cosf(x->elevation_in) * cosf(x->elevation_in) * cosf(x->elevation_in);
                }
            

        }    

    return (w+11);  

}




//Constructor

void *dapannerxyz_tilde_new(t_floatarg f) {
	t_dapannerxyz_tilde *x = (t_dapannerxyz_tilde *)pd_new(dapannerxyz_tilde_class);

    x->order = 0;
    x->order = f;

	inlet_new(&x->x_obj,&x->x_obj.ob_pd, &s_float, gensym("x"));
    inlet_new(&x->x_obj,&x->x_obj.ob_pd, &s_float, gensym("y"));
    inlet_new(&x->x_obj,&x->x_obj.ob_pd, &s_float, gensym("z"));

    switch(x->order){
        default:

        case 0:
        outlet_new(&x->x_obj, gensym ("signal")); //W
        outlet_new(&x->x_obj, gensym ("signal")); //X
        outlet_new(&x->x_obj, gensym ("signal")); //Y
        outlet_new(&x->x_obj, gensym ("signal")); //U
        break;

        case 1:
        outlet_new(&x->x_obj, gensym ("signal")); //W
        outlet_new(&x->x_obj, gensym ("signal")); //X
        outlet_new(&x->x_obj, gensym ("signal")); //Y
        outlet_new(&x->x_obj, gensym ("signal")); //U
        break;

        case 2:
        outlet_new(&x->x_obj, gensym ("signal")); //W
        outlet_new(&x->x_obj, gensym ("signal")); //X
        outlet_new(&x->x_obj, gensym ("signal")); //Y
        outlet_new(&x->x_obj, gensym ("signal")); //U
        outlet_new(&x->x_obj, gensym ("signal")); //V
        break;

        case 3:
        outlet_new(&x->x_obj, gensym ("signal")); //W
        outlet_new(&x->x_obj, gensym ("signal")); //X
        outlet_new(&x->x_obj, gensym ("signal")); //Y
        outlet_new(&x->x_obj, gensym ("signal")); //U
        outlet_new(&x->x_obj, gensym ("signal")); //V
        outlet_new(&x->x_obj, gensym ("signal")); //P
        outlet_new(&x->x_obj, gensym ("signal")); //Q
        break;
    }
	return (void *)x;
}







//DSP Routine - Adds Perform Routine to DSP tree
void dapannerxyz_tilde_dsp(t_dapannerxyz_tilde *x, t_signal **sp) //x is a pointer to a function; t_signal is a pointer to signal vectors ().s_vec. 
{
        post("We made it");
        if(x->order==0)dsp_add(dapannerxyz_tilde_perform, 7, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[0]->s_n);
        if(x->order==1)dsp_add(dapannerxyz_tilde_perform, 7, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[0]->s_n);
        if(x->order==2)dsp_add(dapannerxyz_tilde_perform2, 8, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[0]->s_n);
        if(x->order==3)dsp_add(dapannerxyz_tilde_perform3, 10, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[0]->s_n);
}




void dapannerxyz_tilde_setup(void)
{
    dapannerxyz_tilde_class = class_new(gensym("dapannerxyz~"),(t_newmethod)dapannerxyz_tilde_new,0, sizeof(t_dapannerxyz_tilde),CLASS_DEFAULT,A_DEFFLOAT,0);
    class_addmethod(dapannerxyz_tilde_class,(t_method)dapannerxyz_tilde_dsp, gensym("dsp"), 0);

    class_addmethod(dapannerxyz_tilde_class, (t_method)dapannerxyz_tilde_x, gensym("x"), A_DEFFLOAT, 0);
    class_addmethod(dapannerxyz_tilde_class, (t_method)dapannerxyz_tilde_y, gensym("y"), A_DEFFLOAT, 0);
    class_addmethod(dapannerxyz_tilde_class, (t_method)dapannerxyz_tilde_z, gensym("z"), A_DEFFLOAT, 0);
    CLASS_MAINSIGNALIN(dapannerxyz_tilde_class, t_dapannerxyz_tilde, APf);
}

/* **********************************************DADECODER~************************** ****/
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
    class_addmethod(dadecoder_tilde_class,(t_method)dadecoder_tilde_dsp, gensym("dsp"), 0);
    CLASS_MAINSIGNALIN(dadecoder_tilde_class, t_dadecoder_tilde, APf);
}


/* **** ** * SETUP *** * * * */

void dalib_tilde_setup(void){
	dapannerxyz_tilde_setup();
	dadecoder_tilde_setup();
}
