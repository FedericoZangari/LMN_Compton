#include <iostream>
#include "TCanvas.h"
#include "TF1.h"
#include "TApplication.h"
#include "TH1F.h"
#include "TStyle.h"
#include <fstream>
	#include <fstream>
	#include <string>
	#include <iostream>
	#include <cstdio>
	#include <vector>
    #include <math.h>
    #include <iomanip>
    #include "TH1F.h"
    #include "TCanvas.h"
    #include "TApplication.h"
    #include "TAxis.h"
    #include "TGraph.h"


using namespace std;

TH1F* ReadFill( const char* Filename ) {
		
		ifstream f(Filename);
        TH1F *h1 = new TH1F("h1", "Spettro", 300, 0, 300);
        cout << "ciao" << endl;
		if(!f){
			cerr <<"Error: cannot open file " <<endl;
			exit(0);
		}
		else{
            double var;
			for (;;){
					f>> var;
                    f >> var;
					h1->Fill(var);		
				
					
					if(f.eof()){
						cout << "End of file reached "<< endl;
						break;
					}		
			}
		}
		f.close();	
		return h1;
	}

int main(int argc, char** argv){
        
        if ( argc < 2 ) {
    	    cout << "Code usage : " << argv[0] << " <input_filename> " << endl;
    	    return -1 ;
	    } 
        TApplication app("App", &argc, argv);
        TCanvas *c = new TCanvas("c", "Spettro", 800,800);
        cout << argv[1] << endl;
        TH1F *data = ReadFill(argv[1]);
        
              

        
        data->Draw();
        data->GetXaxis()->SetTitle("x");
        data->GetYaxis()->SetTitle("y");
        data->SetFillColor(kAzure+6);
        data->SetLineColor(kRed-1);
/*
        TF1 *f = new TF1("f", "gaus", -4, 4);
        h1->Fit(f);
        h1->Draw("Same");

        //gStyle->SetOptFit();
        //c->SaveAs("esercizio4.png");
*/
        
        app.Run();
        return 0;
}