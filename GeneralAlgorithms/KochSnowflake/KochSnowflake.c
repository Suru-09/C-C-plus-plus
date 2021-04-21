#include<stdio.h>
#include<stdlib.h>

#define nr_el 90000000

typedef struct punct1{

    double x;
    double y;
}point;

typedef struct linie1{

    point a;
    point b;
}linie;

linie lines[nr_el];
int n_max;
int line_counter ;

//unghiul se invarte cu ajutorul unei matrici de rotatie 2d ( cos teta   -sin teta )
                                                        //  ( sin teta   cos teta  )
                                                    // la un unghi teta  = 60

point invarte_unghi(point a , point b){

        point aux;

        //printf("Eu sunt a : %lf  %lf si eu sunt b : %lf %lf \n" , a.x , a.y , b.x , b.y );

        a.x = a.x - b.x;
        a.y = a.y - b.y;

        aux.x = a.x * 0.5 - 0.866 * a.y + b.x;
        aux.y = a.x * 0.866 + 0.5 * a.y + b.y;

        return aux;
}
void snowflake(point a , point b , int n){

        //We need to calculate the director vector on x and y

        //printf("Eu sunt a : %lf  %lf si eu sunt b : %lf %lf \n" , a.x , a.y , b.x , b.y );
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        //printf("eu sunt dx : %lf si eu sunt dy : %lf \n" , dx , dy );
        //We need to calculate 1/3 from the director vector therefore :

        dx /= 3;
        dy /= 3;

        // then we have 3 points that create a triangle

        //printf("eu sunt dx/3 : %lf si eu sunt dy/3 : %lf \n" , dx , dy );
        point p1;
        p1.x = dx + b.x;
        p1.y = dy + b.y;

       // printf("Il pun pe p1 la x : %lf si y %lf \n" , p1.x , p1.y);
        dx *= 2;
        dy *= 2;

        point p2;

        p2.x = dx + b.x ;
        p2.y = dy  + b.y;
       // printf("Il pun pe p2 la x : %lf si y %lf \n" , p2.x , p2.y);

        //In the following I will rotate my angle so I create my function

        point p3;
        p3 = invarte_unghi(p1 , p2);

        //printf("Il pun pe p3 la x : %lf si y %lf \n\n" , p3.x , p3.y);

        if(n == n_max){

            linie l1;
            l1.a = b;
            l1.b = p1;

            lines[line_counter++ ] = l1;

            linie l2;
            l2.a = p1;
            l2.b = p3;

            lines[line_counter++ ] = l2;

            linie l3;
            l3.a = p3;
            l3.b = p2;

            lines[line_counter++ ] = l3;

            linie l4;
            l4.a = p2;
            l4.b = a;

            lines[line_counter++ ] = l4;
            return;
        }

        snowflake(p1 , b , n + 1);
        snowflake(p3 , p1 , n + 1);
        snowflake(p2 , p3 , n + 1);
        snowflake(a , p2 , n + 1);

}

void svg_first_thing(FILE * out){

      fprintf(out , "<svg  xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" style=\"background: lightskyblue\" > \n\n");
}

void svg_final(FILE * out){

  fprintf(out , "\n\n</svg>");
}

void svg_body(FILE * out , linie lines){

	fprintf(out , " <line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n" , lines.a.x , lines.a.y - 375,
	lines.b.x , lines.b.y - 375 );
}


#define scaling 325
#define adunare 900

int main(){

	FILE * out;
	out = fopen("second.svg" , "w");
	if(!out){
		printf("I couldn't open the file !");
		return 0;
	}
	point t1 ,t2 , t3;

     t1.x = 0  * scaling + adunare;
     t1.y = 1 * scaling + adunare ;

     t2.x = 0.87 * scaling + adunare ;
     t2.y = -0.5  * scaling + adunare;

     t3.x = -0.87 * scaling + adunare;
     t3.y = -0.5 * scaling + adunare;

    	// -------------------------- THIS IS THE NUMBER OF ITERATIONS PLEASE CHANGE N FOR ANOTHER CASE ----------------------------------------- //
     n_max = 0;

     if(n_max == -1){

     		svg_first_thing(out);

     		fprintf(out , " <line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" /\n>" , t2.x , t2.y - 375,
			t3.x , t3.y - 375 );

     		svg_final(out);
     		return 0;
     }
     else if (!n_max){

     	svg_first_thing(out);

     	fprintf(out , " <line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n" , t2.x , t2.y - 375,
		t3.x , t3.y - 375 );
     	fprintf(out , " <line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n" , t2.x , t2.y - 375,
		t1.x , t1.y - 375 );
     	fprintf(out , " <line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n" , t3.x , t3.y - 375,
		t1.x , t1.y - 375 );

     	svg_final(out);

     	return 0;
     }

     snowflake(t1 , t2 , 1);
     snowflake(t2 , t3 , 1);
     snowflake(t3 , t1 , 1);

     int i;
     svg_first_thing(out);
     for(i = 0 ; i < line_counter ; ++i){

     		svg_body(out , lines[i]);
     }
     svg_final(out);
	return 0;
}
