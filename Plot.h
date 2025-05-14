/* ФУНКЦИИ ДЛЯ ОТРИСОВКИ ГРАФИКОВ ЗАРЯДА И ПОТЕНЦИАЛА */
/* НА ВХОД - УКАЗАТЕЛЬ НА LISTBOX и на ЦИЛИНДР */

/* ФУНКЦИЯ ДЛЯ ОТРИСОВКИ ГРАФИКА ЗАРЯДА КОЛЕЦ ЦИЛИНДРА */
static void print_Q(struct TListBox *p, struct cylinder *pcyl){
	//p->Canvas->Unlock(); /* РАЗБЛОКИРОВАНИЕ ФОРМЫ */

	int h, w, PX, PY;
	h = p->Height - 20;  /* ГРАФИКИ РИСУЮТСЯ С ОТСТУПОМ В 10 ПИКСЕЛЕЙ ОТ КРАЁВ */
	w = p->Width - 20;

	long double max_Q, min_Q;
	max_Q = min_Q = (*pcyl).rings[0].Q;

	for (int i = 0; i < (*pcyl).n; i++){
		if( (*pcyl).rings[i].Q > max_Q ){
			max_Q = (*pcyl).rings[i].Q;
		}
		else{
			if( (*pcyl).rings[i].Q < min_Q ){
				min_Q = (*pcyl).rings[i].Q;
			}
		}
	}

	for (int i = 0; i < p->Width; i++){
		for(int j = 0; j < p->Height; j++){
			p->Canvas->Pixels[i][j]= clWhite;
		}
	}

	for (int i = 0; i < (*pcyl).n; i++){
		PX = 10 + i*w/(*pcyl).n; //сдвиг на 10 пикселей
		PY = 10 + h - ((*pcyl).rings[i].Q - min_Q) * h/(max_Q - min_Q);

		p->Canvas->Pixels[PX][PY]= clRed;
		p->Canvas->Pixels[PX-1][PY]= clRed;
		p->Canvas->Pixels[PX][PY+1]= clRed;
		p->Canvas->Pixels[PX+1][PY]= clRed;
		p->Canvas->Pixels[PX][PY-1]= clRed;
	}

	//p->Canvas->TryLock(); /* БЛОКИРОВАНИЕ ФОРМЫ, ЧТОБЫ ДРУГИЕ ГРАФИКИ СЛУЧАЙНО НЕ ПЕРЕКРЫЛИ */
}

/* ФУНКЦИЯ ДЛЯ ОТРИСОВКИ ГРАФИКА ПОТЕНЦИАЛА КОЛЕЦ ЦИЛИНДРА */
static void print_fi(struct TListBox *p, struct cylinder *pcyl){
	//p->Canvas->Unlock();

	int h, w, PX, PY;
	h = p->Height - 20;
	w = p->Width - 20;

	long double max_fi, min_fi;
	max_fi = min_fi = (*pcyl).rings[0].fi;

	for (int i = 0; i < (*pcyl).n; i++){
		if( (*pcyl).rings[i].fi > max_fi ){
			max_fi = (*pcyl).rings[i].fi;
		}
		else{
			if( (*pcyl).rings[i].fi < min_fi ){
				min_fi = (*pcyl).rings[i].fi;
			}
		}
	}

	for (int i = 0; i < p->Width; i++){
		for(int j = 0; j < p->Height; j++){
			p->Canvas->Pixels[i][j]= clWhite;
		}
	}

	for (int i = 0; i < (*pcyl).n; i++){
		PX = 10 + i*w/(*pcyl).n; //сдвиг на 10 пикселей
		PY = 10 + h - ((*pcyl).rings[i].fi - min_fi) * h/(max_fi - min_fi);

		p->Canvas->Pixels[PX][PY]= clBlue;
		p->Canvas->Pixels[PX-1][PY]= clBlue;
		p->Canvas->Pixels[PX][PY+1]= clBlue;
		p->Canvas->Pixels[PX+1][PY]= clBlue;
		p->Canvas->Pixels[PX][PY-1]= clBlue;
	}

	//p->Canvas->TryLock();
}

