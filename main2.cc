#include <iostream>
#include <fstream>
#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"

using namespace std;

TH1F* ReadFillAll( const char* Filename,  const char* min, const char* max) {
    int bin_min = atoi(min);
    int bin_max = atoi(max);
	ifstream f(Filename);
    TH1F *h1 = new TH1F("h1", "Spettro", 8200, 0, 8200);
    int i = 0;
	if(!f){
  		cerr <<"Error: cannot open file " <<endl;
		exit(0);
	}
  	else{
            double var;
			for (;;){
					
                    f >> var;
                    if(i > bin_min && i < bin_max)	h1->SetBinContent(i,var);		
									
					if(f.eof()){
						cout << "End of file reached "<< endl;
						break;
					}
                    i++;		
			}
		}	f.close();

	return h1;
}


int main( int argc , char** argv ) {

  if ( argc < 4 ) {
    cout << "Uso del programma : " << argv[0] << " <filename> " << endl;
    return -1 ;
  }  

  TApplication app("app",0,0);
  
  // leggo dati da file

  TH1F *h = ReadFillAll(argv[1], argv[2], argv[3]);
  h->Sumw2();

  // creo e riempio il vettore. L'opzione StatOvergflows permetter di calcolalare
  // le informazioni statistiche anche se il dato sta fuori dal range di definizione
  // dell'istogramma
  
  
	h->StatOverflows( kTRUE );
	
	h->SetFillColor(kCyan-7);
  
  // accedo a informazioni statistiche 

  cout << "Media dei valori caricati = " << h->GetMean() << endl;

  // disegno

  TCanvas mycanvas ("Histo","Histo");
  h->Draw();
  h->GetXaxis()->SetTitle("measurement");
  TF1 *f = new TF1("f", "gaus", 2200,  2500);
  f->SetParameter(0,h->Integral());
  h->Rebin(18);
  
        h->Fit(f,"W");
        
        h->Draw("Same");
  cout << h->Integral();
  app.Run();
  
}
