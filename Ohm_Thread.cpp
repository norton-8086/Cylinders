//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string.h>

#include <math.h>

#include <chrono>
#include <thread>
#include <mutex>
#include <future>

#include <time.h>

#include <vcl.h>

#include "Elliptic.h"
#include "Matrix.h"
#include "Cylinder.h"
#include "Methods.h"
#include "Plot.h"

#include "Ohm_Win.h"

#include "Ohm_Thread.h"

#include "CPP_MENU.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------



void __fastcall TOhm_Thread::New_Form(){
	Form = new TOhm_Window(Application);
	Form->Show();

	Form->Qtotal_1->Text = MENU->Qtotal_1->Text;
	Form->Qtotal_2->Text = MENU->Qtotal_2->Text;
	Form->R_1->Text = MENU->R_1->Text;
	Form->R_2->Text = MENU->R_2->Text;
	Form->L_1->Text = MENU->L_1->Text;
	Form->L_2->Text = MENU->L_2->Text;
	Form->N_1->Text = MENU->N_1->Text;
	Form->N_2->Text = MENU->N_2->Text;

	Qtotal_1 = (long double)Form->Qtotal_1->Text.ToDouble();
	Qtotal_2 = (long double)Form->Qtotal_2->Text.ToDouble();
	R_1 = (long double)Form->R_1->Text.ToDouble();
	R_2 = (long double)Form->R_2->Text.ToDouble();
	L_1 = (long double)Form->L_1->Text.ToDouble();
	L_2 = (long double)Form->L_2->Text.ToDouble();
	N_1 = Form->N_1->Text.ToInt();
	N_2 = Form->N_2->Text.ToInt();
}

//---------------------------------------------------------------------------

__fastcall TOhm_Thread::TOhm_Thread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------

int find_max_dif(struct cylinder *pcyl){
	int i, n, i_res;
	n = pcyl->n;
	i_res = 0;
	long double max_fi_dif = abs(pcyl->rings[0].fi - pcyl->rings[1].fi);

	for(i = 0; i < n - 1; i++){
		if(abs(pcyl->rings[i].fi - pcyl->rings[i + 1].fi) > max_fi_dif){
			i_res = i;
			max_fi_dif = abs(pcyl->rings[i].fi - pcyl->rings[i + 1].fi);
		}
	}

	return i_res;
}

void step_Ohm_two(struct pair_of_cyl *pair){
	int i, i_max_1, i_max_2, n1, n2;

	i_max_1 = find_max_dif( &(pair->cyl1) );
	i_max_2 = find_max_dif( &(pair->cyl2) );

	long double C1, C2, f, Q_i_prev, Q_i_1_prev;

	Q_i_prev = pair->cyl1.rings[i_max_1].Q;
	Q_i_1_prev = pair->cyl1.rings[i_max_1 + 1].Q;

	C1 = pair->cyl1.rings[i_max_1].fi - pair->arr_Fi.array[i_max_1][i_max_1+1] * Q_i_1_prev;
	C2 = pair->cyl1.rings[i_max_1 + 1].fi - pair->arr_Fi.array[i_max_1][i_max_1+1] * Q_i_prev;
	f = pair->arr_Fi.array[i_max_1][i_max_1+1];

	pair->cyl1.rings[i_max_1].Q = 0.5*(Q_i_prev + Q_i_1_prev + (C1 - C2)/f);
	pair->cyl1.rings[i_max_1 + 1].Q = 0.5*(Q_i_prev + Q_i_1_prev + (C2 - C1)/f);

	Q_i_prev = pair->cyl2.rings[i_max_2].Q;
	Q_i_1_prev = pair->cyl2.rings[i_max_2 + 1].Q;

	C1 = pair->cyl2.rings[i_max_2].fi - pair->arr_Fi.array[i_max_2 + pair->cyl1.n][i_max_2 + pair->cyl1.n + 1] * Q_i_1_prev;
	C2 = pair->cyl2.rings[i_max_2 + 1].fi - pair->arr_Fi.array[i_max_2 + pair->cyl1.n][i_max_2 + pair->cyl1.n + 1] *Q_i_prev;
	f = pair->arr_Fi.array[i_max_2 + pair->cyl1.n][i_max_2 + pair->cyl1.n + 1];

	pair->cyl2.rings[i_max_2].Q = 0.5*(Q_i_prev + Q_i_1_prev + (C1 - C2)/f);
	pair->cyl2.rings[i_max_2 + 1].Q = 0.5*(Q_i_prev + Q_i_1_prev + (C2 - C1)/f);

	update(pair);
}

