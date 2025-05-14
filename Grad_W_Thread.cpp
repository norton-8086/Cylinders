//---------------------------------------------------------------------------
#include <System.hpp>
#pragma hdrstop

#include "CPP_MENU.h"

#include "Grad_W_Thread.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize!!!
//---------------------------------------------------------------------------

void __fastcall TGrad_W_Thread::New_Form(){
	Form = new TGrad_Form(Application);
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

void __fastcall TGrad_W_Thread::Change_param(){
	steps = Form->Steps->Text.ToInt();

	dt = (long double)Form->dt->Text.ToDouble();
	dt_stop = (long double)Form->dt_stop->Text.ToDouble();
	dt_change = (long double)Form->dt_change->Text.ToDouble();

	betta = (long double)Form->betta->Text.ToDouble();
	ep = (long double)Form->ep->Text.ToDouble();

	frames = (long double)Form->Frame->Text.ToDouble();
	z_far = (long double)Form->z_far->Text.ToDouble();
	dz_max = (long double)Form->dz->Text.ToDouble();
}

void __fastcall TGrad_W_Thread::Plot(){
	print_Q( Form->Q_1, &pair.cyl1);
	print_Q( Form->Q_2, &pair.cyl2);
	print_fi( Form->Fi_1, &pair.cyl1);
	print_fi( Form->Fi_2, &pair.cyl2);

	Form->Dev_Fi->Text = FloatToStrF(pair.dev_fi, ffExponent, 8, 2);
	Form->Dev_E->Text =  FloatToStrF(pair.dev_E, ffExponent, 8, 2);
	Form->W_now->Text =  FloatToStrF(pair.W, ffExponent, 8, 2);

	Form->Q_1_now->Text = FloatToStrF((pair.cyl1.rings[0].Q + pair.cyl1.Sum_Q_Except), ffExponent, 8, 2);
	Form->Q_2_now->Text = FloatToStrF((pair.cyl2.rings[0].Q + pair.cyl2.Sum_Q_Except), ffExponent, 8, 2);

	Form->dt->Text = FloatToStrF(dt, ffExponent, 8, 2);
	Form->dt_stop->Text = FloatToStrF(dt_stop, ffExponent, 8, 2);
	Form->dt_change->Text = FloatToStrF(dt_change, ffExponent, 8, 2);

	Form->betta->Text = FloatToStrF(betta, ffExponent, 8, 2);
	Form->Fi_1_now->Text = FloatToStrF(pair.cyl1.fi, ffExponent, 8, 2);
	Form->Fi_2_now->Text = FloatToStrF(pair.cyl2.fi, ffExponent, 8, 2);

	//Form->W_article->Text = FloatToStr((float)pair.W_article);
	Form->W_article->Text = FloatToStrF(W_article, ffExponent, 8, 2);

	Form->z_now->Text = FloatToStr((float)z_now);
	//Form->W_far->Text = FloatToStr((float)pair.W_far);
	Form->W_far->Text = FloatToStrF(W_far, ffExponent, 8, 2);

	Form->z_far->Text = FloatToStrF(z_far, ffExponent, 8, 2);

	paint_cyl(Form->Image, &pair, z_far, z_now);
}

__fastcall TGrad_W_Thread::TGrad_W_Thread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}