static void paint_cyl(struct TImage *Image, struct pair_of_cyl *pair, long double z_max, long double z_now){
	for(int i = 0; i < Image->Width; i++){
		for(int j = 0; j < Image->Height; j++){
            Image->Canvas->Pixels[i][j] = clWhite;
		}
	}

	int width_unit = Image->Width/17;
	int height_unit = Image->Height/7;

	int cyl_1_w;
	int cyl_2_w;
	int cyl_1_h;
	int cyl_2_h;

	int interval = 2*width_unit*z_max/z_now;

	if(pair->cyl1.L >= pair->cyl2.L){
		cyl_1_w = 8*width_unit;
		cyl_2_w = 6*width_unit;
	}
	else{
		cyl_1_w = 6*width_unit;
		cyl_2_w = 8*width_unit;
	}

	if(pair->cyl1.R > pair->cyl2.R){
		cyl_1_h = 5*height_unit;
		cyl_2_h = 4*height_unit;
	}
	else{
		cyl_1_h = 4*height_unit;
		cyl_2_h = 5*height_unit;
	}

	int color_1;
	int color_2;
	if(pair->cyl1.Q > pair->cyl2.Q){
		color_1 = clRed;
		color_2 = clBlue;
	}
	else{
		color_1 = clBlue;
		color_2 = clRed;
    }

	int x;

	if(z_now >= (long double)0.0){
		if(z_now >= 0.5*(pair->cyl1.L + pair->cyl2.L) ){
			if(pair->cyl1.Q > pair->cyl2.Q){
				Image->Canvas->Brush->Color = clRed;
			}
			else{
				Image->Canvas->Brush->Color = clBlue;
			}

			Image->Canvas->Rectangle(width_unit, Image->Height/2 - cyl_1_h/2, width_unit + cyl_1_w, Image->Height/2 + cyl_1_h/2);

			if(pair->cyl1.Q > pair->cyl2.Q){
				Image->Canvas->Brush->Color = clBlue;
			}
			else{
				Image->Canvas->Brush->Color = clRed;
			}

			Image->Canvas->Rectangle(Image->Width - width_unit - cyl_2_w, Image->Height/2 - cyl_2_h/2, Image->Width - width_unit, Image->Height/2 + cyl_2_h/2);
		}

		else{
			x = z_now*(7*width_unit)/(0.5 * (pair->cyl1.L + pair->cyl2.L));

			if(pair->cyl1.L > pair->cyl2.L){
				if(pair->cyl1.Q > pair->cyl2.Q){
					Image->Canvas->Brush->Color = clRed;
				}
				else{
					Image->Canvas->Brush->Color = clBlue;
				}

				Image->Canvas->Rectangle(Image->Width/2 - x/2 - cyl_1_w/2, Image->Height/2 - cyl_1_h/2, Image->Width/2 - x/2 + cyl_1_w/2, Image->Height/2 + cyl_1_h/2);

				if(pair->cyl1.Q > pair->cyl2.Q){
					Image->Canvas->Brush->Color = clBlue;
				}
				else{
					Image->Canvas->Brush->Color = clRed;
				}

				Image->Canvas->Rectangle(Image->Width/2 + x/2 - cyl_2_w/2, Image->Height/2 - cyl_2_h/2, Image->Width/2 + x/2 + cyl_2_w/2, Image->Height/2 + cyl_2_h/2);
			}
			else{
				if(pair->cyl1.Q > pair->cyl2.Q){
					Image->Canvas->Brush->Color = clBlue;
				}
				else{
					Image->Canvas->Brush->Color = clRed;
				}

				Image->Canvas->Rectangle(Image->Width/2 + x/2 - cyl_2_w/2, Image->Height/2 - cyl_2_h/2, Image->Width/2 + x/2 + cyl_2_w/2, Image->Height/2 + cyl_2_h/2);

				if(pair->cyl1.Q > pair->cyl2.Q){
					Image->Canvas->Brush->Color = clRed;
				}
				else{
					Image->Canvas->Brush->Color = clBlue;
				}

				Image->Canvas->Rectangle(Image->Width/2 - x/2 - cyl_1_w/2, Image->Height/2 - cyl_1_h/2, Image->Width/2 - x/2 + cyl_1_w/2, Image->Height/2 + cyl_1_h/2);
			}

		}

	}
	else{
		if(z_now <= - 0.5*(pair->cyl1.L + pair->cyl2.L) ){
			if(pair->cyl2.Q > pair->cyl1.Q){
				Image->Canvas->Brush->Color = clRed;
			}
			else{
				Image->Canvas->Brush->Color = clBlue;
			}

			Image->Canvas->Rectangle(width_unit, Image->Height/2 - cyl_2_h/2, width_unit + cyl_2_w, Image->Height/2 + cyl_2_h/2);

			if(pair->cyl2.Q > pair->cyl1.Q){
				Image->Canvas->Brush->Color = clBlue;
			}
			else{
				Image->Canvas->Brush->Color = clRed;
			}

			Image->Canvas->Rectangle(Image->Width - width_unit - cyl_1_w, Image->Height/2 - cyl_1_h/2, Image->Width - width_unit, Image->Height/2 + cyl_1_h/2);
		}
		else{
			x = z_now*(7*width_unit)/(0.5 * (pair->cyl1.L + pair->cyl2.L));

			if(pair->cyl2.L > pair->cyl1.L){
				if(pair->cyl2.Q > pair->cyl1.Q){
					Image->Canvas->Brush->Color = clRed;
				}
				else{
					Image->Canvas->Brush->Color = clBlue;
				}

				Image->Canvas->Rectangle(Image->Width/2 - abs(x)/2 - cyl_2_w/2, Image->Height/2 - cyl_2_h/2, Image->Width/2 - abs(x)/2 + cyl_2_w/2, Image->Height/2 + cyl_2_h/2);

				if(pair->cyl2.Q > pair->cyl1.Q){
					Image->Canvas->Brush->Color = clBlue;
				}
				else{
					Image->Canvas->Brush->Color = clRed;
				}

				Image->Canvas->Rectangle(Image->Width/2 + abs(x)/2 - cyl_1_w/2, Image->Height/2 - cyl_1_h/2, Image->Width/2 + abs(x)/2 + cyl_1_w/2, Image->Height/2 + cyl_1_h/2);
			}
			else{
                if(pair->cyl2.Q > pair->cyl1.Q){
					Image->Canvas->Brush->Color = clBlue;
				}
				else{
					Image->Canvas->Brush->Color = clRed;
				}

				Image->Canvas->Rectangle(Image->Width/2 + abs(x)/2 - cyl_1_w/2, Image->Height/2 - cyl_1_h/2, Image->Width/2 + abs(x)/2 + cyl_1_w/2, Image->Height/2 + cyl_1_h/2);

                if(pair->cyl2.Q > pair->cyl1.Q){
					Image->Canvas->Brush->Color = clRed;
				}
				else{
					Image->Canvas->Brush->Color = clBlue;
				}

				Image->Canvas->Rectangle(Image->Width/2 - abs(x)/2 - cyl_2_w/2, Image->Height/2 - cyl_2_h/2, Image->Width/2 - abs(x)/2 + cyl_2_w/2, Image->Height/2 + cyl_2_h/2);
            }
		}
	}
}
