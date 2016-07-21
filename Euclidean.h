#include <Arduino.h>
#define MAXLENGTH 32
class Euclidean: public Trigger{
public:
	Parameter len;
	Parameter dens;
	Parameter* parameters[2]={&len, &dens};

	String name="EUCLIDEAN";
	String shortName="EUC";


	unsigned char pattern[MAXLENGTH];
	unsigned char cv[MAXLENGTH];
	unsigned char pos;
	unsigned char length;
	unsigned char density;
	unsigned char reset_position;
	unsigned char reset_state;

	Euclidean():Trigger() {
		init();
	 }
	int test=0;


	void getNextStep ()
	{
				 // cout << "Rectangle class area :" <<endl;

	}

	void init(){
		String no[2]={"",""};

		len.init("LENGTH", "< >", true, no, no,  4, 1, 16, 1);
		dens.init("DENSITY", " * ", true, no, no,  4, 1, 16, 1);


	}
	int getParameterCount(){
		int max= sizeof(parameters) / sizeof(parameters[ 0 ]);
		return max;
	}
	Parameter* getParameter( int param){
		return parameters[param];
	}


	void generateSequence(int *parameters, byte *triggers){

		euclid(pattern, cv, parameters[0], parameters[1]);
			// Serial.print(triggers[0]);
			// Serial.print("sfd");
		for (int i = 0; i < 128; ++i)
		{

			// int nScaleNotes=scaleList[currentScale].count;
						// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
			triggers[i]=pattern[i%length];
			// triggers[i]=1;
			
			// Serial.print(triggers[i]);
			// Serial.print(", ");

		}

	}
	void generateStep(byte step, int *parameters, byte *triggers){

		euclid(pattern, cv, parameters[0], parameters[1]);
			// Serial.print(triggers[0]);
			// Serial.print("sfd");
		for (int i = step; i < 32; ++i)
		{

			// int nScaleNotes=scaleList[currentScale].count;
						// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
			triggers[i]=pattern[i%length];
			// triggers[i]=1;
			
			// Serial.print(triggers[i]);
			// Serial.print(", ");

		}
		
	}

	void add(unsigned char *v, int n, unsigned char delta) {
	  while (n--) *v++ += delta;
	}

	void euclid(unsigned char *p, unsigned char *v, int lengthIn, int pulses) {
		length=lengthIn;
	  char lp[MAXLENGTH];
	  char sp[MAXLENGTH];
	  unsigned char vlp[MAXLENGTH];
	  unsigned char vsp[MAXLENGTH];
	  
	  int p_len, lp_len, sp_len, q, r, i, n, k;

	  if (pulses == 0) {
	    memset(p, 0, length);
	    return;
	  }

	  lp[0] = 1; lp_len = 1; vlp[0] = (length << 4) | pulses;
	  sp[0] = 0; sp_len = 1; vsp[1] = (pulses << 4) | length;
	  n = pulses;
	  k = length - pulses;

	  while (k > 1) {
	    if (k >= n) {
	      q = k / n;
	      r = k % n;
	      for (i = 0; i < q; i++) { 
	        memcpy(lp+lp_len, sp, sp_len);
	        memcpy(vlp+lp_len, vsp, sp_len);
	        add(vsp, sp_len, (q << 4) | r);
	        lp_len += sp_len;
	      }
	      k = r;
	    }
	    else {
	      memcpy(p, lp, lp_len);
	      memcpy(lp + lp_len, sp, sp_len);
	      memcpy(sp, p, lp_len);

	      memcpy(v, vlp, lp_len);
	      memcpy(vlp + lp_len, vsp, sp_len);
	      memcpy(vsp, v, lp_len);

	      i = lp_len;
	      lp_len += sp_len;
	      sp_len = i;
	      
	      r = n - k;
	      n = k;
	      k = r;
	      
	      add(vsp, sp_len, (r << 4));
	    }
	  }

	  p_len = 0;
	  for (i = 0; i < n; i++) { 
	    memcpy(p+p_len, lp, lp_len); 
	    memcpy(v+p_len, vlp, lp_len); 
	    add(vlp, lp_len, (pulses << 4) | length);
	    p_len += lp_len; 
	  }
	  for (i = 0; i < k; i++) { 
	    memcpy(p+p_len, sp, sp_len); 
	    memcpy(v+p_len, vsp, sp_len);
	    add(vsp, sp_len, (length << 4) | pulses);
	    p_len += sp_len; 
	  }
	  	//  
	//   for (int i = 0; i < length; ++i)
	//   {
	//   	Serial.print(pattern[i]);
	//   }
	//   	Serial.println();

	// }
	}
	String getName ()
	{
		return name;
	}
	String getShortName ()
	{
		return shortName;
	}
};