/* void W_der_conserv(struct pair_of_cyl *pair){
	int i, n1, n2, k;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	pair->der_W_colomn.data[0] = (long double)0.0;
	pair->der_W_colomn.data[n1] = (long double)0.0;

	long double der_k = (long double)0.0;

	for(k = 1; k < n1; k++){
		der_k = (long double)0.0;

		der_k += pair->arr_Fi.array[0][n1]*(-pair->cyl2.Q + Sum_Q_Except_First(&pair->cyl2));

		der_k -= (long double)2.0*pair->arr_Fi.array[0][k]*pair->cyl1.rings[k].Q;
		der_k += pair->cyl1.Q * pair->arr_Fi.array[0][k] + pair->cyl2.Q * pair->arr_Fi.array[k][n1];

		for(int i = 1; i < k; i++){
			der_k += pair->cyl1.rings[i].Q*(- pair->arr_Fi.array[0][i] + pair->arr_Fi.array[i][k] - pair->arr_Fi.array[0][k]);
		}

		for(int i = k + 1; i < n1; i++){
			der_k += pair->cyl1.rings[i].Q*(- pair->arr_Fi.array[0][i] + pair->arr_Fi.array[i][k] - pair->arr_Fi.array[0][k]);
		}

		for(int i = n1 + 1; i < n1 + n2; i++){
			der_k += pair->cyl2.rings[i - n1].Q*(pair->arr_Fi.array[k][i] - pair->arr_Fi.array[k][n1] - pair->arr_Fi.array[0][i]);
		}

		pair->der_W_colomn.data[k] = der_k;
	}

	for(k = n1 + 1; k < n1 + n2; k++){
		der_k = (long double)0.0;

		der_k += pair->arr_Fi.array[0][n1]*(-pair->cyl1.Q + Sum_Q_Except_First(&pair->cyl1));
		der_k -= (long double)2.0*pair->arr_Fi.array[k][n1]*pair->cyl2.rings[k - n1].Q;

		der_k += pair->cyl1.Q * pair->arr_Fi.array[0][k] + pair->cyl2.Q * pair->arr_Fi.array[k][n1];

		for(int i = n1 + 1; i < k - 1; i++){
			der_k += pair->cyl2.rings[i - n1].Q*(pair->arr_Fi.array[i][k] - pair->arr_Fi.array[i][n1] - pair->arr_Fi.array[k][n1]);
		}

		for(int i = k + 1; i < n1 + n2; i++){
			der_k += pair->cyl2.rings[i - n1].Q*(pair->arr_Fi.array[i][k] - pair->arr_Fi.array[i][n1] - pair->arr_Fi.array[k][n1]);
		}

		for(int i = 1; i < n1; i++){
			der_k += pair->cyl1.rings[i].Q*(pair->arr_Fi.array[i][k] - pair->arr_Fi.array[i][n1] - pair->arr_Fi.array[k][0]);
		}

		pair->der_W_colomn.data[k] = der_k;
	}
}

void W_shift_conserv(struct pair_of_cyl *pair, long double dt, long double betta){
	int n1, n2;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	for(int i = 1; i < n1; i++){
		pair->der_W_v_colomn.data[i] = betta*(pair->der_W_v_colomn.data[i] - pair->der_W_colomn.data[i]*dt);
		pair->cyl1.rings[i].Q += pair->der_W_v_colomn.data[i]*dt;
	}

	pair->cyl1.rings[0].Q = pair->cyl1.Q - Sum_Q_Except_First(&pair->cyl1);

	for(int i = n1 + 1; i < n1 + n2; i++){
		pair->der_W_v_colomn.data[i] = betta*(pair->der_W_v_colomn.data[i] - pair->der_W_colomn.data[i]*dt);
		pair->cyl2.rings[i - n1].Q += pair->der_W_v_colomn.data[i]*dt;
	}

	pair->cyl2.rings[0].Q = pair->cyl2.Q - Sum_Q_Except_First(&pair->cyl2);
}

void W_conserv_grad_step(struct pair_of_cyl *pair, long double dt, long double *betta){
	long double W_prev = pair->W;
	int n1, n2;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	W_der_conserv(pair);
	W_shift_conserv(pair, dt, *betta);
	update(pair);
	if(pair->W < W_prev){
	}
	else{
		for(int i = 1; i < n1; i++){
			pair->cyl1.rings[i].Q -= pair->der_W_v_colomn.data[i]*dt;
			pair->der_W_v_colomn.data[i] = pair->der_W_v_colomn.data[i] / *betta + pair->der_W_colomn.data[i]*dt;
		}

		pair->cyl1.rings[0].Q = pair->cyl1.Q - Sum_Q_Except_First(&pair->cyl1);

		for(int i = n1 + 1; i < n1 + n2; i++){
			pair->cyl2.rings[i - n1].Q -= pair->der_W_v_colomn.data[i]*dt;
			pair->der_W_v_colomn.data[i] = pair->der_W_v_colomn.data[i] / *betta + pair->der_W_colomn.data[i]*dt;
		}

		pair->cyl2.rings[0].Q = pair->cyl2.Q - Sum_Q_Except_First(&pair->cyl2);


		*betta *= 0.99;
	}
} */