void shift_Ohm(struct pair_of_cyl *pair, long double *Resist){
	int n1, n2;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	long double delta_fi;
	long double dq;

	for(int i = 1; i < n1; i++){
		delta_fi = pair->cyl1.rings[i].fi - pair->cyl1.rings[i - 1].fi;

		dq = delta_fi/(*Resist);

		pair->cyl1.rings[i].Q += dq;
		pair->cyl1.rings[i - 1].Q -= dq;
	}
	for(int i = n1 + 1; i < n1 + n2; i++){
		delta_fi = pair->cyl2.rings[i - n1].fi - pair->cyl2.rings[i - n1 - 1].fi;

		dq = delta_fi/(*Resist);

		pair->cyl2.rings[i - n1].Q += dq;
		pair->cyl2.rings[i - n1 - 1].Q -= dq;
	}

	update(pair);

	pair->Fi_Ohm[0] = True;
	pair->Fi_Ohm[n1] = True;

	for(int i = 1; i < n1; i++){
		if(pair->cyl1.rings[i].fi - pair->cyl1.rings[i - 1].fi > 1e-30){
			pair->Fi_Ohm[i] = True;
		}
		else{
			pair->Fi_Ohm[i] = False;
		}
	}
	for(int i = n1 +1; i < n1 + n2; i++){
		if(pair->cyl2.rings[i - n1].fi - pair->cyl2.rings[i - n1 - 1].fi > 1e-30){
			pair->Fi_Ohm[i] = True;
		}
		else{
			pair->Fi_Ohm[i] = False;
		}
	}
}

void shift_Ohm_back(struct pair_of_cyl *pair){
	int n1, n2;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	for(int i = 0; i < n1; i++){
		pair->cyl1.rings[i].Q = pair->cyl1.Q_Ohm.data[i];
	}
	for(int i = n1; i < n1 + n2; i++){
		pair->cyl2.rings[i - n1].Q = pair->cyl2.Q_Ohm.data[i - n1];
	}
}

void step_Ohm(struct pair_of_cyl *pair, long double *Resist){
	long double W_prev = pair->W;
	long double dev_fi_prev = pair->dev_fi;
	long double dev_E_prev = pair->dev_E;
	int n1, n2;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	shift_Ohm(pair, Resist);

	if(  pair->W < W_prev && pair->dev_fi < dev_fi_prev && pair->dev_E < dev_E_prev && pair->Fi_Ohm == pair->Fi_Ohm_prev){
		for(int i = 0; i < n1; i++){
			pair->cyl1.Q_Ohm.data[i] = pair->cyl1.rings[i].Q;
		}
		for(int i = n1; i < n1 + n2; i++){
			pair->cyl2.Q_Ohm.data[i - n1] = pair->cyl2.rings[i - n1].Q;
		}
	}
	else{
		*Resist *= (long double)1.01;
		shift_Ohm_back(pair);
	}
}



void __fastcall TOhm_Thread::Change_param(){
	Form->Command->Text = "";
}

void __fastcall TOhm_Thread::Plot(){
    print_Q( Form->Q_1, &pair.cyl1);
	print_Q( Form->Q_2, &pair.cyl2);
	print_fi( Form->Fi_1, &pair.cyl1);
	print_fi( Form->Fi_2, &pair.cyl2);

	Form->Dev_Fi->Text =  FloatToStr((float)pair.dev_fi);
	Form->Dev_E->Text =  FloatToStr((float)pair.dev_E);
	Form->W_now->Text =  FloatToStr((float)pair.W);

	Form->Q_1_now->Text = FloatToStr((float)pair.cyl1.rings[0].Q + pair.cyl1.Sum_Q_Except);
	Form->Q_2_now->Text = FloatToStr((float)pair.cyl2.rings[0].Q + pair.cyl2.Sum_Q_Except);

	Form->Fi_1_now->Text = FloatToStr((float)pair.cyl1.fi);
	Form->Fi_2_now->Text = FloatToStr((float)pair.cyl2.fi);

	Form->W_article->Text = FloatToStr((float) pair.W_article);

	Form->Resist->Text = FloatToStr((float) Resist);
}

void __fastcall TOhm_Thread::Execute()
{
	FreeOnTerminate = true;

	Synchronize(&New_Form);
	while(Form->start_flag != true){
        Sleep(10);
	}
	Synchronize(&Change_param);

	pair = new_pair_of_cyl(N_1, N_2, R_1, R_2, L_1, L_2, Qtotal_1, Qtotal_2, 0, 1000000);
	update(&pair);

    pair.W_article = Wformula(&pair.cyl1, &pair.cyl2);

    int n1, n2;
	n1 = pair.cyl1.n;
	n2 = pair.cyl2.n;
    for(int i = 0; i < n1; i++){
		pair.cyl1.Q_Ohm.data[i] = pair.cyl1.rings[i].Q;
	}
	for(int i = n1; i < n1 + n2; i++){
		pair.cyl2.Q_Ohm.data[i - n1] = pair.cyl2.rings[i - n1].Q;
	}

	Resist = (long double)10.0;

	pair.Fi_Ohm_prev[0] = True;
	pair.Fi_Ohm_prev[n1] = True;

	for(int i = 1; i < n1; i++){
		if(pair.cyl1.rings[i].fi - pair.cyl1.rings[i - 1].fi > 1e-30){
			pair.Fi_Ohm_prev[i] = True;
		}
		else{
			pair.Fi_Ohm_prev[i] = False;
		}
	}
	for(int i = n1 +1; i < n1 + n2; i++){
		if(pair.cyl2.rings[i - n1].fi - pair.cyl2.rings[i - n1 - 1].fi > 1e-30){
			pair.Fi_Ohm_prev[i] = True;
		}
		else{
			pair.Fi_Ohm_prev[i] = False;
		}
	}

	for(int i = 0; i < 100000000; i++){
		step_Ohm(&pair, &Resist);

		if(i % 1000000 == 1000){
			Synchronize(&Plot);
		}
	}
}
//---------------------------------------------------------------------------
