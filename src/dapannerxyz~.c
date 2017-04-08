#include <m_pd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define radians 2 * 3.14159265358979323846
#define PI    3.14159265358979323846


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