void W_der(struct pair_of_cyl *pair){
	int n1, n2;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;
	long double der_W = (long double) 0.0;

	for(int i = 0; i < n1; i++){
		der_W = (long double) 0.0;

		for(int j = 0; j < i; j++){
			der_W += pair->arr_Fi.array[i][j] * pair->cyl1.rings[j].Q;
		}

		for(int j = i+1; j < n1; j++){
			der_W += pair->arr_Fi.array[i][j] * pair->cyl1.rings[j].Q;
		}

		for(int j = n1; j < n1 + n2; j++){
			der_W += pair->arr_Fi.array[i][j] * pair->cyl2.rings[j - n1].Q;
		}

		pair->L_W.data[i] = der_W;
	}

	for(int i = n1; i < n1 + n2; i++){
		der_W = (long double) 0.0;

		for(int j = 0; j < n1; j++){
			der_W += pair->arr_Fi.array[i][j] * pair->cyl1.rings[j].Q;
		}

		for(int j = n1; j < i; j++){
			der_W += pair->arr_Fi.array[i][j] * pair->cyl2.rings[j - n1].Q;
		}

		for(int j = i + 1; j < n1 + n2; j++){
			der_W += pair->arr_Fi.array[i][j] * pair->cyl2.rings[j - n1].Q;
		}

		pair->L_W.data[i] = der_W;
	}
}

void W_shift(struct pair_of_cyl *pair, long double dt, long double betta){
	int n1, n2;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	for(int i = 0; i < n1; i++){
		pair->v_W.data[i] = betta*(pair->v_W.data[i] - pair->L_W.data[i] * dt);
		pair->cyl1.rings[i].Q += pair->v_W.data[i]*dt;
	}
	for(int i = n1; i < n1 + n2; i++){
		pair->v_W.data[i] = betta*(pair->v_W.data[i] - pair->L_W.data[i] * dt);
		pair->cyl2.rings[i - n1].Q += pair->v_W.data[i]*dt;
	}

	long double Sum_Q_1 = (long double)0.0;
	long double Sum_Q_2 = (long double)0.0;

	for(int i = 0; i < n1; i++){
		Sum_Q_1 += pair->cyl1.rings[i].Q;
	}
	for(int i = n1; i < n1 + n2; i++){
		Sum_Q_2 += pair->cyl2.rings[i - n2].Q;
	}

	for(int i = 0; i < n1; i++){
		pair->cyl1.rings[i].Q -= (Sum_Q_1 - pair->cyl1.Q)/(long double)n1;
	}

	for(int i = n1; i < n1 + n2; i++){
		pair->cyl2.rings[i - n1].Q -= (Sum_Q_2 - pair->cyl2.Q)/(long double)n2;
	}
}

void W_grad_step(struct pair_of_cyl *pair, long double *dt, long double *betta, long double dt_change){
	long double W_prev = pair->W;
	long double dev_fi_prev = pair->dev_fi;
	long double dev_E_prev = pair->dev_E;
	int n1, n2;
	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	W_der(pair);
	W_shift(pair, *dt, *betta);
	update(pair);
	if(pair->W < W_prev  && pair->dev_fi < dev_fi_prev && pair->dev_E < dev_E_prev ){
	}
	else{
		long double Sum_Q_1 = (long double)0.0;
		long double Sum_Q_2 = (long double)0.0;

		for(int i = 0; i < n1; i++){
			Sum_Q_1 += pair->cyl1.rings[i].Q;
		}
		for(int i = n1; i < n1 + n2; i++){
			Sum_Q_2 += pair->cyl2.rings[i - n2].Q;
		}

		for(int i = 0; i < n1; i++){
			pair->cyl1.rings[i].Q += (Sum_Q_1 - pair->cyl1.Q)/(long double)n1;
		}

		for(int i = n1; i < n1 + n2; i++){
			pair->cyl2.rings[i - n1].Q += (Sum_Q_2 - pair->cyl2.Q)/(long double)n2;
		}

		for(int i = 0; i < n1; i++){
			pair->cyl1.rings[i].Q -= pair->v_W.data[i] **dt;
			pair->der_W_v_colomn.data[i] = pair->v_W.data[i] / *betta + pair->L_W.data[i] **dt;
		}

		for(int i = n1; i < n1 + n2; i++){
			pair->cyl2.rings[i - n1].Q -= pair->v_W.data[i] **dt;
			pair->der_W_v_colomn.data[i] = pair->v_W.data[i] / *betta + pair->L_W.data[i] **dt;
		}

		*dt *= dt_change;
	}
}

