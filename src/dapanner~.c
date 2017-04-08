#include <m_pd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#define radians 2 * 3.14159265358979323846
#define PI    3.14159265358979323846


static t_class *dapanner_tilde_class;

//STRUCTURE
typedef struct _dapanner_tilde {
    t_object  x_obj;
    t_sample APf; 
    double elevation;
    double azimuthimuth_in;
    double elevation_in;
    int order;
    t_sample;


} t_dapanner_tilde;



void dapanner_tilde_azimuth(t_dapanner_tilde *x, t_floatarg APazimuthl)
{
    x->azimuthimuth_in = APazimuthl * radians;
}


void dapanner_tilde_elevation(t_dapanner_tilde *x, t_floatarg APelevationl )

{

    x->elevation = APelevationl;
    x->elevation_in = (APelevationl - 0.5) * (PI);
    
}







//Perform Order 1
t_int *dapanner_tilde_perform(t_int *w)

{

    t_dapanner_tilde *x = (t_dapanner_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APin2 =    (t_sample *)(w[3]);

    t_sample  *APin3 =    (t_sample *)(w[4]);

    t_sample  *APout1 =    (t_sample *)(w[5]);

    t_sample  *APout2 =    (t_sample *)(w[6]);

    t_sample  *APout3 =    (t_sample *)(w[7]);

    t_sample  *APout4 =    (t_sample *)(w[8]);

    int          APn =           (int)(w[9]);


    t_sample sample1, sample2, sample3;
    double l = x->elevation;

    



    while (APn--)

    {        



        sample1 = (*APin1++);

        sample2 = (*APin2++) * radians;

        sample3 = (*APin3++ - 0.5) * PI;

            

            (*APout1++) =   sample1 * 0.707; //W

            (*APout2++) =   sample1 * cosf(sample2); //X

            (*APout3++) =   sample1 * sinf(sample2); //Y            

            (*APout4++) =   sample1 * sinf(sample3); //U

        }    

    return (w+10);  

}




//Perform Order 2
t_int *dapanner_tilde_perform2(t_int *w)

{

    t_dapanner_tilde *x = (t_dapanner_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APin2 =    (t_sample *)(w[3]);

    t_sample  *APin3 =    (t_sample *)(w[4]);

    t_sample  *APout1 =    (t_sample *)(w[5]);

    t_sample  *APout2 =    (t_sample *)(w[6]);

    t_sample  *APout3 =    (t_sample *)(w[7]);

    t_sample  *APout4 =    (t_sample *)(w[8]);

    t_sample  *APout5 =    (t_sample *)(w[9]);

    int          APn =           (int)(w[10]);


    t_sample sample1, sample2, sample3;
    double l = x->elevation;

    



    while (APn--)

    {        



        sample1 = (*APin1++);

        sample2 = (*APin2++) * radians;

        sample3 = (*APin3++ - 0.5) * PI;

            

            (*APout1++) =   sample1 * 0.707; //W

            (*APout2++) =   sample1 * cosf(sample2); //X

            (*APout3++) =   sample1 * sinf(sample2); //Y            

            (*APout4++) =   sample1 * sinf(sample3); //U

            (*APout5++) =   sample1 * sinf(2 * sample2); //V

        }    

    return (w+11);  

}

//Perform Order 3
t_int *dapanner_tilde_perform3(t_int *w)

{

    t_dapanner_tilde *x = (t_dapanner_tilde *)(w[1]);

    t_sample  *APin1 =    (t_sample *)(w[2]);

    t_sample  *APin2 =    (t_sample *)(w[3]);

    t_sample  *APin3 =    (t_sample *)(w[4]);

    t_sample  *APout1 =    (t_sample *)(w[5]);

    t_sample  *APout2 =    (t_sample *)(w[6]);

    t_sample  *APout3 =    (t_sample *)(w[7]);

    t_sample  *APout4 =    (t_sample *)(w[8]);

    t_sample  *APout5 =    (t_sample *)(w[9]);

    t_sample  *APout6 =    (t_sample *)(w[10]);

    t_sample  *APout7 =    (t_sample *)(w[11]);

    int          APn =           (int)(w[12]);


    t_sample sample1, sample2, sample3;
    double l = x->elevation;

    



    while (APn--)

    {        



        sample1 = (*APin1++);

        sample2 = (*APin2++) * radians;

        sample3 = (*APin3++ - 0.5) * PI;

            

            (*APout1++) =   sample1 * 0.707; //W

            (*APout2++) =   sample1 * cosf(sample2); //X

            (*APout3++) =   sample1 * sinf(sample2); //Y            

            (*APout4++) =   sample1 * sinf(sample3); //U

            (*APout5++) =   sample1 * sinf(2 * sample2); //V

            (*APout6++) =   sample1 * cosf(3 * sample2); //P

            (*APout7++) =   sample1 * sinf(3 * sample2); //Q

        }    

    return (w+13);  

}




//Constructor

void *dapanner_tilde_new(t_floatarg f) {
	t_dapanner_tilde *x = (t_dapanner_tilde *)pd_new(dapanner_tilde_class);

    x->order = 0;
    x->order = f;

	inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal,&s_signal);

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
void dapanner_tilde_dsp(t_dapanner_tilde *x, t_signal **sp) //x is a pointer to a function; t_signal is a pointer to signal vectors ().s_vec. 
{
    switch(x->order){
        default:
        case 0:
        dsp_add(dapanner_tilde_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);

        case 1:
        dsp_add(dapanner_tilde_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);

        case 2:
        dsp_add(dapanner_tilde_perform2, 10, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[0]->s_n);

        case 3:
        dsp_add(dapanner_tilde_perform3, 12, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[0]->s_n);


    }
}



void dapanner_tilde_setup(void)
{
    dapanner_tilde_class = class_new(gensym("dapanner~"),(t_newmethod)dapanner_tilde_new,0, sizeof(t_dapanner_tilde),CLASS_DEFAULT,A_DEFFLOAT,0);
    class_addmethod(dapanner_tilde_class,(t_method)dapanner_tilde_dsp, gensym("dsp"), 0);
    class_addmethod(dapanner_tilde_class, (t_method)dapanner_tilde_azimuth,gensym("azimuth"), A_DEFFLOAT, 0);
    class_addmethod(dapanner_tilde_class, (t_method)dapanner_tilde_elevation,gensym("elevation"), A_DEFFLOAT, 0);
    CLASS_MAINSIGNALIN(dapanner_tilde_class, t_dapanner_tilde, APf);
}
