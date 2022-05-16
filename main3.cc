#include <iostream>
#include <fstream>
#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"

using namespace std;

TH1F* ReadFillAll( const char* Filename) {
    
	ifstream f(Filename);
    TH1F *h1 = new TH1F("h1", "Spettro", 7600, 0, 7600);
    int i = 0;
	if(!f){
  		cerr <<"Error: cannot open file " <<endl;
		exit(0);
	}
  	else{
            double var;
			for (;;){
					
                    f >> var;
                    h1->SetBinContent(i,var);		
									
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

  if ( argc < 5 ) {
    cout << "Uso del programma : " << argv[0] << " <filename> " << endl;
    return -1 ;
  }  

  TApplication app("app",0,0);
  
  // leggo dati da file
    double scale = atof(argv[3])/314353.;
  TH1F *bkg = ReadFillAll(argv[1]);
  TH1F *sig = ReadFillAll(argv[2]);

  // creo e riempio il vettore. L'opzione StatOvergflows permetter di calcolalare
  // le informazioni statistiche anche se il dato sta fuori dal range di definizione
  // dell'istogramma
  
  
	bkg->StatOverflows( kTRUE );
    sig->StatOverflows( kTRUE );
	
	bkg->SetLineColor(kCyan-7);
    sig->SetFillColor(kRed);
    TCanvas can1 ("bo","bo");
    bkg->Draw();
    
    bkg->SetTitle("background");
    sig->SetTitle("signal");
  // accedo a informazioni statistiche 

  //cout << "Media dei valori caricati = " << h->GetMean() << endl;

  // disegno

  TCanvas mycanvas ("Histo","Histo");
  mycanvas.cd();
  TH1F * bkg2 = (TH1F*)(bkg->Clone("bkg2"));
  bkg2->Scale(scale);
  bkg2->Draw();
    sig->Add(bkg2,-1);
  TCanvas can("plot", "plot");

  sig->Draw();
    //cout << bkg->GetBinContent(20) << endl << bkg2->GetBinContent(20);

    ofstream out(argv[4]);
    for(int i =0; i< 7600; i++){
        out << sig->GetBinContent(i) << endl;
    }
  app.Run();
  
}