static void change_vector(std::vector<long double> v){
	int length = v.size();
	std::vector <long double> new_v;
	for(int i = length - 1; i > length/2; i--){
		new_v.push_back(v[i]);
	}
	for(int i = 0; i <= length/2; i++){
		new_v.push_back(v[i]);
	}

	v = new_v;
}


//---------------------------------------------------------------------------
void __fastcall TGrad_W_Thread::Execute()
{
	FreeOnTerminate = true;

	Synchronize(&New_Form);
	while(Form->start_flag != true){
		Sleep(10);
	}
	Synchronize(&Change_param);

	go_flag = true;

	z_now = z_far;
	W_far = 0.0;

	pair = new_pair_of_cyl(N_1, N_2, R_1, R_2, L_1, L_2, Qtotal_1, Qtotal_2, 0, z_now);
	update(&pair);

	W_article = Wformula(&pair.cyl1, &pair.cyl2);

	int n1, n2;
	n1 = pair.cyl1.n;
	n2 = pair.cyl2.n;

	for(int i = 0; i < n1 + n2; i++){
		pair.der_W_colomn.data[i] = pair.der_W_v_colomn.data[i] = (long double)0.0;
	}
	for(int i = 0; i < n1 + n2; i++){
		pair.L_W.data[i] = pair.v_W.data[i] = (long double)0.0;
	}
//--------------РАСЧЁТ НА УДАЛЕНИИ----------------------------------------------
	int i = 1;
	dt_now = dt;
	while(dt_now > dt_stop){
		W_grad_step(&pair, &dt_now, &betta, dt_change);
		if(i%frames == 0){
			Synchronize(&Plot);
		}
		i++;
	}
	Synchronize(&Plot);

	W_far = pair.W;

	shift_cylinder(&pair, &pair.cyl2, 0.0 + pair.cyl2.L/(long double)2.0 - pair.cyl1.L/(long double)2.0);

	pair = new_pair_of_cyl(N_1, N_2, R_1, R_2, L_1, L_2, Qtotal_1, Qtotal_2, 0, 0.0 - pair.cyl2.L/(long double)2.0 + pair.cyl1.L/(long double)2.0);
	update(&pair);


	std::vector <long double> z;
	std::vector <long double> W;
	std::vector <long double> dev_fi;
	std::vector <long double> dev_E;

//--------------РАСЧЁТ В ЦЕНТРЕ-------------------------------------------------
	z_now = (long double)0.0;
	update(&pair);
	dt_now = dt;
	i = 1;
	while(dt_now >= dt_stop){
		if(go_flag == false){
			while(go_flag != true){
			}
		}

		Synchronize(&Change_param);

		W_grad_step(&pair, &dt_now, &betta, dt_change);

		if(i%frames == 0){
			Synchronize(&Plot);
		}
		i++;
	}
    Synchronize(&Plot);
	z.push_back(z_now);
	W.push_back(pair.W);
	dev_fi.push_back(pair.dev_fi);
	dev_E.push_back(pair.dev_E);

	z_now += dz_max/(long double)steps;

	shift_cylinder(&pair, &pair.cyl2, z_now - pair.cyl2.L/(long double)2.0 + pair.cyl1.L/(long double)2.0);
	Synchronize(&Plot);

	struct pair_of_cyl center_pair = pair;

//-----------------ДВИЖЕНИЕ ВПРАВО----------------------------------------------
	while(z_now <= dz_max){
		update(&pair);
		dt_now = dt;
		i = 1;
		while(dt_now >= dt_stop){
			if(go_flag == false){
				while(go_flag != true){
				}
			}

			Synchronize(&Change_param);

			W_grad_step(&pair, &dt_now, &betta, dt_change);

			if(i%frames == 0){
				Synchronize(&Plot);
			}
			i++;
		}
		z.push_back(z_now);
		W.push_back(pair.W);
		dev_fi.push_back(pair.dev_fi);
		dev_E.push_back(pair.dev_E);

		z_now += dz_max/(long double)steps;

		shift_cylinder(&pair, &pair.cyl2, z_now - pair.cyl2.L/(long double)2.0 + pair.cyl1.L/(long double)2.0);
		Synchronize(&Plot);
	}

//----------------------ВОЗВРАЩАЕМСЯ В ЦЕНТР------------------------------------
	z_now = (long double)0.0 - dz_max/(long double)steps;
	pair = center_pair;

//---------------------------ДВИЖЕМСЯ ВЛЕВО-------------------------------------
	while(z_now >= -dz_max){
		update(&pair);
		dt_now = dt;

		i = 1;
		while(dt_now >= dt_stop){
			if(go_flag == false){
				while(go_flag != true){
				}
			}

			Synchronize(&Change_param);

			W_grad_step(&pair, &dt_now, &betta, dt_change);

			if(i%frames == 0){
				Synchronize(&Plot);
			}
			i++;
		}
		z.push_back(z_now);
		W.push_back(pair.W);
		dev_fi.push_back(pair.dev_fi);
		dev_E.push_back(pair.dev_E);

		z_now -= dz_max/(long double)steps;

		shift_cylinder(&pair, &pair.cyl2, z_now - pair.cyl2.L/(long double)2.0 + pair.cyl1.L/(long double)2.0);
		Synchronize(&Plot);
	}


//----------------------ЗАПИСЬ ПО ФАЙЛАМ----------------------------------------
	int  decimal, sign;
	std::string chapter_name;

	chapter_name = "Grad_W_R1_" + std::to_string(pair.cyl1.R) + "_R2_" + std::to_string(pair.cyl2.R) + "_L1_" + std::to_string(pair.cyl1.L) + "_L2_" + std::to_string(pair.cyl2.L) + "_Q1_" + std::to_string(pair.cyl1.Q) + "_Q2_" + std::to_string(pair.cyl2.Q) + "_n1_" + std::to_string(pair.cyl1.n) +  "_n2_" + std::to_string(pair.cyl2.n) + "_dt_stop_" + std::to_string(dt_stop) + "_steps_" + std::to_string(steps);

	int length = z.size();

	FILE *file_z = fopen ((chapter_name + "_z.txt").c_str(),"w");

	for(int i =  length - 1; i > length/2; i--){
		fprintf(file_z, "%2.15Lf \n", z[i]);
	}

	for(int i = 0; i < length/2; i++){
		fprintf(file_z, "%2.15Lf \n", z[i]);
	}
	fclose(file_z);

	FILE *file_w = fopen ((chapter_name + "_w.txt").c_str(),"w");

	for(int i =  length - 1; i > length/2; i--){
		fprintf(file_w, "%2.15Lf \n", W[i]);
	}

	for(int i = 0; i < length/2; i++){
		fprintf(file_w, "%2.15Lf \n", W[i]);
	}
	fclose(file_w);

	FILE *file_w_norm = fopen ((chapter_name + "_w_norm.txt").c_str(),"w");

	for(int i =  length - 1; i > length/2; i--){
		fprintf(file_w_norm, "%2.15Lf \n", W[i]/W_far);
	}

	for(int i = 0; i < length/2; i++){
		fprintf(file_w_norm, "%2.15Lf \n", W[i]/W_far);
	}
	fclose(file_w_norm);

	FILE *file_dev_fi = fopen ((chapter_name + "_dev_fi.txt").c_str(),"w");

	for(int i =  length - 1; i > length/2; i--){
		fprintf(file_dev_fi, "%2.15Lf \n", dev_fi[i]);
	}

	for(int i = 0; i < length/2; i++){
		fprintf(file_dev_fi, "%2.15Lf \n", dev_fi[i]);
	}
	fclose(file_dev_fi);

	FILE *file_dev_E = fopen ((chapter_name + "_dev_E.txt").c_str(),"w");

	for(int i =  length - 1; i > length/2; i--){
		fprintf(file_dev_E, "%2.15Lf \n", dev_E[i]);
	}

	for(int i = 0; i < length/2; i++){
		fprintf(file_dev_E, "%2.15Lf \n", dev_E[i]);
	}
	fclose(file_dev_E);
}
//---------------------------------------------------------------------------
